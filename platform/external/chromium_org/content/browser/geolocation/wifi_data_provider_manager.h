// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CONTENT_BROWSER_GEOLOCATION_WIFI_DATA_PROVIDER_MANAGER_H_
#define CONTENT_BROWSER_GEOLOCATION_WIFI_DATA_PROVIDER_MANAGER_H_

#include <set>

#include "base/basictypes.h"
#include "base/bind.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/message_loop/message_loop.h"
#include "base/strings/string16.h"
#include "base/strings/string_util.h"
#include "content/browser/geolocation/wifi_data.h"
#include "content/common/content_export.h"

namespace content {

class WifiDataProvider;

class CONTENT_EXPORT WifiDataProviderManager {
 public:
  typedef WifiDataProvider* (*ImplFactoryFunction)(void);

  
  
  
  
  static void SetFactoryForTesting(ImplFactoryFunction factory_function_in);

  
  static void ResetFactoryForTesting();

  typedef base::Closure WifiDataUpdateCallback;

  
  
  static WifiDataProviderManager* Register(WifiDataUpdateCallback* callback);

  
  
  static bool Unregister(WifiDataUpdateCallback* callback);

  
  
  
  bool GetData(WifiData* data);

 private:
  
  
  WifiDataProviderManager();
  ~WifiDataProviderManager();

  void AddCallback(WifiDataUpdateCallback* callback);
  bool RemoveCallback(WifiDataUpdateCallback* callback);
  bool has_callbacks() const;

  void StartDataProvider();
  void StopDataProvider();

  static WifiDataProvider* DefaultFactoryFunction();

  
  
  
  static WifiDataProviderManager* instance_;

  
  static ImplFactoryFunction factory_function_;

  
  scoped_refptr<WifiDataProvider> impl_;

  DISALLOW_COPY_AND_ASSIGN(WifiDataProviderManager);
};

}  

#endif  
