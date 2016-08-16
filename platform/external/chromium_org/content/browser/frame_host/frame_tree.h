// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_FRAME_TREE_H_
#define CONTENT_BROWSER_FRAME_HOST_FRAME_TREE_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "content/browser/frame_host/frame_tree_node.h"
#include "content/common/content_export.h"

namespace content {

class FrameTreeNode;
class Navigator;
class RenderFrameHostDelegate;
class RenderProcessHost;
class RenderViewHostDelegate;
class RenderViewHostImpl;
class RenderFrameHostManager;
class RenderWidgetHostDelegate;

class CONTENT_EXPORT FrameTree {
 public:
  
  
  
  
  
  
  FrameTree(Navigator* navigator,
            RenderFrameHostDelegate* render_frame_delegate,
            RenderViewHostDelegate* render_view_delegate,
            RenderWidgetHostDelegate* render_widget_delegate,
            RenderFrameHostManager::Delegate* manager_delegate);
  ~FrameTree();

  
  static FrameTreeNode* GloballyFindByID(int64 frame_tree_node_id);

  FrameTreeNode* root() const { return root_.get(); }

  
  
  FrameTreeNode* FindByID(int64 frame_tree_node_id);

  
  FrameTreeNode* FindByRoutingID(int routing_id, int process_id);

  
  
  
  
  
  void ForEach(const base::Callback<bool(FrameTreeNode*)>& on_node) const;

  
  RenderFrameHostImpl* AddFrame(FrameTreeNode* parent,
                                int process_id,
                                int new_routing_id,
                                const std::string& frame_name);
  void RemoveFrame(FrameTreeNode* child);

  
  
  
  
  void CreateProxiesForSiteInstance(
      FrameTreeNode* source,
      SiteInstance* site_instance);

  
  
  
  
  
  void ResetForMainFrameSwap();

  
  
  
  
  
  void RenderProcessGone(RenderViewHost* render_view_host);

  
  RenderFrameHostImpl* GetMainFrame() const;

  
  FrameTreeNode* GetFocusedFrame();

  
  void SetFocusedFrame(FrameTreeNode* node);

  
  
  
  void SetFrameRemoveListener(
      const base::Callback<void(RenderFrameHost*)>& on_frame_removed);

  
  
  
  RenderViewHostImpl* CreateRenderViewHost(SiteInstance* site_instance,
                                           int routing_id,
                                           int main_frame_routing_id,
                                           bool swapped_out,
                                           bool hidden);

  
  
  
  RenderViewHostImpl* GetRenderViewHost(SiteInstance* site_instance);

  
  
  void RegisterRenderFrameHost(RenderFrameHostImpl* render_frame_host);
  void UnregisterRenderFrameHost(RenderFrameHostImpl* render_frame_host);

 private:
  typedef base::hash_map<int, RenderViewHostImpl*> RenderViewHostMap;
  typedef std::multimap<int, RenderViewHostImpl*> RenderViewHostMultiMap;

  
  
  RenderFrameHostDelegate* render_frame_delegate_;
  RenderViewHostDelegate* render_view_delegate_;
  RenderWidgetHostDelegate* render_widget_delegate_;
  RenderFrameHostManager::Delegate* manager_delegate_;

  
  
  
  
  
  
  
  
  RenderViewHostMap render_view_host_map_;

  
  
  
  
  
  RenderViewHostMultiMap render_view_host_pending_shutdown_map_;

  scoped_ptr<FrameTreeNode> root_;

  int64 focused_frame_tree_node_id_;

  base::Callback<void(RenderFrameHost*)> on_frame_removed_;

  DISALLOW_COPY_AND_ASSIGN(FrameTree);
};

}  

#endif  
