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

#include <avbtp/RawSocket.h>
#include <avbtp/Mac.h>
#include <avbtp/Packet.h>

#include <stdexcept>

#include <arpa/inet.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <sys/ioctl.h>

using namespace std;
using namespace avbtp;

RawSocket::RawSocket(const std::string &devName, const MACAddress &dstAddr) : sockAddr { }
{
    sockAddr.sll_family = AF_PACKET;
    sockAddr.sll_halen = ETHER_ADDR_LEN;
    std::copy(begin(dstAddr), end(dstAddr), begin(sockAddr.sll_addr));

    socketFd = ::socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (socketFd.get() == -1) {
        perror("Opening packet socket");
        throw runtime_error("failed to open packet socket");
    }

    struct ifreq ifReq;

    auto ioctlReq = [&](int ioctNum) {
        ifReq = {};
        size_t len = devName.copy(&ifReq.ifr_name[0], IFNAMSIZ - 1, 0);
        ifReq.ifr_name[len] = '\0';
        return ::ioctl(socketFd.get(), ioctNum, &ifReq);
    };

    int ret = ioctlReq(SIOCGIFINDEX);
    if (ret == -1) {
        perror("Getting interface index");
        throw runtime_error("failed requesting interface index");
    }

    sockAddr.sll_ifindex = ifReq.ifr_ifindex;

    ret = ioctlReq(SIOCGIFHWADDR);
    if (ret == -1) {
        perror("Getting src mac address");
        throw runtime_error("failed requesting interface MAC address");
    }

    auto b = begin(ifReq.ifr_hwaddr.sa_data);
    auto e = end(ifReq.ifr_hwaddr.sa_data);

    srcMacAddr = {reinterpret_cast<uint8_t *>(b), reinterpret_cast<uint8_t *>(e)};
}

bool RawSocket::send(const Packet& packet) const
{
    int ret = ::sendto(socketFd.get(), packet.data(), packet.size(), 0,
            reinterpret_cast<const struct sockaddr *>(&sockAddr), sizeof(sockAddr));
    if (ret == -1) {
        perror("sending");
        return false;
    }
    return true;
}

MACAddress RawSocket::getSrcMAC() const
{
    return srcMacAddr;
}
