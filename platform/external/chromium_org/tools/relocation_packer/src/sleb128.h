// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef TOOLS_RELOCATION_PACKER_SRC_SLEB128_H_
#define TOOLS_RELOCATION_PACKER_SRC_SLEB128_H_

#include <stdint.h>
#include <unistd.h>
#include <vector>

#include "elf_traits.h"

namespace relocation_packer {

class Sleb128Encoder {
 public:
  
  Sleb128Encoder();
  ~Sleb128Encoder();

  
  
  void Enqueue(ELF::Sxword value);

  
  
  void EnqueueAll(const std::vector<ELF::Sxword>& values);

  
  
  void GetEncoding(std::vector<uint8_t>* encoding) { *encoding = encoding_; }

 private:
  
  std::vector<uint8_t> encoding_;
};

class Sleb128Decoder {
 public:
  
  
  explicit Sleb128Decoder(const std::vector<uint8_t>& encoding);

  
  ~Sleb128Decoder();

  
  ELF::Sxword Dequeue();

  
  
  void DequeueAll(std::vector<ELF::Sxword>* values);

 private:
  
  std::vector<uint8_t> encoding_;

  
  size_t cursor_;
};

}  

#endif  
