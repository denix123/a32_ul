/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SYSTEM_CORE_INCLUDE_ANDROID_GRAPHICS_H
#define SYSTEM_CORE_INCLUDE_ANDROID_GRAPHICS_H

#include <stdint.h>
#ifndef ANDROID
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


#define HAL_PRIORITY_URGENT_DISPLAY     (-8)


enum {
    HAL_PIXEL_FORMAT_RGBA_8888          = 1,
    HAL_PIXEL_FORMAT_RGBX_8888          = 2,
    HAL_PIXEL_FORMAT_RGB_888            = 3,
    HAL_PIXEL_FORMAT_RGB_565            = 4,
    HAL_PIXEL_FORMAT_BGRA_8888          = 5,

    /*
     * sRGB color pixel formats:
     *
     * The red, green and blue components are stored in sRGB space, and converted
     * to linear space when read, using the standard sRGB to linear equation:
     *
     * Clinear = Csrgb / 12.92                  for Csrgb <= 0.04045
     *         = (Csrgb + 0.055 / 1.055)^2.4    for Csrgb >  0.04045
     *
     * When written the inverse transformation is performed:
     *
     * Csrgb = 12.92 * Clinear                  for Clinear <= 0.0031308
     *       = 1.055 * Clinear^(1/2.4) - 0.055  for Clinear >  0.0031308
     *
     *
     *  The alpha component, if present, is always stored in linear space and
     *  is left unmodified when read or written.
     *
     */
    HAL_PIXEL_FORMAT_sRGB_A_8888        = 0xC,
    HAL_PIXEL_FORMAT_sRGB_X_8888        = 0xD,


    HAL_PIXEL_FORMAT_YV12   = 0x32315659, 


    HAL_PIXEL_FORMAT_Y8     = 0x20203859,

    HAL_PIXEL_FORMAT_Y16    = 0x20363159,

    HAL_PIXEL_FORMAT_RAW_SENSOR = 0x20,

    HAL_PIXEL_FORMAT_BLOB = 0x21,

    HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED = 0x22,

    HAL_PIXEL_FORMAT_YCbCr_420_888 = 0x23,

    
    HAL_PIXEL_FORMAT_YCbCr_422_SP       = 0x10, 
    HAL_PIXEL_FORMAT_YCrCb_420_SP       = 0x11, 
    HAL_PIXEL_FORMAT_YCbCr_422_I        = 0x14, 
};


struct android_ycbcr {
    void *y;
    void *cb;
    void *cr;
    size_t ystride;
    size_t cstride;
    size_t chroma_step;

    
    uint32_t reserved[8];
};


enum {
    
    HAL_TRANSFORM_FLIP_H    = 0x01,
    
    HAL_TRANSFORM_FLIP_V    = 0x02,
    
    HAL_TRANSFORM_ROT_90    = 0x04,
    
    HAL_TRANSFORM_ROT_180   = 0x03,
    
    HAL_TRANSFORM_ROT_270   = 0x07,
    
    HAL_TRANSFORM_RESERVED  = 0x08,
};

#ifdef __cplusplus
}
#endif

#endif 
