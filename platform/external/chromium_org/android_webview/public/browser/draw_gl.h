// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_PUBLIC_BROWSER_DRAW_GL_H_
#define ANDROID_WEBVIEW_PUBLIC_BROWSER_DRAW_GL_H_

#ifdef __cplusplus
extern "C" {
#endif

static const int kAwDrawGLInfoVersion = 1;

struct AwDrawGLInfo {
  int version;  

  
  enum Mode {
    kModeDraw = 0,
    kModeProcess,
    kModeProcessNoContext,
    kModeSync,
  } mode;

  
  
  
  int clip_left;
  int clip_top;
  int clip_right;
  int clip_bottom;

  
  int width;
  int height;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool is_layer;

  
  
  float transform[16];
};

typedef void (AwDrawGLFunction)(long view_context,
                                AwDrawGLInfo* draw_info,
                                void* spare);
enum AwMapMode {
  MAP_READ_ONLY,
  MAP_WRITE_ONLY,
  MAP_READ_WRITE,
};

typedef long AwCreateGraphicBufferFunction(int w, int h);
typedef void AwReleaseGraphicBufferFunction(long buffer_id);
typedef int AwMapFunction(long buffer_id, AwMapMode mode, void** vaddr);
typedef int AwUnmapFunction(long buffer_id);
typedef void* AwGetNativeBufferFunction(long buffer_id);
typedef unsigned int AwGetStrideFunction(long buffer_id);

static const int kAwDrawGLFunctionTableVersion = 1;

struct AwDrawGLFunctionTable {
  int version;
  AwCreateGraphicBufferFunction* create_graphic_buffer;
  AwReleaseGraphicBufferFunction* release_graphic_buffer;
  AwMapFunction* map;
  AwUnmapFunction* unmap;
  AwGetNativeBufferFunction* get_native_buffer;
  AwGetStrideFunction* get_stride;
};

#ifdef __cplusplus
}  
#endif

#endif  
