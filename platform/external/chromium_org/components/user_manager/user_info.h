// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_USER_MANAGER_USER_INFO_H_
#define COMPONENTS_USER_MANAGER_USER_INFO_H_

#include <string>

#include "base/strings/string16.h"
#include "components/user_manager/user_manager_export.h"

namespace gfx {
class ImageSkia;
}

namespace user_manager {

class USER_MANAGER_EXPORT UserInfo {
 public:
  UserInfo();
  virtual ~UserInfo();

  
  virtual base::string16 GetDisplayName() const = 0;

  
  virtual base::string16 GetGivenName() const = 0;

  
  
  
  virtual std::string GetEmail() const = 0;

  
  
  virtual std::string GetUserID() const = 0;

  
  virtual const gfx::ImageSkia& GetImage() const = 0;
};

}  

#endif  
