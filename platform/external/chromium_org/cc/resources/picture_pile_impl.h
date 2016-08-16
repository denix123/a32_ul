// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_PICTURE_PILE_IMPL_H_
#define CC_RESOURCES_PICTURE_PILE_IMPL_H_

#include <list>
#include <map>
#include <set>
#include <vector>

#include "base/time/time.h"
#include "cc/base/cc_export.h"
#include "cc/debug/rendering_stats_instrumentation.h"
#include "cc/resources/picture_pile_base.h"
#include "skia/ext/analysis_canvas.h"
#include "skia/ext/refptr.h"
#include "third_party/skia/include/core/SkPicture.h"

namespace cc {

class CC_EXPORT PicturePileImpl : public PicturePileBase {
 public:
  static scoped_refptr<PicturePileImpl> Create();
  static scoped_refptr<PicturePileImpl> CreateFromOther(
      const PicturePileBase* other);

  
  
  
  
  
  
  void RasterDirect(
      SkCanvas* canvas,
      const gfx::Rect& canvas_rect,
      float contents_scale,
      RenderingStatsInstrumentation* rendering_stats_instrumentation);

  
  
  
  
  void RasterToBitmap(
      SkCanvas* canvas,
      const gfx::Rect& canvas_rect,
      float contents_scale,
      RenderingStatsInstrumentation* stats_instrumentation) const;

  
  
  void RasterForAnalysis(
      skia::AnalysisCanvas* canvas,
      const gfx::Rect& canvas_rect,
      float contents_scale,
      RenderingStatsInstrumentation* stats_instrumentation) const;

  skia::RefPtr<SkPicture> GetFlattenedPicture();

  struct CC_EXPORT Analysis {
    Analysis();
    ~Analysis();

    bool is_solid_color;
    SkColor solid_color;
  };

  void AnalyzeInRect(const gfx::Rect& content_rect,
                     float contents_scale,
                     Analysis* analysis) const;

  void AnalyzeInRect(
      const gfx::Rect& content_rect,
      float contents_scale,
      Analysis* analysis,
      RenderingStatsInstrumentation* stats_instrumentation) const;

  class CC_EXPORT PixelRefIterator {
   public:
    PixelRefIterator(const gfx::Rect& content_rect,
                     float contents_scale,
                     const PicturePileImpl* picture_pile);
    ~PixelRefIterator();

    SkPixelRef* operator->() const { return *pixel_ref_iterator_; }
    SkPixelRef* operator*() const { return *pixel_ref_iterator_; }
    PixelRefIterator& operator++();
    operator bool() const { return pixel_ref_iterator_; }

   private:
    void AdvanceToTilePictureWithPixelRefs();

    const PicturePileImpl* picture_pile_;
    gfx::Rect layer_rect_;
    TilingData::Iterator tile_iterator_;
    Picture::PixelRefIterator pixel_ref_iterator_;
    std::set<const void*> processed_pictures_;
  };

  void DidBeginTracing();

 protected:
  friend class PicturePile;
  friend class PixelRefIterator;

  PicturePileImpl();
  explicit PicturePileImpl(const PicturePileBase* other);
  virtual ~PicturePileImpl();

 private:
  typedef std::map<const Picture*, Region> PictureRegionMap;

  void CoalesceRasters(const gfx::Rect& canvas_rect,
                       const gfx::Rect& content_rect,
                       float contents_scale,
                       PictureRegionMap* result) const;

  void RasterCommon(
      SkCanvas* canvas,
      SkDrawPictureCallback* callback,
      const gfx::Rect& canvas_rect,
      float contents_scale,
      RenderingStatsInstrumentation* rendering_stats_instrumentation,
      bool is_analysis) const;

  DISALLOW_COPY_AND_ASSIGN(PicturePileImpl);
};

}  

#endif  
