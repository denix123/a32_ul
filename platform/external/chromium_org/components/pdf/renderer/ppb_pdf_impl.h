// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENT_PDF_RENDERER_PPB_PDF_IMPL_H_
#define COMPONENT_PDF_RENDERER_PPB_PDF_IMPL_H_

#include "ppapi/c/pp_instance.h"

struct PPB_PDF;

namespace pdf {

class PPB_PDF_Impl {
 public:
  class PrintClient {
   public:
    virtual ~PrintClient() {}

    
    
    virtual bool IsPrintingEnabled(PP_Instance instance_id) = 0;

    
    
    virtual bool Print(PP_Instance instance_id) = 0;
  };

  
  
  static const PPB_PDF* GetInterface();

  
  
  
  static bool InvokePrintingForInstance(PP_Instance instance);

  
  
  
  static void SetPrintClient(PrintClient* print_client);
};

}  

#endif  
