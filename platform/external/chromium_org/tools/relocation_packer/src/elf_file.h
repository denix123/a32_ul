// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef TOOLS_RELOCATION_PACKER_SRC_ELF_FILE_H_
#define TOOLS_RELOCATION_PACKER_SRC_ELF_FILE_H_

#include <string.h>
#include <vector>

#include "elf.h"
#include "libelf.h"
#include "packer.h"

namespace relocation_packer {

class ElfFile {
 public:
  explicit ElfFile(int fd)
      : fd_(fd), is_padding_relocations_(false), elf_(NULL),
        relocations_section_(NULL), dynamic_section_(NULL),
        android_relocations_section_(NULL), relocations_type_(NONE) {}
  ~ElfFile() {}

  
  
  
  
  inline void SetPadding(bool flag) { is_padding_relocations_ = flag; }

  
  
  
  bool PackRelocations();

  
  
  
  bool UnpackRelocations();

 private:
  
  
  
  bool Load();

  
  
  template <typename Rel>
  bool PackTypedRelocations(const std::vector<Rel>& relocations,
                            Elf_Data* data);

  
  
  template <typename Rel>
  bool UnpackTypedRelocations(const std::vector<uint8_t>& packed,
                              Elf_Data* data);

  
  void Flush();

  
  int fd_;

  
  
  bool is_padding_relocations_;

  
  Elf* elf_;

  
  Elf_Scn* relocations_section_;
  Elf_Scn* dynamic_section_;
  Elf_Scn* android_relocations_section_;

  
  enum { NONE = 0, REL, RELA } relocations_type_;
};

}  

#endif  
