// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_TEXT_RANGES_H_
#define MEDIA_BASE_TEXT_RANGES_H_

#include <map>

#include "base/macros.h"
#include "base/time/time.h"
#include "media/base/media_export.h"

namespace media {

class MEDIA_EXPORT TextRanges {
 public:
  TextRanges();
  ~TextRanges();

  
  
  
  void Reset();

  
  
  
  
  
  
  
  bool AddCue(base::TimeDelta start_time);

  
  
  size_t RangeCountForTesting() const;

 private:
  
  
  class Range {
   public:
    
    void ResetCount(base::TimeDelta start_time);

    
    void SetLastTime(base::TimeDelta last_time);

    
    
    
    bool AddCue(base::TimeDelta start_time);

    
    base::TimeDelta last_time() const;

   private:
    
    base::TimeDelta last_time_;

    
    
    int max_count_;

    
    
    int count_;
  };

  typedef std::map<base::TimeDelta, Range> RangeMap;

  
  
  
  void NewRange(base::TimeDelta start_time);

  
  void Merge(Range& curr_range, const RangeMap::iterator& next_range_itr);

  
  
  RangeMap range_map_;

  
  RangeMap::iterator curr_range_itr_;

  DISALLOW_COPY_AND_ASSIGN(TextRanges);
};

}  

#endif  
