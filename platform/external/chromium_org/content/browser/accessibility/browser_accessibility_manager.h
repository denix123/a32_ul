// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_ACCESSIBILITY_BROWSER_ACCESSIBILITY_MANAGER_H_
#define CONTENT_BROWSER_ACCESSIBILITY_BROWSER_ACCESSIBILITY_MANAGER_H_

#include <vector>

#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "build/build_config.h"
#include "content/common/content_export.h"
#include "third_party/WebKit/public/web/WebAXEnums.h"
#include "ui/accessibility/ax_node_data.h"
#include "ui/accessibility/ax_serializable_tree.h"
#include "ui/accessibility/ax_tree_update.h"
#include "ui/gfx/native_widget_types.h"

struct AccessibilityHostMsg_EventParams;
struct AccessibilityHostMsg_LocationChangeParams;

namespace content {
class BrowserAccessibility;
class BrowserAccessibilityManager;
#if defined(OS_ANDROID)
class BrowserAccessibilityManagerAndroid;
#endif
#if defined(OS_WIN)
class BrowserAccessibilityManagerWin;
#endif

CONTENT_EXPORT ui::AXTreeUpdate MakeAXTreeUpdate(
    const ui::AXNodeData& node,
    const ui::AXNodeData& node2 = ui::AXNodeData(),
    const ui::AXNodeData& node3 = ui::AXNodeData(),
    const ui::AXNodeData& node4 = ui::AXNodeData(),
    const ui::AXNodeData& node5 = ui::AXNodeData(),
    const ui::AXNodeData& node6 = ui::AXNodeData(),
    const ui::AXNodeData& node7 = ui::AXNodeData(),
    const ui::AXNodeData& node8 = ui::AXNodeData(),
    const ui::AXNodeData& node9 = ui::AXNodeData());

class CONTENT_EXPORT BrowserAccessibilityDelegate {
 public:
  virtual ~BrowserAccessibilityDelegate() {}
  virtual void AccessibilitySetFocus(int acc_obj_id) = 0;
  virtual void AccessibilityDoDefaultAction(int acc_obj_id) = 0;
  virtual void AccessibilityShowMenu(const gfx::Point& global_point) = 0;
  virtual void AccessibilityScrollToMakeVisible(
      int acc_obj_id, const gfx::Rect& subfocus) = 0;
  virtual void AccessibilityScrollToPoint(
      int acc_obj_id, const gfx::Point& point) = 0;
  virtual void AccessibilitySetTextSelection(
      int acc_obj_id, int start_offset, int end_offset) = 0;
  virtual bool AccessibilityViewHasFocus() const = 0;
  virtual gfx::Rect AccessibilityGetViewBounds() const = 0;
  virtual gfx::Point AccessibilityOriginInScreen(
      const gfx::Rect& bounds) const = 0;
  virtual void AccessibilityHitTest(
      const gfx::Point& point) = 0;
  virtual void AccessibilityFatalError() = 0;
  virtual gfx::AcceleratedWidget AccessibilityGetAcceleratedWidget() = 0;
  virtual gfx::NativeViewAccessible AccessibilityGetNativeViewAccessible() = 0;
  virtual BrowserAccessibilityManager* AccessibilityGetChildFrame(
      int accessibility_node_id) = 0;
  virtual BrowserAccessibility* AccessibilityGetParentFrame() = 0;
};

class CONTENT_EXPORT BrowserAccessibilityFactory {
 public:
  virtual ~BrowserAccessibilityFactory() {}

  
  
  virtual BrowserAccessibility* Create();
};

class CONTENT_EXPORT BrowserAccessibilityManager : public ui::AXTreeDelegate {
 public:
  
  
  static BrowserAccessibilityManager* Create(
      const ui::AXTreeUpdate& initial_tree,
      BrowserAccessibilityDelegate* delegate,
      BrowserAccessibilityFactory* factory = new BrowserAccessibilityFactory());

  virtual ~BrowserAccessibilityManager();

  void Initialize(const ui::AXTreeUpdate& initial_tree);

  static ui::AXTreeUpdate GetEmptyDocument();

