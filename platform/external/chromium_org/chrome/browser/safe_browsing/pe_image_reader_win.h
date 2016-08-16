// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_PE_IMAGE_READER_WIN_H_
#define CHROME_BROWSER_SAFE_BROWSING_PE_IMAGE_READER_WIN_H_

#include <windows.h>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace safe_browsing {

class PeImageReader {
 public:
  enum WordSize {
    WORD_SIZE_32,
    WORD_SIZE_64,
  };

  PeImageReader();
  ~PeImageReader();

  
  bool Initialize(const uint8_t* image_data, size_t image_size);

  
  WordSize GetWordSize();

  const IMAGE_DOS_HEADER* GetDosHeader();
  const IMAGE_FILE_HEADER* GetCoffFileHeader();

  
  const uint8_t* GetOptionalHeaderData(size_t* optional_data_size);
  size_t GetNumberOfSections();
  const IMAGE_SECTION_HEADER* GetSectionHeaderAt(size_t index);

  
  
  const uint8_t* GetExportSection(size_t* section_size);

  size_t GetNumberOfDebugEntries();
  const IMAGE_DEBUG_DIRECTORY* GetDebugEntry(size_t index,
                                             const uint8_t** raw_data,
                                             size_t* raw_data_size);

 private:
  
  enum ValidationStages {
    VALID_DOS_HEADER = 1 << 0,
    VALID_PE_SIGNATURE = 1 << 1,
    VALID_COFF_FILE_HEADER = 1 << 2,
    VALID_OPTIONAL_HEADER = 1 << 3,
    VALID_SECTION_HEADERS = 1 << 4,
  };

  
  class OptionalHeader {
   public:
    virtual ~OptionalHeader() {}

    virtual WordSize GetWordSize() = 0;

    
    
    virtual size_t GetDataDirectoryOffset() = 0;

    
    virtual DWORD GetDataDirectorySize() = 0;

    
    virtual const IMAGE_DATA_DIRECTORY* GetDataDirectoryEntries() = 0;
  };

  template<class OPTIONAL_HEADER_TYPE>
  class OptionalHeaderImpl;

  void Clear();
  bool ValidateDosHeader();
  bool ValidatePeSignature();
  bool ValidateCoffFileHeader();
  bool ValidateOptionalHeader();
  bool ValidateSectionHeaders();

  
  const uint8_t* GetOptionalHeaderStart();
  size_t GetOptionalHeaderSize();

  
  const IMAGE_DATA_DIRECTORY* GetDataDirectoryEntryAt(size_t index);

  
  
  const IMAGE_SECTION_HEADER* FindSectionFromRva(uint32_t relative_address);

  
  
  const uint8_t* GetImageData(size_t index, size_t* data_length);

  
  
  
  
  template<typename T> bool GetStructureAt(size_t offset, const T** structure) {
    return GetStructureAt(offset, sizeof(**structure), structure);
  }

  
  
  
  
  template<typename T> bool GetStructureAt(size_t offset,
                                           size_t structure_size,
                                           const T** structure) {
    if (offset > image_size_)
      return false;
    if (structure_size > image_size_ - offset)
      return false;
    *structure = reinterpret_cast<const T*>(image_data_ + offset);
    return true;
  }

  const uint8_t* image_data_;
  size_t image_size_;
  uint32_t validation_state_;
  scoped_ptr<OptionalHeader> optional_header_;
  DISALLOW_COPY_AND_ASSIGN(PeImageReader);
};

}  

#endif  
