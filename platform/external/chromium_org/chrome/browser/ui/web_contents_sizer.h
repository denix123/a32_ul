// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEB_CONTENTS_SIZER_H_
#define CHROME_BROWSER_UI_WEB_CONTENTS_SIZER_H_

namespace content {
class WebContents;
}

namespace gfx {
class Size;
}

void ResizeWebContents(content::WebContents* web_contents,
                       const gfx::Size& size);

#endif  
