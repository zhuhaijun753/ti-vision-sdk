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

#include <avbtp/Packet.h>
#include <avbtp/DataSource.h>
#include <avbtp/Mac.h>

#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>

#include <netinet/in.h>

using namespace std;
using namespace avbtp;

static void writeNetOrder(vector<uint8_t>::iterator it, uint16_t val);

Packet::Packet(size_t headerLen, size_t payloadSize, IDataSource& source)
        : headerLen(headerLen),
          payloadSize(payloadSize),
          _size(headerLen + payloadSize),
          _data(headerLen + payloadSize),
          source(&source),
          randomizeLen(false),
          distribution(1, payloadSize)
{
}

Packet::~Packet() = default;

size_t Packet::size() const
{
    return _size;
}

const uint8_t *Packet::data() const
{
    return _data.data();
}

bool Packet::fill()
{
    if (randomizeLen) {
        payloadSize = distribution(engine);
    }
    size_t readSize = source->read(&_data[headerLen], payloadSize);
    _size = readSize + headerLen;
    return readSize != 0;
}

void Packet::print(ostream& stream) const
{
    stringstream ss;
    ss << "size: " << _size << endl;
    if (headerLen > 0) {
        ss << "--header-- " << endl;
        for (size_t i = 0; i < headerLen; i++) {
            ss << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(_data[i]);
            if (i < headerLen - 1) ss << " ";
            if (((i + 1) % 6) == 0) ss << endl;
        }
        ss << "--end-- " << endl;
    }
    if (payloadSize > 0) {
        ss << "--payload-- " << endl;
        for (size_t i = 0; i < min((size_t)18u, payloadSize); i++) {
            ss << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(_data[i+headerLen]);
            if (i < payloadSize - 1) ss << " ";
            if (((i + 1) % 6) == 0) ss << endl;
        }
        ss << "--end-- " << endl;
    }
    stream << ss.str();
}

StreamAVBTPDU::StreamAVBTPDU(uint16_t id, IDataSource& source, const MACAddress& srcMac, const MACAddress& dstMac)
        : Packet(StreamAVBTPDU::header_size, StreamAVBTPDU::max_payload, source), seqNum(0)
{
    // Common AVBTPDU stream header
    // 6 bytes - dst MAC address
    // 6 bytes - src MAC address
    // 4 bytes - 802.1Q VLAN tag
    // 2 bytes - ether type
    // 1 bit - control data (0 for stream AVBTPDU)
    // 7 bits - AVB subtype
    // 1 bit - sv field - stream ID valid flag (always 1 for stream AVBTPDU)
    // 3 bit - AVBTP version (0 for current IEEE-1722)
    // 1 bit - media clock restart
    // 1 bit - reserved bit
    // 1 bit - gv - gateway info valid
    // 1 bit - tv - timestamp valid
    // 1 byte - sequence num
    // 7 bits - reserved bits
    // 1 bit - tu - timestamp uncertain
    // 8 bytes - stream ID (composed of src MAC address + 16-bit unique ID)
    // 4 bytes - timestamp
    // 4 bytes - gateway info
    // 2 bytes - payload length
    // 2 bytes - protocol specific header

    auto start = begin(_data);

    std::copy(begin(dstMac), end(dstMac), start);
    std::copy(begin(srcMac), end(srcMac), start + 6);

    writeNetOrder(start + 12, StreamAVBTPDU::vlan_tpid);
    setVLAN(StreamAVBTPDU::vlan_default_id, StreamAVBTPDU::vlan_default_prio);

    writeNetOrder(start + 16, StreamAVBTPDU::ether_type_old);

    //avb subtype
    start[18] = StreamAVBTPDU::subtype_reserved;
    //stream valid flag set to true
    start[19] = 1u << 7;

    // streamID which is 6-bytes srcMAC and a unique ID
    std::copy(begin(srcMac), end(srcMac), start + 22);
    writeNetOrder(start + 28, id);
}

void StreamAVBTPDU::setVLAN(uint16_t vlanId, uint8_t vlanPriority)
{
    writeNetOrder(begin(_data) + 14, (vlanPriority << 13) | vlanId);
}

void StreamAVBTPDU::writePayloadLen()
{
    writeNetOrder(begin(_data) + 38, _size - headerLen);
}

void StreamAVBTPDU::writeSeqNum()
{
    _data[20] = seqNum;
    seqNum++;
}

bool StreamAVBTPDU::fill()
{
    bool filled = Packet::fill();
    if (filled) {
        writeSeqNum();
        writePayloadLen();
    }
    return filled;
}

static void writeNetOrder(vector<uint8_t>::iterator it, uint16_t val)
{
    val = htons(val);
    it[0] = val & 0xFF;
    it[1] = val >> 8;
}

ostream& operator<<(ostream& os, const Packet& packet)
{
    packet.print(os);
    return os;
}
