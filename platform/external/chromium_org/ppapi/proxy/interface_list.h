// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_INTERFACE_LIST_H_
#define PPAPI_PROXY_INTERFACE_LIST_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/synchronization/lock.h"
#include "ppapi/proxy/interface_proxy.h"
#include "ppapi/proxy/ppapi_proxy_export.h"
#include "ppapi/shared_impl/ppapi_permissions.h"

namespace ppapi {
namespace proxy {

class PPAPI_PROXY_EXPORT InterfaceList {
 public:
  InterfaceList();
  ~InterfaceList();

  static InterfaceList* GetInstance();

  
  
  
  
  
  
  
  
  
  
  static void SetProcessGlobalPermissions(const PpapiPermissions& permissions);

  
  
  InterfaceProxy::Factory GetFactoryForID(ApiID id) const;

  
  
  const void* GetInterfaceForPPB(const std::string& name);
  const void* GetInterfaceForPPP(const std::string& name) const;

 private:
  friend class InterfaceListTest;

  class InterfaceInfo {
   public:
    InterfaceInfo(const void* in_interface, Permission in_perm)
        : iface_(in_interface),
          required_permission_(in_perm),
          sent_to_uma_(false) {
    }

    const void* iface() { return iface_; }

    
    
    
    Permission required_permission() { return required_permission_; };

    
    
    
    void LogWithUmaOnce(IPC::Sender* sender, const std::string& name);
   private:
    DISALLOW_COPY_AND_ASSIGN(InterfaceInfo);

    const void* const iface_;
    const Permission required_permission_;

    bool sent_to_uma_;
    base::Lock sent_to_uma_lock_;
  };
  
  friend class InterfaceInfo;

  typedef base::ScopedPtrHashMap<std::string, InterfaceInfo>
      NameToInterfaceInfoMap;

  void AddProxy(ApiID id, InterfaceProxy::Factory factory);

  
  
  
  void AddPPB(const char* name, const void* iface, Permission permission);
  void AddPPP(const char* name, const void* iface);

  
  static int HashInterfaceName(const std::string& name);

  PpapiPermissions permissions_;

  NameToInterfaceInfoMap name_to_browser_info_;
  NameToInterfaceInfoMap name_to_plugin_info_;

  InterfaceProxy::Factory id_to_factory_[API_ID_COUNT];

  DISALLOW_COPY_AND_ASSIGN(InterfaceList);
};

}  
}  

#endif  