  virtual void NotifyAccessibilityEvent(
      ui::AXEvent event_type, BrowserAccessibility* node) { }

  
  BrowserAccessibility* GetRoot();

  
  BrowserAccessibility* GetFromAXNode(ui::AXNode* node);

  
  
  BrowserAccessibility* GetFromID(int32 id);

  
  
  virtual void OnWindowFocused();

  
  
  virtual void OnWindowBlurred();

  
  
  void GotMouseDown();

  
  
  
  void SetFocus(ui::AXNode* node, bool notify);
  void SetFocus(BrowserAccessibility* node, bool notify);

  
  void DoDefaultAction(const BrowserAccessibility& node);

  
  
  
  
  void ScrollToMakeVisible(
      const BrowserAccessibility& node, gfx::Rect subfocus);

  
  
  void ScrollToPoint(
      const BrowserAccessibility& node, gfx::Point point);

  
  void SetTextSelection(
      const BrowserAccessibility& node, int start_offset, int end_offset);

  
  gfx::Rect GetViewBounds();

  
  void OnAccessibilityEvents(
      const std::vector<AccessibilityHostMsg_EventParams>& params);

  
  
  void OnLocationChanges(
      const std::vector<AccessibilityHostMsg_LocationChangeParams>& params);

#if defined(OS_WIN)
  BrowserAccessibilityManagerWin* ToBrowserAccessibilityManagerWin();
#endif

#if defined(OS_ANDROID)
  BrowserAccessibilityManagerAndroid* ToBrowserAccessibilityManagerAndroid();
#endif

  
  
  virtual BrowserAccessibility* GetFocus(BrowserAccessibility* root);

  
  
  BrowserAccessibility* GetActiveDescendantFocus(BrowserAccessibility* root);

  
  
  virtual bool UseRootScrollOffsetsWhenComputingBounds();

  
  BrowserAccessibility* NextInTreeOrder(BrowserAccessibility* node);
  BrowserAccessibility* PreviousInTreeOrder(BrowserAccessibility* node);

  
  virtual void OnNodeWillBeDeleted(ui::AXNode* node) OVERRIDE;
  virtual void OnNodeCreated(ui::AXNode* node) OVERRIDE;
  virtual void OnNodeChanged(ui::AXNode* node) OVERRIDE;
  virtual void OnNodeCreationFinished(ui::AXNode* node) OVERRIDE;
  virtual void OnNodeChangeFinished(ui::AXNode* node) OVERRIDE;
  virtual void OnRootChanged(ui::AXNode* new_root) OVERRIDE {}

  BrowserAccessibilityDelegate* delegate() const { return delegate_; }
  void set_delegate(BrowserAccessibilityDelegate* delegate) {
    delegate_ = delegate;
  }

  
  ui::AXTreeUpdate SnapshotAXTreeForTesting();

 protected:
  BrowserAccessibilityManager(
      BrowserAccessibilityDelegate* delegate,
      BrowserAccessibilityFactory* factory);

  BrowserAccessibilityManager(
      const ui::AXTreeUpdate& initial_tree,
      BrowserAccessibilityDelegate* delegate,
      BrowserAccessibilityFactory* factory);

  
  virtual void OnTreeUpdateFinished() {}

 private:
  
  
  enum OnScreenKeyboardState {
    
    OSK_DISALLOWED_BECAUSE_TAB_HIDDEN,

    
    
    OSK_DISALLOWED_BECAUSE_TAB_JUST_APPEARED,

    
    
    
    
    OSK_ALLOWED_WITHIN_FOCUSED_OBJECT,

    
    
    
    OSK_ALLOWED
  };

 protected:
  
  BrowserAccessibilityDelegate* delegate_;

  
  scoped_ptr<BrowserAccessibilityFactory> factory_;

  
  scoped_ptr<ui::AXSerializableTree> tree_;

  
  ui::AXNode* focus_;

  
  base::hash_map<int32, BrowserAccessibility*> id_wrapper_map_;

  
  OnScreenKeyboardState osk_state_;

  DISALLOW_COPY_AND_ASSIGN(BrowserAccessibilityManager);
};

}  

#endif  
