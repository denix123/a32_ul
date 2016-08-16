// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef TOOLS_RELOCATION_PACKER_SRC_LEB128_H_
#define TOOLS_RELOCATION_PACKER_SRC_LEB128_H_

#include <stdint.h>
#include <vector>

#include "elf_traits.h"

namespace relocation_packer {

class Leb128Encoder {
 public:
  
  Leb128Encoder();
  ~Leb128Encoder();

  
  
  void Enqueue(ELF::Xword value);

  
  
  void EnqueueAll(const std::vector<ELF::Xword>& values);

  
  
  void GetEncoding(std::vector<uint8_t>* encoding) { *encoding = encoding_; }

 private:
  
  std::vector<uint8_t> encoding_;
};

class Leb128Decoder {
 public:
  
  
  explicit Leb128Decoder(const std::vector<uint8_t>& encoding);

  
  ~Leb128Decoder();

  
  ELF::Xword Dequeue();

  
  
  void DequeueAll(std::vector<ELF::Xword>* values);

 private:
  
  std::vector<uint8_t> encoding_;

  
  size_t cursor_;
};

}  

#endif  
