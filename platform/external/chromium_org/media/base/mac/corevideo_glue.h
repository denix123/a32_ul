// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_MAC_COREVIDEO_GLUE_H_
#define MEDIA_BASE_MAC_COREVIDEO_GLUE_H_

#include "base/basictypes.h"
#include "media/base/media_export.h"

class MEDIA_EXPORT CoreVideoGlue {
 public:
  
  typedef struct CVPlanarPixelBufferInfo_YCbCrPlanar
      CVPlanarPixelBufferInfo_YCbCrPlanar;
  struct CVPlanarPixelBufferInfo_YCbCrBiPlanar {
    CVPlanarComponentInfo componentInfoY;
    CVPlanarComponentInfo componentInfoCbCr;
  };
  typedef struct CVPlanarPixelBufferInfo_YCbCrBiPlanar
      CVPlanarPixelBufferInfo_YCbCrBiPlanar;

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(CoreVideoGlue);
};

#endif  
