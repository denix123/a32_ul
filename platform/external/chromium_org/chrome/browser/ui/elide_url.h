// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ELIDE_URL_H_
#define CHROME_BROWSER_UI_ELIDE_URL_H_

#include <string>

#include "base/strings/string16.h"

class GURL;

namespace gfx {
class FontList;
}

base::string16 ElideUrl(const GURL& url,
                        const gfx::FontList& font_list,
                        float available_pixel_width,
                        const std::string& languages);

base::string16 ElideHost(const GURL& host_url,
                         const gfx::FontList& font_list,
                         float available_pixel_width);

#endif  
