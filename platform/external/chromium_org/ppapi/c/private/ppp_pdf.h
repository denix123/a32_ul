// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_C_PRIVATE_PPP_PDF_H_
#define PPAPI_C_PRIVATE_PPP_PDF_H_

#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_point.h"
#include "ppapi/c/pp_var.h"

#define PPP_PDF_INTERFACE_1 "PPP_Pdf;1"
#define PPP_PDF_INTERFACE PPP_PDF_INTERFACE_1

typedef enum {
  
  PP_PRIVATEPAGETRANSFORMTYPE_ROTATE_90_CW,
  
  PP_PRIVATEPAGETRANSFORMTYPE_ROTATE_90_CCW
} PP_PrivatePageTransformType;
PP_COMPILE_ASSERT_SIZE_IN_BYTES(PP_PrivatePageTransformType, 4);

struct PPP_Pdf_1 {
  
  PP_Var (*GetLinkAtPosition)(PP_Instance instance,
                              PP_Point point);

  
  void (*Transform)(PP_Instance instance, PP_PrivatePageTransformType type);
};

typedef PPP_Pdf_1 PPP_Pdf;

#endif  
