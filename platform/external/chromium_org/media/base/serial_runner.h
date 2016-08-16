// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_SERIAL_RUNNER_H_
#define MEDIA_BASE_SERIAL_RUNNER_H_

#include <queue>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "media/base/media_export.h"
#include "media/base/pipeline_status.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class MEDIA_EXPORT SerialRunner {
 public:
  typedef base::Callback<void(const base::Closure&)> BoundClosure;
  typedef base::Callback<void(const PipelineStatusCB&)> BoundPipelineStatusCB;

  
  class MEDIA_EXPORT Queue {
   public:
    Queue();
    ~Queue();

    void Push(const base::Closure& closure);
    void Push(const BoundClosure& bound_fn);
    void Push(const BoundPipelineStatusCB& bound_fn);

   private:
    friend class SerialRunner;

    BoundPipelineStatusCB Pop();
    bool empty();

    std::queue<BoundPipelineStatusCB> bound_fns_;
  };

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static scoped_ptr<SerialRunner> Run(
      const Queue& bound_fns, const PipelineStatusCB& done_cb);

 private:
  friend struct base::DefaultDeleter<SerialRunner>;

  SerialRunner(const Queue& bound_fns, const PipelineStatusCB& done_cb);
  ~SerialRunner();

  void RunNextInSeries(PipelineStatus last_status);

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  Queue bound_fns_;
  PipelineStatusCB done_cb_;

  
  base::WeakPtrFactory<SerialRunner> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SerialRunner);
};

}  

#endif  
