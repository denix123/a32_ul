// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_MANIFEST_HANDLERS_UI_OVERRIDES_HANDLER_H_
#define CHROME_COMMON_EXTENSIONS_MANIFEST_HANDLERS_UI_OVERRIDES_HANDLER_H_

#include "chrome/common/extensions/api/manifest_types.h"
#include "extensions/common/extension.h"
#include "extensions/common/manifest_handler.h"

namespace extensions {

class ManifestPermission;

struct UIOverrides : public Extension::ManifestData {
  UIOverrides();
  virtual ~UIOverrides();

  static const UIOverrides* Get(const Extension* extension);

  static bool RemovesBookmarkButton(const Extension* extension);
  static bool RemovesBookmarkShortcut(const Extension* extension);
  static bool RemovesBookmarkOpenPagesShortcut(const Extension* extension);

  scoped_ptr<api::manifest_types::ChromeUIOverrides::Bookmarks_ui> bookmarks_ui;

  scoped_ptr<ManifestPermission> manifest_permission;

 private:
  DISALLOW_COPY_AND_ASSIGN(UIOverrides);
};

class UIOverridesHandler : public ManifestHandler {
 public:
  UIOverridesHandler();
  virtual ~UIOverridesHandler();

  virtual bool Parse(Extension* extension, base::string16* error) OVERRIDE;
  virtual bool Validate(const Extension* extension,
                        std::string* error,
                        std::vector<InstallWarning>* warnings) const OVERRIDE;

  virtual ManifestPermission* CreatePermission() OVERRIDE;
  virtual ManifestPermission* CreateInitialRequiredPermission(
      const Extension* extension) OVERRIDE;

 private:
  class ManifestPermissionImpl;

  virtual const std::vector<std::string> Keys() const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(UIOverridesHandler);
};

}  
#endif  
