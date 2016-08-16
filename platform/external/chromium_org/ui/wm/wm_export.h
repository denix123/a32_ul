// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_WM_WM_EXPORT_H_
#define UI_WM_WM_EXPORT_H_


#if defined(COMPONENT_BUILD)
#if defined(WIN32)

#if defined(WM_IMPLEMENTATION)
#define WM_EXPORT __declspec(dllexport)
#else
#define WM_EXPORT __declspec(dllimport)
#endif  

#else  
#if defined(WM_IMPLEMENTATION)
#define WM_EXPORT __attribute__((visibility("default")))
#else
#define WM_EXPORT
#endif
#endif

#else  
#define WM_EXPORT
#endif

#endif  
