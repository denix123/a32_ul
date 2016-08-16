// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MOJO_SYSTEM_OPTIONS_VALIDATION_H_
#define MOJO_SYSTEM_OPTIONS_VALIDATION_H_

#include <stddef.h>
#include <stdint.h>

#include <algorithm>

#include "base/logging.h"
#include "base/macros.h"
#include "mojo/public/c/system/types.h"
#include "mojo/system/constants.h"
#include "mojo/system/memory.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

template <class Options>
class UserOptionsReader {
 public:
  
  
  
  
  explicit UserOptionsReader(UserPointer<const Options> options)
      : options_reader_(UserPointer<const char>::Reader::NoCheck(),
                        options.template ReinterpretCast<const char>(),
                        GetSizeForReader(options)) {
    static_assert(offsetof(Options, struct_size) == 0,
                  "struct_size not first member of Options");
    
    
    
    
  }

  bool is_valid() const { return !!options_reader_.GetPointer(); }

  const Options& options() const {
    DCHECK(is_valid());
    return *reinterpret_cast<const Options*>(options_reader_.GetPointer());
  }

  
  
  
  bool HasMember(size_t offset, size_t size) const {
    DCHECK(is_valid());
    
    
    
    return options().struct_size >= offset + size;
  }

 private:
  static inline size_t GetSizeForReader(UserPointer<const Options> options) {
    uint32_t struct_size =
        options.template ReinterpretCast<const uint32_t>().Get();
    if (struct_size < sizeof(uint32_t))
      return 0;

    
    
    
    internal::CheckUserPointerWithSize<MOJO_ALIGNOF(Options)>(options.pointer_,
                                                              struct_size);
    options.template ReinterpretCast<const char>().CheckArray(struct_size);
    
    return std::min(static_cast<size_t>(struct_size), sizeof(Options));
  }

  UserPointer<const char>::Reader options_reader_;

  DISALLOW_COPY_AND_ASSIGN(UserOptionsReader);
};

#define OPTIONS_STRUCT_HAS_MEMBER(Options, member, reader) \
  reader.HasMember(offsetof(Options, member), sizeof(reader.options().member))

}  
}  

#endif  
