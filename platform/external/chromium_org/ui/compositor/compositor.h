// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_COMPOSITOR_COMPOSITOR_H_
#define UI_COMPOSITOR_COMPOSITOR_H_

#include <string>

#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/single_thread_task_runner.h"
#include "base/time/time.h"
#include "cc/trees/layer_tree_host_client.h"
#include "cc/trees/layer_tree_host_single_thread_client.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/compositor/compositor_animation_observer.h"
#include "ui/compositor/compositor_export.h"
#include "ui/compositor/compositor_observer.h"
#include "ui/compositor/layer_animator_collection.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/size.h"
#include "ui/gfx/vector2d.h"

class SkBitmap;

namespace base {
class MessageLoopProxy;
class RunLoop;
}

namespace cc {
class ContextProvider;
class Layer;
class LayerTreeDebugState;
class LayerTreeHost;
class SharedBitmapManager;
}

namespace gfx {
class Rect;
class Size;
}

namespace gpu {
struct Mailbox;
}

namespace ui {

class Compositor;
class CompositorVSyncManager;
class Layer;
class Reflector;
class Texture;
struct LatencyInfo;

class COMPOSITOR_EXPORT ContextFactory {
 public:
  virtual ~ContextFactory() {}

  
  
  
  virtual scoped_ptr<cc::OutputSurface> CreateOutputSurface(
      Compositor* compositor, bool software_fallback) = 0;

  
  
  virtual scoped_refptr<Reflector> CreateReflector(
      Compositor* mirrored_compositor,
      Layer* mirroring_layer) = 0;
  
  virtual void RemoveReflector(scoped_refptr<Reflector> reflector) = 0;

  
  
  virtual scoped_refptr<cc::ContextProvider>
      SharedMainThreadContextProvider() = 0;

  
  virtual void RemoveCompositor(Compositor* compositor) = 0;

  
  
  virtual bool DoesCreateTestContexts() = 0;

  
  virtual cc::SharedBitmapManager* GetSharedBitmapManager() = 0;

  
  
