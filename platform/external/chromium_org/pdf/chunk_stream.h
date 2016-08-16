// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PDF_CHUNK_STREAM_H_
#define PDF_CHUNK_STREAM_H_

#include <stddef.h>

#include <map>
#include <vector>

namespace chrome_pdf {

class ChunkStream {
 public:
  ChunkStream();
  ~ChunkStream();

  void Clear();

  void Preallocate(size_t stream_size);
  size_t GetSize();

  bool WriteData(size_t offset, void* buffer, size_t size);
  bool ReadData(size_t offset, size_t size, void* buffer) const;

  
  bool GetMissedRanges(size_t offset, size_t size,
      std::vector<std::pair<size_t, size_t> >* ranges) const;
  bool IsRangeAvailable(size_t offset, size_t size) const;
  size_t GetFirstMissingByte() const;

  size_t GetLastByteBefore(size_t offset) const;
  size_t GetFirstByteAfter(size_t offset) const;

 private:
  std::vector<unsigned char> data_;

  
  std::map<size_t, size_t> chunks_;
};

};  

#endif
