// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_PLATFORM_THUNK_EXPORT_H_
#define MOJO_PUBLIC_PLATFORM_THUNK_EXPORT_H_

#if defined(WIN32)
#define THUNK_EXPORT __declspec(dllexport)
#else
#define THUNK_EXPORT __attribute__((visibility("default")))
#endif

#endif 
