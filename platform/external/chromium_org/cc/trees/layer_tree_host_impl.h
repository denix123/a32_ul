// Copyright 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_TREES_LAYER_TREE_HOST_IMPL_H_
#define CC_TREES_LAYER_TREE_HOST_IMPL_H_

#include <list>
#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "cc/animation/animation_events.h"
#include "cc/animation/animation_registrar.h"
#include "cc/animation/scrollbar_animation_controller.h"
#include "cc/base/cc_export.h"
#include "cc/debug/micro_benchmark_controller_impl.h"
#include "cc/input/input_handler.h"
#include "cc/input/layer_scroll_offset_delegate.h"
#include "cc/input/top_controls_manager_client.h"
#include "cc/layers/layer_lists.h"
#include "cc/layers/render_pass_sink.h"
#include "cc/output/begin_frame_args.h"
#include "cc/output/managed_memory_policy.h"
#include "cc/output/output_surface_client.h"
#include "cc/output/renderer.h"
#include "cc/quads/render_pass.h"
#include "cc/resources/resource_provider.h"
#include "cc/resources/tile_manager.h"
#include "cc/scheduler/draw_result.h"
#include "skia/ext/refptr.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/gfx/rect.h"

namespace cc {

class CompletionEvent;
class CompositorFrameMetadata;
class DebugRectHistory;
class EvictionTilePriorityQueue;
class FrameRateCounter;
class LayerImpl;
class LayerTreeHostImplTimeSourceAdapter;
class LayerTreeImpl;
class MemoryHistory;
class PageScaleAnimation;
class PaintTimeCounter;
class PictureLayerImpl;
class RasterTilePriorityQueue;
class RasterWorkerPool;
class RenderPassDrawQuad;
class RenderingStatsInstrumentation;
class ResourcePool;
class ScrollbarLayerImplBase;
class TextureMailboxDeleter;
class TopControlsManager;
class UIResourceBitmap;
class UIResourceRequest;
struct RendererCapabilitiesImpl;

class LayerTreeHostImplClient {
 public:
  virtual void UpdateRendererCapabilitiesOnImplThread() = 0;
  virtual void DidLoseOutputSurfaceOnImplThread() = 0;
  virtual void CommitVSyncParameters(base::TimeTicks timebase,
                                     base::TimeDelta interval) = 0;
  virtual void SetEstimatedParentDrawTime(base::TimeDelta draw_time) = 0;
  virtual void SetMaxSwapsPendingOnImplThread(int max) = 0;
  virtual void DidSwapBuffersOnImplThread() = 0;
  virtual void DidSwapBuffersCompleteOnImplThread() = 0;
  virtual void BeginFrame(const BeginFrameArgs& args) = 0;
  virtual void OnCanDrawStateChanged(bool can_draw) = 0;
  virtual void NotifyReadyToActivate() = 0;
  
  
  
  virtual void SetNeedsRedrawOnImplThread() = 0;
  virtual void SetNeedsRedrawRectOnImplThread(const gfx::Rect& damage_rect) = 0;
  virtual void SetNeedsAnimateOnImplThread() = 0;
  virtual void DidInitializeVisibleTileOnImplThread() = 0;
  virtual void SetNeedsCommitOnImplThread() = 0;
  virtual void SetNeedsManageTilesOnImplThread() = 0;
  virtual void PostAnimationEventsToMainThreadOnImplThread(
      scoped_ptr<AnimationEventsVector> events) = 0;
  
  virtual bool ReduceContentsTextureMemoryOnImplThread(
      size_t limit_bytes,
      int priority_cutoff) = 0;
  virtual bool IsInsideDraw() = 0;
  virtual void RenewTreePriority() = 0;
  virtual void PostDelayedScrollbarFadeOnImplThread(
      const base::Closure& start_fade,
      base::TimeDelta delay) = 0;
  virtual void DidActivateSyncTree() = 0;
  virtual void DidManageTiles() = 0;

