// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_EXTENSIONS_CLIENT_H_
#define EXTENSIONS_COMMON_EXTENSIONS_CLIENT_H_

#include <set>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"

class GURL;

namespace extensions {

class APIPermissionSet;
class Extension;
class ExtensionAPI;
class FeatureProvider;
class JSONFeatureProviderSource;
class ManifestPermissionSet;
class PermissionMessage;
class PermissionMessageProvider;
class SimpleFeature;
class URLPatternSet;

class ExtensionsClient {
 public:
  typedef std::vector<std::string> ScriptingWhitelist;

  virtual ~ExtensionsClient() {}

  
  
  
  virtual void Initialize() = 0;

  
  
  virtual const PermissionMessageProvider& GetPermissionMessageProvider()
      const = 0;

  
  virtual const std::string GetProductName() = 0;

  
  virtual scoped_ptr<FeatureProvider> CreateFeatureProvider(
      const std::string& name) const = 0;

  
  
  
  
  virtual scoped_ptr<JSONFeatureProviderSource> CreateFeatureProviderSource(
      const std::string& name) const = 0;

  
  
  
  virtual void FilterHostPermissions(
      const URLPatternSet& hosts,
      URLPatternSet* new_hosts,
      std::set<PermissionMessage>* messages) const = 0;

  
  
  virtual void SetScriptingWhitelist(const ScriptingWhitelist& whitelist) = 0;

  
  
  virtual const ScriptingWhitelist& GetScriptingWhitelist() const = 0;

  
  virtual URLPatternSet GetPermittedChromeSchemeHosts(
      const Extension* extension,
      const APIPermissionSet& api_permissions) const = 0;

  
  virtual bool IsScriptableURL(const GURL& url, std::string* error) const = 0;

  
  virtual bool IsAPISchemaGenerated(const std::string& name) const = 0;

  
  virtual base::StringPiece GetAPISchema(const std::string& name) const = 0;

  
  
  virtual void RegisterAPISchemaResources(ExtensionAPI* api) const = 0;

  
  
  virtual bool ShouldSuppressFatalErrors() const = 0;

  
  virtual std::string GetWebstoreBaseURL() const = 0;

  
  virtual std::string GetWebstoreUpdateURL() const = 0;

  
  
  virtual bool IsBlacklistUpdateURL(const GURL& url) const = 0;

  
  static ExtensionsClient* Get();

  
  static void Set(ExtensionsClient* client);
};

}  

#endif  
