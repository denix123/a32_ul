// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_APPLICATION_MANAGER_APPLICATION_MANAGER_EXPORT_H_
#define MOJO_APPLICATION_MANAGER_APPLICATION_MANAGER_EXPORT_H_

#if defined(COMPONENT_BUILD)

#if defined(WIN32)

#if defined(MOJO_APPLICATION_MANAGER_IMPLEMENTATION)
#define MOJO_APPLICATION_MANAGER_EXPORT __declspec(dllexport)
#else
#define MOJO_APPLICATION_MANAGER_EXPORT __declspec(dllimport)
#endif

#else  

#if defined(MOJO_APPLICATION_MANAGER_IMPLEMENTATION)
#define MOJO_APPLICATION_MANAGER_EXPORT __attribute__((visibility("default")))
#else
#define MOJO_APPLICATION_MANAGER_EXPORT
#endif

#endif  

#else  
#define MOJO_APPLICATION_MANAGER_EXPORT
#endif

#endif  