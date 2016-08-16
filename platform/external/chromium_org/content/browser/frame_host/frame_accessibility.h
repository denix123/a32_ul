// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_FRAME_ACCESSIBILITY_H_
#define CONTENT_BROWSER_FRAME_HOST_FRAME_ACCESSIBILITY_H_

#include <vector>

#include "base/basictypes.h"
#include "base/memory/singleton.h"
#include "content/common/content_export.h"

namespace content {

class RenderFrameHostImpl;

class CONTENT_EXPORT FrameAccessibility {
 public:
  static FrameAccessibility* GetInstance();

  
  
  
  void AddChildFrame(RenderFrameHostImpl* parent_frame_host,
                     int accessibility_node_id,
                     int64 child_frame_tree_node_id);

  
  
  
  void AddGuestWebContents(RenderFrameHostImpl* parent_frame_host,
                           int accessibility_node_id,
                           int browser_plugin_instance_id);

  
  
  void OnRenderFrameHostDestroyed(RenderFrameHostImpl* render_frame_host);

  
  
  
  
  
  RenderFrameHostImpl* GetChild(RenderFrameHostImpl* parent_frame_host,
                                int accessibility_node_id);

  
  
  
  
  bool GetParent(RenderFrameHostImpl* child_frame_host,
                 RenderFrameHostImpl** out_parent_frame_host,
                 int* out_accessibility_node_id);

 private:
  FrameAccessibility();
  virtual ~FrameAccessibility();

  struct ChildFrameMapping {
    ChildFrameMapping();

    RenderFrameHostImpl* parent_frame_host;
    int accessibility_node_id;
    int64 child_frame_tree_node_id;
    int browser_plugin_instance_id;
  };

  std::vector<ChildFrameMapping> mappings_;

  friend struct DefaultSingletonTraits<FrameAccessibility>;
};

}  

#endif  
