// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_PICTURE_LAYER_TILING_H_
#define CC_RESOURCES_PICTURE_LAYER_TILING_H_

#include <set>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "cc/base/cc_export.h"
#include "cc/base/region.h"
#include "cc/base/tiling_data.h"
#include "cc/resources/tile.h"
#include "cc/resources/tile_priority.h"
#include "cc/trees/occlusion.h"
#include "ui/gfx/rect.h"

namespace base {
namespace debug {
class TracedValue;
}
}

namespace cc {

class PictureLayerTiling;
class PicturePileImpl;

class CC_EXPORT PictureLayerTilingClient {
 public:
  
  
  virtual scoped_refptr<Tile> CreateTile(
    PictureLayerTiling* tiling,
    const gfx::Rect& content_rect) = 0;
  virtual PicturePileImpl* GetPile() = 0;
  virtual gfx::Size CalculateTileSize(
    const gfx::Size& content_bounds) const = 0;
  virtual const Region* GetInvalidation() = 0;
  virtual const PictureLayerTiling* GetTwinTiling(
      const PictureLayerTiling* tiling) const = 0;
  virtual PictureLayerTiling* GetRecycledTwinTiling(
      const PictureLayerTiling* tiling) = 0;
  virtual size_t GetMaxTilesForInterestArea() const = 0;
  virtual float GetSkewportTargetTimeInSeconds() const = 0;
  virtual int GetSkewportExtrapolationLimitInContentPixels() const = 0;
  virtual WhichTree GetTree() const = 0;

 protected:
  virtual ~PictureLayerTilingClient() {}
};

class CC_EXPORT PictureLayerTiling {
 public:
  enum EvictionCategory {
    EVENTUALLY,
    EVENTUALLY_AND_REQUIRED_FOR_ACTIVATION,
    SOON,
    SOON_AND_REQUIRED_FOR_ACTIVATION,
    NOW,
    NOW_AND_REQUIRED_FOR_ACTIVATION
  };

  class CC_EXPORT TilingRasterTileIterator {
   public:
    TilingRasterTileIterator();
    TilingRasterTileIterator(PictureLayerTiling* tiling, WhichTree tree);
    ~TilingRasterTileIterator();

    operator bool() const { return !!current_tile_; }
    const Tile* operator*() const { return current_tile_; }
    Tile* operator*() { return current_tile_; }
    TilePriority::PriorityBin get_type() const {
      switch (phase_) {
        case VISIBLE_RECT:
          return TilePriority::NOW;
        case SKEWPORT_RECT:
        case SOON_BORDER_RECT:
          return TilePriority::SOON;
        case EVENTUALLY_RECT:
          return TilePriority::EVENTUALLY;
      }
      NOTREACHED();
      return TilePriority::EVENTUALLY;
    }

    TilingRasterTileIterator& operator++();

   private:
    enum Phase {
      VISIBLE_RECT,
      SKEWPORT_RECT,
      SOON_BORDER_RECT,
      EVENTUALLY_RECT
    };

    void AdvancePhase();
    bool TileNeedsRaster(Tile* tile) const {
      RasterMode mode = tile->DetermineRasterModeForTree(tree_);
      return !tile->is_occluded(tree_) && tile->NeedsRasterForMode(mode);
    }

    PictureLayerTiling* tiling_;

    Phase phase_;
    WhichTree tree_;

    Tile* current_tile_;
    TilingData::Iterator visible_iterator_;
    TilingData::SpiralDifferenceIterator spiral_iterator_;
  };

  class CC_EXPORT TilingEvictionTileIterator {
   public:
    TilingEvictionTileIterator();
    TilingEvictionTileIterator(PictureLayerTiling* tiling,
                               TreePriority tree_priority,
                               EvictionCategory category);
    ~TilingEvictionTileIterator();

    operator bool() const;
    const Tile* operator*() const;
    Tile* operator*();
    TilingEvictionTileIterator& operator++();

   private:
    const std::vector<Tile*>* eviction_tiles_;
    size_t current_eviction_tiles_index_;
  };

  ~PictureLayerTiling();

  
  static scoped_ptr<PictureLayerTiling> Create(
      float contents_scale,
      const gfx::Size& layer_bounds,
      PictureLayerTilingClient* client);
  gfx::Size layer_bounds() const { return layer_bounds_; }
  void UpdateTilesToCurrentPile(const Region& layer_invalidation,
                                const gfx::Size& new_layer_bounds);
  void CreateMissingTilesInLiveTilesRect();
  void RemoveTilesInRegion(const Region& layer_region);

  void SetClient(PictureLayerTilingClient* client);
  void set_resolution(TileResolution resolution) { resolution_ = resolution; }
  TileResolution resolution() const { return resolution_; }

  gfx::Size tiling_size() const { return tiling_data_.tiling_size(); }
  gfx::Rect live_tiles_rect() const { return live_tiles_rect_; }
  gfx::Size tile_size() const { return tiling_data_.max_texture_size(); }
  float contents_scale() const { return contents_scale_; }

  Tile* TileAt(int i, int j) const {
    TileMap::const_iterator iter = tiles_.find(TileMapKey(i, j));
    return (iter == tiles_.end()) ? NULL : iter->second.get();
  }

  void CreateAllTilesForTesting() {
    SetLiveTilesRect(gfx::Rect(tiling_data_.tiling_size()));
  }

  const TilingData& TilingDataForTesting() const { return tiling_data_; }

  std::vector<Tile*> AllTilesForTesting() const {
    std::vector<Tile*> all_tiles;
    for (TileMap::const_iterator it = tiles_.begin();
         it != tiles_.end(); ++it)
      all_tiles.push_back(it->second.get());
    return all_tiles;
  }

