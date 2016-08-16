// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef TOOLS_RELOCATION_PACKER_SRC_RUN_LENGTH_ENCODER_H_
#define TOOLS_RELOCATION_PACKER_SRC_RUN_LENGTH_ENCODER_H_

#include <vector>

#include "elf.h"
#include "elf_traits.h"

namespace relocation_packer {

class RelocationRunLengthCodec {
 public:
  
  
  
  static void Encode(const std::vector<ELF::Rel>& relocations,
                     std::vector<ELF::Xword>* packed);

  
  
  
  static void Decode(const std::vector<ELF::Xword>& packed,
                     std::vector<ELF::Rel>* relocations);
};

}  

#endif  
