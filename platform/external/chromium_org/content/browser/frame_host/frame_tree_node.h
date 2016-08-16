// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_FRAME_TREE_NODE_H_
#define CONTENT_BROWSER_FRAME_HOST_FRAME_TREE_NODE_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "content/browser/frame_host/render_frame_host_impl.h"
#include "content/browser/frame_host/render_frame_host_manager.h"
#include "content/common/content_export.h"
#include "url/gurl.h"

namespace content {

class FrameTree;
class Navigator;
class RenderFrameHostImpl;

class CONTENT_EXPORT FrameTreeNode {
 public:

  FrameTreeNode(FrameTree* frame_tree,
                Navigator* navigator,
                RenderFrameHostDelegate* render_frame_delegate,
                RenderViewHostDelegate* render_view_delegate,
                RenderWidgetHostDelegate* render_widget_delegate,
                RenderFrameHostManager::Delegate* manager_delegate,
                const std::string& name);

  ~FrameTreeNode();

  bool IsMainFrame() const;

  void AddChild(scoped_ptr<FrameTreeNode> child,
                int process_id,
                int frame_routing_id);
  void RemoveChild(FrameTreeNode* child);

  
  void ResetForNewProcess();

  FrameTree* frame_tree() const {
    return frame_tree_;
  }

  Navigator* navigator() {
    return navigator_.get();
  }

  RenderFrameHostManager* render_manager() {
    return &render_manager_;
  }

  int64 frame_tree_node_id() const {
    return frame_tree_node_id_;
  }

  const std::string& frame_name() const {
    return frame_name_;
  }

  size_t child_count() const {
    return children_.size();
  }

  FrameTreeNode* parent() const { return parent_; }

  FrameTreeNode* child_at(size_t index) const {
    return children_[index];
  }

  const GURL& current_url() const {
    return current_url_;
  }

  void set_current_url(const GURL& url) {
    current_url_ = url;
  }

  RenderFrameHostImpl* current_frame_host() const {
    return render_manager_.current_frame_host();
  }

 private:
  void set_parent(FrameTreeNode* parent) { parent_ = parent; }

  
  static int64 next_frame_tree_node_id_;

  
  FrameTree* frame_tree_;  

  
  
  scoped_refptr<Navigator> navigator_;

  
  
  
  
  RenderFrameHostManager render_manager_;

  
  
  const int64 frame_tree_node_id_;

  
  
  std::string frame_name_;

  
  
  FrameTreeNode* parent_;

  
  ScopedVector<FrameTreeNode> children_;

  
  
  
  
  GURL current_url_;

  DISALLOW_COPY_AND_ASSIGN(FrameTreeNode);
};

}  

#endif  
