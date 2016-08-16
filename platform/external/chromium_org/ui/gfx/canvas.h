// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_CANVAS_H_
#define UI_GFX_CANVAS_H_

#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "skia/ext/platform_canvas.h"
#include "skia/ext/refptr.h"
#include "ui/gfx/image/image_skia.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/shadow_value.h"
#include "ui/gfx/text_constants.h"

namespace gfx {

class Rect;
class FontList;
class Point;
class Size;
class Transform;

class GFX_EXPORT Canvas {
 public:
  
  enum {
    TEXT_ALIGN_LEFT = 1 << 0,
    TEXT_ALIGN_CENTER = 1 << 1,
    TEXT_ALIGN_RIGHT = 1 << 2,

    
    MULTI_LINE = 1 << 3,

    
    
    
    
    
    SHOW_PREFIX = 1 << 4,
    HIDE_PREFIX = 1 << 5,

    
    NO_ELLIPSIS = 1 << 6,

    
    
    CHARACTER_BREAK = 1 << 7,

    
    
    
    
    
    
    
    
    FORCE_RTL_DIRECTIONALITY = 1 << 8,

    
    
    FORCE_LTR_DIRECTIONALITY = 1 << 9,

    
    
    
    NO_SUBPIXEL_RENDERING = 1 << 10,
  };

  
  Canvas();

  
  
  
  Canvas(const Size& size, float image_scale, bool is_opaque);

  
  
  Canvas(const ImageSkiaRep& image_rep, bool is_opaque);

  virtual ~Canvas();

  
  
  
  static Canvas* CreateCanvasWithoutScaling(SkCanvas* sk_canvas,
                                            float image_scale);

  
  
  
  
  
  
  void RecreateBackingCanvas(const Size& size,
                             float image_scale,
                             bool is_opaque);

  
  
  
  
  
  static void SizeStringInt(const base::string16& text,
                            const FontList& font_list,
                            int* width,
                            int* height,
                            int line_height,
                            int flags);

  
  
  static void SizeStringFloat(const base::string16& text,
                              const FontList& font_list,
                              float* width,
                              float* height,
                              int line_height,
                              int flags);

  
  
  static int GetStringWidth(const base::string16& text,
                            const FontList& font_list);

  
  
  
  
  
  static float GetStringWidthF(const base::string16& text,
                               const FontList& font_list);

  
  
  
  
  
  
  
  static int DefaultCanvasTextAlignment();

  
  
  
  
  
  
  
  
  
  void DrawStringRectWithHalo(const base::string16& text,
                              const FontList& font_list,
                              SkColor text_color,
                              SkColor halo_color,
                              const Rect& display_rect,
                              int flags);

  
  ImageSkiaRep ExtractImageRep() const;

  
  void DrawDashedRect(const Rect& rect, SkColor color);

  
  
  void Save();

  
  
  
  
  void SaveLayerAlpha(uint8 alpha);
  void SaveLayerAlpha(uint8 alpha, const Rect& layer_bounds);

  
  
  void Restore();

  
  void ClipRect(const Rect& rect);

  
  
  void ClipPath(const SkPath& path, bool do_anti_alias);

  
  bool IsClipEmpty() const;

  
  
  bool GetClipBounds(Rect* bounds);

  void Translate(const Vector2d& offset);

  void Scale(int x_scale, int y_scale);

  
  
  void DrawColor(SkColor color);

  
  
  void DrawColor(SkColor color, SkXfermode::Mode mode);

  
  
  void FillRect(const Rect& rect, SkColor color);

  
  void FillRect(const Rect& rect, SkColor color, SkXfermode::Mode mode);

  
  
  
  
  void DrawRect(const Rect& rect, SkColor color);

  
  
  
  
  void DrawRect(const Rect& rect, SkColor color, SkXfermode::Mode mode);

  
  void DrawRect(const Rect& rect, const SkPaint& paint);

  
  void DrawPoint(const Point& p, const SkPaint& paint);

  
  void DrawLine(const Point& p1, const Point& p2, SkColor color);

  
  void DrawLine(const Point& p1, const Point& p2, const SkPaint& paint);

  
  void DrawCircle(const Point& center_point,
                  int radius,
                  const SkPaint& paint);

  
  
