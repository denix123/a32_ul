/*
 * Copyright (C) 2008 The Android Open Source Project
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


#ifndef ANDROID_FB_INTERFACE_H
#define ANDROID_FB_INTERFACE_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <cutils/native_handle.h>

#include <hardware/hardware.h>

__BEGIN_DECLS

#define GRALLOC_HARDWARE_FB0 "fb0"




typedef struct framebuffer_device_t {
    struct hw_device_t common;

    
    const uint32_t  flags;

    
    const uint32_t  width;
    const uint32_t  height;

    
    const int       stride;

    
    const int       format;

    
    const float     xdpi;
    const float     ydpi;

    
    const float     fps;

    
    const int       minSwapInterval;

    
    const int       maxSwapInterval;

    
    const int       numFramebuffers;

    int reserved[7];

    int (*setSwapInterval)(struct framebuffer_device_t* window,
            int interval);

    int (*setUpdateRect)(struct framebuffer_device_t* window,
            int left, int top, int width, int height);

    int (*post)(struct framebuffer_device_t* dev, buffer_handle_t buffer);



    int (*compositionComplete)(struct framebuffer_device_t* dev);

    void (*dump)(struct framebuffer_device_t* dev, char *buff, int buff_len);

    int (*enableScreen)(struct framebuffer_device_t* dev, int enable);

    void* reserved_proc[6];

} framebuffer_device_t;



static inline int framebuffer_open(const struct hw_module_t* module,
        struct framebuffer_device_t** device) {
    return module->methods->open(module,
            GRALLOC_HARDWARE_FB0, (struct hw_device_t**)device);
}

static inline int framebuffer_close(struct framebuffer_device_t* device) {
    return device->common.close(&device->common);
}


__END_DECLS

#endif  
