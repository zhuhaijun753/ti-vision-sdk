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

#ifndef _AVBTP_PACKET_
#define _AVBTP_PACKET_

#include <cstdint>
#include <cstddef>
#include <vector>
#include <iostream>
#include <random>

namespace avbtp {

class MACAddress;
class IDataSource;

class Packet
{
public:
    Packet(size_t headerLen, size_t payloadSize, IDataSource& source);
    virtual ~Packet();

    size_t size() const;
    const uint8_t *data() const;

    virtual bool fill();
    virtual void print(std::ostream& stream) const;
    void randomizePayloadLen(bool flag) { randomizeLen = flag; }

protected:
    size_t headerLen;
    size_t payloadSize;
    size_t _size;
    std::vector<uint8_t> _data;
    IDataSource *source;
    bool randomizeLen;
    std::uniform_int_distribution<uint16_t> distribution;
    std::default_random_engine engine;
};

class StreamAVBTPDU : public Packet
{
public:
    static const size_t max_payload = 1472u;
    StreamAVBTPDU(uint16_t id, IDataSource& source, const MACAddress& src, const MACAddress& dst);
    StreamAVBTPDU(const StreamAVBTPDU& packet) = default;

    void setVLAN(uint16_t vlanId, uint8_t vlanPriority);
    bool fill();

private:
    void writePayloadLen();
    void writeSeqNum();

    uint8_t seqNum;

    static const size_t header_size = 42u;
    static const uint16_t vlan_tpid = 0x8100u;
    static const uint16_t vlan_default_id = 1024u;
    static const uint8_t  vlan_default_prio = 5u;

    static const uint16_t ether_type = 0x22F0u;
    static const uint16_t ether_type_old = 0x88B5u;

    static const uint8_t subtype_reserved = 0x02u;
    static const uint8_t subtype_61883 = 0x00;
    static const uint8_t subtype_experimental = 0x7Fu;
};

}

std::ostream& operator<< (std::ostream& os, const avbtp::Packet& packet);

#endif
