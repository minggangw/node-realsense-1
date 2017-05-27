// Copyright (c) 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "rs_extrinsics.h"

RSExtrinsics::RSExtrinsics(rs::extrinsics extrinsics)
    : Extrinsics(extrinsics.rotation, extrinsics.translation),
      extrinsics_(extrinsics),
      isIdentity_(extrinsics.is_identity()) {
  SetupTypedArrayHelper(&transform_, transform_store_, TRANSLATION_SIZE);
}

RSExtrinsics::RSExtrinsics(const RSExtrinsics& rhs) {
  // TODO(widl-nan): copy from rhs if you want this behavior
  // Or mark ctor = delete in rs_extrinsics.h
}

Float32ArrayHelper RSExtrinsics::transform(
    const Float32ArrayHelper& point) {
  DeepCopyFromTypedArrayHelper(point, transform_store_, TRANSLATION_SIZE);
  rs::float3 transform;
  transform.x = transform_store_[0];
  transform.y = transform_store_[1];
  transform.z = transform_store_[2];

  transform =
      extrinsics_.transform(transform);

  transform_store_[0] = transform.x;
  transform_store_[1] = transform.y;
  transform_store_[2] = transform.z;

  return transform_;
}

RSExtrinsics& RSExtrinsics::operator = (const RSExtrinsics& rhs) {
  if (&rhs != this) {
    // TODO(widl-nan): copy members from rhs
  }
  return *this;
}
