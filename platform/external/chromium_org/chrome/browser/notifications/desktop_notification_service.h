// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NOTIFICATIONS_DESKTOP_NOTIFICATION_SERVICE_H_
#define CHROME_BROWSER_NOTIFICATIONS_DESKTOP_NOTIFICATION_SERVICE_H_

#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_member.h"
#include "base/scoped_observer.h"
#include "base/strings/string16.h"
#include "chrome/browser/content_settings/permission_context_base.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/keyed_service/core/keyed_service.h"
#include "third_party/WebKit/public/platform/WebNotificationPermission.h"
#include "third_party/WebKit/public/web/WebTextDirection.h"
#include "ui/message_center/notifier_settings.h"
#include "url/gurl.h"

#if defined(ENABLE_EXTENSIONS)
#include "extensions/browser/extension_registry_observer.h"
#endif

class Notification;
class NotificationDelegate;
class NotificationUIManager;
class Profile;

namespace content {
class DesktopNotificationDelegate;
class RenderFrameHost;
struct ShowDesktopNotificationHostMsgParams;
}

#if defined(ENABLE_EXTENSIONS)
namespace extensions {
class ExtensionRegistry;
}
#endif

namespace gfx {
class Image;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

typedef base::Callback<void(blink::WebNotificationPermission)>
    NotificationPermissionCallback;

class DesktopNotificationService : public PermissionContextBase
#if defined(ENABLE_EXTENSIONS)
                                   ,
                                   public extensions::ExtensionRegistryObserver
#endif
                                   {
 public:
  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* prefs);

    
  static std::string AddIconNotification(const GURL& origin_url,
                                         const base::string16& title,
                                         const base::string16& message,
                                         const gfx::Image& icon,
                                         const base::string16& replace_id,
                                         NotificationDelegate* delegate,
                                         Profile* profile);

  explicit DesktopNotificationService(Profile* profile);
  virtual ~DesktopNotificationService();

  
  
  void RequestNotificationPermission(
      content::WebContents* web_contents,
      const PermissionRequestID& request_id,
      const GURL& requesting_frame,
      bool user_gesture,
      const NotificationPermissionCallback& callback);

  
  
  void ShowDesktopNotification(
      const content::ShowDesktopNotificationHostMsgParams& params,
      content::RenderFrameHost* render_frame_host,
      scoped_ptr<content::DesktopNotificationDelegate> delegate,
      base::Closure* cancel_callback);

  
  
  bool IsNotifierEnabled(const message_center::NotifierId& notifier_id);

  
  void SetNotifierEnabled(const message_center::NotifierId& notifier_id,
                          bool enabled);

 private:
  
  
  
  base::string16 DisplayNameForOriginInProcessId(const GURL& origin,
                                                 int process_id);

  
  void OnStringListPrefChanged(
      const char* pref_name, std::set<std::string>* ids_field);

  
  void OnDisabledExtensionIdsChanged();

  
  
  void OnNotificationPermissionRequested(
      const base::Callback<void(blink::WebNotificationPermission)>& callback,
      bool allowed);

  void FirePermissionLevelChangedEvent(
      const message_center::NotifierId& notifier_id,
      bool enabled);

#if defined(ENABLE_EXTENSIONS)
  
  virtual void OnExtensionUninstalled(
      content::BrowserContext* browser_context,
      const extensions::Extension* extension,
      extensions::UninstallReason reason) OVERRIDE;
#endif

  
  virtual void UpdateContentSetting(const GURL& requesting_origin,
                                    const GURL& embedder_origin,
                                    bool allowed) OVERRIDE;

  
  Profile* profile_;

  
  StringListPrefMember disabled_extension_id_pref_;

  
  StringListPrefMember disabled_system_component_id_pref_;

  
  std::set<std::string> disabled_extension_ids_;

  
  std::set<std::string> disabled_system_component_ids_;

#if defined(ENABLE_EXTENSIONS)
  
  ScopedObserver<extensions::ExtensionRegistry,
                 extensions::ExtensionRegistryObserver>
      extension_registry_observer_;
#endif

  base::WeakPtrFactory<DesktopNotificationService> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DesktopNotificationService);
};

#endif  
