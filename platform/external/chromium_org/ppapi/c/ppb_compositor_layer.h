/* Copyright 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PPB_COMPOSITOR_LAYER_H_
#define PPAPI_C_PPB_COMPOSITOR_LAYER_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_point.h"
#include "ppapi/c/pp_rect.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_size.h"
#include "ppapi/c/pp_stdint.h"

#define PPB_COMPOSITORLAYER_INTERFACE_0_1 "PPB_CompositorLayer;0.1" 
#define PPB_COMPOSITORLAYER_INTERFACE_0_2 "PPB_CompositorLayer;0.2" 


typedef enum {
  PP_BLENDMODE_NONE,
  PP_BLENDMODE_SRC_OVER,
  PP_BLENDMODE_LAST = PP_BLENDMODE_SRC_OVER
} PP_BlendMode;

struct PPB_CompositorLayer_0_2 { 
  PP_Bool (*IsCompositorLayer)(PP_Resource resource);
  int32_t (*SetColor)(PP_Resource layer,
                      float red,
                      float green,
                      float blue,
                      float alpha,
                      const struct PP_Size* size);
  int32_t (*SetTexture)(PP_Resource layer,
                        PP_Resource context,
                        uint32_t target,
                        uint32_t texture,
                        const struct PP_Size* size,
                        struct PP_CompletionCallback cc);
  int32_t (*SetImage)(PP_Resource layer,
                      PP_Resource image_data,
                      const struct PP_Size* size,
                      struct PP_CompletionCallback cc);
  int32_t (*SetClipRect)(PP_Resource layer, const struct PP_Rect* rect);
  int32_t (*SetTransform)(PP_Resource layer, const float matrix[16]);
  int32_t (*SetOpacity)(PP_Resource layer, float opacity);
  int32_t (*SetBlendMode)(PP_Resource layer, PP_BlendMode mode);
  int32_t (*SetSourceRect)(PP_Resource layer, const struct PP_FloatRect* rect);
  int32_t (*SetPremultipliedAlpha)(PP_Resource layer, PP_Bool premult);
};

struct PPB_CompositorLayer_0_1 { 
  PP_Bool (*IsCompositorLayer)(PP_Resource resource);
  int32_t (*SetColor)(PP_Resource layer,
                      float red,
                      float green,
                      float blue,
                      float alpha,
                      const struct PP_Size* size);
  int32_t (*SetTexture)(PP_Resource layer,
                        PP_Resource context,
                        uint32_t texture,
                        const struct PP_Size* size,
                        struct PP_CompletionCallback cc);
  int32_t (*SetImage)(PP_Resource layer,
                      PP_Resource image_data,
                      const struct PP_Size* size,
                      struct PP_CompletionCallback cc);
  int32_t (*SetClipRect)(PP_Resource layer, const struct PP_Rect* rect);
  int32_t (*SetTransform)(PP_Resource layer, const float matrix[16]);
  int32_t (*SetOpacity)(PP_Resource layer, float opacity);
  int32_t (*SetBlendMode)(PP_Resource layer, PP_BlendMode mode);
  int32_t (*SetSourceRect)(PP_Resource layer, const struct PP_FloatRect* rect);
  int32_t (*SetPremultipliedAlpha)(PP_Resource layer, PP_Bool premult);
};

#endif  

