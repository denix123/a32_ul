// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_OMNIBOX_OMNIBOX_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_OMNIBOX_OMNIBOX_API_H_

#include <set>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/scoped_observer.h"
#include "base/strings/string16.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "chrome/browser/extensions/extension_icon_manager.h"
#include "chrome/common/extensions/api/omnibox.h"
#include "components/omnibox/autocomplete_match.h"
#include "components/search_engines/template_url_service.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/extension_registry_observer.h"
#include "ui/base/window_open_disposition.h"

class Profile;
class TemplateURL;
class TemplateURLService;

namespace base {
class ListValue;
}

namespace content {
class BrowserContext;
class WebContents;
}

namespace gfx {
class Image;
}

namespace extensions {
class ExtensionRegistry;

class ExtensionOmniboxEventRouter {
 public:
  
  
  static void OnInputStarted(
      Profile* profile, const std::string& extension_id);

  
  
  
  static bool OnInputChanged(
      Profile* profile,
      const std::string& extension_id,
      const std::string& input, int suggest_id);

  
  static void OnInputEntered(
      content::WebContents* web_contents,
      const std::string& extension_id,
      const std::string& input,
      WindowOpenDisposition disposition);

  
  
  static void OnInputCancelled(
      Profile* profile, const std::string& extension_id);

 private:
  DISALLOW_COPY_AND_ASSIGN(ExtensionOmniboxEventRouter);
};

class OmniboxSendSuggestionsFunction : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("omnibox.sendSuggestions", OMNIBOX_SENDSUGGESTIONS)

 protected:
  virtual ~OmniboxSendSuggestionsFunction() {}

  
  virtual bool RunSync() OVERRIDE;
};

class OmniboxAPI : public BrowserContextKeyedAPI,
                   public ExtensionRegistryObserver {
 public:
  explicit OmniboxAPI(content::BrowserContext* context);
  virtual ~OmniboxAPI();

  
  static BrowserContextKeyedAPIFactory<OmniboxAPI>* GetFactoryInstance();

  
  static OmniboxAPI* Get(content::BrowserContext* context);

  
  virtual void Shutdown() OVERRIDE;

  
  gfx::Image GetOmniboxIcon(const std::string& extension_id);

  
  
  gfx::Image GetOmniboxPopupIcon(const std::string& extension_id);

 private:
  friend class BrowserContextKeyedAPIFactory<OmniboxAPI>;

  typedef std::set<const Extension*> PendingExtensions;

  void OnTemplateURLsLoaded();

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;

  
  static const char* service_name() {
    return "OmniboxAPI";
  }
  static const bool kServiceRedirectedInIncognito = true;

  Profile* profile_;

  TemplateURLService* url_service_;

  
  
  PendingExtensions pending_extensions_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  
  ExtensionIconManager omnibox_icon_manager_;
  ExtensionIconManager omnibox_popup_icon_manager_;

  scoped_ptr<TemplateURLService::Subscription> template_url_sub_;

  DISALLOW_COPY_AND_ASSIGN(OmniboxAPI);
};

template <>
void BrowserContextKeyedAPIFactory<OmniboxAPI>::DeclareFactoryDependencies();

class OmniboxSetDefaultSuggestionFunction : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("omnibox.setDefaultSuggestion",
                             OMNIBOX_SETDEFAULTSUGGESTION)

 protected:
  virtual ~OmniboxSetDefaultSuggestionFunction() {}

  
  virtual bool RunSync() OVERRIDE;
};

void ApplyDefaultSuggestionForExtensionKeyword(
    Profile* profile,
    const TemplateURL* keyword,
    const base::string16& remaining_input,
    AutocompleteMatch* match);

ACMatchClassifications StyleTypesToACMatchClassifications(
    const api::omnibox::SuggestResult &suggestion);

}  

#endif  
