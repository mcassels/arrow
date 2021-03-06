// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <cstdint>
#include <memory>

#include "arrow/status.h"
#include "arrow/util/compression.h"
#include "arrow/util/visibility.h"

namespace arrow {
namespace util {

constexpr int kGZipDefaultCompressionLevel = 9;

// GZip codec.
class ARROW_EXPORT GZipCodec : public Codec {
 public:
  /// Compression formats supported by the zlib library
  enum Format {
    ZLIB,
    DEFLATE,
    GZIP,
  };

  explicit GZipCodec(int compression_level = kGZipDefaultCompressionLevel,
                     Format format = GZIP);
  ~GZipCodec() override;

  Status Init() override;

  Result<int64_t> Decompress(int64_t input_len, const uint8_t* input,
                             int64_t output_buffer_len, uint8_t* output_buffer) override;

  Result<int64_t> Compress(int64_t input_len, const uint8_t* input,
                           int64_t output_buffer_len, uint8_t* output_buffer) override;

  int64_t MaxCompressedLen(int64_t input_len, const uint8_t* input) override;

  Result<std::shared_ptr<Compressor>> MakeCompressor() override;

  Result<std::shared_ptr<Decompressor>> MakeDecompressor() override;

  const char* name() const override;

 private:
  // The gzip compressor is stateful
  class GZipCodecImpl;
  std::unique_ptr<GZipCodecImpl> impl_;
};

}  // namespace util
}  // namespace arrow
