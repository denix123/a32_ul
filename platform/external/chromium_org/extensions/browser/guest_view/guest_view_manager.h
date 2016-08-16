// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_GUEST_VIEW_GUEST_VIEW_MANAGER_H_
#define EXTENSIONS_BROWSER_GUEST_VIEW_GUEST_VIEW_MANAGER_H_

#include <map>

#include "base/gtest_prod_util.h"
#include "base/lazy_instance.h"
#include "base/macros.h"
#include "content/public/browser/browser_plugin_guest_manager.h"
#include "content/public/browser/site_instance.h"
#include "content/public/browser/web_contents.h"

class GURL;

namespace content {
class BrowserContext;
class WebContents;
}  

namespace extensions{
class GuestViewBase;
class GuestViewManagerFactory;

class GuestViewManager : public content::BrowserPluginGuestManager,
                         public base::SupportsUserData::Data {
 public:
  explicit GuestViewManager(content::BrowserContext* context);
  virtual ~GuestViewManager();

  static GuestViewManager* FromBrowserContext(content::BrowserContext* context);

  
  
  static void set_factory_for_testing(GuestViewManagerFactory* factory) {
    GuestViewManager::factory_ = factory;
  }
  
  
  
  
  
  content::WebContents* GetGuestByInstanceIDSafely(
      int guest_instance_id,
      int embedder_render_process_id);

  
  
  
  void AttachGuest(int embedder_render_process_id,
                   int embedder_routing_id,
                   int element_instance_id,
                   int guest_instance_id,
                   const base::DictionaryValue& attach_params);

  int GetNextInstanceID();
  int GetGuestInstanceIDForElementID(
      content::WebContents* embedder_web_contents,
      int element_instance_id);

  typedef base::Callback<void(content::WebContents*)>
      WebContentsCreatedCallback;
  void CreateGuest(const std::string& view_type,
                   const std::string& embedder_extension_id,
                   content::WebContents* embedder_web_contents,
                   const base::DictionaryValue& create_params,
                   const WebContentsCreatedCallback& callback);

  content::WebContents* CreateGuestWithWebContentsParams(
      const std::string& view_type,
      const std::string& embedder_extension_id,
      int embedder_render_process_id,
      const content::WebContents::CreateParams& create_params);

  content::SiteInstance* GetGuestSiteInstance(
      const GURL& guest_site);

  
  virtual content::WebContents* GetGuestByInstanceID(
      content::WebContents* embedder_web_contents,
      int element_instance_id) OVERRIDE;
  virtual bool ForEachGuest(content::WebContents* embedder_web_contents,
                            const GuestCallback& callback) OVERRIDE;
 protected:
  friend class GuestViewBase;
  FRIEND_TEST_ALL_PREFIXES(GuestViewManagerTest, AddRemove);

  
  virtual void AddGuest(int guest_instance_id,
                        content::WebContents* guest_web_contents);

  
  virtual void RemoveGuest(int guest_instance_id);

  content::WebContents* GetGuestByInstanceID(int guest_instance_id);

  bool CanEmbedderAccessInstanceIDMaybeKill(
      int embedder_render_process_id,
      int guest_instance_id);

  bool CanEmbedderAccessInstanceID(int embedder_render_process_id,
                                   int guest_instance_id);

  
  
  
  
  bool CanUseGuestInstanceID(int guest_instance_id);

  
  static GuestViewManagerFactory* factory_;

  
  typedef std::map<int, content::WebContents*> GuestInstanceMap;
  GuestInstanceMap guest_web_contents_by_instance_id_;

  struct ElementInstanceKey {
    content::WebContents* embedder_web_contents;
    int element_instance_id;
    ElementInstanceKey(content::WebContents* embedder_web_contents,
                       int element_instance_id)
        : embedder_web_contents(embedder_web_contents),
          element_instance_id(element_instance_id) {}
    bool operator<(const ElementInstanceKey& other) const {
      if (embedder_web_contents != other.embedder_web_contents)
        return embedder_web_contents < other.embedder_web_contents;
      return element_instance_id < other.element_instance_id;
    }
  };

  typedef std::map<ElementInstanceKey, int> GuestInstanceIDMap;
  GuestInstanceIDMap instance_id_map_;
  
  typedef std::map<int, ElementInstanceKey> GuestInstanceIDReverseMap;
  GuestInstanceIDReverseMap reverse_instance_id_map_;

  int current_instance_id_;

  
  
  
  
  int last_instance_id_removed_;
  
  
  std::set<int> removed_instance_ids_;

  content::BrowserContext* context_;

  DISALLOW_COPY_AND_ASSIGN(GuestViewManager);
};

}  

#endif  
