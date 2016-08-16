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

#ifndef ANDROID_INCLUDE_HARDWARE_HWCOMPOSER_H
#define ANDROID_INCLUDE_HARDWARE_HWCOMPOSER_H

#include <stdint.h>
#include <sys/cdefs.h>

#include <hardware/gralloc.h>
#include <hardware/hardware.h>
#include <cutils/native_handle.h>

#include <hardware/hwcomposer_defs.h>

__BEGIN_DECLS


#define HWC_MODULE_API_VERSION      HWC_MODULE_API_VERSION_0_1
#define HWC_DEVICE_API_VERSION      HWC_DEVICE_API_VERSION_0_1
#define HWC_API_VERSION             HWC_DEVICE_API_VERSION


#define HWC_HARDWARE_MODULE_ID "hwcomposer"

#define HWC_HARDWARE_COMPOSER   "composer"

typedef struct hwc_rect {
    int left;
    int top;
    int right;
    int bottom;
} hwc_rect_t;

typedef struct hwc_frect {
    float left;
    float top;
    float right;
    float bottom;
} hwc_frect_t;

typedef struct hwc_region {
    size_t numRects;
    hwc_rect_t const* rects;
} hwc_region_t;

typedef struct hwc_color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} hwc_color_t;

typedef struct hwc_layer_1 {
    int32_t compositionType;

    uint32_t hints;

    
    uint32_t flags;

    union {
        
        hwc_color_t backgroundColor;

        struct {
            buffer_handle_t handle;

            
            uint32_t transform;

            
            int32_t blending;

            union {
                
                hwc_rect_t sourceCropi;
                hwc_rect_t sourceCrop; 
                
                hwc_frect_t sourceCropf;
            };

            hwc_rect_t displayFrame;

            hwc_region_t visibleRegionScreen;

            int acquireFenceFd;

            int releaseFenceFd;

            uint8_t planeAlpha;

            
            uint8_t _pad[3];
        };
    };

    int32_t reserved[24 - 19];

} hwc_layer_1_t;

typedef void* hwc_display_t;

typedef void* hwc_surface_t;

enum {
    HWC_GEOMETRY_CHANGED = 0x00000001,
};

typedef struct hwc_display_contents_1 {
    int retireFenceFd;

    union {
        
        struct {
            hwc_display_t dpy;
            hwc_surface_t sur;
        };

        struct {
            buffer_handle_t outbuf;

            /* File descriptor for a fence that will signal when outbuf is
             * ready to be written. The h/w composer is responsible for closing
             * this when no longer needed.
             *
             * Will be -1 whenever outbuf is NULL, or when the outbuf can be
             * written immediately.
             */
            int outbufAcquireFenceFd;
        };
    };

    uint32_t flags;
    size_t numHwLayers;
    hwc_layer_1_t hwLayers[0];

} hwc_display_contents_1_t;

typedef struct hwc_procs {
    void (*invalidate)(const struct hwc_procs* procs);

    void (*vsync)(const struct hwc_procs* procs, int disp, int64_t timestamp);

    void (*hotplug)(const struct hwc_procs* procs, int disp, int connected);

} hwc_procs_t;



typedef struct hwc_module {
    struct hw_module_t common;
} hwc_module_t;

typedef struct hwc_composer_device_1 {
    struct hw_device_t common;

    int (*prepare)(struct hwc_composer_device_1 *dev,
                    size_t numDisplays, hwc_display_contents_1_t** displays);

    int (*set)(struct hwc_composer_device_1 *dev,
                size_t numDisplays, hwc_display_contents_1_t** displays);

    int (*eventControl)(struct hwc_composer_device_1* dev, int disp,
            int event, int enabled);

    int (*blank)(struct hwc_composer_device_1* dev, int disp, int blank);

    int (*query)(struct hwc_composer_device_1* dev, int what, int* value);

    void (*registerProcs)(struct hwc_composer_device_1* dev,
            hwc_procs_t const* procs);

    void (*dump)(struct hwc_composer_device_1* dev, char *buff, int buff_len);

    /*
     * (*getDisplayConfigs)() returns handles for the configurations available
     * on the connected display. These handles must remain valid as long as the
     * display is connected.
     *
     * Configuration handles are written to configs. The number of entries
     * allocated by the caller is passed in *numConfigs; getDisplayConfigs must
     * not try to write more than this number of config handles. On return, the
     * total number of configurations available for the display is returned in
     * *numConfigs. If *numConfigs is zero on entry, then configs may be NULL.
     *
     * HWC_DEVICE_API_VERSION_1_1 does not provide a way to choose a config.
     * For displays that support multiple configurations, the h/w composer
     * implementation should choose one and report it as the first config in
     * the list. Reporting the not-chosen configs is not required.
     *
     * Returns 0 on success or -errno on error. If disp is a hotpluggable
     * display type and no display is connected, an error should be returned.
     *
     * This field is REQUIRED for HWC_DEVICE_API_VERSION_1_1 and later.
     * It should be NULL for previous versions.
     */
    int (*getDisplayConfigs)(struct hwc_composer_device_1* dev, int disp,
            uint32_t* configs, size_t* numConfigs);

    /*
     * (*getDisplayAttributes)() returns attributes for a specific config of a
     * connected display. The config parameter is one of the config handles
     * returned by getDisplayConfigs.
     *
     * The list of attributes to return is provided in the attributes
     * parameter, terminated by HWC_DISPLAY_NO_ATTRIBUTE. The value for each
     * requested attribute is written in order to the values array. The
     * HWC_DISPLAY_NO_ATTRIBUTE attribute does not have a value, so the values
     * array will have one less value than the attributes array.
     *
     * This field is REQUIRED for HWC_DEVICE_API_VERSION_1_1 and later.
     * It should be NULL for previous versions.
     *
     * If disp is a hotpluggable display type and no display is connected,
     * or if config is not a valid configuration for the display, a negative
     * value should be returned.
     */
    int (*getDisplayAttributes)(struct hwc_composer_device_1* dev, int disp,
            uint32_t config, const uint32_t* attributes, int32_t* values);

    void* reserved_proc[4];

} hwc_composer_device_1_t;


static inline int hwc_open_1(const struct hw_module_t* module,
        hwc_composer_device_1_t** device) {
    return module->methods->open(module,
            HWC_HARDWARE_COMPOSER, (struct hw_device_t**)device);
}

static inline int hwc_close_1(hwc_composer_device_1_t* device) {
    return device->common.close(&device->common);
}


__END_DECLS

#endif 
