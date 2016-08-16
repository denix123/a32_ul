// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EXTENSIONS_MEDIA_PLAYER_EVENT_ROUTER_H_
#define CHROME_BROWSER_CHROMEOS_EXTENSIONS_MEDIA_PLAYER_EVENT_ROUTER_H_

#include "base/basictypes.h"

namespace content {
class BrowserContext;
}

namespace extensions {

class MediaPlayerEventRouter {
 public:
  explicit MediaPlayerEventRouter(content::BrowserContext* context);
  virtual ~MediaPlayerEventRouter();

  
  void NotifyNextTrack();

 
  void NotifyPrevTrack();

  
  void NotifyTogglePlayState();

 private:
  content::BrowserContext* browser_context_;

  DISALLOW_COPY_AND_ASSIGN(MediaPlayerEventRouter);
};

}  

#endif  
