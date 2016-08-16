// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_GEOLOCATION_WIFI_DATA_PROVIDER_H_
#define CONTENT_BROWSER_GEOLOCATION_WIFI_DATA_PROVIDER_H_

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

class CONTENT_EXPORT WifiDataProvider
    : public base::RefCountedThreadSafe<WifiDataProvider> {
 public:
  WifiDataProvider();

  
  
  virtual void StartDataProvider() = 0;

  
  
  virtual void StopDataProvider() = 0;

  
  
  
  virtual bool GetData(WifiData* data) = 0;

  typedef base::Closure WifiDataUpdateCallback;

  void AddCallback(WifiDataUpdateCallback* callback);

  bool RemoveCallback(WifiDataUpdateCallback* callback);

  bool has_callbacks() const;

 protected:
  friend class base::RefCountedThreadSafe<WifiDataProvider>;
  virtual ~WifiDataProvider();

  typedef std::set<WifiDataUpdateCallback*> CallbackSet;

  
  
  void RunCallbacks();

  bool CalledOnClientThread() const;

  base::MessageLoop* client_loop() const;

 private:
  void DoRunCallbacks();

  
  
  base::MessageLoop* client_loop_;

  CallbackSet callbacks_;

  DISALLOW_COPY_AND_ASSIGN(WifiDataProvider);
};

}  

#endif  
