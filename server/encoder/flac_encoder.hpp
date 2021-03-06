/***
    This file is part of snapcast
    Copyright (C) 2014-2019  Johannes Pohl

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef FLAC_ENCODER_H
#define FLAC_ENCODER_H
#include "encoder.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FLAC/metadata.h"
#include "FLAC/stream_encoder.h"

namespace encoder
{

class FlacEncoder : public Encoder
{
public:
    FlacEncoder(const std::string& codecOptions = "");
    ~FlacEncoder() override;
    void encode(const msg::PcmChunk* chunk) override;
    std::string getAvailableOptions() const override;
    std::string getDefaultOptions() const override;
    std::string name() const override;

    FLAC__StreamEncoderWriteStatus write_callback(const FLAC__StreamEncoder* encoder, const FLAC__byte buffer[], size_t bytes, unsigned samples,
                                                  unsigned current_frame);

protected:
    void initEncoder() override;

    FLAC__StreamEncoder* encoder_;
    FLAC__StreamMetadata* metadata_[2];

    FLAC__int32* pcmBuffer_;
    int pcmBufferSize_;

    msg::PcmChunk* flacChunk_;
    size_t encodedSamples_;
};

} // namespace encoder

#endif
