// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FILES_MEMORY_MAPPED_FILE_H_
#define BASE_FILES_MEMORY_MAPPED_FILE_H_

#include "base/base_export.h"
#include "base/basictypes.h"
#include "base/files/file.h"
#include "build/build_config.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

namespace base {

class FilePath;

class BASE_EXPORT MemoryMappedFile {
 public:
  
  MemoryMappedFile();
  ~MemoryMappedFile();

  
  struct BASE_EXPORT Region {
    static const Region kWholeFile;

    Region(int64 offset, int64 size);

    bool operator==(const Region& other) const;

    
    int64 offset;

    
    int64 size;

   private:
    
    
    Region(base::LinkerInitialized);
  };

  
  
  
  
  
  bool Initialize(const FilePath& file_name);

  
  
  bool Initialize(File file);

  
  bool Initialize(File file, const Region& region);

#if defined(OS_WIN)
  
  
  bool InitializeAsImageSection(const FilePath& file_name);
#endif  

  const uint8* data() const { return data_; }
  size_t length() const { return length_; }

  
  bool IsValid() const;

 private:
  
  
  
  
  
  
  static void CalculateVMAlignedBoundaries(int64 start,
                                           int64 size,
                                           int64* aligned_start,
                                           int64* aligned_size,
                                           int32* offset);

  
  
  bool MapFileRegionToMemory(const Region& region);

  
  void CloseHandles();

  File file_;
  uint8* data_;
  size_t length_;

#if defined(OS_WIN)
  win::ScopedHandle file_mapping_;
  bool image_;  
#endif

  DISALLOW_COPY_AND_ASSIGN(MemoryMappedFile);
};

}  

#endif  
