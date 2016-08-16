// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_PENDING_EXTENSION_INFO_H_
#define CHROME_BROWSER_EXTENSIONS_PENDING_EXTENSION_INFO_H_

#include <string>

#include "base/gtest_prod_util.h"
#include "base/version.h"
#include "extensions/common/manifest.h"
#include "url/gurl.h"

FORWARD_DECLARE_TEST(ExtensionServiceTest, AddPendingExtensionFromSync);

namespace extensions {
class Extension;

class PendingExtensionInfo {
 public:
  typedef bool (*ShouldAllowInstallPredicate)(const Extension*);

  PendingExtensionInfo(const std::string& id,
                       const std::string& install_parameter,
                       const GURL& update_url,
                       const Version& version,
                       ShouldAllowInstallPredicate should_allow_install,
                       bool is_from_sync,
                       bool install_silently,
                       Manifest::Location install_source,
                       int creation_flags,
                       bool mark_acknowledged,
                       bool remote_install);

  
  PendingExtensionInfo();

  ~PendingExtensionInfo();

  
  bool operator==(const PendingExtensionInfo& rhs) const;

  const std::string& id() const { return id_; }
  const GURL& update_url() const { return update_url_; }
  const Version& version() const { return version_; }
  const std::string& install_parameter() const { return install_parameter_; }

  
  
  
  
  
  
  bool ShouldAllowInstall(const Extension* extension) const {
    return should_allow_install_(extension);
  }
  bool is_from_sync() const { return is_from_sync_; }
  bool install_silently() const { return install_silently_; }
  Manifest::Location install_source() const { return install_source_; }
  int creation_flags() const { return creation_flags_; }
  bool mark_acknowledged() const { return mark_acknowledged_; }
  bool remote_install() const { return remote_install_; }

  
  
  
  
  
  int CompareTo(const PendingExtensionInfo& other) const;

 private:
  std::string id_;

  GURL update_url_;
  Version version_;
  std::string install_parameter_;

  
  
  
  ShouldAllowInstallPredicate should_allow_install_;

  bool is_from_sync_;  
  bool install_silently_;
  Manifest::Location install_source_;
  int creation_flags_;
  bool mark_acknowledged_;
  bool remote_install_;

  FRIEND_TEST_ALL_PREFIXES(::ExtensionServiceTest, AddPendingExtensionFromSync);
};

}  

#endif  
