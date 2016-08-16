// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_APPLICATION_APPLICATION_DELEGATE_H_
#define MOJO_PUBLIC_APPLICATION_APPLICATION_DELEGATE_H_

#include <string>

#include "mojo/public/cpp/system/macros.h"

namespace mojo {

class ApplicationConnection;
class ApplicationImpl;

class ApplicationDelegate {
 public:
  ApplicationDelegate();
  virtual ~ApplicationDelegate();

  
  
  static ApplicationDelegate* Create();

  virtual void Initialize(ApplicationImpl* app);

  
  
  
  virtual bool ConfigureIncomingConnection(ApplicationConnection* connection);

  
  
  
  virtual bool ConfigureOutgoingConnection(ApplicationConnection* connection);

 private:
  MOJO_DISALLOW_COPY_AND_ASSIGN(ApplicationDelegate);
};

}  

#endif  
