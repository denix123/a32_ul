// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BLINK_BUFFERED_DATA_SOURCE_HOST_IMPL_H_
#define MEDIA_BLINK_BUFFERED_DATA_SOURCE_HOST_IMPL_H_

#include "base/time/time.h"
#include "media/base/media_export.h"
#include "media/base/ranges.h"
#include "media/blink/buffered_data_source.h"

namespace media {

class MEDIA_EXPORT BufferedDataSourceHostImpl
    : public BufferedDataSourceHost {
 public:
  BufferedDataSourceHostImpl();
  virtual ~BufferedDataSourceHostImpl();

  
  virtual void SetTotalBytes(int64 total_bytes) OVERRIDE;
  virtual void AddBufferedByteRange(int64 start, int64 end) OVERRIDE;

  
  
  void AddBufferedTimeRanges(
      Ranges<base::TimeDelta>* buffered_time_ranges,
      base::TimeDelta media_duration) const;

  bool DidLoadingProgress();

 private:
  
  int64 total_bytes_;

  
  Ranges<int64> buffered_byte_ranges_;

  
  
  bool did_loading_progress_;

  DISALLOW_COPY_AND_ASSIGN(BufferedDataSourceHostImpl);
};

}  

#endif  
