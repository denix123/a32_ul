// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COPRESENCE_HANDLERS_AUDIO_AUDIO_DIRECTIVE_LIST_H_
#define COMPONENTS_COPRESENCE_HANDLERS_AUDIO_AUDIO_DIRECTIVE_LIST_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"

namespace media {
class AudioBusRefCounted;
}

namespace copresence {

struct AudioDirective {
  
  AudioDirective();
  AudioDirective(const std::string& op_id, base::Time end_time);

  std::string op_id;
  base::Time end_time;
};

class AudioDirectiveList {
 public:
  AudioDirectiveList();
  virtual ~AudioDirectiveList();

  void AddDirective(const std::string& op_id, base::TimeDelta ttl);
  void RemoveDirective(const std::string& op_id);

  scoped_ptr<AudioDirective> GetActiveDirective();

 private:
  
  class LatestFirstComparator {
   public:
    
    bool operator()(const AudioDirective& left,
                    const AudioDirective& right) const {
      return left.end_time < right.end_time;
    }
  };

  std::vector<AudioDirective>::iterator FindDirectiveByOpId(
      const std::string& op_id);

  
  
  std::vector<AudioDirective> active_directives_;

  DISALLOW_COPY_AND_ASSIGN(AudioDirectiveList);
};

}  

#endif  
