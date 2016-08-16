// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_MANIFEST_HANDLERS_SYNTHESIZE_BROWSER_ACTION_HANDLER_H_
#define CHROME_COMMON_EXTENSIONS_MANIFEST_HANDLERS_SYNTHESIZE_BROWSER_ACTION_HANDLER_H_

#include <string>

#include "extensions/common/manifest_handler.h"

namespace extensions {

class SynthesizeBrowserActionHandler : public ManifestHandler {
 public:
  SynthesizeBrowserActionHandler();
  virtual ~SynthesizeBrowserActionHandler();

  virtual bool Parse(Extension* extension, base::string16* error) OVERRIDE;
  virtual bool AlwaysParseForType(Manifest::Type type) const OVERRIDE;

 private:
  virtual const std::vector<std::string> Keys() const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(SynthesizeBrowserActionHandler);
};

}  

#endif  
