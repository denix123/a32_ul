// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_GEOLOCATION_GEOPOSITION_H_
#define CHROME_BROWSER_CHROMEOS_GEOLOCATION_GEOPOSITION_H_

#include <string>

#include "base/time/time.h"

namespace chromeos {

struct Geoposition {
  
  
  enum Status {
    STATUS_NONE,
    STATUS_OK,             
    STATUS_SERVER_ERROR,   
    STATUS_NETWORK_ERROR,  
    STATUS_TIMEOUT,        
    STATUS_LAST = STATUS_TIMEOUT
  };

  
  
  Geoposition();

  
  bool Valid() const;

  
  std::string ToString() const;

  
  double latitude;

  
  double longitude;

  
  double accuracy;

  
  
  int error_code;

  
  std::string error_message;

  
  
  
  base::Time timestamp;

  
  Status status;
};

}  

#endif  
