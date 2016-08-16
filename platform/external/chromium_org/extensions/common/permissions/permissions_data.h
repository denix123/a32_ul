// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_PERMISSIONS_PERMISSIONS_DATA_H_
#define EXTENSIONS_COMMON_PERMISSIONS_PERMISSIONS_DATA_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "base/synchronization/lock.h"
#include "extensions/common/extension.h"
#include "extensions/common/manifest.h"
#include "extensions/common/permissions/api_permission.h"
#include "extensions/common/permissions/permission_message.h"
#include "extensions/common/permissions/permission_set.h"

class GURL;

namespace extensions {

class PermissionSet;
class Extension;
class URLPatternSet;
class UserScript;

class PermissionsData {
 public:
  
  enum AccessType {
    ACCESS_DENIED,   
    ACCESS_ALLOWED,  
    ACCESS_WITHHELD  
                     
  };

  
  
  class PolicyDelegate {
   public:
    virtual ~PolicyDelegate() {}

    
    
    virtual bool CanExecuteScriptOnPage(const Extension* extension,
                                        const GURL& document_url,
                                        const GURL& top_document_url,
                                        int tab_id,
                                        int process_id,
                                        std::string* error) = 0;
  };

  static void SetPolicyDelegate(PolicyDelegate* delegate);

  PermissionsData(const Extension* extension);
  virtual ~PermissionsData();

  
  
  
  
  
  
  static bool CanSilentlyIncreasePermissions(const Extension* extension);

  
  
  static bool CanExecuteScriptEverywhere(const Extension* extension);

  
  
  static bool ShouldSkipPermissionWarnings(const std::string& extension_id);

  
  
  
  static bool IsRestrictedUrl(const GURL& document_url,
                              const GURL& top_frame_url,
                              const Extension* extension,
                              std::string* error);

  
  
  void SetPermissions(const scoped_refptr<const PermissionSet>& active,
                      const scoped_refptr<const PermissionSet>& withheld) const;

  
  
  void UpdateTabSpecificPermissions(
      int tab_id,
      scoped_refptr<const PermissionSet> permissions) const;

  
  void ClearTabSpecificPermissions(int tab_id) const;

  
  
  
  
  
  
  bool HasAPIPermission(APIPermission::ID permission) const;
  bool HasAPIPermission(const std::string& permission_name) const;
  bool HasAPIPermissionForTab(int tab_id, APIPermission::ID permission) const;
  bool CheckAPIPermissionWithParam(
      APIPermission::ID permission,
      const APIPermission::CheckParam* param) const;

  
  
  
  
  

  
  const URLPatternSet& GetEffectiveHostPermissions() const;

  
  bool HasHostPermission(const GURL& url) const;

  
  
  
  
  
  bool HasEffectiveAccessToAllHosts() const;

  
  
  PermissionMessages GetPermissionMessages() const;

  
  
  std::vector<base::string16> GetPermissionMessageStrings() const;

  
  
  std::vector<base::string16> GetPermissionMessageDetailsStrings() const;

  
  
  bool HasWithheldImpliedAllHosts() const;

  
  
  
  
  
  bool CanAccessPage(const Extension* extension,
                     const GURL& document_url,
                     const GURL& top_document_url,
                     int tab_id,
                     int process_id,
                     std::string* error) const;
  
  
  
  AccessType GetPageAccess(const Extension* extension,
                           const GURL& document_url,
                           const GURL& top_document_url,
                           int tab_id,
                           int process_id,
                           std::string* error) const;

  
  
  
  
  
  
  bool CanRunContentScriptOnPage(const Extension* extension,
                                 const GURL& document_url,
                                 const GURL& top_document_url,
                                 int tab_id,
                                 int process_id,
                                 std::string* error) const;
  
  
  
  
  AccessType GetContentScriptAccess(const Extension* extension,
                                    const GURL& document_url,
                                    const GURL& top_document_url,
                                    int tab_id,
                                    int process_id,
                                    std::string* error) const;

  
  
  
  
  bool CanCaptureVisiblePage(int tab_id, std::string* error) const;

  const scoped_refptr<const PermissionSet>& active_permissions() const {
    
    base::AutoLock auto_lock(runtime_lock_);
    return active_permissions_unsafe_;
  }

  const scoped_refptr<const PermissionSet>& withheld_permissions() const {
    
    return withheld_permissions_unsafe_;
  }

#if defined(UNIT_TEST)
  scoped_refptr<const PermissionSet> GetTabSpecificPermissionsForTesting(
      int tab_id) const {
    return GetTabSpecificPermissions(tab_id);
  }
#endif

 private:
  typedef std::map<int, scoped_refptr<const PermissionSet> > TabPermissionsMap;

  
  
  scoped_refptr<const PermissionSet> GetTabSpecificPermissions(
      int tab_id) const;

  
  
  
  
  bool HasTabSpecificPermissionToExecuteScript(int tab_id,
                                               const GURL& url) const;

  
  
  
  AccessType CanRunOnPage(const Extension* extension,
                          const GURL& document_url,
                          const GURL& top_document_url,
                          int tab_id,
                          int process_id,
                          const URLPatternSet& permitted_url_patterns,
                          const URLPatternSet& withheld_url_patterns,
                          std::string* error) const;

  
  std::string extension_id_;

  
  Manifest::Type manifest_type_;

  mutable base::Lock runtime_lock_;

  
  
  
  
  
  mutable scoped_refptr<const PermissionSet> active_permissions_unsafe_;

  
  
  
  
  
  mutable scoped_refptr<const PermissionSet> withheld_permissions_unsafe_;

  mutable TabPermissionsMap tab_specific_permissions_;

  DISALLOW_COPY_AND_ASSIGN(PermissionsData);
};

}  

#endif  
