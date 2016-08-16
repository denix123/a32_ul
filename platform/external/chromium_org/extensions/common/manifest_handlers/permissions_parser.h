// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_MANIFEST_HANDLERS_PERMISSIONS_PARSER_H_
#define EXTENSIONS_COMMON_MANIFEST_HANDLERS_PERMISSIONS_PARSER_H_

#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "extensions/common/permissions/api_permission.h"
#include "extensions/common/permissions/permission_set.h"

namespace extensions {

class Extension;
class URLPatternSet;

class PermissionsParser {
 public:
  PermissionsParser();
  ~PermissionsParser();

  
  bool Parse(Extension* extension, base::string16* error);

  
  
  void Finalize(Extension* extension);

  
  
  static void AddAPIPermission(Extension* extension,
                               APIPermission::ID permission);
  static void AddAPIPermission(Extension* extension, APIPermission* permission);
  static bool HasAPIPermission(const Extension* extension,
                               APIPermission::ID permission);
  static void SetScriptableHosts(Extension* extension,
                                 const URLPatternSet& scriptable_hosts);

  
  
  
  static scoped_refptr<const PermissionSet> GetRequiredPermissions(
      const Extension* extension);
  static scoped_refptr<const PermissionSet> GetOptionalPermissions(
      const Extension* extension);

 private:
  struct InitialPermissions;

  
  scoped_ptr<InitialPermissions> initial_required_permissions_;
  scoped_ptr<InitialPermissions> initial_optional_permissions_;
};

}  

#endif  
