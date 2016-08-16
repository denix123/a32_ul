// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_EXTENSIONS_RESOURCE_REQUEST_POLICY_H_
#define CHROME_RENDERER_EXTENSIONS_RESOURCE_REQUEST_POLICY_H_

#include "ui/base/page_transition_types.h"

class GURL;

namespace blink {
class WebFrame;
}

namespace extensions {

class ExtensionSet;

class ResourceRequestPolicy {
 public:
  
  
  
  
  static bool CanRequestResource(const GURL& resource_url,
                                 blink::WebFrame* frame,
                                 ui::PageTransition transition_type,
                                 const ExtensionSet* loaded_extensions);
  
  
  static bool CanRequestExtensionResourceScheme(const GURL& resource_url,
                                                blink::WebFrame* frame);

 private:
  ResourceRequestPolicy();
};

}  

#endif  