// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_COMPOSITOR_DELEGATED_FRAME_HOST_H_
#define CONTENT_BROWSER_COMPOSITOR_DELEGATED_FRAME_HOST_H_

#include "cc/layers/delegated_frame_provider.h"
#include "cc/layers/delegated_frame_resource_collection.h"
#include "cc/output/copy_output_result.h"
#include "cc/surfaces/surface_factory_client.h"
#include "content/browser/compositor/image_transport_factory.h"
#include "content/browser/compositor/owned_mailbox.h"
#include "content/browser/renderer_host/delegated_frame_evictor.h"
#include "content/browser/renderer_host/dip_util.h"
#include "content/browser/renderer_host/render_widget_host_impl.h"
#include "content/browser/renderer_host/render_widget_host_view_base.h"
#include "content/public/browser/render_process_host.h"
#include "ui/compositor/compositor.h"
#include "ui/compositor/compositor_observer.h"
#include "ui/compositor/compositor_vsync_manager.h"
#include "ui/compositor/layer.h"
#include "ui/compositor/layer_owner_delegate.h"
#include "ui/gfx/rect_conversions.h"

namespace cc {
class SurfaceFactory;
}

namespace media {
class VideoFrame;
}

namespace content {

class DelegatedFrameHost;
class ReadbackYUVInterface;
class RenderWidgetHostViewFrameSubscriber;
class RenderWidgetHostImpl;
class ResizeLock;

class CONTENT_EXPORT DelegatedFrameHostClient {
 public:
  virtual ui::Compositor* GetCompositor() const = 0;
  virtual ui::Layer* GetLayer() = 0;
  virtual RenderWidgetHostImpl* GetHost() = 0;
  virtual bool IsVisible() = 0;
  virtual scoped_ptr<ResizeLock> CreateResizeLock(
      bool defer_compositor_lock) = 0;
  virtual gfx::Size DesiredFrameSize() = 0;

  
  
  virtual float CurrentDeviceScaleFactor() = 0;
  virtual gfx::Size ConvertViewSizeToPixel(const gfx::Size& size) = 0;

  
  
  
  
