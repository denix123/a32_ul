// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_GUEST_VIEW_GUEST_VIEW_BASE_H_
#define EXTENSIONS_BROWSER_GUEST_VIEW_GUEST_VIEW_BASE_H_

#include <queue>

#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "content/public/browser/browser_plugin_guest_delegate.h"
#include "content/public/browser/render_process_host_observer.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_delegate.h"
#include "content/public/browser/web_contents_observer.h"

struct RendererContentSettingRules;

namespace extensions {

class GuestViewBase : public content::BrowserPluginGuestDelegate,
                      public content::RenderProcessHostObserver,
                      public content::WebContentsDelegate,
                      public content::WebContentsObserver {
 public:
  class Event {
   public:
    Event(const std::string& name, scoped_ptr<base::DictionaryValue> args);
    ~Event();

    const std::string& name() const { return name_; }

    scoped_ptr<base::DictionaryValue> GetArguments();

   private:
    const std::string name_;
    scoped_ptr<base::DictionaryValue> args_;
  };

  
  template <typename T>
  T* As() {
    if (IsViewType(T::Type))
      return static_cast<T*>(this);

    return NULL;
  }

  typedef base::Callback<GuestViewBase*(
      content::BrowserContext*, int)> GuestCreationCallback;
  static void RegisterGuestViewType(const std::string& view_type,
                                    const GuestCreationCallback& callback);

  static GuestViewBase* Create(content::BrowserContext* browser_context,
                               int guest_instance_id,
                               const std::string& view_type);

  static GuestViewBase* FromWebContents(content::WebContents* web_contents);

  static GuestViewBase* From(int embedder_process_id, int instance_id);

  static bool IsGuest(content::WebContents* web_contents);

  virtual const char* GetViewType() const = 0;

  
  
  
  
  
  virtual void DidAttachToEmbedder() {}

  
  
  
  
  virtual void DidInitialize() {}

  
  
  virtual void DidStopLoading() {}

  
  
  
  
  
  virtual void EmbedderDestroyed() {}

  
  
  
  
  virtual void GuestDestroyed() {}

  
  
  
  
  
  virtual void GuestReady() {}

  
  
  
  
  
  virtual void GuestSizeChangedDueToAutoSize(const gfx::Size& old_size,
                                             const gfx::Size& new_size) {}

  
  
  
  virtual bool IsAutoSizeSupported() const;

  
  
  
  virtual bool IsDragAndDropEnabled() const;

  
  
  
  
  
  virtual void WillAttachToEmbedder() {}

  
  
  
  
  virtual void WillDestroy() {}

  
  
  
  
  
  
  virtual const char* GetAPINamespace() const = 0;

  
  
  
  virtual int GetTaskPrefix() const = 0;

  
  
  
  typedef base::Callback<void(content::WebContents*)>
      WebContentsCreatedCallback;
  virtual void CreateWebContents(
      const std::string& embedder_extension_id,
      int embedder_render_process_id,
      const GURL& embedder_site_url,
      const base::DictionaryValue& create_params,
      const WebContentsCreatedCallback& callback) = 0;

  
  
  void Init(const std::string& embedder_extension_id,
            content::WebContents* embedder_web_contents,
            const base::DictionaryValue& create_params,
            const WebContentsCreatedCallback& callback);

  void InitWithWebContents(
      const std::string& embedder_extension_id,
      int embedder_render_process_id,
      content::WebContents* guest_web_contents);

  bool IsViewType(const char* const view_type) const {
    return !strcmp(GetViewType(), view_type);
  }

  
  void SetAutoSize(bool enabled,
                   const gfx::Size& min_size,
                   const gfx::Size& max_size);

  base::WeakPtr<GuestViewBase> AsWeakPtr();

  bool initialized() const { return initialized_; }

  content::WebContents* embedder_web_contents() const {
    return embedder_web_contents_;
  }

  
  
  base::DictionaryValue* attach_params() const { return attach_params_.get(); }

  
  bool attached() const { return !!embedder_web_contents_; }

  
  int view_instance_id() const { return view_instance_id_; }

  
  int guest_instance_id() const { return guest_instance_id_; }

  
  const std::string& embedder_extension_id() const {
    return embedder_extension_id_;
  }

  
  bool in_extension() const { return !embedder_extension_id_.empty(); }

  
  content::BrowserContext* browser_context() const { return browser_context_; }

  
  int embedder_render_process_id() const { return embedder_render_process_id_; }

  GuestViewBase* GetOpener() const {
    return opener_.get();
  }

  
  void SetAttachParams(const base::DictionaryValue& params);
  void SetOpener(GuestViewBase* opener);

  
  virtual void RenderProcessExited(content::RenderProcessHost* host,
                                   base::ProcessHandle handle,
                                   base::TerminationStatus status,
                                   int exit_code) OVERRIDE;

  
  virtual void Destroy() OVERRIDE FINAL;
  virtual void DidAttach(int guest_proxy_routing_id) OVERRIDE FINAL;
  virtual void ElementSizeChanged(const gfx::Size& old_size,
                                  const gfx::Size& new_size) OVERRIDE FINAL;
  virtual void GuestSizeChanged(const gfx::Size& old_size,
                                const gfx::Size& new_size) OVERRIDE FINAL;
  virtual void RegisterDestructionCallback(
      const DestructionCallback& callback) OVERRIDE FINAL;
  virtual void WillAttach(
      content::WebContents* embedder_web_contents,
      int browser_plugin_instance_id) OVERRIDE FINAL;

  
  void DispatchEventToEmbedder(Event* event);

 protected:
  GuestViewBase(content::BrowserContext* browser_context,
                int guest_instance_id);

  virtual ~GuestViewBase();

 private:
  class EmbedderWebContentsObserver;

  void SendQueuedEvents();

  void CompleteInit(const std::string& embedder_extension_id,
                    int embedder_render_process_id,
                    const WebContentsCreatedCallback& callback,
                    content::WebContents* guest_web_contents);

  static void RegisterGuestViewTypes();

  
  virtual void DidStopLoading(
      content::RenderViewHost* render_view_host) OVERRIDE FINAL;
  virtual void RenderViewReady() OVERRIDE FINAL;
  virtual void WebContentsDestroyed() OVERRIDE FINAL;

  
  virtual void ActivateContents(content::WebContents* contents) OVERRIDE FINAL;
  virtual void DeactivateContents(
      content::WebContents* contents) OVERRIDE FINAL;
  virtual void RunFileChooser(
      content::WebContents* web_contents,
      const content::FileChooserParams& params) OVERRIDE;
  virtual bool ShouldFocusPageAfterCrash() OVERRIDE FINAL;
  virtual bool PreHandleGestureEvent(
      content::WebContents* source,
      const blink::WebGestureEvent& event) OVERRIDE FINAL;

  content::WebContents* embedder_web_contents_;
  std::string embedder_extension_id_;
  int embedder_render_process_id_;
  content::BrowserContext* browser_context_;

  
  
  const int guest_instance_id_;

  
  
  int view_instance_id_;

  
  
  int element_instance_id_;

  bool initialized_;

  
  
  std::deque<linked_ptr<Event> > pending_events_;

  
  base::WeakPtr<GuestViewBase> opener_;

  DestructionCallback destruction_callback_;

  
  
  
  
  scoped_ptr<base::DictionaryValue> attach_params_;

  scoped_ptr<EmbedderWebContentsObserver> embedder_web_contents_observer_;

  
  gfx::Size element_size_;

  
  
  gfx::Size guest_size_;

  
  bool auto_size_enabled_;

  
  gfx::Size max_auto_size_;

  
  gfx::Size min_auto_size_;

  
  
  base::WeakPtrFactory<GuestViewBase> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(GuestViewBase);
};

}  

#endif  