  virtual base::MessageLoopProxy* GetCompositorMessageLoop() = 0;
};

class COMPOSITOR_EXPORT CompositorLock
    : public base::RefCounted<CompositorLock>,
      public base::SupportsWeakPtr<CompositorLock> {
 private:
  friend class base::RefCounted<CompositorLock>;
  friend class Compositor;

  explicit CompositorLock(Compositor* compositor);
  ~CompositorLock();

  void CancelLock();

  Compositor* compositor_;
  DISALLOW_COPY_AND_ASSIGN(CompositorLock);
};

class COMPOSITOR_EXPORT Compositor
    : NON_EXPORTED_BASE(public cc::LayerTreeHostClient),
      NON_EXPORTED_BASE(public cc::LayerTreeHostSingleThreadClient) {
 public:
  Compositor(gfx::AcceleratedWidget widget,
             ui::ContextFactory* context_factory,
             scoped_refptr<base::SingleThreadTaskRunner> task_runner);
  virtual ~Compositor();

  ui::ContextFactory* context_factory() { return context_factory_; }

  
  void ScheduleDraw();

  
  
  
  
  
  const Layer* root_layer() const { return root_layer_; }
  Layer* root_layer() { return root_layer_; }
  void SetRootLayer(Layer* root_layer);

  
  
  
  void SetHostHasTransparentBackground(bool host_has_transparent_background);

  
  
  float device_scale_factor() const { return device_scale_factor_; }

  
  void Draw();

  
  
  
  void ScheduleFullRedraw();

  
  
  void ScheduleRedrawRect(const gfx::Rect& damage_rect);

  
  void FinishAllRendering();

  void SetLatencyInfo(const LatencyInfo& latency_info);

  
  void SetScaleAndSize(float scale, const gfx::Size& size_in_pixel);

  
  const gfx::Size& size() const { return size_; }

  
  
  void SetBackgroundColor(SkColor color);

  
  void SetVisible(bool visible);

  
  gfx::AcceleratedWidget widget() const { return widget_; }

  
  scoped_refptr<CompositorVSyncManager> vsync_manager() const;

  
  
  scoped_refptr<base::SingleThreadTaskRunner> task_runner() const {
    return task_runner_;
  }

  
  
  void AddObserver(CompositorObserver* observer);
  void RemoveObserver(CompositorObserver* observer);
  bool HasObserver(CompositorObserver* observer);

  void AddAnimationObserver(CompositorAnimationObserver* observer);
  void RemoveAnimationObserver(CompositorAnimationObserver* observer);
  bool HasAnimationObserver(CompositorAnimationObserver* observer);

  
  
  scoped_refptr<CompositorLock> GetCompositorLock();

  
  

  
  void OnSwapBuffersPosted();

  
  void OnSwapBuffersComplete();

  
  void OnSwapBuffersAborted();

  
  virtual void WillBeginMainFrame(int frame_id) OVERRIDE {}
  virtual void DidBeginMainFrame() OVERRIDE {}
  virtual void BeginMainFrame(const cc::BeginFrameArgs& args) OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual void ApplyViewportDeltas(
      const gfx::Vector2d& scroll_delta,
      float page_scale,
      float top_controls_delta) OVERRIDE {}
  virtual void RequestNewOutputSurface(bool fallback) OVERRIDE;
  virtual void DidInitializeOutputSurface() OVERRIDE {}
  virtual void WillCommit() OVERRIDE {}
  virtual void DidCommit() OVERRIDE;
  virtual void DidCommitAndDrawFrame() OVERRIDE;
  virtual void DidCompleteSwapBuffers() OVERRIDE;

  
  virtual void ScheduleComposite() OVERRIDE;
  virtual void ScheduleAnimation() OVERRIDE;
  virtual void DidPostSwapBuffers() OVERRIDE;
  virtual void DidAbortSwapBuffers() OVERRIDE;

  int last_started_frame() { return last_started_frame_; }
  int last_ended_frame() { return last_ended_frame_; }

  bool IsLocked() { return compositor_lock_ != NULL; }

  const cc::LayerTreeDebugState& GetLayerTreeDebugState() const;
  void SetLayerTreeDebugState(const cc::LayerTreeDebugState& debug_state);

  LayerAnimatorCollection* layer_animator_collection() {
    return &layer_animator_collection_;
  }

 private:
  friend class base::RefCounted<Compositor>;
  friend class CompositorLock;

  
  void UnlockCompositor();

  
  void CancelCompositorLock();

  
  void NotifyEnd();

  gfx::Size size_;

  ui::ContextFactory* context_factory_;

  
  Layer* root_layer_;

  ObserverList<CompositorObserver> observer_list_;
  ObserverList<CompositorAnimationObserver> animation_observer_list_;

  gfx::AcceleratedWidget widget_;
  scoped_refptr<cc::Layer> root_web_layer_;
  scoped_ptr<cc::LayerTreeHost> host_;
  scoped_refptr<base::MessageLoopProxy> compositor_thread_loop_;
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  
  scoped_refptr<CompositorVSyncManager> vsync_manager_;

  
  
  float device_scale_factor_;

  int last_started_frame_;
  int last_ended_frame_;

  bool disable_schedule_composite_;

  CompositorLock* compositor_lock_;

  
  bool defer_draw_scheduling_;

  
  bool waiting_on_compositing_end_;
  bool draw_on_compositing_end_;
  enum SwapState { SWAP_NONE, SWAP_POSTED, SWAP_COMPLETED };
  SwapState swap_state_;

  LayerAnimatorCollection layer_animator_collection_;

  base::WeakPtrFactory<Compositor> schedule_draw_factory_;

  DISALLOW_COPY_AND_ASSIGN(Compositor);
};

}  

#endif  
