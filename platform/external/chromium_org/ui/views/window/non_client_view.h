// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_WINDOW_NON_CLIENT_VIEW_H_
#define UI_VIEWS_WINDOW_NON_CLIENT_VIEW_H_

#include "ui/views/view.h"
#include "ui/views/view_targeter_delegate.h"

namespace gfx {
class Path;
}

namespace views {

class ClientView;

class VIEWS_EXPORT NonClientFrameView : public View,
                                        public ViewTargeterDelegate {
 public:
  
  static const char kViewClassName[];

  enum {
    
    
    kFrameShadowThickness = 1,

    
    
    kClientEdgeThickness = 1,
  };

  virtual ~NonClientFrameView();

  
  
  
  
  void SetInactiveRenderingDisabled(bool disable);

  
  
  bool ShouldPaintAsActive() const;

  
  
  
  
  int GetHTComponentForFrame(const gfx::Point& point,
                             int top_resize_border_height,
                             int resize_border_thickness,
                             int top_resize_corner_height,
                             int resize_corner_width,
                             bool can_resize);

  
  
  virtual gfx::Rect GetBoundsForClientView() const = 0;

  virtual gfx::Rect GetWindowBoundsForClientBounds(
      const gfx::Rect& client_bounds) const = 0;

  
  
  
  
  virtual int NonClientHitTest(const gfx::Point& point) = 0;
  virtual void GetWindowMask(const gfx::Size& size,
                             gfx::Path* window_mask) = 0;
  virtual void ResetWindowControls() = 0;
  virtual void UpdateWindowIcon() = 0;
  virtual void UpdateWindowTitle() = 0;
  virtual void SizeConstraintsChanged() = 0;

  
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;
  virtual const char* GetClassName() const OVERRIDE;

 protected:
  virtual void OnBoundsChanged(const gfx::Rect& previous_bounds) OVERRIDE;

  NonClientFrameView();

 private:
  
  virtual bool DoesIntersectRect(const View* target,
                                 const gfx::Rect& rect) const OVERRIDE;

  
  
  bool inactive_rendering_disabled_;
};

class VIEWS_EXPORT NonClientView : public View, public ViewTargeterDelegate {
 public:
  
  static const char kViewClassName[];

  NonClientView();
  virtual ~NonClientView();

  
  
  NonClientFrameView* frame_view() const { return frame_view_.get(); }

  
  void SetFrameView(NonClientFrameView* frame_view);

  
  void SetOverlayView(View* view);

  
  
  bool CanClose();

  
  void WindowClosing();

  
  
  void UpdateFrame();

  
  
  
  void SetInactiveRenderingDisabled(bool disable);

  
  
  gfx::Rect GetWindowBoundsForClientBounds(const gfx::Rect client_bounds) const;

  
  
  int NonClientHitTest(const gfx::Point& point);

  
  
  void GetWindowMask(const gfx::Size& size, gfx::Path* window_mask);

  
  
  
  
  
  void ResetWindowControls();

  
  void UpdateWindowIcon();

  
  
  void UpdateWindowTitle();

  
  void SizeConstraintsChanged();

  
  ClientView* client_view() const { return client_view_; }
  void set_client_view(ClientView* client_view) {
    client_view_ = client_view;
  }

  
  
  
  void LayoutFrameView();

  
  void SetAccessibleName(const base::string16& name);

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual gfx::Size GetMinimumSize() const OVERRIDE;
  virtual gfx::Size GetMaximumSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;
  virtual const char* GetClassName() const OVERRIDE;

  virtual views::View* GetTooltipHandlerForPoint(
      const gfx::Point& point) OVERRIDE;

 protected:
  
  virtual void ViewHierarchyChanged(
      const ViewHierarchyChangedDetails& details) OVERRIDE;

 private:
  
  virtual View* TargetForRect(View* root, const gfx::Rect& rect) OVERRIDE;

  
  
  
  ClientView* client_view_;

  
  
  
  scoped_ptr<NonClientFrameView> frame_view_;

  
  
  View* overlay_view_;

  
  base::string16 accessible_name_;

  DISALLOW_COPY_AND_ASSIGN(NonClientView);
};

}  

#endif  
