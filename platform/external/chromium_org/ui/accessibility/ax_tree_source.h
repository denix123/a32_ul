// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_ACCESSIBILITY_AX_TREE_SOURCE_H_
#define UI_ACCESSIBILITY_AX_TREE_SOURCE_H_

#include <vector>

#include "ui/accessibility/ax_node_data.h"

namespace ui {

template<typename AXNodeSource>
class AXTreeSource {
 public:
  virtual ~AXTreeSource() {}

  
  virtual AXNodeSource GetRoot() const = 0;

  
  
  virtual AXNodeSource GetFromId(int32 id) const = 0;

  
  virtual int32 GetId(AXNodeSource node) const = 0;

  
  virtual void GetChildren(AXNodeSource node,
                           std::vector<AXNodeSource>* out_children) const = 0;

  
  virtual AXNodeSource GetParent(AXNodeSource node) const = 0;

  
  
  virtual bool IsValid(AXNodeSource node) const = 0;

  
  virtual bool IsEqual(AXNodeSource node1,
                       AXNodeSource node2) const = 0;

  
  virtual AXNodeSource GetNull() const = 0;

  
  virtual void SerializeNode(AXNodeSource node, AXNodeData* out_data) const = 0;

 protected:
  AXTreeSource() {}
};

}  

#endif  
