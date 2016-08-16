// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_CONTENT_SUPPORT_ASH_WITH_CONTENT_EXPORT_H_
#define ASH_CONTENT_SUPPORT_ASH_WITH_CONTENT_EXPORT_H_


#if defined(COMPONENT_BUILD)
#if defined(WIN32)

#if defined(ASH_WITH_CONTENT_IMPLEMENTATION)
#define ASH_WITH_CONTENT_EXPORT __declspec(dllexport)
#else
#define ASH_WITH_CONTENT_EXPORT __declspec(dllimport)
#endif  

#else  
#if defined(ASH_WITH_CONTENT_IMPLEMENTATION)
#define ASH_WITH_CONTENT_EXPORT __attribute__((visibility("default")))
#else
#define ASH_WITH_CONTENT_EXPORT
#endif
#endif

#else  
#define ASH_WITH_CONTENT_EXPORT
#endif

#endif  
