// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_GLUE_EXTENSION_BACKED_DATA_TYPE_CONTROLLER_H_
#define CHROME_BROWSER_SYNC_GLUE_EXTENSION_BACKED_DATA_TYPE_CONTROLLER_H_

#include <string>

#include "base/compiler_specific.h"
#include "components/sync_driver/ui_data_type_controller.h"
#include "extensions/browser/extension_registry_observer.h"

class Profile;

namespace browser_sync {

class ExtensionBackedDataTypeController
    : public sync_driver::UIDataTypeController,
      public extensions::ExtensionRegistryObserver {
 public:
  ExtensionBackedDataTypeController(
      syncer::ModelType type,
      const std::string& extension_hash,
      sync_driver::SyncApiComponentFactory* sync_factory,
      Profile* profile);

  
  virtual bool ReadyForStart() const OVERRIDE;
  virtual bool StartModels() OVERRIDE;

  
  virtual void OnExtensionLoaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UnloadedExtensionInfo::Reason reason) OVERRIDE;

 private:
  
  virtual ~ExtensionBackedDataTypeController();

  
  bool IsSyncingExtensionEnabled() const;

  
  bool DoesExtensionMatch(const extensions::Extension& extension) const;

  
  const std::string extension_hash_;

  
  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionBackedDataTypeController);
};

}  

#endif  
