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

#include <avbtp/TCPSocket.h>
#include <avbtp/Packet.h>

#include <stdexcept>

using namespace std;
using namespace avbtp;

AddrInfo::AddrInfo(string ipString, string portString) : pAddrInfo(nullptr)
{
    struct addrinfo hints = {};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int ret = getaddrinfo(ipString.c_str(), portString.c_str(), &hints, &pAddrInfo);
    if (ret != 0 || pAddrInfo == nullptr) {
        string errorString(gai_strerror(ret));
        cout << "error: " << errorString;
        throw invalid_argument(errorString);
    }
}

AddrInfo::~AddrInfo()
{
    freeaddrinfo(pAddrInfo);
}

TCPSocket::TCPSocket(string ipString, string portString) : ip(ipString), port(portString)
{
    AddrInfo addr(ip, port);

    socketFd = {::socket(addr.ai_family(), SOCK_STREAM, 0)};
    if (socketFd.get() == -1) {
        perror("Opening TCP socket");
        throw runtime_error("failed opening tcp socket");
    }

    int ret = ::connect(socketFd.get(), addr.ai_addr(), addr.ai_addrlen());
    if (ret == -1) {
        perror("Connecting TCP socket");
        throw runtime_error("tcp socket failed to connect");
    }
}

bool TCPSocket::send(const Packet& packet) const
{
    int ret = ::send(socketFd.get(), packet.data(), packet.size(), 0);
    if (ret == -1) {
        perror("sending");
        return false;
    }
    return true;
}

vector<uint8_t> TCPSocket::receive(size_t size)
{
    vector<uint8_t> buf(size);
    size_t remaining = buf.size();
    size_t idx = 0;
    while (remaining > 0) {
        ssize_t ret = ::recv(socketFd.get(), &buf[idx], remaining, 0);
        if (ret <= 0) {
            if (ret < 0) {
                perror("TCPSocket error in recv: ");
            }
            break;
        } else {
            idx += ret;
            remaining -= ret;
        }
    }

    return buf;
}