 protected:
  virtual ~LayerTreeHostImplClient() {}
};

class CC_EXPORT LayerTreeHostImpl
    : public InputHandler,
      public RendererClient,
      public TileManagerClient,
      public OutputSurfaceClient,
      public TopControlsManagerClient,
      public ScrollbarAnimationControllerClient,
      public base::SupportsWeakPtr<LayerTreeHostImpl> {
 public:
  static scoped_ptr<LayerTreeHostImpl> Create(
      const LayerTreeSettings& settings,
      LayerTreeHostImplClient* client,
      Proxy* proxy,
      RenderingStatsInstrumentation* rendering_stats_instrumentation,
      SharedBitmapManager* manager,
      int id);
  virtual ~LayerTreeHostImpl();

  
  virtual void BindToClient(InputHandlerClient* client) OVERRIDE;
  virtual InputHandler::ScrollStatus ScrollBegin(
      const gfx::Point& viewport_point,
      InputHandler::ScrollInputType type) OVERRIDE;
  virtual InputHandler::ScrollStatus ScrollAnimated(
      const gfx::Point& viewport_point,
      const gfx::Vector2dF& scroll_delta) OVERRIDE;
  virtual bool ScrollBy(const gfx::Point& viewport_point,
                        const gfx::Vector2dF& scroll_delta) OVERRIDE;
  virtual bool ScrollVerticallyByPage(const gfx::Point& viewport_point,
                                      ScrollDirection direction) OVERRIDE;
  virtual void SetRootLayerScrollOffsetDelegate(
      LayerScrollOffsetDelegate* root_layer_scroll_offset_delegate) OVERRIDE;
  virtual void OnRootLayerDelegatedScrollOffsetChanged() OVERRIDE;
  virtual void ScrollEnd() OVERRIDE;
  virtual InputHandler::ScrollStatus FlingScrollBegin() OVERRIDE;
  virtual void MouseMoveAt(const gfx::Point& viewport_point) OVERRIDE;
  virtual void PinchGestureBegin() OVERRIDE;
  virtual void PinchGestureUpdate(float magnify_delta,
                                  const gfx::Point& anchor) OVERRIDE;
  virtual void PinchGestureEnd() OVERRIDE;
  virtual void SetNeedsAnimate() OVERRIDE;
  virtual bool IsCurrentlyScrollingLayerAt(
      const gfx::Point& viewport_point,
      InputHandler::ScrollInputType type) OVERRIDE;
  virtual bool HaveTouchEventHandlersAt(
      const gfx::Point& viewport_port) OVERRIDE;
  virtual scoped_ptr<SwapPromiseMonitor> CreateLatencyInfoSwapPromiseMonitor(
      ui::LatencyInfo* latency) OVERRIDE;

  
  virtual void SetControlsTopOffset(float offset) OVERRIDE;
  virtual float ControlsTopOffset() const OVERRIDE;
  virtual void DidChangeTopControlsPosition() OVERRIDE;
  virtual bool HaveRootScrollLayer() const OVERRIDE;

  struct CC_EXPORT FrameData : public RenderPassSink {
    FrameData();
    virtual ~FrameData();
    void AsValueInto(base::debug::TracedValue* value) const;

    std::vector<gfx::Rect> occluding_screen_space_rects;
    std::vector<gfx::Rect> non_occluding_screen_space_rects;
    RenderPassList render_passes;
    RenderPassIdHashMap render_passes_by_id;
    const LayerImplList* render_surface_layer_list;
    LayerImplList will_draw_layers;
    bool contains_incomplete_tile;
    bool has_no_damage;

    
    virtual void AppendRenderPass(scoped_ptr<RenderPass> render_pass) OVERRIDE;
  };

  virtual void BeginMainFrameAborted(bool did_handle);
  virtual void BeginCommit();
  virtual void CommitComplete();
  virtual void Animate(base::TimeTicks monotonic_time);
  virtual void UpdateAnimationState(bool start_ready_animations);
  void ActivateAnimations();
  void MainThreadHasStoppedFlinging();
  void UpdateBackgroundAnimateTicking(bool should_background_tick);
  void DidAnimateScrollOffset();
  void SetViewportDamage(const gfx::Rect& damage_rect);

  virtual void ManageTiles();

  
  
  
  
  virtual DrawResult PrepareToDraw(FrameData* frame);
  virtual void DrawLayers(FrameData* frame, base::TimeTicks frame_begin_time);
  
  void DidDrawAllLayers(const FrameData& frame);

  const LayerTreeSettings& settings() const { return settings_; }

  
  void EvictTexturesForTesting();

  
  
  
  virtual void BlockNotifyReadyToActivateForTesting(bool block);

  
  void DidInitializeVisibleTileForTesting();

  
  void ResetTreesForTesting();
  void ResetRecycleTreeForTesting();

  DrawMode GetDrawMode() const;

  
  
  gfx::Size DrawViewportSize() const;

  
  const gfx::Rect ViewportRectForTilePriority() const;

  
  virtual void SetFullRootLayerDamage() OVERRIDE;

  
  virtual const std::vector<PictureLayerImpl*>& GetPictureLayers()
      const OVERRIDE;
  virtual void NotifyReadyToActivate() OVERRIDE;
  virtual void NotifyTileStateChanged(const Tile* tile) OVERRIDE;
  virtual void BuildRasterQueue(RasterTilePriorityQueue* queue,
                                TreePriority tree_priority) OVERRIDE;
  virtual void BuildEvictionQueue(EvictionTilePriorityQueue* queue,
                                  TreePriority tree_priority) OVERRIDE;

  
  virtual void PostDelayedScrollbarFade(const base::Closure& start_fade,
                                        base::TimeDelta delay) OVERRIDE;
  virtual void SetNeedsScrollbarAnimationFrame() OVERRIDE;

  
  virtual void DeferredInitialize() OVERRIDE;
  virtual void ReleaseGL() OVERRIDE;
  virtual void CommitVSyncParameters(base::TimeTicks timebase,
                                     base::TimeDelta interval) OVERRIDE;
  virtual void SetNeedsRedrawRect(const gfx::Rect& rect) OVERRIDE;
  virtual void BeginFrame(const BeginFrameArgs& args) OVERRIDE;

  virtual void SetExternalDrawConstraints(
      const gfx::Transform& transform,
      const gfx::Rect& viewport,
      const gfx::Rect& clip,
      const gfx::Rect& viewport_rect_for_tile_priority,
      const gfx::Transform& transform_for_tile_priority,
      bool resourceless_software_draw) OVERRIDE;
  virtual void DidLoseOutputSurface() OVERRIDE;
  virtual void DidSwapBuffers() OVERRIDE;
  virtual void DidSwapBuffersComplete() OVERRIDE;
  virtual void ReclaimResources(const CompositorFrameAck* ack) OVERRIDE;
  virtual void SetMemoryPolicy(const ManagedMemoryPolicy& policy) OVERRIDE;
  virtual void SetTreeActivationCallback(const base::Closure& callback)
      OVERRIDE;

  
  void OnCanDrawStateChangedForTree();

  
  int id() const { return id_; }
  bool CanDraw() const;
  OutputSurface* output_surface() const { return output_surface_.get(); }

  std::string LayerTreeAsJson() const;

  void FinishAllRendering();
  int SourceAnimationFrameNumber() const;

  virtual bool InitializeRenderer(scoped_ptr<OutputSurface> output_surface);
  TileManager* tile_manager() { return tile_manager_.get(); }
  void SetUseGpuRasterization(bool use_gpu);
  bool use_gpu_rasterization() const { return use_gpu_rasterization_; }
  bool create_low_res_tiling() const {
    return settings_.create_low_res_tiling && !use_gpu_rasterization_;
  }
  ResourcePool* resource_pool() { return resource_pool_.get(); }
  Renderer* renderer() { return renderer_.get(); }
  const RendererCapabilitiesImpl& GetRendererCapabilities() const;

  virtual bool SwapBuffers(const FrameData& frame);
  void SetNeedsBeginFrame(bool enable);
  virtual void WillBeginImplFrame(const BeginFrameArgs& args);
  void DidModifyTilePriorities();

  LayerTreeImpl* active_tree() { return active_tree_.get(); }
  const LayerTreeImpl* active_tree() const { return active_tree_.get(); }
  LayerTreeImpl* pending_tree() { return pending_tree_.get(); }
  const LayerTreeImpl* pending_tree() const { return pending_tree_.get(); }
  LayerTreeImpl* recycle_tree() { return recycle_tree_.get(); }
  const LayerTreeImpl* recycle_tree() const { return recycle_tree_.get(); }
  
  LayerTreeImpl* sync_tree() {
    return pending_tree_ ? pending_tree_.get() : active_tree_.get();
  }
  virtual void CreatePendingTree();
  virtual void UpdateVisibleTiles();
  virtual void ActivateSyncTree();

  
  LayerImpl* RootLayer() const;
  LayerImpl* InnerViewportScrollLayer() const;
  LayerImpl* OuterViewportScrollLayer() const;
  LayerImpl* CurrentlyScrollingLayer() const;

  int scroll_layer_id_when_mouse_over_scrollbar() const {
    return scroll_layer_id_when_mouse_over_scrollbar_;
  }
  bool scroll_affects_scroll_handler() const {
    return scroll_affects_scroll_handler_;
  }
  void QueueSwapPromiseForMainThreadScrollUpdate(
      scoped_ptr<SwapPromise> swap_promise);

  bool IsActivelyScrolling() const;

  virtual void SetVisible(bool visible);
  bool visible() const { return visible_; }

  void SetNeedsCommit() { client_->SetNeedsCommitOnImplThread(); }
  void SetNeedsRedraw();

  ManagedMemoryPolicy ActualManagedMemoryPolicy() const;

  size_t memory_allocation_limit_bytes() const;
  int memory_allocation_priority_cutoff() const;

  void SetViewportSize(const gfx::Size& device_viewport_size);
  gfx::Size device_viewport_size() const { return device_viewport_size_; }

  void SetOverhangUIResource(UIResourceId overhang_ui_resource_id,
                             const gfx::Size& overhang_ui_resource_size);

  void SetDeviceScaleFactor(float device_scale_factor);
  float device_scale_factor() const { return device_scale_factor_; }

  const gfx::Transform& DrawTransform() const;

  scoped_ptr<ScrollAndScaleSet> ProcessScrollDeltas();

  bool needs_animate_layers() const {
    return !animation_registrar_->active_animation_controllers().empty();
  }

  void set_max_memory_needed_bytes(size_t bytes) {
    max_memory_needed_bytes_ = bytes;
  }

  FrameRateCounter* fps_counter() {
    return fps_counter_.get();
  }
  PaintTimeCounter* paint_time_counter() {
    return paint_time_counter_.get();
  }
  MemoryHistory* memory_history() {
    return memory_history_.get();
  }
  DebugRectHistory* debug_rect_history() {
    return debug_rect_history_.get();
  }
  ResourceProvider* resource_provider() {
    return resource_provider_.get();
  }
  TopControlsManager* top_controls_manager() {
    return top_controls_manager_.get();
  }
  const GlobalStateThatImpactsTilePriority& global_tile_state() {
    return global_tile_state_;
  }

  Proxy* proxy() const { return proxy_; }

  AnimationRegistrar* animation_registrar() const {
    return animation_registrar_.get();
  }

  void SetDebugState(const LayerTreeDebugState& new_debug_state);
  const LayerTreeDebugState& debug_state() const { return debug_state_; }

  class CC_EXPORT CullRenderPassesWithNoQuads {
   public:
    bool ShouldRemoveRenderPass(const RenderPassDrawQuad& quad,
                                const FrameData& frame) const;

    
    
    size_t RenderPassListBegin(const RenderPassList& list) const { return 0; }
    size_t RenderPassListEnd(const RenderPassList& list) const {
      return list.size();
    }
    size_t RenderPassListNext(size_t it) const { return it + 1; }
  };

  template <typename RenderPassCuller>
      static void RemoveRenderPasses(RenderPassCuller culler, FrameData* frame);

  gfx::Vector2dF accumulated_root_overscroll() const {
    return accumulated_root_overscroll_;
  }

  bool pinch_gesture_active() const { return pinch_gesture_active_; }

  void SetTreePriority(TreePriority priority);

  void UpdateCurrentBeginFrameArgs(const BeginFrameArgs& args);
  void ResetCurrentBeginFrameArgsForNextFrame();
  virtual BeginFrameArgs CurrentBeginFrameArgs() const;

  
  base::TimeDelta begin_impl_frame_interval() const {
    return begin_impl_frame_interval_;
  }

  void AsValueInto(base::debug::TracedValue* value) const {
    return AsValueWithFrameInto(NULL, value);
  }
  void AsValueWithFrameInto(FrameData* frame,
                            base::debug::TracedValue* value) const;
  scoped_refptr<base::debug::ConvertableToTraceFormat> AsValue() const;
  scoped_refptr<base::debug::ConvertableToTraceFormat> AsValueWithFrame(
      FrameData* frame) const;
  scoped_refptr<base::debug::ConvertableToTraceFormat> ActivationStateAsValue()
      const;
  void ActivationStateAsValueInto(base::debug::TracedValue* value) const;

  bool page_scale_animation_active() const { return !!page_scale_animation_; }

  virtual void CreateUIResource(UIResourceId uid,
                                const UIResourceBitmap& bitmap);
  
  virtual void DeleteUIResource(UIResourceId uid);
  void EvictAllUIResources();
  bool EvictedUIResourcesExist() const;

  virtual ResourceProvider::ResourceId ResourceIdForUIResource(
      UIResourceId uid) const;

  virtual bool IsUIResourceOpaque(UIResourceId uid) const;

  struct UIResourceData {
    ResourceProvider::ResourceId resource_id;
    gfx::Size size;
    bool opaque;
  };

  void ScheduleMicroBenchmark(scoped_ptr<MicroBenchmarkImpl> benchmark);

  CompositorFrameMetadata MakeCompositorFrameMetadata() const;
  
  
  
  gfx::Rect DeviceViewport() const;
  gfx::Rect DeviceClip() const;

  
  
  
  
  void InsertSwapPromiseMonitor(SwapPromiseMonitor* monitor);
  void RemoveSwapPromiseMonitor(SwapPromiseMonitor* monitor);

  void RegisterPictureLayerImpl(PictureLayerImpl* layer);
  void UnregisterPictureLayerImpl(PictureLayerImpl* layer);

  void GetPictureLayerImplPairs(
      std::vector<PictureLayerImpl::Pair>* layers) const;

  void SetTopControlsLayoutHeight(float height);

 protected:
  LayerTreeHostImpl(
      const LayerTreeSettings& settings,
      LayerTreeHostImplClient* client,
      Proxy* proxy,
      RenderingStatsInstrumentation* rendering_stats_instrumentation,
      SharedBitmapManager* manager,
      int id);

  void UpdateInnerViewportContainerSize();

  
  virtual void AnimateLayers(base::TimeTicks monotonic_time);

  
  virtual base::TimeDelta LowFrequencyAnimationInterval() const;

  const AnimationRegistrar::AnimationControllerMap&
      active_animation_controllers() const {
    return animation_registrar_->active_animation_controllers();
  }

  bool manage_tiles_needed() const { return tile_priorities_dirty_; }

  LayerTreeHostImplClient* client_;
  Proxy* proxy_;

 private:
  void CreateAndSetRenderer();
  void CreateAndSetTileManager();
  void DestroyTileManager();
  void ReleaseTreeResources();
  void EnforceZeroBudget(bool zero_budget);

  bool UsePendingTreeForSync() const;
  bool UseZeroCopyRasterizer() const;
  bool UseOneCopyRasterizer() const;

  void ScrollViewportBy(gfx::Vector2dF scroll_delta);
  void AnimatePageScale(base::TimeTicks monotonic_time);
  void AnimateScrollbars(base::TimeTicks monotonic_time);
  void AnimateTopControls(base::TimeTicks monotonic_time);

  gfx::Vector2dF ScrollLayerWithViewportSpaceDelta(
      LayerImpl* layer_impl,
      float scale_from_viewport_to_screen_space,
      const gfx::PointF& viewport_point,
      const gfx::Vector2dF& viewport_delta);

  void TrackDamageForAllSurfaces(
      LayerImpl* root_draw_layer,
      const LayerImplList& render_surface_layer_list);

  void UpdateTileManagerMemoryPolicy(const ManagedMemoryPolicy& policy);

  
  
  
  DrawResult CalculateRenderPasses(FrameData* frame);

  void ClearCurrentlyScrollingLayer();

  bool HandleMouseOverScrollbar(LayerImpl* layer_impl,
                                const gfx::PointF& device_viewport_point);

  void AnimateScrollbarsRecursive(LayerImpl* layer,
                                  base::TimeTicks time);

  LayerImpl* FindScrollLayerForDeviceViewportPoint(
      const gfx::PointF& device_viewport_point,
      InputHandler::ScrollInputType type,
      LayerImpl* layer_hit_by_point,
      bool* scroll_on_main_thread,
      bool* optional_has_ancestor_scroll_handler) const;
  float DeviceSpaceDistanceToLayer(const gfx::PointF& device_viewport_point,
                                   LayerImpl* layer_impl);
  void StartScrollbarFadeRecursive(LayerImpl* layer);
  void SetManagedMemoryPolicy(const ManagedMemoryPolicy& policy,
                              bool zero_budget);
  void EnforceManagedMemoryPolicy(const ManagedMemoryPolicy& policy);

  void DidInitializeVisibleTile();

  void MarkUIResourceNotEvicted(UIResourceId uid);

  void NotifySwapPromiseMonitorsOfSetNeedsRedraw();
  void NotifySwapPromiseMonitorsOfForwardingToMainThread();

  typedef base::hash_map<UIResourceId, UIResourceData>
      UIResourceMap;
  UIResourceMap ui_resource_map_;

  
  
  
  std::set<UIResourceId> evicted_ui_resources_;

  scoped_ptr<OutputSurface> output_surface_;

  
  
  scoped_ptr<ResourceProvider> resource_provider_;
  scoped_ptr<TileManager> tile_manager_;
  bool use_gpu_rasterization_;
  scoped_ptr<RasterWorkerPool> raster_worker_pool_;
  scoped_ptr<ResourcePool> resource_pool_;
  scoped_ptr<ResourcePool> staging_resource_pool_;
  scoped_ptr<Renderer> renderer_;

  GlobalStateThatImpactsTilePriority global_tile_state_;

  
  scoped_ptr<LayerTreeImpl> active_tree_;

  
  
  scoped_ptr<LayerTreeImpl> pending_tree_;

  
  
  scoped_ptr<LayerTreeImpl> recycle_tree_;

  InputHandlerClient* input_handler_client_;
  bool did_lock_scrolling_layer_;
  bool should_bubble_scrolls_;
  bool wheel_scrolling_;
  bool scroll_affects_scroll_handler_;
  int scroll_layer_id_when_mouse_over_scrollbar_;
  ScopedPtrVector<SwapPromise> swap_promises_for_main_thread_scroll_update_;

  bool tile_priorities_dirty_;

  
  LayerScrollOffsetDelegate* root_layer_scroll_offset_delegate_;
  LayerTreeSettings settings_;
  LayerTreeDebugState debug_state_;
  bool visible_;
  ManagedMemoryPolicy cached_managed_memory_policy_;

  gfx::Vector2dF accumulated_root_overscroll_;

  bool pinch_gesture_active_;
  bool pinch_gesture_end_should_clear_scrolling_layer_;
  gfx::Point previous_pinch_anchor_;

  scoped_ptr<TopControlsManager> top_controls_manager_;

  scoped_ptr<PageScaleAnimation> page_scale_animation_;

  
  scoped_ptr<LayerTreeHostImplTimeSourceAdapter> time_source_client_adapter_;

  scoped_ptr<FrameRateCounter> fps_counter_;
  scoped_ptr<PaintTimeCounter> paint_time_counter_;
  scoped_ptr<MemoryHistory> memory_history_;
  scoped_ptr<DebugRectHistory> debug_rect_history_;

  scoped_ptr<TextureMailboxDeleter> texture_mailbox_deleter_;

  
  
  size_t max_memory_needed_bytes_;

  bool zero_budget_;

  
  
  
  
  gfx::Size device_viewport_size_;

  
  
  float device_scale_factor_;

  
  UIResourceId overhang_ui_resource_id_;
  gfx::Size overhang_ui_resource_size_;

  
  
  
  
  
  
  
  gfx::Transform external_transform_;
  gfx::Rect external_viewport_;
  gfx::Rect external_clip_;
  gfx::Rect viewport_rect_for_tile_priority_;
  bool resourceless_software_draw_;

  gfx::Rect viewport_damage_rect_;

  BeginFrameArgs current_begin_frame_args_;

  
  base::TimeDelta begin_impl_frame_interval_;

  scoped_ptr<AnimationRegistrar> animation_registrar_;

  RenderingStatsInstrumentation* rendering_stats_instrumentation_;
  MicroBenchmarkControllerImpl micro_benchmark_controller_;

  bool need_to_update_visible_tiles_before_draw_;

  
  base::Closure tree_activation_callback_;

  SharedBitmapManager* shared_bitmap_manager_;
  int id_;

  std::set<SwapPromiseMonitor*> swap_promise_monitor_;

  std::vector<PictureLayerImpl*> picture_layers_;
  std::vector<PictureLayerImpl::Pair> picture_layer_pairs_;

  DISALLOW_COPY_AND_ASSIGN(LayerTreeHostImpl);
};

}  

#endif  