  virtual DelegatedFrameHost* GetDelegatedFrameHost() const = 0;
  virtual bool ShouldCreateResizeLock();
  virtual void RequestCopyOfOutput(scoped_ptr<cc::CopyOutputRequest> request);
};

class CONTENT_EXPORT DelegatedFrameHost
    : public ui::CompositorObserver,
      public ui::CompositorVSyncManager::Observer,
      public ui::LayerOwnerDelegate,
      public ImageTransportFactoryObserver,
      public DelegatedFrameEvictorClient,
      public cc::DelegatedFrameResourceCollectionClient,
      public cc::SurfaceFactoryClient,
      public base::SupportsWeakPtr<DelegatedFrameHost> {
 public:
  DelegatedFrameHost(DelegatedFrameHostClient* client);
  virtual ~DelegatedFrameHost();

  bool CanCopyToBitmap() const;

  
  void SwapDelegatedFrame(
      uint32 output_surface_id,
      scoped_ptr<cc::DelegatedFrameData> frame_data,
      float frame_device_scale_factor,
      const std::vector<ui::LatencyInfo>& latency_info);
  void WasHidden();
  void WasShown(const ui::LatencyInfo& latency_info);
  void WasResized();
  bool HasSavedFrame();
  gfx::Size GetRequestedRendererSize() const;
  void AddedToWindow();
  void RemovingFromWindow();
  void CopyFromCompositingSurface(const gfx::Rect& src_subrect,
                                  const gfx::Size& output_size,
                                  CopyFromCompositingSurfaceCallback& callback,
                                  const SkColorType color_type);
  void CopyFromCompositingSurfaceToVideoFrame(
      const gfx::Rect& src_subrect,
      const scoped_refptr<media::VideoFrame>& target,
      const base::Callback<void(bool)>& callback);
  bool CanCopyToVideoFrame() const;
  bool CanSubscribeFrame() const;
  void BeginFrameSubscription(
      scoped_ptr<RenderWidgetHostViewFrameSubscriber> subscriber);
  void EndFrameSubscription();
  bool HasFrameSubscriber() const { return frame_subscriber_; }

  
  cc::DelegatedFrameProvider* FrameProviderForTesting() const {
    return frame_provider_.get();
  }
  void OnCompositingDidCommitForTesting(ui::Compositor* compositor) {
    OnCompositingDidCommit(compositor);
  }
  bool ShouldCreateResizeLockForTesting() { return ShouldCreateResizeLock(); }
  bool ReleasedFrontLockActiveForTesting() const {
    return !!released_front_lock_.get();
  }

 private:
  friend class DelegatedFrameHostClient;
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest,
                           SkippedDelegatedFrames);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest,
                           DiscardDelegatedFramesWithLocking);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraCopyRequestTest,
                           DestroyedAfterCopyRequest);

  RenderWidgetHostViewFrameSubscriber* frame_subscriber() const {
    return frame_subscriber_.get();
  }
  bool ShouldCreateResizeLock();
  void RequestCopyOfOutput(scoped_ptr<cc::CopyOutputRequest> request);

  void LockResources();
  void UnlockResources();

  
  virtual void OnCompositingDidCommit(ui::Compositor* compositor) OVERRIDE;
  virtual void OnCompositingStarted(ui::Compositor* compositor,
                                    base::TimeTicks start_time) OVERRIDE;
  virtual void OnCompositingEnded(ui::Compositor* compositor) OVERRIDE;
  virtual void OnCompositingAborted(ui::Compositor* compositor) OVERRIDE;
  virtual void OnCompositingLockStateChanged(
      ui::Compositor* compositor) OVERRIDE;

  
  virtual void OnUpdateVSyncParameters(base::TimeTicks timebase,
                                       base::TimeDelta interval) OVERRIDE;

  
  virtual void OnLayerRecreated(ui::Layer* old_layer,
                                ui::Layer* new_layer) OVERRIDE;

  
  virtual void OnLostResources() OVERRIDE;

  bool ShouldSkipFrame(gfx::Size size_in_dip) const;

  
  
  void MaybeCreateResizeLock();

  
  void CheckResizeLock();

  
  void RunOnCommitCallbacks();

  
  void AddOnCommitCallbackAndDisableLocks(const base::Closure& callback);

  
  
  static void CopyFromCompositingSurfaceHasResult(
      const gfx::Size& dst_size_in_pixel,
      const SkColorType color_type,
      const base::Callback<void(bool, const SkBitmap&)>& callback,
      scoped_ptr<cc::CopyOutputResult> result);
  static void PrepareTextureCopyOutputResult(
      const gfx::Size& dst_size_in_pixel,
      const SkColorType color_type,
      const base::Callback<void(bool, const SkBitmap&)>& callback,
      scoped_ptr<cc::CopyOutputResult> result);
  static void PrepareBitmapCopyOutputResult(
      const gfx::Size& dst_size_in_pixel,
      const SkColorType color_type,
      const base::Callback<void(bool, const SkBitmap&)>& callback,
      scoped_ptr<cc::CopyOutputResult> result);
  static void CopyFromCompositingSurfaceHasResultForVideo(
      base::WeakPtr<DelegatedFrameHost> rwhva,
      scoped_refptr<OwnedMailbox> subscriber_texture,
      scoped_refptr<media::VideoFrame> video_frame,
      const base::Callback<void(bool)>& callback,
      scoped_ptr<cc::CopyOutputResult> result);
  static void CopyFromCompositingSurfaceFinishedForVideo(
      base::WeakPtr<DelegatedFrameHost> rwhva,
      const base::Callback<void(bool)>& callback,
      scoped_refptr<OwnedMailbox> subscriber_texture,
      scoped_ptr<cc::SingleReleaseCallback> release_callback,
      bool result);
  static void ReturnSubscriberTexture(
      base::WeakPtr<DelegatedFrameHost> rwhva,
      scoped_refptr<OwnedMailbox> subscriber_texture,
      uint32 sync_point);

  void SendDelegatedFrameAck(uint32 output_surface_id);
  void SendReturnedDelegatedResources(uint32 output_surface_id);

  
  virtual void EvictDelegatedFrame() OVERRIDE;

  
  virtual void UnusedResourcesAreAvailable() OVERRIDE;

  
  virtual void ReturnResources(
      const cc::ReturnedResourceArray& resources) OVERRIDE;

  void DidReceiveFrameFromRenderer(const gfx::Rect& damage_rect);

  DelegatedFrameHostClient* client_;

  
  
  bool use_surfaces_;

  std::vector<base::Closure> on_compositing_did_commit_callbacks_;

  
  scoped_refptr<ui::CompositorVSyncManager> vsync_manager_;

  
  
  base::TimeTicks vsync_timebase_;
  base::TimeDelta vsync_interval_;

  
  
  
  uint32 last_output_surface_id_;

  
  
  int pending_delegated_ack_count_;

  
  
  bool skipped_frames_;
  std::vector<ui::LatencyInfo> skipped_latency_info_list_;

  
  
  
  scoped_refptr<cc::DelegatedFrameResourceCollection> resource_collection_;

  
  scoped_refptr<cc::DelegatedFrameProvider> frame_provider_;

  
  scoped_ptr<cc::SurfaceIdAllocator> id_allocator_;
  scoped_ptr<cc::SurfaceFactory> surface_factory_;
  cc::SurfaceId surface_id_;
  gfx::Size current_surface_size_;
  cc::ReturnedResourceArray surface_returned_resources_;

  
  
  
  
  
  
  scoped_ptr<ResizeLock> resize_lock_;

  
  gfx::Size current_frame_size_in_dip_;

  
  scoped_refptr<ui::CompositorLock> released_front_lock_;

  enum CanLockCompositorState {
    YES_CAN_LOCK,
    
    YES_DID_LOCK,
    
    NO_PENDING_RENDERER_FRAME,
    
    NO_PENDING_COMMIT,
  };
  CanLockCompositorState can_lock_compositor_;

  base::TimeTicks last_draw_ended_;

  
  scoped_ptr<RenderWidgetHostViewFrameSubscriber> frame_subscriber_;
  std::vector<scoped_refptr<OwnedMailbox> > idle_frame_subscriber_textures_;

  
  scoped_ptr<content::ReadbackYUVInterface>
      yuv_readback_pipeline_;

  scoped_ptr<DelegatedFrameEvictor> delegated_frame_evictor_;
};

}  

#endif  
