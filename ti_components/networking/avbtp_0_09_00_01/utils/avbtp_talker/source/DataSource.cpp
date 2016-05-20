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

#include <avbtp/DataSource.h>

#include <random>
#include <exception>

extern "C" {
#include <libavcodec/avcodec.h>
}


using namespace std;
using namespace avbtp;

IDataSource::~IDataSource() = default;

FileSource::FileSource(const std::string& name, bool loop)
        : fStream(name, fstream::in | fstream::binary), loop(loop)
{
}

std::size_t FileSource::read(uint8_t *data, std::size_t size)
{
    size_t readSize = fStream.readsome(reinterpret_cast<char *>(data), size);

    if (loop && readSize == 0) {
        fStream.seekg(0, fstream::beg);
        readSize = fStream.readsome(reinterpret_cast<char *>(data), size);
    }

    return readSize;
}

RandomDataSource::RandomDataSource(size_t size, bool loop) : readIdx(0), data(size), loop(loop)
{
    uniform_int_distribution<uint8_t> distribution(0u, 255u);
    default_random_engine engine;
    for(auto& d: data) {
        d = distribution(engine);
    }
}

std::size_t RandomDataSource::read(uint8_t *out, std::size_t size)
{
    size_t remaining = data.size() - readIdx;
    size_t copySize = min(size, remaining);
    if (copySize > 0) {
        auto inputBegin = begin(data) + readIdx;
        std::copy(inputBegin, inputBegin + copySize, out);
        readIdx += copySize;
    }
    if (loop && readIdx == data.size()) readIdx = 0;
    return copySize;
}

std::once_flag JPEGSource::avFormatInit;

void JPEGSource::AVFormatContextDeleter::operator () (AVFormatContext* p) const
{
    avformat_close_input(&p);
}

JPEGSource::JPEGSource(const string& fileName, bool loop) : loop(loop), readIdx(0), streamIdx(-1)
{
    std::call_once(avFormatInit, []() { av_register_all(); });

    unique_ptr<AVFormatContext, AVFormatContextDeleter> ctx(avformat_alloc_context());
    avFmtContext = std::move(ctx);

    if (avFmtContext == nullptr) {
        throw runtime_error("failed allocating avformat context");
    }

    auto avFormatCtxPtr = avFmtContext.get();
    if (avformat_open_input(&avFormatCtxPtr, fileName.c_str(), nullptr, nullptr) < 0) {
        throw runtime_error("failed opening file");
    }

    if (avformat_find_stream_info(avFormatCtxPtr, nullptr) < 0) {
        throw runtime_error("failed populating stream information");
    }

    auto findJPEGStreamIdx = [&]() {
        for (unsigned int i = 0; i < avFmtContext->nb_streams; i++) {
           AVStream *stream = avFmtContext->streams[i];
           if (CODEC_ID_MJPEG == stream->codec->codec_id) {
               streamIdx = i;
               return true;
           }
        }
        return false;
    };

    bool foundStream = findJPEGStreamIdx();
    if (!foundStream) {
        throw runtime_error("not a JPEG or MJPG file");
    }

    av_init_packet(&avPacket);
    avPacket.data = nullptr;
    avPacket.size = 0;
}

JPEGSource::~JPEGSource()
{
    if (avPacket.data != nullptr) {
       av_free_packet(&avPacket);
    }
}

bool JPEGSource::nextFrame()
{
    if (avPacket.data != nullptr) {
        av_free_packet(&avPacket);
    }

    auto findFrame = [&]() {
        while (av_read_frame(avFmtContext.get(), &avPacket) == 0) {
            if (avPacket.stream_index == streamIdx) {
                return true;
            }
            av_free_packet(&avPacket);
        }
        return false;
    };

    bool foundFrame = findFrame();
    if (!foundFrame && loop) {
        if (av_seek_frame(avFmtContext.get(), streamIdx, 0, AVSEEK_FLAG_ANY) == 0) {
            foundFrame = findFrame();
        }
    }

    if (!foundFrame) {
        avPacket.data = nullptr;
        avPacket.size = 0;
    }

    readIdx = 0;
    return foundFrame;
}

std::size_t JPEGSource::read(uint8_t *out, std::size_t size)
{
    size_t remaining = avPacket.size - readIdx;
    if (remaining == 0) {
        if (!nextFrame()) return 0;
        remaining = avPacket.size;
    }

    size_t copySize = min(size, remaining);
    if (copySize > 0) {
        auto start = avPacket.data + readIdx;
        std::copy(start, start + copySize, out);
        readIdx += copySize;
    }

    return copySize;
}
