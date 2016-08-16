// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MAC_BIND_OBJC_BLOCK_H_
#define BASE_MAC_BIND_OBJC_BLOCK_H_

#include <Block.h>

#include "base/bind.h"
#include "base/callback_forward.h"
#include "base/mac/scoped_block.h"


namespace base {

namespace internal {

template<typename R>
R RunBlock(base::mac::ScopedBlock<R(^)()> block) {
  R(^extracted_block)() = block.get();
  return extracted_block();
}

template<typename R, typename A1>
R RunBlock(base::mac::ScopedBlock<R(^)(A1)> block, A1 a) {
  R(^extracted_block)(A1) = block.get();
  return extracted_block(a);
}

template<typename R, typename A1, typename A2>
R RunBlock(base::mac::ScopedBlock<R(^)(A1, A2)> block, A1 a, A2 b) {
  R(^extracted_block)(A1, A2) = block.get();
  return extracted_block(a, b);
}

}  

template<typename R>
base::Callback<R(void)> BindBlock(R(^block)()) {
  return base::Bind(&base::internal::RunBlock<R>,
                    base::mac::ScopedBlock<R(^)()>(Block_copy(block)));
}

template<typename R, typename A1>
base::Callback<R(A1)> BindBlock(R(^block)(A1)) {
  return base::Bind(&base::internal::RunBlock<R, A1>,
                    base::mac::ScopedBlock<R(^)(A1)>(Block_copy(block)));
}

template<typename R, typename A1, typename A2>
base::Callback<R(A1, A2)> BindBlock(R(^block)(A1, A2)) {
  return base::Bind(&base::internal::RunBlock<R, A1, A2>,
                    base::mac::ScopedBlock<R(^)(A1, A2)>(Block_copy(block)));
}

}  

#endif  