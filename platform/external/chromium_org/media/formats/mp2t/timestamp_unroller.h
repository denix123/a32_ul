// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MP2T_TIMESTAMP_UNROLLER_H_
#define MEDIA_FORMATS_MP2T_TIMESTAMP_UNROLLER_H_

#include "base/basictypes.h"
#include "base/macros.h"
#include "media/base/media_export.h"

namespace media {
namespace mp2t {

class MEDIA_EXPORT TimestampUnroller {
 public:
  TimestampUnroller();
  ~TimestampUnroller();

  
  
  
  
  
  
  
  
  
  int64 GetUnrolledTimestamp(int64 timestamp);

  
  void Reset();

 private:
  
  bool is_previous_timestamp_valid_;

  
  int64 previous_unrolled_timestamp_;

  DISALLOW_COPY_AND_ASSIGN(TimestampUnroller);
};

}  
}  

#endif  
