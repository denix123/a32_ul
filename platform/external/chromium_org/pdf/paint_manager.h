// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PDF_PAINT_MANAGER_H_
#define PDF_PAINT_MANAGER_H_

#include <vector>

#include "pdf/paint_aggregator.h"
#include "ppapi/cpp/graphics_2d.h"
#include "ppapi/utility/completion_callback_factory.h"

namespace pp {
class Graphics2D;
class Instance;
class Point;
class Rect;
};

class PaintManager {
 public:
  
  
  
  struct ReadyRect {
    pp::Point offset;
    pp::Rect rect;
    pp::ImageData image_data;
    bool flush_now;

    ReadyRect(const pp::Rect& r, const pp::ImageData& i, bool f)
        : rect(r), image_data(i), flush_now(f) {}

    operator PaintAggregator::ReadyRect() const {
      PaintAggregator::ReadyRect rv;
      rv.offset = offset;
      rv.rect = rect;
      rv.image_data = image_data;
      return rv;
    }
  };
  class Client {
   public:
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    virtual void OnPaint(const std::vector<pp::Rect>& paint_rects,
                         std::vector<ReadyRect>* ready,
                         std::vector<pp::Rect>* pending) = 0;
   protected:
    
    virtual ~Client() {}
  };

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  PaintManager(pp::Instance* instance, Client* client, bool is_always_opaque);

  ~PaintManager();

  
  
  
  
  static pp::Size GetNewContextSize(const pp::Size& current_context_size,
                                    const pp::Size& plugin_size);

  
  
  void Initialize(pp::Instance* instance, Client* client,
                  bool is_always_opaque);

  
  
  
  
  
  
  
  
  
  void SetSize(const pp::Size& new_size, float new_device_scale);

  
  void Invalidate();

  
  void InvalidateRect(const pp::Rect& rect);

  
  void ScrollRect(const pp::Rect& clip_rect, const pp::Point& amount);

  
  
  
  
  pp::Size GetEffectiveSize() const;
  float GetEffectiveDeviceScale() const;

 private:
  
  PaintManager(const PaintManager&);
  PaintManager& operator=(const PaintManager&);

  
  
  
  
  void EnsureCallbackPending();

  
  void DoPaint();

  
  void OnFlushComplete(int32_t);

  
  
  void OnManualCallbackComplete(int32_t);

  pp::Instance* instance_;

  
  Client* client_;

  bool is_always_opaque_;

  pp::CompletionCallbackFactory<PaintManager> callback_factory_;

  
  
  pp::Graphics2D graphics_;

  PaintAggregator aggregator_;

  
  bool manual_callback_pending_;
  bool flush_pending_;

  
  
  
  bool has_pending_resize_;
  bool graphics_need_to_be_bound_;
  pp::Size pending_size_;
  pp::Size plugin_size_;
  float pending_device_scale_;
  float device_scale_;

  
  bool in_paint_;

  
  bool first_paint_;

  
  bool view_size_changed_waiting_for_paint_;
};

#endif  
