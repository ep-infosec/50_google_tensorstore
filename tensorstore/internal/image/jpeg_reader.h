// Copyright 2022 The TensorStore Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TENSORSTORE_INTERNAL_IMAGE_JPEG_READER_H_
#define TENSORSTORE_INTERNAL_IMAGE_JPEG_READER_H_

#include "riegeli/bytes/reader.h"
#include "tensorstore/internal/image/image_info.h"
#include "tensorstore/internal/image/image_reader.h"
#include "tensorstore/util/span.h"

namespace tensorstore {
namespace internal_image {

struct JpegReaderOptions {};

class JpegReader : public ImageReader {
 public:
  struct Context;

  JpegReader();
  ~JpegReader() override;

  JpegReader(JpegReader&& src);
  JpegReader& operator=(JpegReader&& src);

  // Initialize the decoder.
  absl::Status Initialize(riegeli::Reader* reader) override;

  // Returns the current ImageInfo.
  ImageInfo GetImageInfo() override;

  // Decodes the next available image into 'dest'.
  absl::Status Decode(tensorstore::span<unsigned char> dest) override {
    return DecodeImpl(dest, {});
  }
  absl::Status Decode(tensorstore::span<unsigned char> dest,
                      const JpegReaderOptions& options) {
    return DecodeImpl(dest, options);
  }

 private:
  absl::Status DecodeImpl(tensorstore::span<unsigned char> dest,
                          const JpegReaderOptions& options);

  riegeli::Reader* reader_ = nullptr;  // unowned
  std::unique_ptr<Context> context_;
};

}  // namespace internal_image
}  // namespace tensorstore

#endif  // TENSORSTORE_INTERNAL_IMAGE_JPEG_READER_H_
