// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_COCOA_BRIDGED_NATIVE_WIDGET_H_
#define UI_VIEWS_COCOA_BRIDGED_NATIVE_WIDGET_H_

#import <Cocoa/Cocoa.h>

#import "base/mac/scoped_nsobject.h"
#include "base/memory/scoped_ptr.h"
#import "ui/views/focus/focus_manager.h"
#include "ui/views/ime/input_method_delegate.h"
#include "ui/views/views_export.h"
#include "ui/views/widget/widget.h"

@class BridgedContentView;
@class ViewsNSWindowDelegate;

namespace ui {
class InputMethod;
}

namespace views {

class InputMethod;
class NativeWidgetMac;
class View;

class VIEWS_EXPORT BridgedNativeWidget : public internal::InputMethodDelegate,
                                         public FocusChangeListener {
 public:
  
  explicit BridgedNativeWidget(NativeWidgetMac* parent);
  virtual ~BridgedNativeWidget();

  
  void Init(base::scoped_nsobject<NSWindow> window,
            const Widget::InitParams& params);

  
  
  void SetFocusManager(FocusManager* focus_manager);

  
  
  void SetRootView(views::View* view);

  
  void OnWindowWillClose();

  
  InputMethod* CreateInputMethod();
  ui::InputMethod* GetHostInputMethod();

  NativeWidgetMac* native_widget_mac() { return native_widget_mac_; }
  BridgedContentView* ns_view() { return bridged_view_; }
  NSWindow* ns_window() { return window_; }

  
  virtual void DispatchKeyEventPostIME(const ui::KeyEvent& key) OVERRIDE;

 private:
  
  void RemoveOrDestroyChildren();

  views::NativeWidgetMac* native_widget_mac_;  
  base::scoped_nsobject<NSWindow> window_;
  base::scoped_nsobject<ViewsNSWindowDelegate> window_delegate_;
  base::scoped_nsobject<BridgedContentView> bridged_view_;
  scoped_ptr<ui::InputMethod> input_method_;
  FocusManager* focus_manager_;  

  
  virtual void OnWillChangeFocus(View* focused_before,
                                 View* focused_now) OVERRIDE;
  virtual void OnDidChangeFocus(View* focused_before,
                                View* focused_now) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(BridgedNativeWidget);
};

}  

#endif  
