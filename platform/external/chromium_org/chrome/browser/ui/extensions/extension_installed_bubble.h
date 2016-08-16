// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_EXTENSIONS_EXTENSION_INSTALLED_BUBBLE_H_
#define CHROME_BROWSER_UI_EXTENSIONS_EXTENSION_INSTALLED_BUBBLE_H_

#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/browser/extension_registry_observer.h"
#include "third_party/skia/include/core/SkBitmap.h"

class Browser;

namespace extensions {
class Extension;
class ExtensionRegistry;
}

class ExtensionInstalledBubble : public content::NotificationObserver,
                                 public extensions::ExtensionRegistryObserver {
 public:
  
  enum BubbleType {
    OMNIBOX_KEYWORD,
    BROWSER_ACTION,
    PAGE_ACTION,
    GENERIC
  };

  
  class Delegate {
   public:
    virtual ~Delegate() {}

    
    
    
    virtual bool MaybeShowNow() = 0;
  };

  ExtensionInstalledBubble(Delegate* delegate,
                           const extensions::Extension* extension,
                           Browser *browser,
                           const SkBitmap& icon);

  virtual ~ExtensionInstalledBubble();

  const extensions::Extension* extension() const { return extension_; }
  Browser* browser() { return browser_; }
  const Browser* browser() const { return browser_; }
  const SkBitmap& icon() const { return icon_; }
  BubbleType type() const { return type_; }

  
  void IgnoreBrowserClosing();

 private:
  
  void ShowInternal();

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnExtensionLoaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UnloadedExtensionInfo::Reason reason) OVERRIDE;

  
  Delegate* delegate_;

  
  const extensions::Extension* extension_;
  Browser* browser_;
  const SkBitmap icon_;
  BubbleType type_;
  content::NotificationRegistrar registrar_;

  
  ScopedObserver<extensions::ExtensionRegistry,
                 extensions::ExtensionRegistryObserver>
      extension_registry_observer_;

  
  
  int animation_wait_retries_;

  base::WeakPtrFactory<ExtensionInstalledBubble> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionInstalledBubble);
};

#endif  
