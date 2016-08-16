// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_WEB_CONTENTS_WEB_CONTENTS_VIEW_H_
#define CONTENT_BROWSER_WEB_CONTENTS_WEB_CONTENTS_VIEW_H_

#include <string>

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "content/common/content_export.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/size.h"

namespace content {
class RenderViewHost;
class RenderWidgetHost;
class RenderWidgetHostViewBase;
struct DropData;

class WebContentsView {
 public:
  virtual ~WebContentsView() {}

  
  virtual gfx::NativeView GetNativeView() const = 0;

  
  
  
  virtual gfx::NativeView GetContentNativeView() const = 0;

  
  
  virtual gfx::NativeWindow GetTopLevelNativeWindow() const = 0;

  
  
  virtual void GetContainerBounds(gfx::Rect* out) const = 0;

  
  
  
  
  
  
  
  
  virtual void SizeContents(const gfx::Size& size) = 0;

  
  virtual void Focus() = 0;

  
  
  virtual void SetInitialFocus() = 0;

  
  virtual void StoreFocus() = 0;

  
  
  virtual void RestoreFocus() = 0;

  
  virtual DropData* GetDropData() const = 0;

  
  virtual gfx::Rect GetViewBounds() const = 0;

  virtual void CreateView(
      const gfx::Size& initial_size, gfx::NativeView context) = 0;

  
  
  
  virtual RenderWidgetHostViewBase* CreateViewForWidget(
      RenderWidgetHost* render_widget_host) = 0;

  
  virtual RenderWidgetHostViewBase* CreateViewForPopupWidget(
      RenderWidgetHost* render_widget_host) = 0;

  
  
  
  
  virtual void SetPageTitle(const base::string16& title) = 0;

  
  
  virtual void RenderViewCreated(RenderViewHost* host) = 0;

  
  
  virtual void RenderViewSwappedIn(RenderViewHost* host) = 0;

  
  virtual void SetOverscrollControllerEnabled(bool enabled) = 0;

#if defined(OS_MACOSX)
  
  
  virtual void SetAllowOtherViews(bool allow) = 0;

  
  virtual bool GetAllowOtherViews() const = 0;

  
  
  
  
  
  virtual bool IsEventTracking() const = 0;
  virtual void CloseTabAfterEventTracking() = 0;
#endif
};

}  

#endif  
