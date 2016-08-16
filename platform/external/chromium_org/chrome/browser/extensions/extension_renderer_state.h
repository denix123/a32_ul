// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_RENDERER_STATE_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_RENDERER_STATE_H_

#include <map>
#include <set>
#include <string>
#include <utility>

#include "base/basictypes.h"
#include "base/memory/singleton.h"

namespace content {
class ResourceRequestInfo;
}

class ExtensionRendererState {
 public:
  static ExtensionRendererState* GetInstance();

  
  
  void Init();
  void Shutdown();

  
  
  bool GetTabAndWindowId(
      const content::ResourceRequestInfo* info, int* tab_id, int* window_id);

 private:
  class RenderViewHostObserver;
  class TabObserver;
  friend class TabObserver;
  friend struct DefaultSingletonTraits<ExtensionRendererState>;

  typedef std::pair<int, int> RenderId;
  typedef std::pair<int, int> TabAndWindowId;
  typedef std::map<RenderId, TabAndWindowId> TabAndWindowIdMap;

  ExtensionRendererState();
  ~ExtensionRendererState();

  
  void SetTabAndWindowId(
      int render_process_host_id, int routing_id, int tab_id, int window_id);
  void ClearTabAndWindowId(
      int render_process_host_id, int routing_id);

  TabObserver* observer_;
  TabAndWindowIdMap map_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionRendererState);
};

#endif  
