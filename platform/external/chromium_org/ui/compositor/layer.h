// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_COMPOSITOR_LAYER_H_
#define UI_COMPOSITOR_LAYER_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/message_loop/message_loop.h"
#include "cc/animation/animation_events.h"
#include "cc/animation/layer_animation_event_observer.h"
#include "cc/base/scoped_ptr_vector.h"
#include "cc/layers/content_layer_client.h"
#include "cc/layers/layer_client.h"
#include "cc/layers/texture_layer_client.h"
#include "cc/resources/texture_mailbox.h"
#include "cc/surfaces/surface_id.h"
#include "third_party/skia/include/core/SkColor.h"
#include "third_party/skia/include/core/SkRegion.h"
#include "ui/compositor/compositor.h"
#include "ui/compositor/layer_animation_delegate.h"
#include "ui/compositor/layer_delegate.h"
#include "ui/compositor/layer_type.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/transform.h"

class SkCanvas;

namespace cc {
class ContentLayer;
class CopyOutputRequest;
class DelegatedFrameProvider;
class DelegatedRendererLayer;
class Layer;
class NinePatchLayer;
class ResourceUpdateQueue;
class SolidColorLayer;
class SurfaceLayer;
class TextureLayer;
struct ReturnedResource;
typedef std::vector<ReturnedResource> ReturnedResourceArray;
}

