// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MP4_SAMPLE_TO_GROUP_ITERATOR_H_
#define MEDIA_FORMATS_MP4_SAMPLE_TO_GROUP_ITERATOR_H_

#include <vector>

#include "media/formats/mp4/box_definitions.h"

namespace media {
namespace mp4 {

class MEDIA_EXPORT SampleToGroupIterator {
 public:
  explicit SampleToGroupIterator(const SampleToGroup& sample_to_group);
  ~SampleToGroupIterator();

  
  
  bool Advance();

  
  bool IsValid() const;

  
  uint32 group_description_index() const {
    return iterator_->group_description_index;
  }

 private:
  
  uint32 remaining_samples_;
  const std::vector<SampleToGroupEntry>& sample_to_group_table_;
  std::vector<SampleToGroupEntry>::const_iterator iterator_;

  DISALLOW_COPY_AND_ASSIGN(SampleToGroupIterator);
};

}  
}  

#endif  
