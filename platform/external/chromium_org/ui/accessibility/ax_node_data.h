// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_ACCESSIBILITY_AX_NODE_DATA_H_
#define UI_ACCESSIBILITY_AX_NODE_DATA_H_

#include <map>
#include <string>
#include <vector>

#include "base/strings/string16.h"
#include "base/strings/string_split.h"
#include "ui/accessibility/ax_enums.h"
#include "ui/accessibility/ax_export.h"
#include "ui/gfx/rect.h"

namespace ui {

struct AX_EXPORT AXNodeData {
  AXNodeData();
  virtual ~AXNodeData();

  void AddStringAttribute(AXStringAttribute attribute,
                          const std::string& value);
  void AddIntAttribute(AXIntAttribute attribute, int value);
  void AddFloatAttribute(AXFloatAttribute attribute, float value);
  void AddBoolAttribute(AXBoolAttribute attribute, bool value);
  void AddIntListAttribute(AXIntListAttribute attribute,
                           const std::vector<int32>& value);

  
  
  void SetName(std::string name);
  
  void SetValue(std::string value);

  
  std::string ToString() const;

  
  
  int32 id;
  AXRole role;
  uint32 state;
  gfx::Rect location;
  std::vector<std::pair<AXStringAttribute, std::string> > string_attributes;
  std::vector<std::pair<AXIntAttribute, int32> > int_attributes;
  std::vector<std::pair<AXFloatAttribute, float> > float_attributes;
  std::vector<std::pair<AXBoolAttribute, bool> > bool_attributes;
  std::vector<std::pair<AXIntListAttribute, std::vector<int32> > >
      intlist_attributes;
  base::StringPairs html_attributes;
  std::vector<int32> child_ids;
};

}  

#endif  
