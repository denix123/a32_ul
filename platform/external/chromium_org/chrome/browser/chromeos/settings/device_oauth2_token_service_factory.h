// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_SETTINGS_DEVICE_OAUTH2_TOKEN_SERVICE_FACTORY_H_
#define CHROME_BROWSER_CHROMEOS_SETTINGS_DEVICE_OAUTH2_TOKEN_SERVICE_FACTORY_H_

#include <queue>
#include <string>

#include "base/basictypes.h"

namespace chromeos {

class DeviceOAuth2TokenService;

class DeviceOAuth2TokenServiceFactory {
 public:
  
  
  
  
  
  
  static DeviceOAuth2TokenService* Get();

  
  
  
  static void Initialize();

  
  
  
  
  static void Shutdown();

 private:
  DeviceOAuth2TokenServiceFactory();
  ~DeviceOAuth2TokenServiceFactory();

  DISALLOW_COPY_AND_ASSIGN(DeviceOAuth2TokenServiceFactory);
};

}  

#endif  
