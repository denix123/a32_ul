// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_ACCELEROMETER_UI_ACCELEROMETER_EXPORT_H_
#define UI_ACCELEROMETER_UI_ACCELEROMETER_EXPORT_H_


#if defined(COMPONENT_BUILD)

#if defined(WIN32)

#if defined(UI_ACCELEROMETER_IMPLEMENTATION)
#define UI_ACCELEROMETER_EXPORT __declspec(dllexport)
#else
#define UI_ACCELEROMETER_EXPORT __declspec(dllimport)
#endif

#else  

#if defined(UI_ACCELEROMETER_IMPLEMENTATION)
#define UI_ACCELEROMETER_EXPORT __attribute__((visibility("default")))
#else
#define UI_ACCELEROMETER_EXPORT
#endif

#endif

#else  

#define UI_ACCELEROMETER_EXPORT

#endif

#endif  
