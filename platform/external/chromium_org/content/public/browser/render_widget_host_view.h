// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_RENDER_WIDGET_HOST_VIEW_H_
#define CONTENT_PUBLIC_BROWSER_RENDER_WIDGET_HOST_VIEW_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "content/common/content_export.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkRegion.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"
#include "ui/gfx/native_widget_types.h"

class GURL;

namespace gfx {
class Rect;
class Size;
}

namespace ui {
class TextInputClient;
}

namespace content {

class RenderWidgetHost;
class RenderWidgetHostViewFrameSubscriber;

class CONTENT_EXPORT RenderWidgetHostView {
 public:
  virtual ~RenderWidgetHostView() {}

  
  
  
  virtual void InitAsChild(gfx::NativeView parent_view) = 0;

  
  virtual RenderWidgetHost* GetRenderWidgetHost() const = 0;

  
  virtual void SetSize(const gfx::Size& size) = 0;

  
  
  virtual void SetBounds(const gfx::Rect& rect) = 0;

  
  virtual gfx::Vector2dF GetLastScrollOffset() const = 0;

  
  
  virtual gfx::NativeView GetNativeView() const = 0;
  virtual gfx::NativeViewId GetNativeViewId() const = 0;
  virtual gfx::NativeViewAccessible GetNativeViewAccessible() = 0;

  
  
  
  
  
  virtual ui::TextInputClient* GetTextInputClient() = 0;

  
  virtual void Focus() = 0;
  
  virtual bool HasFocus() const = 0;
  
  virtual bool IsSurfaceAvailableForCopy() const = 0;

  
  
  virtual void Show() = 0;
  virtual void Hide() = 0;

  
  virtual bool IsShowing() = 0;

  
  virtual gfx::Rect GetViewBounds() const = 0;

  
  virtual bool IsShowingContextMenu() const = 0;

  
  virtual void SetShowingContextMenu(bool showing) = 0;

  
  virtual base::string16 GetSelectedText() const = 0;

  
  
  virtual void SetBackgroundOpaque(bool opaque) = 0;
  virtual bool GetBackgroundOpaque() = 0;

  
  virtual bool LockMouse() = 0;
  virtual void UnlockMouse() = 0;
  
  virtual bool IsMouseLocked() = 0;

  
  
  
  virtual gfx::Size GetVisibleViewportSize() const = 0;

  
  
  virtual void SetInsets(const gfx::Insets& insets) = 0;

  
  
  
  virtual void BeginFrameSubscription(
      scoped_ptr<RenderWidgetHostViewFrameSubscriber> subscriber) = 0;

  
  
  virtual void EndFrameSubscription() = 0;

#if defined(OS_MACOSX)
  
  virtual void SetActive(bool active) = 0;

  
  
  
  
  virtual void SetTakesFocusOnlyOnMouseDown(bool flag) = 0;

  
  
  
  
  
  
  virtual void SetWindowVisibility(bool visible) = 0;

  
  virtual void WindowFrameChanged() = 0;

  
  virtual void ShowDefinitionForSelection() = 0;

  
  virtual bool SupportsSpeech() const = 0;
  
  virtual void SpeakSelection() = 0;
  
  virtual bool IsSpeaking() const = 0;
  
  virtual void StopSpeaking() = 0;
#endif  
};

}  

#endif  
