// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_TOOLBAR_MODEL_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_TOOLBAR_MODEL_H_

#include "base/compiler_specific.h"
#include "base/observer_list.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/scoped_observer.h"
#include "chrome/browser/extensions/api/extension_action/extension_action_api.h"
#include "chrome/browser/extensions/extension_action.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/extension_prefs.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/common/extension.h"

class Browser;
class PrefService;
class Profile;

namespace extensions {
class ExtensionRegistry;
class ExtensionSet;

class ExtensionToolbarModel : public content::NotificationObserver,
                              public ExtensionActionAPI::Observer,
                              public ExtensionRegistryObserver,
                              public KeyedService {
 public:
  ExtensionToolbarModel(Profile* profile, ExtensionPrefs* extension_prefs);
  virtual ~ExtensionToolbarModel();

  
  
  
  
  class Observer {
   public:
    
    virtual void ToolbarExtensionAdded(const Extension* extension,
                                       int index) = 0;

    
    virtual void ToolbarExtensionRemoved(const Extension* extension) = 0;

    
    
    
    virtual void ToolbarExtensionMoved(const Extension* extension,
                                       int index) = 0;

    
    
    virtual void ToolbarExtensionUpdated(const Extension* extension) = 0;

    
    
    
    
    virtual bool ShowExtensionActionPopup(const Extension* extension,
                                          bool grant_active_tab) = 0;

    
    
    virtual void ToolbarVisibleCountChanged() = 0;

    
    
    
    
    
    
    
    virtual void ToolbarHighlightModeChanged(bool is_highlighting) = 0;

    
    virtual Browser* GetBrowser() = 0;

   protected:
    virtual ~Observer() {}
  };

  
  static ExtensionToolbarModel* Get(Profile* profile);

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  void MoveExtensionIcon(const Extension* extension, int index);

  
  
  
  void SetVisibleIconCount(int count);

  
  int GetVisibleIconCount() const { return visible_icon_count_; }

  bool extensions_initialized() const { return extensions_initialized_; }

  const ExtensionList& toolbar_items() const {
    return is_highlighting_ ? highlighted_items_ : toolbar_items_;
  }

  bool is_highlighting() const { return is_highlighting_; }

  
  
  int IncognitoIndexToOriginal(int incognito_index);
  int OriginalIndexToIncognito(int original_index);

  void OnExtensionToolbarPrefChange();

  
  
  
  
  bool ShowExtensionActionPopup(const Extension* extension,
                                Browser* browser,
                                bool grant_active_tab);

  
  
  
  void EnsureVisibility(const ExtensionIdList& extension_ids);

  
  
  
  
  
  bool HighlightExtensions(const ExtensionIdList& extension_ids);

  
  
  void StopHighlighting();

  
  void SetVisibleIconCountForTest(size_t visible_icons);

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  void OnReady();

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;

  
  virtual void OnExtensionActionUpdated(
      ExtensionAction* extension_action,
      content::WebContents* web_contents,
      content::BrowserContext* browser_context) OVERRIDE;

  
  
  
  void InitializeExtensionList(const ExtensionSet& extensions);
  void Populate(const ExtensionIdList& positions,
                const ExtensionSet& extensions);

  
  void UpdatePrefs();

  
  
  void MaybeUpdateVisibilityPref(const Extension* extension, int index);

  
  void MaybeUpdateVisibilityPrefs();

  
  
  size_t FindNewPositionFromLastKnownGood(const Extension* extension);

  
  bool ShouldAddExtension(const Extension* extension);

  
  void AddExtension(const Extension* extension);
  void RemoveExtension(const Extension* extension);

  
  ObserverList<Observer> observers_;

  
  Profile* profile_;

  ExtensionPrefs* extension_prefs_;
  PrefService* prefs_;

  
  bool extensions_initialized_;

  
  
  bool include_all_extensions_;

  
  ExtensionList toolbar_items_;

  
  ExtensionList highlighted_items_;

  
  
  
  bool is_highlighting_;

  
  
  int old_visible_icon_count_;

  ExtensionIdList last_known_positions_;

  
  
  int visible_icon_count_;

  content::NotificationRegistrar registrar_;

  ScopedObserver<ExtensionActionAPI, ExtensionActionAPI::Observer>
      extension_action_observer_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  
  PrefChangeRegistrar pref_change_registrar_;
  base::Closure pref_change_callback_;

  base::WeakPtrFactory<ExtensionToolbarModel> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionToolbarModel);
};

}  

#endif  