  void DrawRoundRect(const Rect& rect, int radius, const SkPaint& paint);

  
  void DrawPath(const SkPath& path, const SkPaint& paint);

  
  
  
  
  void DrawImageInt(const ImageSkia&, int x, int y);

  
  
  void DrawImageInt(const ImageSkia&, int x, int y, uint8 alpha);

  
  
  
  
  
  void DrawImageInt(const ImageSkia& image,
                    int x,
                    int y,
                    const SkPaint& paint);

  
  
  
  
  
  
  
  
  
  
  
  
  void DrawImageInt(const ImageSkia& image,
                    int src_x,
                    int src_y,
                    int src_w,
                    int src_h,
                    int dest_x,
                    int dest_y,
                    int dest_w,
                    int dest_h,
                    bool filter);
  void DrawImageInt(const ImageSkia& image,
                    int src_x,
                    int src_y,
                    int src_w,
                    int src_h,
                    int dest_x,
                    int dest_y,
                    int dest_w,
                    int dest_h,
                    bool filter,
                    const SkPaint& paint);

  
  
  
  
  void DrawImageIntInPixel(const ImageSkia& image,
                           int src_x,
                           int src_y,
                           int src_w,
                           int src_h,
                           int dest_x,
                           int dest_y,
                           int dest_w,
                           int dest_h,
                           bool filter,
                           const SkPaint& paint);

  
  
  
  
  void DrawImageInPath(const ImageSkia& image,
                       int x,
                       int y,
                       const SkPath& path,
                       const SkPaint& paint);

  
  
  
  void DrawStringRect(const base::string16& text,
                      const FontList& font_list,
                      SkColor color,
                      const Rect& display_rect);

  
  
  
  void DrawStringRectWithFlags(const base::string16& text,
                               const FontList& font_list,
                               SkColor color,
                               const Rect& display_rect,
                               int flags);

  
  
  
  void DrawStringRectWithShadows(const base::string16& text,
                                 const FontList& font_list,
                                 SkColor color,
                                 const Rect& text_bounds,
                                 int line_height,
                                 int flags,
                                 const ShadowValues& shadows);

  
  void DrawFocusRect(const Rect& rect);

  
  
  void DrawSolidFocusRect(const Rect& rect, SkColor color);

  
  
  
  void TileImageInt(const ImageSkia& image,
                    int x,
                    int y,
                    int w,
                    int h);
  void TileImageInt(const ImageSkia& image,
                    int src_x,
                    int src_y,
                    int dest_x,
                    int dest_y,
                    int w,
                    int h);
  void TileImageInt(const ImageSkia& image,
                    int src_x,
                    int src_y,
                    float tile_scale_x,
                    float tile_scale_y,
                    int dest_x,
                    int dest_y,
                    int w,
                    int h);

  
  
  NativeDrawingContext BeginPlatformPaint();

  
  
  void EndPlatformPaint();

  
  void Transform(const Transform& transform);

  
  void DrawFadedString(const base::string16& text,
                       const FontList& font_list,
                       SkColor color,
                       const Rect& display_rect,
                       int flags);

  skia::PlatformCanvas* platform_canvas() { return owned_canvas_.get(); }
  SkCanvas* sk_canvas() { return canvas_; }
  float image_scale() const { return image_scale_; }

 private:
  Canvas(SkCanvas* canvas, float image_scale);

  
  bool IntersectsClipRectInt(int x, int y, int w, int h);
  bool IntersectsClipRect(const Rect& rect);

  
  
  
  void DrawImageIntHelper(const ImageSkia& image,
                          int src_x,
                          int src_y,
                          int src_w,
                          int src_h,
                          int dest_x,
                          int dest_y,
                          int dest_w,
                          int dest_h,
                          bool filter,
                          const SkPaint& paint,
                          float image_scale,
                          bool pixel);

  
  
  
  float image_scale_;

  skia::RefPtr<skia::PlatformCanvas> owned_canvas_;
  SkCanvas* canvas_;

  DISALLOW_COPY_AND_ASSIGN(Canvas);
};

}  

#endif  
