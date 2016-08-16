// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_CONTENT_CONTENT_PROXY_H_
#define ATHENA_CONTENT_CONTENT_PROXY_H_

#include "base/macros.h"
#include "base/memory/ref_counted_memory.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "ui/gfx/image/image_skia.h"

namespace views {
class WebView;
}

namespace athena {

class Activity;
class ProxyImageData;

class ContentProxy {
 public:
  
  
  ContentProxy(views::WebView* web_view, Activity* activity);
  
  

  
  
  virtual ~ContentProxy();

  
  void ContentWillUnload();

  
  
  
  
  void EvictContent();

  
  
  gfx::ImageSkia GetContentImage();

  
  
  void OnPreContentDestroyed();

 private:
  
  
  void ShowOriginalContent();

  
  
  void HideOriginalContent();

  
  void CreateProxyContent();

  
  bool CreateContentImage();

  
  void OnContentImageRead(bool success, const SkBitmap& bitmap);

  
  void OnContentImageEncodeComplete(scoped_refptr<ProxyImageData> image);

  
  
  
  views::WebView* web_view_;

  
  
  
  
  gfx::ImageSkia raw_image_;

  
  bool content_visible_;

  
  
  bool content_loaded_;

  
  
  bool content_creation_called_;

  
  scoped_refptr<base::RefCountedBytes> png_data_;

  
  
  
  base::WeakPtrFactory<ContentProxy> proxy_content_to_image_factory_;

  DISALLOW_COPY_AND_ASSIGN(ContentProxy);
};

}  

#endif  
