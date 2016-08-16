// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_HOST_DISPATCHER_H_
#define PPAPI_PROXY_HOST_DISPATCHER_H_

#include <map>
#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/process/process.h"
#include "ipc/message_filter.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/proxy/dispatcher.h"

struct PPB_Proxy_Private;

namespace ppapi {

struct Preferences;

namespace proxy {

class PPAPI_PROXY_EXPORT HostDispatcher : public Dispatcher {
 public:
  
  
  
  
  
  
  
  class SyncMessageStatusObserver {
   public:
    
    virtual void BeginBlockOnSyncMessage() = 0;

    
    
    virtual void EndBlockOnSyncMessage() = 0;

   protected:
    virtual ~SyncMessageStatusObserver() {}
  };

  
  
  
  
  HostDispatcher(PP_Module module,
                 PP_GetInterface_Func local_get_interface,
                 const PpapiPermissions& permissions);
  ~HostDispatcher();

  
  
  
  virtual bool InitHostWithChannel(Delegate* delegate,
                                   base::ProcessId peer_pid,
                                   const IPC::ChannelHandle& channel_handle,
                                   bool is_client,
                                   const Preferences& preferences);

  
  
  static HostDispatcher* GetForInstance(PP_Instance instance);
  static void SetForInstance(PP_Instance instance,
                             HostDispatcher* dispatcher);
  static void RemoveForInstance(PP_Instance instance);

  
  
  
  
  
  
  PP_Module pp_module() const { return pp_module_; }

  
  virtual bool IsPlugin() const;
  virtual bool Send(IPC::Message* msg);

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;
  virtual void OnChannelError() OVERRIDE;

  
  
  
  
  const void* GetProxiedInterface(const std::string& iface_name);

  
  
  
  void set_allow_plugin_reentrancy() {
    allow_plugin_reentrancy_ = true;
  }

  
  const PPB_Proxy_Private* ppb_proxy() const { return ppb_proxy_; }

  
  
  
  
  
  base::Closure AddSyncMessageStatusObserver(SyncMessageStatusObserver* obs);

  void AddFilter(IPC::Listener* listener);

 protected:
  
  virtual void OnInvalidMessageReceived();

 private:
  void OnHostMsgLogWithSource(PP_Instance instance,
                              int int_log_level,
                              const std::string& source,
                              const std::string& value);

  void RemoveSyncMessageStatusObserver(SyncMessageStatusObserver* obs);

  PP_Module pp_module_;

  
  
  typedef base::hash_map<std::string, bool> PluginSupportedMap;
  PluginSupportedMap plugin_supported_;

  
  const PPB_Proxy_Private* ppb_proxy_;

  
  
  
  
  
  bool allow_plugin_reentrancy_;

  ObserverList<SyncMessageStatusObserver> sync_status_observer_list_;

  std::vector<IPC::Listener*> filters_;

  base::WeakPtrFactory<HostDispatcher> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HostDispatcher);
};

class ScopedModuleReference {
 public:
  explicit ScopedModuleReference(Dispatcher* dispatcher);
  ~ScopedModuleReference();

 private:
  HostDispatcher* dispatcher_;

  DISALLOW_COPY_AND_ASSIGN(ScopedModuleReference);
};

}  
}  

#endif  
