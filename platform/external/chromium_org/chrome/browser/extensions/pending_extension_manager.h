// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_PENDING_EXTENSION_MANAGER_H_
#define CHROME_BROWSER_EXTENSIONS_PENDING_EXTENSION_MANAGER_H_

#include <list>
#include <string>

#include "chrome/browser/extensions/pending_extension_info.h"
#include "extensions/common/manifest.h"

class GURL;

namespace base {
class Version;
}

namespace content {
class BrowserContext;
}

FORWARD_DECLARE_TEST(ExtensionServiceTest,
                     UpdatePendingExtensionAlreadyInstalled);

namespace extensions {
class Extension;
class PendingExtensionManager;

class ExtensionUpdaterTest;
void SetupPendingExtensionManagerForTest(
    int count, const GURL& update_url,
    PendingExtensionManager* pending_extension_manager);

class PendingExtensionManager {
 public:
  explicit PendingExtensionManager(content::BrowserContext* context);
  ~PendingExtensionManager();

  
  

  
  
  bool Remove(const std::string& id);

  
  
  const PendingExtensionInfo* GetById(const std::string& id) const;

  
  bool IsIdPending(const std::string& id) const;

  
  bool HasPendingExtensions() const;

  
  bool HasPendingExtensionFromSync() const;

  
  
  
  
  
  
  
  
  
  bool AddFromSync(
      const std::string& id,
      const GURL& update_url,
      PendingExtensionInfo::ShouldAllowInstallPredicate should_allow_install,
      bool install_silently,
      bool remote_install,
      bool installed_by_custodian);

  
  bool AddFromExtensionImport(
      const std::string& id,
      const GURL& update_url,
      PendingExtensionInfo::ShouldAllowInstallPredicate should_allow_install);

  
  
  bool AddFromExternalUpdateUrl(const std::string& id,
                                const std::string& install_parameter,
                                const GURL& update_url,
                                Manifest::Location location,
                                int creation_flags,
                                bool mark_acknowledged);

  
  
  
  bool AddFromExternalFile(
      const std::string& id,
      Manifest::Location location,
      const base::Version& version,
      int creation_flags,
      bool mark_acknowledged);

  
  
  
  void GetPendingIdsForUpdateCheck(
      std::list<std::string>* out_ids_for_update_check) const;

 private:
  typedef std::list<PendingExtensionInfo> PendingExtensionList;

  
  
  bool AddExtensionImpl(
      const std::string& id,
      const std::string& install_parameter,
      const GURL& update_url,
      const base::Version& version,
      PendingExtensionInfo::ShouldAllowInstallPredicate should_allow_install,
      bool is_from_sync,
      bool install_silently,
      Manifest::Location install_source,
      int creation_flags,
      bool mark_acknowledged,
      bool remote_install);

  
  
  
  void AddForTesting(const PendingExtensionInfo& pending_extension_info);

  
  content::BrowserContext* context_;

  PendingExtensionList pending_extension_list_;

  FRIEND_TEST_ALL_PREFIXES(::ExtensionServiceTest,
                           UpdatePendingExtensionAlreadyInstalled);
  friend class ExtensionUpdaterTest;
  friend void SetupPendingExtensionManagerForTest(
      int count, const GURL& update_url,
      PendingExtensionManager* pending_extension_manager);

  DISALLOW_COPY_AND_ASSIGN(PendingExtensionManager);
};

}  

#endif  
