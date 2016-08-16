// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_MANIFEST_HANDLERS_OPTIONS_PAGE_INFO_H_
#define EXTENSIONS_COMMON_MANIFEST_HANDLERS_OPTIONS_PAGE_INFO_H_

#include <string>
#include <vector>

#include "base/values.h"
#include "extensions/common/extension.h"
#include "extensions/common/manifest_handler.h"
#include "url/gurl.h"

namespace base {
class Value;
}

namespace extensions {

class OptionsPageInfo : public Extension::ManifestData {
 public:
  OptionsPageInfo(const GURL& options_page,
                  bool chrome_styles,
                  bool open_in_tab);
  virtual ~OptionsPageInfo();

  
  
  
  static const GURL& GetOptionsPage(const Extension* extension);

  
  
  
  static bool HasOptionsPage(const Extension* extension);

  
  
  static bool ShouldUseChromeStyle(const Extension* extension);

  
  
  static bool ShouldOpenInTab(const Extension* extension);

  static scoped_ptr<OptionsPageInfo> Create(
      Extension* extension,
      const base::Value* options_ui_value,
      const std::string& options_page_string,
      std::vector<InstallWarning>* install_warnings,
      base::string16* error);

 private:
  
  
  
  GURL options_page_;

  bool chrome_styles_;

  bool open_in_tab_;

  DISALLOW_COPY_AND_ASSIGN(OptionsPageInfo);
};

class OptionsPageManifestHandler : public ManifestHandler {
 public:
  OptionsPageManifestHandler();
  virtual ~OptionsPageManifestHandler();

  virtual bool Parse(Extension* extension, base::string16* error) OVERRIDE;
  virtual bool Validate(const Extension* extension,
                        std::string* error,
                        std::vector<InstallWarning>* warnings) const OVERRIDE;

 private:
  virtual const std::vector<std::string> Keys() const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(OptionsPageManifestHandler);
};

}  

#endif  
