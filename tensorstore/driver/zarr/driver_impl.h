// Copyright 2020 The TensorStore Authors
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

#ifndef TENSORSTORE_DRIVER_ZARR_DRIVER_IMPL_H_
#define TENSORSTORE_DRIVER_ZARR_DRIVER_IMPL_H_

#include <string>

#include "tensorstore/driver/zarr/metadata.h"
#include "tensorstore/index.h"
#include "tensorstore/util/span.h"

namespace tensorstore {
namespace internal_zarr {

/// Encodes a chunk grid index vector as a storage key suffix.
std::string EncodeChunkIndices(span<const Index> indices,
                               DimensionSeparator dimension_separator);

}  // namespace internal_zarr
}  // namespace tensorstore

#endif  // TENSORSTORE_DRIVER_ZARR_DRIVER_IMPL_H_
