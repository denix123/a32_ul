// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_LAYERS_LAYER_ITERATOR_H_
#define CC_LAYERS_LAYER_ITERATOR_H_

#include "cc/base/cc_export.h"
#include "cc/trees/layer_tree_host_common.h"

namespace cc {





struct LayerIteratorValue {
  static const int kInvalidTargetRenderSurfaceLayerIndex = -1;
  
  
  
  static const int kLayerIndexRepresentingTargetRenderSurface = -1;
};

template <typename LayerType> struct LayerIteratorPosition {
  bool represents_target_render_surface;
  bool represents_contributing_render_surface;
  bool represents_itself;
  LayerType* target_render_surface_layer;
  LayerType* current_layer;
};

template <typename LayerType>
class LayerIterator {
  typedef LayerIterator<LayerType> LayerIteratorType;
  typedef typename LayerType::LayerListType LayerList;
  typedef typename LayerType::RenderSurfaceListType RenderSurfaceLayerList;
  typedef typename LayerType::RenderSurfaceType RenderSurfaceType;

 public:
  LayerIterator() : render_surface_layer_list_(NULL) {}

  static LayerIteratorType Begin(
      const RenderSurfaceLayerList* render_surface_layer_list) {
    return LayerIteratorType(render_surface_layer_list, true);
  }
  static LayerIteratorType End(
      const RenderSurfaceLayerList* render_surface_layer_list) {
    return LayerIteratorType(render_surface_layer_list, false);
  }

  LayerIteratorType& operator++() {
    MoveToNext();
    return *this;
  }
  bool operator==(const LayerIterator& other) const {
    return target_render_surface_layer_index_ ==
           other.target_render_surface_layer_index_ &&
           current_layer_index_ == other.current_layer_index_;
  }
  bool operator!=(const LayerIteratorType& other) const {
    return !(*this == other);
  }

  LayerType* operator->() const { return current_layer(); }
  LayerType* operator*() const { return current_layer(); }

  bool represents_target_render_surface() const {
    return current_layer_represents_target_render_surface();
  }
  bool represents_contributing_render_surface() const {
    return !represents_target_render_surface() &&
           current_layer_represents_contributing_render_surface();
  }
  bool represents_itself() const {
    return !represents_target_render_surface() &&
           !represents_contributing_render_surface();
  }

  LayerType* target_render_surface_layer() const {
    return render_surface_layer_list_->at(target_render_surface_layer_index_);
  }

  operator const LayerIteratorPosition<LayerType>() const {
    LayerIteratorPosition<LayerType> position;
    position.represents_target_render_surface =
        represents_target_render_surface();
    position.represents_contributing_render_surface =
        represents_contributing_render_surface();
    position.represents_itself = represents_itself();
    position.target_render_surface_layer = target_render_surface_layer();
    position.current_layer = current_layer();
    return position;
  }

 private:
  LayerIterator(const RenderSurfaceLayerList* render_surface_layer_list,
                bool start)
      : render_surface_layer_list_(render_surface_layer_list),
        target_render_surface_layer_index_(0) {
    for (size_t i = 0; i < render_surface_layer_list->size(); ++i) {
      if (!render_surface_layer_list->at(i)->render_surface()) {
        NOTREACHED();
        MoveToEnd();
        return;
      }
    }

    if (start && !render_surface_layer_list->empty())
      MoveToBegin();
    else
      MoveToEnd();
  }

  void MoveToBegin() {
    target_render_surface_layer_index_ = 0;
    current_layer_index_ = target_render_surface_children().size() - 1;
    MoveToHighestInSubtree();
  }

  void MoveToEnd() {
    target_render_surface_layer_index_ =
        LayerIteratorValue::kInvalidTargetRenderSurfaceLayerIndex;
    current_layer_index_ = 0;
  }

  void MoveToNext() {
    
    
    
    
    
    
    

    if (!current_layer_represents_target_render_surface()) {
      
      
      --current_layer_index_;
      MoveToHighestInSubtree();
    } else {
      while (current_layer_represents_target_render_surface()) {
        if (!target_render_surface_layer_index_) {
          
          target_render_surface_layer_index_ =
              LayerIteratorValue::kInvalidTargetRenderSurfaceLayerIndex;
          current_layer_index_ = 0;
          return;
        }
        target_render_surface_layer_index_ =
            target_render_surface()->target_render_surface_layer_index_history_;
        current_layer_index_ =
            target_render_surface()->current_layer_index_history_;
      }
    }
  }

  void MoveToHighestInSubtree() {
    if (current_layer_represents_target_render_surface())
      return;
    while (current_layer_represents_contributing_render_surface()) {
      
      
      
      target_render_surface()->current_layer_index_history_ =
          current_layer_index_;
      int previous_target_render_surface_layer =
          target_render_surface_layer_index_;

      for (LayerType* layer = current_layer();
           target_render_surface_layer() != layer;
           ++target_render_surface_layer_index_) {
      }
      current_layer_index_ = target_render_surface_children().size() - 1;

      target_render_surface()->target_render_surface_layer_index_history_ =
          previous_target_render_surface_layer;
    }
  }

  inline LayerType* current_layer() const {
    return current_layer_represents_target_render_surface()
               ? target_render_surface_layer()
               : LayerTreeHostCommon::get_layer_as_raw_ptr(
                     target_render_surface_children(), current_layer_index_);
  }

  inline bool current_layer_represents_contributing_render_surface() const {
    return LayerTreeHostCommon::RenderSurfaceContributesToTarget<LayerType>(
        current_layer(), target_render_surface_layer()->id());
  }
  inline bool current_layer_represents_target_render_surface() const {
    return current_layer_index_ ==
           LayerIteratorValue::kLayerIndexRepresentingTargetRenderSurface;
  }

  inline RenderSurfaceType* target_render_surface() const {
    return target_render_surface_layer()->render_surface();
  }
  inline const LayerList& target_render_surface_children() const {
    return target_render_surface()->layer_list();
  }

  const RenderSurfaceLayerList* render_surface_layer_list_;

  

  
  
  
  
  
  
  int target_render_surface_layer_index_;
  
  
  
  
  
  
  int current_layer_index_;
};

}  

#endif  
