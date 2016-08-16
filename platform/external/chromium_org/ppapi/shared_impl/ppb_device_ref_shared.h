// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_SHARED_IMPL_PPB_DEVICE_REF_SHARED_H_
#define PPAPI_SHARED_IMPL_PPB_DEVICE_REF_SHARED_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ppapi/shared_impl/resource.h"
#include "ppapi/thunk/ppb_device_ref_api.h"

namespace ppapi {

struct PPAPI_SHARED_EXPORT DeviceRefData {
  DeviceRefData();

  bool operator==(const DeviceRefData& other) const {
    return type == other.type && name == other.name && id == other.id;
  }

  PP_DeviceType_Dev type;
  std::string name;
  std::string id;
};

class PPAPI_SHARED_EXPORT PPB_DeviceRef_Shared
    : public Resource,
      public thunk::PPB_DeviceRef_API {
 public:
  PPB_DeviceRef_Shared(ResourceObjectType type,
                       PP_Instance instance,
                       const DeviceRefData& data);

  
  virtual PPB_DeviceRef_API* AsPPB_DeviceRef_API() OVERRIDE;

  
  virtual const DeviceRefData& GetDeviceRefData() const OVERRIDE;
  virtual PP_DeviceType_Dev GetType() OVERRIDE;
  virtual PP_Var GetName() OVERRIDE;

 private:
  DeviceRefData data_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(PPB_DeviceRef_Shared);
};

}  

#endif  