// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_CHANNEL_OBSERVER_H_
#define UI_OZONE_PLATFORM_DRI_CHANNEL_OBSERVER_H_

namespace ui {

class ChannelObserver {
 public:
  virtual ~ChannelObserver() {}

  virtual void OnChannelEstablished() = 0;
  virtual void OnChannelDestroyed() = 0;
};

}  

#endif  
