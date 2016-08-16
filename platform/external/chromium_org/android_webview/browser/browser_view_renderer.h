// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_BROWSER_BROWSER_VIEW_RENDERER_H_
#define ANDROID_WEBVIEW_BROWSER_BROWSER_VIEW_RENDERER_H_

#include "android_webview/browser/global_tile_manager.h"
#include "android_webview/browser/global_tile_manager_client.h"
#include "android_webview/browser/parent_compositor_draw_constraints.h"
#include "android_webview/browser/shared_renderer_state.h"
#include "base/android/scoped_java_ref.h"
#include "base/callback.h"
#include "base/cancelable_callback.h"
#include "base/values.h"
#include "content/public/browser/android/synchronous_compositor.h"
#include "content/public/browser/android/synchronous_compositor_client.h"
#include "skia/ext/refptr.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/vector2d_f.h"

class SkCanvas;
class SkPicture;
struct AwDrawGLInfo;
struct AwDrawSWFunctionTable;

namespace content {
class ContentViewCore;
struct SynchronousCompositorMemoryPolicy;
class WebContents;
}

namespace android_webview {

class BrowserViewRendererClient;

class BrowserViewRendererJavaHelper {
 public:
  static BrowserViewRendererJavaHelper* GetInstance();

  typedef base::Callback<bool(SkCanvas*)> RenderMethod;

  
  
  
  
  virtual bool RenderViaAuxilaryBitmapIfNeeded(
      jobject java_canvas,
      const gfx::Vector2d& scroll_correction,
      const gfx::Size& auxiliary_bitmap_size,
      RenderMethod render_source) = 0;

 protected:
  virtual ~BrowserViewRendererJavaHelper() {}
};

class BrowserViewRenderer : public content::SynchronousCompositorClient,
                            public GlobalTileManagerClient {
 public:
  static void CalculateTileMemoryPolicy(bool use_zero_copy);

  BrowserViewRenderer(
      BrowserViewRendererClient* client,
      SharedRendererState* shared_renderer_state,
      content::WebContents* web_contents,
      const scoped_refptr<base::SingleThreadTaskRunner>& ui_task_runner);

  virtual ~BrowserViewRenderer();

  
  
  
  
  
  
  
  bool OnDraw(jobject java_canvas,
              bool is_hardware_canvas,
              const gfx::Vector2d& scroll,
              const gfx::Rect& global_visible_rect);

  
  skia::RefPtr<SkPicture> CapturePicture(int width, int height);
  void EnableOnNewPicture(bool enabled);

  void ClearView();

  
  void SetIsPaused(bool paused);
  void SetViewVisibility(bool visible);
  void SetWindowVisibility(bool visible);
  void OnSizeChanged(int width, int height);
  void OnAttachedToWindow(int width, int height);
  void OnDetachedFromWindow();

  
  void SetDipScale(float dip_scale);

  
  void ScrollTo(gfx::Vector2d new_value);

  
  bool IsVisible() const;
  gfx::Rect GetScreenRect() const;
  bool attached_to_window() const { return attached_to_window_; }
  bool hardware_enabled() const { return hardware_enabled_; }
  void ReleaseHardware();

  
  
  
  void RequestMemoryPolicy(content::SynchronousCompositorMemoryPolicy& policy);

  void TrimMemory(const int level, const bool visible);

  
  virtual void DidInitializeCompositor(
      content::SynchronousCompositor* compositor) OVERRIDE;
  virtual void DidDestroyCompositor(content::SynchronousCompositor* compositor)
      OVERRIDE;
  virtual void SetContinuousInvalidate(bool invalidate) OVERRIDE;
  virtual void DidUpdateContent() OVERRIDE;
  virtual gfx::Vector2dF GetTotalRootLayerScrollOffset() OVERRIDE;
  virtual void UpdateRootLayerState(
      const gfx::Vector2dF& total_scroll_offset_dip,
      const gfx::Vector2dF& max_scroll_offset_dip,
      const gfx::SizeF& scrollable_size_dip,
      float page_scale_factor,
      float min_page_scale_factor,
      float max_page_scale_factor) OVERRIDE;
  virtual bool IsExternalFlingActive() const OVERRIDE;
  virtual void DidOverscroll(gfx::Vector2dF accumulated_overscroll,
                             gfx::Vector2dF latest_overscroll_delta,
                             gfx::Vector2dF current_fling_velocity) OVERRIDE;

  
  virtual content::SynchronousCompositorMemoryPolicy GetMemoryPolicy()
      const OVERRIDE;
  virtual void SetMemoryPolicy(
      content::SynchronousCompositorMemoryPolicy new_policy,
      bool effective_immediately) OVERRIDE;

  void UpdateParentDrawConstraints();
  void DidSkipCommitFrame();

 private:
  void SetTotalRootLayerScrollOffset(gfx::Vector2dF new_value_dip);
  
  
  
  
  
  void EnsureContinuousInvalidation(bool force_invalidate,
                                    bool skip_reschedule_tick);
  bool OnDrawSoftware(jobject java_canvas);
  bool CompositeSW(SkCanvas* canvas);
  void DidComposite();
  void DidSkipCompositeInDraw();
  scoped_ptr<base::Value> RootLayerStateAsValue(
      const gfx::Vector2dF& total_scroll_offset_dip,
      const gfx::SizeF& scrollable_size_dip);

  bool OnDrawHardware(jobject java_canvas);
  scoped_ptr<cc::CompositorFrame> CompositeHw();
  void ReturnUnusedResource(scoped_ptr<cc::CompositorFrame> frame);
  void ReturnResourceFromParent();

  
  
  
  
  void PostFallbackTick();
  void FallbackTickFired();

  
  
  
  void ForceFakeCompositeSW();

  void EnforceMemoryPolicyImmediately(
      content::SynchronousCompositorMemoryPolicy policy);

  gfx::Vector2d max_scroll_offset() const;

  content::SynchronousCompositorMemoryPolicy CalculateDesiredMemoryPolicy();
  
  
  std::string ToString(AwDrawGLInfo* draw_info) const;

  BrowserViewRendererClient* client_;
  SharedRendererState* shared_renderer_state_;
  content::WebContents* web_contents_;
  scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner_;

  content::SynchronousCompositor* compositor_;

  bool is_paused_;
  bool view_visible_;
  bool window_visible_;  
  bool attached_to_window_;
  bool hardware_enabled_;
  float dip_scale_;
  float page_scale_factor_;
  bool on_new_picture_enable_;
  bool clear_view_;

  gfx::Vector2d last_on_draw_scroll_offset_;
  gfx::Rect last_on_draw_global_visible_rect_;

  
  
  ParentCompositorDrawConstraints parent_draw_constraints_;

  
  
  
  
  bool compositor_needs_continuous_invalidate_;

  bool invalidate_after_composite_;

  
  bool block_invalidates_;

  base::CancelableClosure post_fallback_tick_;
  base::CancelableClosure fallback_tick_fired_;
  bool fallback_tick_pending_;

  int width_;
  int height_;

  
  gfx::Vector2dF scroll_offset_dip_;

  
  gfx::Vector2dF max_scroll_offset_dip_;

  
  
  
  gfx::Vector2dF overscroll_rounding_error_;

  GlobalTileManager::Key tile_manager_key_;
  content::SynchronousCompositorMemoryPolicy memory_policy_;

  DISALLOW_COPY_AND_ASSIGN(BrowserViewRenderer);
};

}  

#endif  
