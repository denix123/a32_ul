// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_TEST_LEAKY_BUCKET_H_
#define REMOTING_TEST_LEAKY_BUCKET_H_

#include "base/basictypes.h"
#include "base/time/time.h"

namespace remoting {

class LeakyBucket {
 public:
  
  LeakyBucket(double depth, double rate);
  ~LeakyBucket();

  
  
  
  base::TimeDelta AddPacket(int size);

 private:
  void UpdateLevel();

  double depth_;
  double rate_;

  double level_;
  base::TimeTicks last_update_;

  DISALLOW_COPY_AND_ASSIGN(LeakyBucket);
};

}  

#endif  
