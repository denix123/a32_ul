// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_CAPTIVE_PORTAL_CAPTIVE_PORTAL_EXPORT_H_
#define COMPONENTS_CAPTIVE_PORTAL_CAPTIVE_PORTAL_EXPORT_H_

#if defined(COMPONENT_BUILD)
#if defined(WIN32)

#if defined(CAPTIVE_PORTAL_IMPLEMENTATION)
#define CAPTIVE_PORTAL_EXPORT __declspec(dllexport)
#else
#define CAPTIVE_PORTAL_EXPORT __declspec(dllimport)
#endif  

#else  
#if defined(CAPTIVE_PORTAL_IMPLEMENTATION)
#define CAPTIVE_PORTAL_EXPORT __attribute__((visibility("default")))
#else
#define CAPTIVE_PORTAL_EXPORT
#endif
#endif

#else  
#define CAPTIVE_PORTAL_EXPORT
#endif

#endif  
