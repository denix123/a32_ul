// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PDF_PAINT_AGGREGATOR_H_
#define PDF_PAINT_AGGREGATOR_H_

#include <vector>

#include "ppapi/cpp/image_data.h"
#include "ppapi/cpp/rect.h"
#include "ppapi/cpp/rect.h"

class PaintAggregator {
 public:
  
  
  
  struct ReadyRect {
    pp::Point offset;
    pp::Rect rect;
    pp::ImageData image_data;
  };

  struct PaintUpdate {
    PaintUpdate();
    ~PaintUpdate();

    
    
    bool has_scroll;

    
    
    
    
    
    
    pp::Point scroll_delta;

    
    
    
    pp::Rect scroll_rect;

    
    
    
    
    std::vector<pp::Rect> paint_rects;
  };

  PaintAggregator();

  
  
  bool HasPendingUpdate() const;
  void ClearPendingUpdate();

  PaintUpdate GetPendingUpdate();

  
  
  
  void SetIntermediateResults(const std::vector<ReadyRect>& ready,
                              const std::vector<pp::Rect>& pending);

  
  std::vector<ReadyRect> GetReadyRects() const;

  
  void InvalidateRect(const pp::Rect& rect);

  
  void ScrollRect(const pp::Rect& clip_rect, const pp::Point& amount);

 private:
  
  
  
  
  
  
  
  
  
  class InternalPaintUpdate {
   public:
    InternalPaintUpdate();
    ~InternalPaintUpdate();

    
    
    
    pp::Rect GetScrollDamage() const;

    pp::Point scroll_delta;
    pp::Rect scroll_rect;

    
    
    std::vector<pp::Rect> paint_rects;

    
    std::vector<ReadyRect> ready_rects;

    
    bool synthesized_scroll_damage_rect_;
  };

  pp::Rect ScrollPaintRect(const pp::Rect& paint_rect,
                           const pp::Point& amount) const;
  void InvalidateScrollRect();

  
  
  
  void InvalidateRectInternal(const pp::Rect& rect, bool check_scroll);

  InternalPaintUpdate update_;
};

#endif  
