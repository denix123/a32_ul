// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_ANDROID_JAVA_GIN_JAVA_BRIDGE_DISPATCHER_HOST_H_
#define CONTENT_BROWSER_ANDROID_JAVA_GIN_JAVA_BRIDGE_DISPATCHER_HOST_H_

#include <map>
#include <set>

#include "base/android/jni_weak_ref.h"
#include "base/android/scoped_java_ref.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/lock.h"
#include "content/browser/android/java/gin_java_bound_object.h"
#include "content/browser/android/java/gin_java_method_invocation_helper.h"
#include "content/public/browser/browser_message_filter.h"
#include "content/public/browser/web_contents_observer.h"

namespace base {
class ListValue;
}

namespace IPC {
class Message;
}

namespace content {

class GinJavaBridgeDispatcherHost
    : public WebContentsObserver,
      public BrowserMessageFilter,
      public GinJavaMethodInvocationHelper::DispatcherDelegate {
 public:

  GinJavaBridgeDispatcherHost(WebContents* web_contents,
                              jobject retained_object_set);

  void AddNamedObject(
      const std::string& name,
      const base::android::JavaRef<jobject>& object,
      const base::android::JavaRef<jclass>& safe_annotation_clazz);
  void RemoveNamedObject(const std::string& name);
  void SetAllowObjectContentsInspection(bool allow);

  
  virtual void RenderFrameCreated(RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void RenderFrameDeleted(RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void DocumentAvailableInMainFrame() OVERRIDE;

  
  using BrowserMessageFilter::Send;
  virtual void OnDestruct() const OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual base::TaskRunner* OverrideTaskRunnerForMessage(
      const IPC::Message& message) OVERRIDE;

  
  virtual JavaObjectWeakGlobalRef GetObjectWeakRef(
      GinJavaBoundObject::ObjectID object_id) OVERRIDE;

 private:
  friend class BrowserThread;
  friend class base::DeleteHelper<GinJavaBridgeDispatcherHost>;

  typedef std::map<GinJavaBoundObject::ObjectID,
                   scoped_refptr<GinJavaBoundObject>> ObjectMap;

  virtual ~GinJavaBridgeDispatcherHost() OVERRIDE;

  void AddBrowserFilterIfNeeded();

  
  GinJavaBoundObject::ObjectID AddObject(
      const base::android::JavaRef<jobject>& object,
      const base::android::JavaRef<jclass>& safe_annotation_clazz,
      bool is_named,
      int32 holder);
  scoped_refptr<GinJavaBoundObject> FindObject(
      GinJavaBoundObject::ObjectID object_id);
  bool FindObjectId(const base::android::JavaRef<jobject>& object,
                    GinJavaBoundObject::ObjectID* object_id);
  void RemoveFromRetainedObjectSetLocked(const JavaObjectWeakGlobalRef& ref);
  JavaObjectWeakGlobalRef RemoveHolderAndAdvanceLocked(
      int32 holder,
      ObjectMap::iterator* iter_ptr);

  
  void OnGetMethods(GinJavaBoundObject::ObjectID object_id,
                    std::set<std::string>* returned_method_names);
  void OnHasMethod(GinJavaBoundObject::ObjectID object_id,
                   const std::string& method_name,
                   bool* result);
  void OnInvokeMethod(GinJavaBoundObject::ObjectID object_id,
                      const std::string& method_name,
                      const base::ListValue& arguments,
                      base::ListValue* result,
                      content::GinJavaBridgeError* error_code);
  void OnObjectWrapperDeleted(GinJavaBoundObject::ObjectID object_id);
  int GetCurrentRoutingID() const;
  void SetCurrentRoutingID(int routing_id);

  bool browser_filter_added_;

  typedef std::map<std::string, GinJavaBoundObject::ObjectID> NamedObjectMap;
  NamedObjectMap named_objects_;

  

  
  
  
  
  
  
  JavaObjectWeakGlobalRef retained_object_set_;
  
  
  ObjectMap objects_;
  base::Lock objects_lock_;

  
  bool allow_object_contents_inspection_;
  
  int32 current_routing_id_;

  DISALLOW_COPY_AND_ASSIGN(GinJavaBridgeDispatcherHost);
};

}  

#endif  
