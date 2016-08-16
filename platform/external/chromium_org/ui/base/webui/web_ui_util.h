// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_WEBUI_WEB_UI_UTIL_H_
#define UI_BASE_WEBUI_WEB_UI_UTIL_H_

#include <string>

#include "base/strings/string_piece.h"
#include "base/values.h"
#include "ui/base/ui_base_export.h"
#include "ui/base/window_open_disposition.h"

class GURL;
class SkBitmap;

namespace webui {

UI_BASE_EXPORT std::string GetBitmapDataUrl(const SkBitmap& bitmap);

UI_BASE_EXPORT std::string GetBitmapDataUrlFromResource(int resource_id);

UI_BASE_EXPORT WindowOpenDisposition
    GetDispositionFromClick(const base::ListValue* args, int start_index);

UI_BASE_EXPORT bool ParseScaleFactor(const base::StringPiece& identifier,
                                     float* scale_factor);

UI_BASE_EXPORT void ParsePathAndScale(const GURL& url,
                                      std::string* path,
                                      float* scale_factor);

UI_BASE_EXPORT void SetFontAndTextDirection(
    base::DictionaryValue* localized_strings);

}  

#endif  
