// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_MANIFEST_HANDLERS_NACL_MODULES_HANDLER_H_
#define EXTENSIONS_COMMON_MANIFEST_HANDLERS_NACL_MODULES_HANDLER_H_

#include <list>
#include <string>

#include "extensions/common/extension.h"
#include "extensions/common/manifest_handler.h"

namespace extensions {

struct NaClModuleInfo {
  typedef std::list<NaClModuleInfo> List;
  
  static const NaClModuleInfo::List* GetNaClModules(
      const Extension* extension);

  GURL url;
  std::string mime_type;
};

class NaClModulesHandler : public ManifestHandler {
 public:
  NaClModulesHandler();
  virtual ~NaClModulesHandler();

  virtual bool Parse(Extension* extension, base::string16* error) OVERRIDE;

 private:
  virtual const std::vector<std::string> Keys() const OVERRIDE;
};

}  

#endif  
