// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_FAVICON_BASE_FAVICON_CALLBACK_H_
#define COMPONENTS_FAVICON_BASE_FAVICON_CALLBACK_H_

#include <vector>

#include "base/callback.h"

namespace favicon_base {

struct FaviconRawBitmapResult;
struct FaviconImageResult;

typedef base::Callback<void(const FaviconImageResult&)> FaviconImageCallback;

typedef base::Callback<void(const FaviconRawBitmapResult&)>
    FaviconRawBitmapCallback;

typedef base::Callback<void(const std::vector<FaviconRawBitmapResult>&)>
    FaviconResultsCallback;

}  

#endif  
