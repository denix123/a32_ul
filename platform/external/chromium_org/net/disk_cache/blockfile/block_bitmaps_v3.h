// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_DISK_CACHE_BLOCKFILE_BLOCK_BITMAPS_V3_H_
#define NET_DISK_CACHE_BLOCKFILE_BLOCK_BITMAPS_V3_H_

#include "base/files/file_path.h"
#include "net/base/net_export.h"
#include "net/disk_cache/blockfile/addr.h"
#include "net/disk_cache/blockfile/block_files.h"

namespace disk_cache {

class BackendImplV3;

class NET_EXPORT_PRIVATE BlockBitmaps {
 public:
  BlockBitmaps();
  ~BlockBitmaps();

  void Init(const BlockFilesBitmaps& bitmaps);

  
  
  
  bool CreateBlock(FileType block_type, int block_count, Addr* block_address);

  
  void DeleteBlock(Addr address);

  
  void Clear();

  
  void ReportStats();

  
  
  bool IsValid(Addr address);

 private:
  
  int GetHeaderNumber(Addr address);

  
  int HeaderNumberForNewBlock(FileType block_type, int block_count);

  
  void GetFileStats(int index, int* used_count, int* load);

  BlockFilesBitmaps bitmaps_;

  DISALLOW_COPY_AND_ASSIGN(BlockBitmaps);
};

}  

#endif  
