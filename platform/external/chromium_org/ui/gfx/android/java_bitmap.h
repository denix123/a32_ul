// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_ANDROID_JAVA_BITMAP_H_
#define UI_GFX_ANDROID_JAVA_BITMAP_H_

#include <jni.h>

#include "base/android/scoped_java_ref.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/gfx/size.h"

namespace gfx {

enum BitmapFormat {
  BITMAP_FORMAT_NO_CONFIG,
  BITMAP_FORMAT_ALPHA_8,
  BITMAP_FORMAT_ARGB_4444,
  BITMAP_FORMAT_ARGB_8888,
  BITMAP_FORMAT_RGB_565,
};

class GFX_EXPORT JavaBitmap {
 public:
  explicit JavaBitmap(jobject bitmap);
  ~JavaBitmap();

  inline void* pixels() { return pixels_; }
  inline const void* pixels() const { return pixels_; }
  inline const gfx::Size& size() const { return size_; }
  
  inline int format() const { return format_; }
  inline uint32_t stride() const { return stride_; }

  
  static bool RegisterJavaBitmap(JNIEnv* env);

 private:
  jobject bitmap_;
  void* pixels_;
  gfx::Size size_;
  int format_;
  uint32_t stride_;

  DISALLOW_COPY_AND_ASSIGN(JavaBitmap);
};

GFX_EXPORT base::android::ScopedJavaLocalRef<jobject> CreateJavaBitmap(
    int width,
    int height,
    SkColorType color_type);

GFX_EXPORT SkBitmap
    CreateSkBitmapFromAndroidResource(const char* name, gfx::Size size);

GFX_EXPORT base::android::ScopedJavaLocalRef<jobject> ConvertToJavaBitmap(
    const SkBitmap* skbitmap);

GFX_EXPORT SkBitmap CreateSkBitmapFromJavaBitmap(const JavaBitmap& jbitmap);

GFX_EXPORT SkColorType ConvertToSkiaColorType(jobject jbitmap_config);

}  

#endif  
