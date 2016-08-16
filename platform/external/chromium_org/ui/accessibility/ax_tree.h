// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_ACCESSIBILITY_AX_TREE_H_
#define UI_ACCESSIBILITY_AX_TREE_H_

#include <set>

#include "base/containers/hash_tables.h"
#include "ui/accessibility/ax_export.h"
#include "ui/accessibility/ax_tree_update.h"

namespace ui {

class AXNode;
struct AXTreeUpdateState;

class AX_EXPORT AXTreeDelegate {
 public:
  AXTreeDelegate();
  virtual ~AXTreeDelegate();

  
  
  
  virtual void OnNodeWillBeDeleted(AXNode* node) = 0;

  
  
  virtual void OnNodeCreated(AXNode* node) = 0;

  
  
  virtual void OnNodeChanged(AXNode* node) = 0;

  
  
  virtual void OnNodeCreationFinished(AXNode* node) = 0;

  
  
  virtual void OnNodeChangeFinished(AXNode* node) = 0;

  
  virtual void OnRootChanged(AXNode* new_root) = 0;
};

class AX_EXPORT AXTree {
 public:
  AXTree();
  explicit AXTree(const AXTreeUpdate& initial_state);
  virtual ~AXTree();

  virtual void SetDelegate(AXTreeDelegate* delegate);

  virtual AXNode* GetRoot() const;
  virtual AXNode* GetFromId(int32 id) const;

  
  
  
  virtual bool Unserialize(const AXTreeUpdate& update);

  
  std::string ToString() const;

  
  
  const std::string& error() { return error_; }

 private:
  AXNode* CreateNode(AXNode* parent, int32 id, int32 index_in_parent);

  
  bool UpdateNode(const AXNodeData& src, AXTreeUpdateState* update_state);

  void OnRootChanged();

  
  
  void DestroyNodeAndSubtree(AXNode* node);

  
  
  
  bool DeleteOldChildren(AXNode* node,
                         const std::vector<int32> new_child_ids);

  
  
  
  
  
  bool CreateNewChildVector(AXNode* node,
                            const std::vector<int32> new_child_ids,
                            std::vector<AXNode*>* new_children,
                            AXTreeUpdateState* update_state);

  AXTreeDelegate* delegate_;
  AXNode* root_;
  base::hash_map<int32, AXNode*> id_map_;
  std::string error_;
};

}  

#endif  
