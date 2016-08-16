// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_PPP_PDF_PROXY_H_
#define PPAPI_PROXY_PPP_PDF_PROXY_H_

#include "ppapi/c/private/ppp_pdf.h"
#include "ppapi/proxy/interface_proxy.h"

namespace ppapi {

namespace proxy {

class PPP_Pdf_Proxy : public InterfaceProxy {
 public:
  PPP_Pdf_Proxy(Dispatcher* dispatcher);
  virtual ~PPP_Pdf_Proxy();

  static const PPP_Pdf* GetProxyInterface();

  
  virtual bool OnMessageReceived(const IPC::Message& msg);

 private:
  
  void OnPluginMsgRotate(PP_Instance instance, bool clockwise);

  
  
  
  const PPP_Pdf* ppp_pdf_;

  DISALLOW_COPY_AND_ASSIGN(PPP_Pdf_Proxy);
};

}  
}  

#endif  
