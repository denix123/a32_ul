// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_RENDER_MEDIA_LOG_H_
#define CONTENT_RENDERER_MEDIA_RENDER_MEDIA_LOG_H_

#include <vector>

#include "base/time/time.h"
#include "content/common/content_export.h"
#include "media/base/media_log.h"

namespace base {
class MessageLoopProxy;
}

namespace content {

class CONTENT_EXPORT RenderMediaLog : public media::MediaLog {
 public:
  RenderMediaLog();

  
  virtual void AddEvent(scoped_ptr<media::MediaLogEvent> event) OVERRIDE;

  
  void SetTickClockForTesting(scoped_ptr<base::TickClock> tick_clock);

 private:
  virtual ~RenderMediaLog();

  scoped_refptr<base::MessageLoopProxy> render_loop_;
  scoped_ptr<base::TickClock> tick_clock_;
  base::TimeTicks last_ipc_send_time_;
  std::vector<media::MediaLogEvent> queued_media_events_;

  
  scoped_ptr<media::MediaLogEvent> last_buffered_extents_changed_event_;

  DISALLOW_COPY_AND_ASSIGN(RenderMediaLog);
};

}  

#endif  