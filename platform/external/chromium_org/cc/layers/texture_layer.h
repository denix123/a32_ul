// Copyright 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_LAYERS_TEXTURE_LAYER_H_
#define CC_LAYERS_TEXTURE_LAYER_H_

#include <string>

#include "base/callback.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread_checker.h"
#include "cc/base/cc_export.h"
#include "cc/layers/layer.h"
#include "cc/resources/texture_mailbox.h"

namespace cc {
class BlockingTaskRunner;
class SingleReleaseCallback;
class SingleReleaseCallbackImpl;
class TextureLayerClient;

class CC_EXPORT TextureLayer : public Layer {
 public:
  class CC_EXPORT TextureMailboxHolder
      : public base::RefCountedThreadSafe<TextureMailboxHolder> {
   public:
    class CC_EXPORT MainThreadReference {
     public:
      explicit MainThreadReference(TextureMailboxHolder* holder);
      ~MainThreadReference();
      TextureMailboxHolder* holder() { return holder_.get(); }

     private:
      scoped_refptr<TextureMailboxHolder> holder_;
      DISALLOW_COPY_AND_ASSIGN(MainThreadReference);
    };

    const TextureMailbox& mailbox() const { return mailbox_; }
    void Return(uint32 sync_point, bool is_lost);

    
    
    scoped_ptr<SingleReleaseCallbackImpl> GetCallbackForImplThread();

   protected:
    friend class TextureLayer;

    
    static scoped_ptr<MainThreadReference> Create(
        const TextureMailbox& mailbox,
        scoped_ptr<SingleReleaseCallback> release_callback);
    virtual ~TextureMailboxHolder();

   private:
    friend class base::RefCountedThreadSafe<TextureMailboxHolder>;
    friend class MainThreadReference;
    explicit TextureMailboxHolder(
        const TextureMailbox& mailbox,
        scoped_ptr<SingleReleaseCallback> release_callback);

    void InternalAddRef();
    void InternalRelease();
    void ReturnAndReleaseOnImplThread(
        uint32 sync_point,
        bool is_lost,
        BlockingTaskRunner* main_thread_task_runner);

    
    
    unsigned internal_references_;
    TextureMailbox mailbox_;
    scoped_ptr<SingleReleaseCallback> release_callback_;

    
    
    
    
    base::Lock arguments_lock_;
    uint32 sync_point_;
    bool is_lost_;
    base::ThreadChecker main_thread_checker_;
    DISALLOW_COPY_AND_ASSIGN(TextureMailboxHolder);
  };

  
  static scoped_refptr<TextureLayer> CreateForMailbox(
      TextureLayerClient* client);

  
  void ClearClient();

  
  void ClearTexture();

  virtual scoped_ptr<LayerImpl> CreateLayerImpl(LayerTreeImpl* tree_impl)
      OVERRIDE;

  
  
  void SetFlipped(bool flipped);

  
  void SetUV(const gfx::PointF& top_left, const gfx::PointF& bottom_right);

  
  
  void SetVertexOpacity(float bottom_left,
                        float top_left,
                        float top_right,
                        float bottom_right);

  
  
  void SetPremultipliedAlpha(bool premultiplied_alpha);

  
  
  void SetBlendBackgroundColor(bool blend);

  
  
  
  void SetRateLimitContext(bool rate_limit);

  
  void SetTextureMailbox(const TextureMailbox& mailbox,
                         scoped_ptr<SingleReleaseCallback> release_callback);

  
  
  
  
  void SetTextureMailboxWithoutReleaseCallback(const TextureMailbox& mailbox);

  virtual void SetNeedsDisplayRect(const gfx::RectF& dirty_rect) OVERRIDE;

  virtual void SetLayerTreeHost(LayerTreeHost* layer_tree_host) OVERRIDE;
  virtual bool Update(ResourceUpdateQueue* queue,
                      const OcclusionTracker<Layer>* occlusion) OVERRIDE;
  virtual void PushPropertiesTo(LayerImpl* layer) OVERRIDE;
  virtual SimpleEnclosedRegion VisibleContentOpaqueRegion() const OVERRIDE;

 protected:
  explicit TextureLayer(TextureLayerClient* client);
  virtual ~TextureLayer();
  virtual bool HasDrawableContent() const OVERRIDE;

 private:
  void SetTextureMailboxInternal(
      const TextureMailbox& mailbox,
      scoped_ptr<SingleReleaseCallback> release_callback,
      bool requires_commit,
      bool allow_mailbox_reuse);

  TextureLayerClient* client_;

  bool flipped_;
  gfx::PointF uv_top_left_;
  gfx::PointF uv_bottom_right_;
  
  float vertex_opacity_[4];
  bool premultiplied_alpha_;
  bool blend_background_color_;
  bool rate_limit_context_;

  scoped_ptr<TextureMailboxHolder::MainThreadReference> holder_ref_;
  bool needs_set_mailbox_;

  DISALLOW_COPY_AND_ASSIGN(TextureLayer);
};

}  
#endif  
