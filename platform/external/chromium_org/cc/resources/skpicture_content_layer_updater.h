// Copyright 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_SKPICTURE_CONTENT_LAYER_UPDATER_H_
#define CC_RESOURCES_SKPICTURE_CONTENT_LAYER_UPDATER_H_

#include "cc/resources/content_layer_updater.h"
#include "skia/ext/refptr.h"
#include "third_party/skia/include/core/SkPicture.h"

class SkCanvas;

namespace cc {

class LayerPainter;

class SkPictureContentLayerUpdater : public ContentLayerUpdater {
 protected:
  SkPictureContentLayerUpdater(
      scoped_ptr<LayerPainter> painter,
      RenderingStatsInstrumentation* stats_instrumentation,
      int layer_id);
  virtual ~SkPictureContentLayerUpdater();

  virtual void PrepareToUpdate(const gfx::Size& content_size,
                               const gfx::Rect& paint_rect,
                               const gfx::Size& tile_size,
                               float contents_width_scale,
                               float contents_height_scale) OVERRIDE;
  void DrawPicture(SkCanvas* canvas);

 private:
  skia::RefPtr<SkPicture> picture_;

  DISALLOW_COPY_AND_ASSIGN(SkPictureContentLayerUpdater);
};

}  

#endif  