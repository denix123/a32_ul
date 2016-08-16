/*
 * Copyright (C) 2006 The Android Open Source Project
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

#ifndef __CUTILS_PROPERTIES_H
#define __CUTILS_PROPERTIES_H

#include <sys/cdefs.h>
#include <stddef.h>
#ifdef ANDROID
#include <sys/system_properties.h>
#else
#ifndef PROP_NAME_MAX
#define PROP_NAME_MAX  32
#endif
#ifndef PROP_VALUE_MAX
#define PROP_VALUE_MAX  92
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define PROPERTY_KEY_MAX   PROP_NAME_MAX
#define PROPERTY_VALUE_MAX  PROP_VALUE_MAX

int property_get(const char *key, char *value, const char *default_value);

int property_set(const char *key, const char *value);
    
int property_list(void (*propfn)(const char *key, const char *value, void *cookie), void *cookie);    

#if defined(__BIONIC_FORTIFY)

extern int __property_get_real(const char *, char *, const char *)
    __asm__(__USER_LABEL_PREFIX__ "property_get");
__errordecl(__property_get_too_small_error, "property_get() called with too small of a buffer");

__BIONIC_FORTIFY_INLINE
int property_get(const char *key, char *value, const char *default_value) {
    size_t bos = __bos(value);
    if (bos < PROPERTY_VALUE_MAX) {
        __property_get_too_small_error();
    }
    return __property_get_real(key, value, default_value);
}

#endif

#ifdef HAVE_SYSTEM_PROPERTY_SERVER
#define SYSTEM_PROPERTY_PIPE_NAME       "/tmp/android-sysprop"

enum {
    kSystemPropertyUnknown = 0,
    kSystemPropertyGet,
    kSystemPropertySet,
    kSystemPropertyList
};
#endif 


#ifdef __cplusplus
}
#endif

#endif
