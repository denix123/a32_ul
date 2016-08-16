// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_RENDERER_RENDER_FONT_WARMUP_WIN_H_
#define CONTENT_PUBLIC_RENDERER_RENDER_FONT_WARMUP_WIN_H_

#include "content/common/content_export.h"

class SkFontMgr;
class SkTypeface;

namespace content {

CONTENT_EXPORT void DoPreSandboxWarmupForTypeface(SkTypeface* typeface);

CONTENT_EXPORT SkFontMgr* GetPreSandboxWarmupFontMgr();

}  

#endif  
