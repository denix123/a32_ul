// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_ACCESSIBILITY_BROWSER_ACCESSIBILITY_H_
#define CONTENT_BROWSER_ACCESSIBILITY_BROWSER_ACCESSIBILITY_H_

#include <map>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "base/strings/string_split.h"
#include "build/build_config.h"
#include "content/common/content_export.h"
#include "third_party/WebKit/public/web/WebAXEnums.h"
#include "ui/accessibility/ax_node.h"
#include "ui/accessibility/ax_node_data.h"

#if defined(OS_MACOSX) && __OBJC__
@class BrowserAccessibilityCocoa;
#endif

namespace content {
class BrowserAccessibilityManager;
#if defined(OS_WIN)
class BrowserAccessibilityWin;
#endif

class CONTENT_EXPORT BrowserAccessibility {
 public:
  
  
  static BrowserAccessibility* Create();

  virtual ~BrowserAccessibility();

  
  
  
  virtual void Init(BrowserAccessibilityManager* manager, ui::AXNode* node);

  
  
  virtual void OnDataChanged();

  
  
  virtual void OnUpdateFinished() {}

  
  
  virtual bool IsNative() const;

  
  virtual void OnLocationChanged() {}

  
  bool IsDescendantOf(BrowserAccessibility* ancestor);

  
  
  
  
  
  
  virtual bool PlatformIsLeaf() const;

  
  
  uint32 PlatformChildCount() const;

  
  
  BrowserAccessibility* PlatformGetChild(uint32 child_index) const;

  
  
  BrowserAccessibility* GetPreviousSibling();

  
  
  BrowserAccessibility* GetNextSibling();

  
  
  gfx::Rect GetLocalBoundsRect() const;

  
  gfx::Rect GetGlobalBoundsRect() const;

  
  
  
  gfx::Rect GetLocalBoundsForRange(int start, int len) const;

  
  
  gfx::Rect GetGlobalBoundsForRange(int start, int len) const;

  
  
  BrowserAccessibility* BrowserAccessibilityForPoint(const gfx::Point& point);

  
  
  
  
  
  
  
  
  
  virtual void Destroy();

  
  virtual void NativeAddReference() { }

  
  virtual void NativeReleaseReference();

  
  
  

  BrowserAccessibilityManager* manager() const { return manager_; }
  bool instance_active() const { return node_ != NULL; }
  ui::AXNode* node() const { return node_; }
  const std::string& name() const { return name_; }
  const std::string& value() const { return value_; }
  void set_name(const std::string& name) { name_ = name; }
  void set_value(const std::string& value) { value_ = value; }

  
  
  
  
  uint32 InternalChildCount() const;
  BrowserAccessibility* InternalGetChild(uint32 child_index) const;

  BrowserAccessibility* GetParent() const;
  int32 GetIndexInParent() const;

  int32 GetId() const;
  const ui::AXNodeData& GetData() const;
  gfx::Rect GetLocation() const;
  int32 GetRole() const;
  int32 GetState() const;

  typedef base::StringPairs HtmlAttributes;
  const HtmlAttributes& GetHtmlAttributes() const;

#if defined(OS_MACOSX) && __OBJC__
  BrowserAccessibilityCocoa* ToBrowserAccessibilityCocoa();
#elif defined(OS_WIN)
  BrowserAccessibilityWin* ToBrowserAccessibilityWin();
#endif

  
  
  
  
  
  
  
  
  
  
  
  
  
  

  bool HasBoolAttribute(ui::AXBoolAttribute attr) const;
  bool GetBoolAttribute(ui::AXBoolAttribute attr) const;
  bool GetBoolAttribute(ui::AXBoolAttribute attr, bool* value) const;

  bool HasFloatAttribute(ui::AXFloatAttribute attr) const;
  float GetFloatAttribute(ui::AXFloatAttribute attr) const;
  bool GetFloatAttribute(ui::AXFloatAttribute attr, float* value) const;

  bool HasIntAttribute(ui::AXIntAttribute attribute) const;
  int GetIntAttribute(ui::AXIntAttribute attribute) const;
  bool GetIntAttribute(ui::AXIntAttribute attribute, int* value) const;

  bool HasStringAttribute(
      ui::AXStringAttribute attribute) const;
  const std::string& GetStringAttribute(ui::AXStringAttribute attribute) const;
  bool GetStringAttribute(ui::AXStringAttribute attribute,
                          std::string* value) const;

  bool GetString16Attribute(ui::AXStringAttribute attribute,
                            base::string16* value) const;
  base::string16 GetString16Attribute(
      ui::AXStringAttribute attribute) const;

  bool HasIntListAttribute(ui::AXIntListAttribute attribute) const;
  const std::vector<int32>& GetIntListAttribute(
      ui::AXIntListAttribute attribute) const;
  bool GetIntListAttribute(ui::AXIntListAttribute attribute,
                           std::vector<int32>* value) const;

  void SetStringAttribute(ui::AXStringAttribute attribute,
                          const std::string& value);

  
  
  bool GetHtmlAttribute(const char* attr, base::string16* value) const;
  bool GetHtmlAttribute(const char* attr, std::string* value) const;

  
  
  
  
  
  
  
  
  
  
  
  
  bool GetAriaTristate(const char* attr_name,
                       bool* is_defined,
                       bool* is_mixed) const;

  
  bool HasState(ui::AXState state_enum) const;

  
  bool IsEditableText() const;

  
  std::string GetTextRecursive() const;

 protected:
  BrowserAccessibility();

  
  BrowserAccessibilityManager* manager_;

  
  ui::AXNode* node_;

 private:
  
  
  int GetStaticTextLenRecursive() const;

  std::string name_;
  std::string value_;

  DISALLOW_COPY_AND_ASSIGN(BrowserAccessibility);
};

}  

#endif  