namespace ui {

class Compositor;
class LayerAnimator;
class LayerOwner;

class COMPOSITOR_EXPORT Layer
    : public LayerAnimationDelegate,
      NON_EXPORTED_BASE(public cc::ContentLayerClient),
      NON_EXPORTED_BASE(public cc::TextureLayerClient),
      NON_EXPORTED_BASE(public cc::LayerClient),
      NON_EXPORTED_BASE(public cc::LayerAnimationEventObserver) {
 public:
  Layer();
  explicit Layer(LayerType type);
  virtual ~Layer();

  static bool UsingPictureLayer();

  
  
  Compositor* GetCompositor();

  
  
  void SetCompositor(Compositor* compositor);

  LayerDelegate* delegate() { return delegate_; }
  void set_delegate(LayerDelegate* delegate) { delegate_ = delegate; }

  LayerOwner* owner() { return owner_; }

  
  void Add(Layer* child);

  
  void Remove(Layer* child);

  
  void StackAtTop(Layer* child);

  
  
  
  void StackAbove(Layer* child, Layer* other);

  
  void StackAtBottom(Layer* child);

  
  
  void StackBelow(Layer* child, Layer* other);

  
  const std::vector<Layer*>& children() const { return children_; }

  
  const Layer* parent() const { return parent_; }
  Layer* parent() { return parent_; }

  LayerType type() const { return type_; }

  
  bool Contains(const Layer* other) const;

  
  
  
  void SetAnimator(LayerAnimator* animator);

  
  
  LayerAnimator* GetAnimator();

  
  void SetTransform(const gfx::Transform& transform);
  gfx::Transform transform() const;

  
  
  gfx::Transform GetTargetTransform() const;

  
  void SetBounds(const gfx::Rect& bounds);
  const gfx::Rect& bounds() const { return bounds_; }

  
  
  void SetSubpixelPositionOffset(const gfx::Vector2dF offset);
  const gfx::Vector2dF& subpixel_position_offset() const {
    return subpixel_position_offset_;
  }

  
  
  gfx::Rect GetTargetBounds() const;

  
  
  void SetMasksToBounds(bool masks_to_bounds);
  bool GetMasksToBounds() const;

  
  
  float opacity() const;
  void SetOpacity(float opacity);

  
  
  float GetCombinedOpacity() const;

  
  
  int background_blur() const { return background_blur_radius_; }
  void SetBackgroundBlur(int blur_radius);

  
  
  
  float layer_saturation() const { return layer_saturation_; }
  void SetLayerSaturation(float saturation);

  
  
  
  float layer_brightness() const { return layer_brightness_; }
  void SetLayerBrightness(float brightness);

  
  
  float GetTargetBrightness() const;

  
  
  
  float layer_grayscale() const { return layer_grayscale_; }
  void SetLayerGrayscale(float grayscale);

  
  
  float GetTargetGrayscale() const;

  
  
  void SetBackgroundZoom(float zoom, int inset);

  
  SkRegion* alpha_shape() const { return alpha_shape_.get(); }
  void SetAlphaShape(scoped_ptr<SkRegion> region);

  
  bool layer_inverted() const { return layer_inverted_; }
  void SetLayerInverted(bool inverted);

  
  
  float GetTargetOpacity() const;

  
  
  
  
  
  void SetMaskLayer(Layer* layer_mask);
  Layer* layer_mask_layer() { return layer_mask_; }

  
  
  void SetVisible(bool visible);
  bool visible() const { return visible_; }

  
  
  bool GetTargetVisibility() const;

  
  
  bool IsDrawn() const;

  
  
  bool ShouldDraw() const;

  
  
  
  static void ConvertPointToLayer(const Layer* source,
                                  const Layer* target,
                                  gfx::Point* point);

  
  
  
  bool GetTargetTransformRelativeTo(const Layer* ancestor,
                                    gfx::Transform* transform) const;

  
  void SetFillsBoundsOpaquely(bool fills_bounds_opaquely);
  bool fills_bounds_opaquely() const { return fills_bounds_opaquely_; }

  
  
  void SetFillsBoundsCompletely(bool fills_bounds_completely);

  const std::string& name() const { return name_; }
  void set_name(const std::string& name) { name_ = name; }

  
  
  void SetTextureMailbox(const cc::TextureMailbox& mailbox,
                         scoped_ptr<cc::SingleReleaseCallback> release_callback,
                         gfx::Size texture_size_in_dip);
  void SetTextureSize(gfx::Size texture_size_in_dip);

  
  void SetShowDelegatedContent(cc::DelegatedFrameProvider* frame_provider,
                               gfx::Size frame_size_in_dip);

  
  void SetShowSurface(cc::SurfaceId id, gfx::Size frame_size_in_dip);

  bool has_external_content() {
    return texture_layer_.get() || delegated_renderer_layer_.get() ||
           surface_layer_.get();
  }

  void SetShowPaintedContent();

  
  void SetColor(SkColor color);

  
  
  void UpdateNinePatchLayerBitmap(const SkBitmap& bitmap);
  void UpdateNinePatchLayerAperture(const gfx::Rect& aperture);
  void UpdateNinePatchLayerBorder(const gfx::Rect& border);

  
  
  bool SchedulePaint(const gfx::Rect& invalid_rect);

  
  
  
  void ScheduleDraw();

  
  
  void SendDamagedRects();

  const SkRegion& damaged_region() const { return damaged_region_; }

  void CompleteAllAnimations();

  
  void SuppressPaint();

  
  void OnDeviceScaleFactorChanged(float device_scale_factor);

  
  
  void OnDelegatedFrameDamage(const gfx::Rect& damage_rect_in_dip);

  
  void RequestCopyOfOutput(scoped_ptr<cc::CopyOutputRequest> request);

  
  virtual void PaintContents(
      SkCanvas* canvas,
      const gfx::Rect& clip,
      ContentLayerClient::GraphicsContextStatus gc_status) OVERRIDE;
  virtual void DidChangeLayerCanUseLCDText() OVERRIDE {}
  virtual bool FillsBoundsCompletely() const OVERRIDE;

  cc::Layer* cc_layer() { return cc_layer_; }

  
  virtual bool PrepareTextureMailbox(
      cc::TextureMailbox* mailbox,
      scoped_ptr<cc::SingleReleaseCallback>* release_callback,
      bool use_shared_memory) OVERRIDE;

  float device_scale_factor() const { return device_scale_factor_; }

  
  
  void SetForceRenderSurface(bool force);
  bool force_render_surface() const { return force_render_surface_; }

  
  virtual scoped_refptr<base::debug::ConvertableToTraceFormat>
      TakeDebugInfo() OVERRIDE;

  
  virtual void OnAnimationStarted(const cc::AnimationEvent& event) OVERRIDE;

  
  bool HasPendingThreadedAnimations() {
    return pending_threaded_animations_.size() != 0;
  }

  
  void SwitchCCLayerForTest();

 private:
  friend class LayerOwner;

  void CollectAnimators(std::vector<scoped_refptr<LayerAnimator> >* animators);

  
  
  void StackRelativeTo(Layer* child, Layer* other, bool above);

  bool ConvertPointForAncestor(const Layer* ancestor, gfx::Point* point) const;
  bool ConvertPointFromAncestor(const Layer* ancestor, gfx::Point* point) const;

  
  virtual void SetBoundsFromAnimation(const gfx::Rect& bounds) OVERRIDE;
  virtual void SetTransformFromAnimation(
      const gfx::Transform& transform) OVERRIDE;
  virtual void SetOpacityFromAnimation(float opacity) OVERRIDE;
  virtual void SetVisibilityFromAnimation(bool visibility) OVERRIDE;
  virtual void SetBrightnessFromAnimation(float brightness) OVERRIDE;
  virtual void SetGrayscaleFromAnimation(float grayscale) OVERRIDE;
  virtual void SetColorFromAnimation(SkColor color) OVERRIDE;
  virtual void ScheduleDrawForAnimation() OVERRIDE;
  virtual const gfx::Rect& GetBoundsForAnimation() const OVERRIDE;
  virtual gfx::Transform GetTransformForAnimation() const OVERRIDE;
  virtual float GetOpacityForAnimation() const OVERRIDE;
  virtual bool GetVisibilityForAnimation() const OVERRIDE;
  virtual float GetBrightnessForAnimation() const OVERRIDE;
  virtual float GetGrayscaleForAnimation() const OVERRIDE;
  virtual SkColor GetColorForAnimation() const OVERRIDE;
  virtual float GetDeviceScaleFactor() const OVERRIDE;
  virtual void AddThreadedAnimation(
      scoped_ptr<cc::Animation> animation) OVERRIDE;
  virtual void RemoveThreadedAnimation(int animation_id) OVERRIDE;
  virtual LayerAnimatorCollection* GetLayerAnimatorCollection() OVERRIDE;

  
  void CreateWebLayer();

  
  void RecomputeDrawsContentAndUVRect();
  void RecomputePosition();

  
  void SetLayerFilters();

  
  void SetLayerBackgroundFilters();

  
  void SwitchToLayer(scoped_refptr<cc::Layer> new_layer);

  
  
  
  
  void SendPendingThreadedAnimations();

  void AddAnimatorsInTreeToCollection(LayerAnimatorCollection* collection);
  void RemoveAnimatorsInTreeFromCollection(LayerAnimatorCollection* collection);

  
  bool IsAnimating() const;

  const LayerType type_;

  Compositor* compositor_;

  Layer* parent_;

  
  std::vector<Layer*> children_;

  gfx::Rect bounds_;
  gfx::Vector2dF subpixel_position_offset_;

  
  bool visible_;

  bool force_render_surface_;

  bool fills_bounds_opaquely_;
  bool fills_bounds_completely_;

  
  
  SkRegion damaged_region_;

  int background_blur_radius_;

  
  
  float layer_saturation_;
  float layer_brightness_;
  float layer_grayscale_;
  bool layer_inverted_;

  
  Layer* layer_mask_;
  
  
  
  Layer* layer_mask_back_link_;

  
  
  float zoom_;

  
  int zoom_inset_;

  
  scoped_ptr<SkRegion> alpha_shape_;

  std::string name_;

  LayerDelegate* delegate_;

  LayerOwner* owner_;

  scoped_refptr<LayerAnimator> animator_;

  
  
  cc::ScopedPtrVector<cc::Animation> pending_threaded_animations_;

  
  
  scoped_refptr<cc::Layer> content_layer_;
  scoped_refptr<cc::NinePatchLayer> nine_patch_layer_;
  scoped_refptr<cc::TextureLayer> texture_layer_;
  scoped_refptr<cc::SolidColorLayer> solid_color_layer_;
  scoped_refptr<cc::DelegatedRendererLayer> delegated_renderer_layer_;
  scoped_refptr<cc::SurfaceLayer> surface_layer_;
  cc::Layer* cc_layer_;

  
  float device_scale_factor_;

  
  cc::TextureMailbox mailbox_;

  
  
  scoped_ptr<cc::SingleReleaseCallback> mailbox_release_callback_;

  
  
  gfx::Size frame_size_in_dip_;

  DISALLOW_COPY_AND_ASSIGN(Layer);
};

}  

#endif  
