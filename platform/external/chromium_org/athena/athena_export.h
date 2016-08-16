// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_ATHENA_EXPORT_H_
#define ATHENA_ATHENA_EXPORT_H_


#if defined(COMPONENT_BUILD)
#if defined(WIN32)

#if defined(ATHENA_IMPLEMENTATION)
#define ATHENA_EXPORT __declspec(dllexport)
#else
#define ATHENA_EXPORT __declspec(dllimport)
#endif  

#else  
#if defined(ATHENA_IMPLEMENTATION)
#define ATHENA_EXPORT __attribute__((visibility("default")))
#else
#define ATHENA_EXPORT
#endif
#endif

#else  
#define ATHENA_EXPORT
#endif

#endif  
