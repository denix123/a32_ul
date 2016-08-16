// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_PICTURE_LAYER_TILING_SET_H_
#define CC_RESOURCES_PICTURE_LAYER_TILING_SET_H_

#include "cc/base/region.h"
#include "cc/base/scoped_ptr_vector.h"
#include "cc/resources/picture_layer_tiling.h"
#include "ui/gfx/size.h"

namespace base {
namespace debug {
class TracedValue;
}
}

namespace cc {

class CC_EXPORT PictureLayerTilingSet {
 public:
  enum TilingRangeType {
    HIGHER_THAN_HIGH_RES,
    HIGH_RES,
    BETWEEN_HIGH_AND_LOW_RES,
    LOW_RES,
    LOWER_THAN_LOW_RES
  };
  struct TilingRange {
    TilingRange(size_t start, size_t end) : start(start), end(end) {}

    size_t start;
    size_t end;
  };

  PictureLayerTilingSet(PictureLayerTilingClient* client,
                        const gfx::Size& layer_bounds);
  ~PictureLayerTilingSet();

  void SetClient(PictureLayerTilingClient* client);
  const PictureLayerTilingClient* client() const { return client_; }

  void RemoveTilesInRegion(const Region& region);

  
  
  
  
  
  bool SyncTilings(const PictureLayerTilingSet& other,
                   const gfx::Size& new_layer_bounds,
                   const Region& layer_invalidation,
                   float minimum_contents_scale);

  gfx::Size layer_bounds() const { return layer_bounds_; }

  PictureLayerTiling* AddTiling(float contents_scale);
  size_t num_tilings() const { return tilings_.size(); }
  int NumHighResTilings() const;
  PictureLayerTiling* tiling_at(size_t idx) { return tilings_[idx]; }
  const PictureLayerTiling* tiling_at(size_t idx) const {
    return tilings_[idx];
  }

  PictureLayerTiling* TilingAtScale(float scale) const;

  
  void RemoveAllTilings();

  
  void Remove(PictureLayerTiling* tiling);

  
  void RemoveAllTiles();

  void DidBecomeActive();
  void DidBecomeRecycled();

  
  
  
  
  
  class CC_EXPORT CoverageIterator {
   public:
    CoverageIterator(const PictureLayerTilingSet* set,
      float contents_scale,
      const gfx::Rect& content_rect,
      float ideal_contents_scale);
    ~CoverageIterator();

    
    
    gfx::Rect geometry_rect() const;
    
    gfx::RectF texture_rect() const;
    
    gfx::Size texture_size() const;

    Tile* operator->() const;
    Tile* operator*() const;

    CoverageIterator& operator++();
    operator bool() const;

    PictureLayerTiling* CurrentTiling();

   private:
    int NextTiling() const;

    const PictureLayerTilingSet* set_;
    float contents_scale_;
    float ideal_contents_scale_;
    PictureLayerTiling::CoverageIterator tiling_iter_;
    int current_tiling_;
    int ideal_tiling_;

    Region current_region_;
    Region missing_region_;
    Region::Iterator region_iter_;
  };

  void AsValueInto(base::debug::TracedValue* array) const;
  size_t GPUMemoryUsageInBytes() const;

  TilingRange GetTilingRange(TilingRangeType type) const;

 private:
  PictureLayerTilingClient* client_;
  gfx::Size layer_bounds_;
  ScopedPtrVector<PictureLayerTiling> tilings_;

  friend class Iterator;
  DISALLOW_COPY_AND_ASSIGN(PictureLayerTilingSet);
};

}  

#endif  
