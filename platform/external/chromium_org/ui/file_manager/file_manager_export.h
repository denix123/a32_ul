// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_FILE_MANAGER_FILE_MANAGER_EXPORT_H_
#define UI_FILE_MANAGER_FILE_MANAGER_EXPORT_H_


#if defined(COMPONENT_BUILD)
#if defined(WIN32)

#if defined(FILE_MANAGER_IMPLEMENTATION)
#define FILE_MANAGER_EXPORT __declspec(dllexport)
#else
#define FILE_MANAGER_EXPORT __declspec(dllimport)
#endif  

#else  
#if defined(FILE_MANAGER_IMPLEMENTATION)
#define FILE_MANAGER_EXPORT __attribute__((visibility("default")))
#else
#define FILE_MANAGER_EXPORT
#endif
#endif

#else  
#define FILE_MANAGER_EXPORT
#endif

#endif  