  std::vector<scoped_refptr<Tile> > AllRefTilesForTesting() const {
    std::vector<scoped_refptr<Tile> > all_tiles;
    for (TileMap::const_iterator it = tiles_.begin(); it != tiles_.end(); ++it)
      all_tiles.push_back(it->second);
    return all_tiles;
  }

  const gfx::Rect& GetCurrentVisibleRectForTesting() const {
    return current_visible_rect_;
  }

  
  
  
  
  class CC_EXPORT CoverageIterator {
   public:
    CoverageIterator();
    CoverageIterator(const PictureLayerTiling* tiling,
        float dest_scale,
        const gfx::Rect& rect);
    ~CoverageIterator();

    
    
    gfx::Rect geometry_rect() const;
    
    gfx::RectF texture_rect() const;
    gfx::Size texture_size() const;

    
    
    gfx::Rect full_tile_geometry_rect() const;

    Tile* operator->() const { return current_tile_; }
    Tile* operator*() const { return current_tile_; }

    CoverageIterator& operator++();
    operator bool() const { return tile_j_ <= bottom_; }

    int i() const { return tile_i_; }
    int j() const { return tile_j_; }

   private:
    const PictureLayerTiling* tiling_;
    gfx::Rect dest_rect_;
    float dest_to_content_scale_;

    Tile* current_tile_;
    gfx::Rect current_geometry_rect_;
    int tile_i_;
    int tile_j_;
    int left_;
    int top_;
    int right_;
    int bottom_;

    friend class PictureLayerTiling;
  };

  void Reset();

  void UpdateTilePriorities(WhichTree tree,
                            const gfx::Rect& viewport_in_layer_space,
                            float ideal_contents_scale,
                            double current_frame_time_in_seconds,
                            const Occlusion& occlusion_in_layer_space);

  
  
  
  void DidBecomeActive();

  
  
  
  
  
  void DidBecomeRecycled();

  bool NeedsUpdateForFrameAtTimeAndViewport(
      double frame_time_in_seconds,
      const gfx::Rect& viewport_in_layer_space) {
    return frame_time_in_seconds != last_impl_frame_time_in_seconds_ ||
           viewport_in_layer_space != last_viewport_in_layer_space_;
  }

  void GetAllTilesForTracing(std::set<const Tile*>* tiles) const;
  void AsValueInto(base::debug::TracedValue* array) const;
  size_t GPUMemoryUsageInBytes() const;

  struct RectExpansionCache {
    RectExpansionCache();

    gfx::Rect previous_start;
    gfx::Rect previous_bounds;
    gfx::Rect previous_result;
    int64 previous_target;
  };

  static
  gfx::Rect ExpandRectEquallyToAreaBoundedBy(
      const gfx::Rect& starting_rect,
      int64 target_area,
      const gfx::Rect& bounding_rect,
      RectExpansionCache* cache);

  bool has_ever_been_updated() const {
    return last_impl_frame_time_in_seconds_ != 0.0;
  }

 protected:
  friend class CoverageIterator;
  friend class TilingRasterTileIterator;
  friend class TilingEvictionTileIterator;

  typedef std::pair<int, int> TileMapKey;
  typedef base::hash_map<TileMapKey, scoped_refptr<Tile> > TileMap;

  PictureLayerTiling(float contents_scale,
                     const gfx::Size& layer_bounds,
                     PictureLayerTilingClient* client);
  void SetLiveTilesRect(const gfx::Rect& live_tiles_rect);
  void VerifyLiveTilesRect();
  Tile* CreateTile(int i, int j, const PictureLayerTiling* twin_tiling);
  
  bool RemoveTileAt(int i, int j, PictureLayerTiling* recycled_twin);

  
  
  
  
  gfx::Rect ComputeSkewport(double current_frame_time_in_seconds,
                            const gfx::Rect& visible_rect_in_content_space)
      const;

  void UpdateEvictionCacheIfNeeded(TreePriority tree_priority);
  const std::vector<Tile*>* GetEvictionTiles(TreePriority tree_priority,
                                             EvictionCategory category);

  void Invalidate(const Region& layer_region);

  void DoInvalidate(const Region& layer_region,
                    bool recreate_invalidated_tiles);

  
  float contents_scale_;
  gfx::Size layer_bounds_;
  TileResolution resolution_;
  PictureLayerTilingClient* client_;

  
  TilingData tiling_data_;
  TileMap tiles_;  
  gfx::Rect live_tiles_rect_;

  
  double last_impl_frame_time_in_seconds_;
  gfx::Rect last_viewport_in_layer_space_;
  gfx::Rect last_visible_rect_in_content_space_;

  
  gfx::Rect current_visible_rect_;
  gfx::Rect current_skewport_rect_;
  gfx::Rect current_soon_border_rect_;
  gfx::Rect current_eventually_rect_;

  bool has_visible_rect_tiles_;
  bool has_skewport_rect_tiles_;
  bool has_soon_border_rect_tiles_;
  bool has_eventually_rect_tiles_;

  
  
  
  std::vector<Tile*> eviction_tiles_now_;
  std::vector<Tile*> eviction_tiles_now_and_required_for_activation_;
  std::vector<Tile*> eviction_tiles_soon_;
  std::vector<Tile*> eviction_tiles_soon_and_required_for_activation_;
  std::vector<Tile*> eviction_tiles_eventually_;
  std::vector<Tile*> eviction_tiles_eventually_and_required_for_activation_;

  bool eviction_tiles_cache_valid_;
  TreePriority eviction_cache_tree_priority_;

 private:
  DISALLOW_ASSIGN(PictureLayerTiling);

  RectExpansionCache expansion_cache_;
};

}  

#endif  
