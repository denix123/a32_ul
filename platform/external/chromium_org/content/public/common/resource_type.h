// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_COMMON_RESOURCE_TYPE_H_
#define CONTENT_PUBLIC_COMMON_RESOURCE_TYPE_H_

#include "content/common/content_export.h"

namespace content {

enum ResourceType {
  RESOURCE_TYPE_MAIN_FRAME = 0,  
  RESOURCE_TYPE_SUB_FRAME,       
  RESOURCE_TYPE_STYLESHEET,      
  RESOURCE_TYPE_SCRIPT,          
  RESOURCE_TYPE_IMAGE,           
  RESOURCE_TYPE_FONT_RESOURCE,   
  RESOURCE_TYPE_SUB_RESOURCE,    
  RESOURCE_TYPE_OBJECT,          
                                 
  RESOURCE_TYPE_MEDIA,           
  RESOURCE_TYPE_WORKER,          
  RESOURCE_TYPE_SHARED_WORKER,   
  RESOURCE_TYPE_PREFETCH,        
  RESOURCE_TYPE_FAVICON,         
  RESOURCE_TYPE_XHR,             
  RESOURCE_TYPE_PING,            
  RESOURCE_TYPE_SERVICE_WORKER,  
  RESOURCE_TYPE_LAST_TYPE
};

CONTENT_EXPORT bool IsResourceTypeFrame(ResourceType type);

}  

#endif  
