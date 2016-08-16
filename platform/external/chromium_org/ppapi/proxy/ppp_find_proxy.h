// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_PPP_FIND_PROXY_H_
#define PPAPI_PROXY_PPP_FIND_PROXY_H_

#include <string>

#include "ppapi/c/private/ppp_find_private.h"
#include "ppapi/proxy/interface_proxy.h"

namespace ppapi {

namespace proxy {

class PPP_Find_Proxy : public InterfaceProxy {
 public:
  explicit PPP_Find_Proxy(Dispatcher* dispatcher);
  virtual ~PPP_Find_Proxy();

  static const PPP_Find_Private* GetProxyInterface();

  
  virtual bool OnMessageReceived(const IPC::Message& msg);

 private:
  
  void OnPluginMsgStartFind(PP_Instance instance,
                            const std::string& text);
  void OnPluginMsgSelectFindResult(PP_Instance instance,
                                   PP_Bool forward);
  void OnPluginMsgStopFind(PP_Instance instance);

  
  
  
  const PPP_Find_Private* ppp_find_;

  DISALLOW_COPY_AND_ASSIGN(PPP_Find_Proxy);
};

}  
}  

#endif  
