/*
 * Copyright (C) 2010 The Android Open Source Project
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

#ifndef ANDROID_INCLUDE_HARDWARE_HWCOMPOSER_DEFS_H
#define ANDROID_INCLUDE_HARDWARE_HWCOMPOSER_DEFS_H

#include <stdint.h>
#include <sys/cdefs.h>

#include <hardware/gralloc.h>
#include <hardware/hardware.h>
#include <cutils/native_handle.h>

__BEGIN_DECLS


#define HWC_HEADER_VERSION          1

#define HWC_MODULE_API_VERSION_0_1  HARDWARE_MODULE_API_VERSION(0, 1)

#define HWC_DEVICE_API_VERSION_1_0  HARDWARE_DEVICE_API_VERSION_2(1, 0, HWC_HEADER_VERSION)
#define HWC_DEVICE_API_VERSION_1_1  HARDWARE_DEVICE_API_VERSION_2(1, 1, HWC_HEADER_VERSION)
#define HWC_DEVICE_API_VERSION_1_2  HARDWARE_DEVICE_API_VERSION_2(1, 2, HWC_HEADER_VERSION)
#define HWC_DEVICE_API_VERSION_1_3  HARDWARE_DEVICE_API_VERSION_2(1, 3, HWC_HEADER_VERSION)

enum {
    
    HWC_EGL_ERROR = -1
};

enum {
    HWC_HINT_TRIPLE_BUFFER  = 0x00000001,

    HWC_HINT_CLEAR_FB       = 0x00000002
};

enum {
    HWC_SKIP_LAYER = 0x00000001,
};

enum {
    
    HWC_FRAMEBUFFER = 0,

    
    HWC_OVERLAY = 1,

    HWC_BACKGROUND = 2,

    HWC_FRAMEBUFFER_TARGET = 3,
};

enum {
    
    HWC_BLENDING_NONE     = 0x0100,

    
    HWC_BLENDING_PREMULT  = 0x0105,

    
    HWC_BLENDING_COVERAGE = 0x0405
};

enum {
    
    HWC_TRANSFORM_FLIP_H = HAL_TRANSFORM_FLIP_H,
    
    HWC_TRANSFORM_FLIP_V = HAL_TRANSFORM_FLIP_V,
    
    HWC_TRANSFORM_ROT_90 = HAL_TRANSFORM_ROT_90,
    
    HWC_TRANSFORM_ROT_180 = HAL_TRANSFORM_ROT_180,
    
    HWC_TRANSFORM_ROT_270 = HAL_TRANSFORM_ROT_270,
};

enum {
    HWC_BACKGROUND_LAYER_SUPPORTED      = 0,

    HWC_VSYNC_PERIOD                    = 1,

    HWC_DISPLAY_TYPES_SUPPORTED         = 2,
};

enum {
    
    HWC_DISPLAY_NO_ATTRIBUTE                = 0,

    
    HWC_DISPLAY_VSYNC_PERIOD                = 1,

    
    HWC_DISPLAY_WIDTH                       = 2,
    HWC_DISPLAY_HEIGHT                      = 3,

    HWC_DISPLAY_DPI_X                       = 4,
    HWC_DISPLAY_DPI_Y                       = 5,
};

enum {
    HWC_EVENT_VSYNC     = 0
};

enum {
    HWC_DISPLAY_PRIMARY     = 0,
    HWC_DISPLAY_EXTERNAL    = 1,    
    HWC_DISPLAY_VIRTUAL     = 2,

    HWC_NUM_PHYSICAL_DISPLAY_TYPES = 2,
    HWC_NUM_DISPLAY_TYPES          = 3,
};

enum {
    HWC_DISPLAY_PRIMARY_BIT     = 1 << HWC_DISPLAY_PRIMARY,
    HWC_DISPLAY_EXTERNAL_BIT    = 1 << HWC_DISPLAY_EXTERNAL,
    HWC_DISPLAY_VIRTUAL_BIT     = 1 << HWC_DISPLAY_VIRTUAL,
};


__END_DECLS

#endif 
