// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef TOOLS_RELOCATION_PACKER_SRC_PACKER_H_
#define TOOLS_RELOCATION_PACKER_SRC_PACKER_H_

#include <stdint.h>
#include <vector>

#include "elf.h"
#include "elf_traits.h"

namespace relocation_packer {

class RelocationPacker {
 public:
  
  
  
  static void PackRelativeRelocations(const std::vector<ELF::Rel>& relocations,
                                      std::vector<uint8_t>* packed);
  static void PackRelativeRelocations(const std::vector<ELF::Rela>& relocations,
                                      std::vector<uint8_t>* packed);

  
  
  
  static void UnpackRelativeRelocations(const std::vector<uint8_t>& packed,
                                        std::vector<ELF::Rel>* relocations);
  static void UnpackRelativeRelocations(const std::vector<uint8_t>& packed,
                                        std::vector<ELF::Rela>* relocations);
};

}  

#endif  
