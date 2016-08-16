// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_GEOLOCATION_PROVIDER_H_
#define CONTENT_PUBLIC_BROWSER_GEOLOCATION_PROVIDER_H_

#include "base/callback_list.h"
#include "content/common/content_export.h"

namespace content {
struct Geoposition;

class GeolocationProvider {
 public:
  CONTENT_EXPORT static GeolocationProvider* GetInstance();

  typedef base::Callback<void(const Geoposition&)> LocationUpdateCallback;
  typedef base::CallbackList<void(const Geoposition&)>::Subscription
      Subscription;

  
  
  
  virtual scoped_ptr<Subscription> AddLocationUpdateCallback(
      const LocationUpdateCallback& callback, bool use_high_accuracy) = 0;

  
  
  
  
  virtual void UserDidOptIntoLocationServices() = 0;

  
  
  
  
  
  
  
  
  
  
  virtual void OverrideLocationForTesting(const Geoposition& position) = 0;

 protected:
  virtual~GeolocationProvider() {}
};

}  

#endif  
