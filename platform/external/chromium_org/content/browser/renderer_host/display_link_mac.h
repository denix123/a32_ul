// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_DISPLAY_LINK_MAC_H_
#define CONTENT_BROWSER_RENDERER_HOST_DISPLAY_LINK_MAC_H_

#include <QuartzCore/CVDisplayLink.h>
#include <map>

#include "base/lazy_instance.h"
#include "base/mac/scoped_typeref.h"
#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "base/time/time.h"
#include "base/timer/timer.h"

namespace content {

class DisplayLinkMac : public base::RefCounted<DisplayLinkMac> {
 public:
  static scoped_refptr<DisplayLinkMac> GetForDisplay(
      CGDirectDisplayID display_id);

  
  bool GetVSyncParameters(
      base::TimeTicks* timebase,
      base::TimeDelta* interval);

 private:
  friend class base::RefCounted<DisplayLinkMac>;

  DisplayLinkMac(
      CGDirectDisplayID display_id,
      base::ScopedTypeRef<CVDisplayLinkRef> display_link);
  virtual ~DisplayLinkMac();

  void StartOrContinueDisplayLink();
  void StopDisplayLink();
  void Tick(const CVTimeStamp* time);

  static CVReturn DisplayLinkCallback(
      CVDisplayLinkRef display_link,
      const CVTimeStamp* now,
      const CVTimeStamp* output_time,
      CVOptionFlags flags_in,
      CVOptionFlags* flags_out,
      void* context);

  
  CGDirectDisplayID display_id_;

  
  base::ScopedTypeRef<CVDisplayLinkRef> display_link_;

  
  
  base::DelayTimer<DisplayLinkMac> stop_timer_;

  
  bool timebase_and_interval_valid_;
  base::TimeTicks timebase_;
  base::TimeDelta interval_;

  
  base::Lock lock_;

  
  
  typedef std::map<CGDirectDisplayID, DisplayLinkMac*> DisplayMap;
  static base::LazyInstance<DisplayMap> display_map_;
};

}  

#endif  
