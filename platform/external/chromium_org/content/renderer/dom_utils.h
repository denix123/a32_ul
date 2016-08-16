// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_DOM_UTILS_H_
#define CONTENT_RENDERER_DOM_UTILS_H_

namespace blink {
class WebNode;
}

namespace content {

class DomUtils {
 public:
  
  
  static blink::WebNode ExtractParentAnchorNode(const blink::WebNode& node);
};

}  

#endif  
