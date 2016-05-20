/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include <avbtp/AVBTPTalker.h>
#include <avbtp/Options.h>
#include <avbtp/Mac.h>
#include <avbtp/DataSource.h>
#include <avbtp/Packet.h>
#include <avbtp/RawSocket.h>
#include <avbtp/TCPSocket.h>
#include <avbtp/Utils.h>

#include <algorithm>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;
using namespace avbtp;

namespace avbtp {
class AVBTalker
{
public:
    AVBTalker(const StreamAVBTPDU& packet);


};
}

static void tcpThreadTask(string ip, string port, bool verbose, const atomic_bool& shutDown);

static void usage(const Options& opts) {

    auto printOpt = [&](bool required) {
        for (auto& opt : opts.data()) {
            if (required == (opt.second.req == OptVal::required)) {
               cout << "    --" << opt.first;
               if (opt.second.type == OptVal::boolean) {
                   cout << " [false] ";
               } else {
                   cout << " <value> ";
               }
               cout << endl;
            }
        }
        cout << endl;
    };

    cout << "Usage: avbtp_talker [ OPTIONS ] REQUIRED" << endl << endl;
    cout << "REQUIRED" << endl;
    printOpt(true);
    cout << "OPTIONS" << endl;
    printOpt(false);
}

int main(int argc, char *argv[])
{
    map<string, OptVal> optDefaults {
        {"input",           {"", OptVal::notboolean, OptVal::required} },
        {"num-talkers",     {"4"} },
        {"dev",             {"eth0"} },
        {"mac-dest",        {"FF:FF:FF:FF:FF:FF"} },
        {"mac-src",         {""} },
        {"ip",              {"192.168.1.200"} },
        {"tcp-port",        {"7"} },
        {"tcp-send",        {"false", OptVal::boolean} },
        {"loop",            {"false", OptVal::boolean} },
        {"vlan-id",         {"1024"} },
        {"vlan-priority",   {"5"} },
        {"verbose",         {"false", OptVal::boolean} }
    };

    Options opts(optDefaults);
    if (!opts.parseCmdLine(argc, argv)) {
        usage(opts);
        return 1;
    }

    cout << opts << endl;

    MACAddress dstAddr{opts.get("mac-dest")};
    RawSocket socket(opts.get("dev"), dstAddr);
    MACAddress srcMac = socket.getSrcMAC();

    string srcMacString = opts.get("mac-src");
    if (!srcMacString.empty()) {
        //Spoof the mac address instead of using the one from the NIC
        srcMac = {srcMacString};
    }

    int numTalkers = opts.getInt("num-talkers");
    if (numTalkers == -1) numTalkers = 4;

    vector<string> fileNames = tokenize(opts.get("input"), ' ');
    replicateLast(fileNames, numTalkers);

    //Instantiate a data source for each of the talkers
    vector<unique_ptr<IDataSource>> dataSources;
    dataSources.reserve(numTalkers);
    bool enableLooping = opts.getBool("loop");
    for (int i = 0; i < numTalkers; i++) {
        unique_ptr<IDataSource> dataSource = make_unique<JPEGSource>(fileNames[i], enableLooping);
        dataSources.push_back(std::move(dataSource));
    }

    int vlanId = opts.getInt("vlan-id");
    if (vlanId == -1) vlanId = 1024;
    int vlanPrio = opts.getInt("vlan-priority");
    if (vlanPrio == -1) vlanPrio = 5;

    //The talker uses a pull streaming model (packets are filled with data from the data source).
    //Looping is provided by the data source itselflook like a continuous stream of data).
    vector<AVBTPTalker> talkers;
    talkers.reserve(numTalkers);
    for (int i = 0; i < numTalkers; i++) {
        AVBTPTalker talker(i, *dataSources[i], socket, srcMac, dstAddr);
        talker.setVLAN(vlanId, vlanPrio);
        talkers.push_back(talker);
    }

    //A thread to send TCP/IP traffic to an echo server concurrently with AVB traffic
    bool verbose = opts.getBool("verbose");
    bool createTCPThread = opts.getBool("tcp-send");
    atomic_bool shutDown{false};
    thread tcpThread;
    if (createTCPThread) {
        tcpThread =  thread(tcpThreadTask, opts.get("ip"), opts.get("tcp-port"), verbose, ref(shutDown));
    }

    cout << "AVB: sending packets..." << endl;
    //remove_if will iterate over the complete list, invoking the sendPacket lambda on each of the talkers.
    //if a talker could not send a packet (either from running out of data or an error on the socket send) then
    //remove_if will move that element to the end of the list returning the iterator to that element which
    //we can now use in an erase call (Erase-remove idiom)
    auto sendPacket = [](AVBTPTalker& talker) { return !talker.send(); };
    while(talkers.size() > 0) {
       talkers.erase(remove_if(begin(talkers), end(talkers), sendPacket), end(talkers));
    }
    cout << "AVB: stopped" << endl;

    if (createTCPThread) {
        shutDown = true;
        tcpThread.join();
    }

    return 0;
}

static void tcpThreadTask(string ip, string port, bool verbose, const atomic_bool& shutDown)
{
    try {
        cout << "TCP: connecting to " << ip << endl;

        size_t packetSize = 10*1024;
        TCPSocket tcpSocket(ip, port);
        RandomDataSource source(packetSize, true);
        Packet p(0, packetSize, source);

        unsigned long count = 1;
        cout << "TCP: connected! Sending packets..." << endl;
        while (!shutDown) {
            if (!p.fill()) {
                cout << "TCP: no more data!" << endl;
                break;
            }

            tcpSocket.send(p);
            if (verbose) {
                cout << "TCP: sent " << p.size() << " bytes - ";
            }

            vector<uint8_t> recvBuf = tcpSocket.receive(p.size());
            if (verbose) {
                cout << "received: " << recvBuf.size() << " bytes " << endl;
            }

            if (!std::equal(begin(recvBuf), end(recvBuf), p.data())) {
                cout << "TCP: mismatch detected! " << endl;
            }

            if ((count % 200) == 0) {
                cout << "TCP: verified " << count << " buffers" << endl;
            }
            ++count;
        }
    } catch(std::exception& e) {
        cout << "TCP: exception - " << e.what() << endl;
    }
    cout << "TCP: stopped" << endl;

}
