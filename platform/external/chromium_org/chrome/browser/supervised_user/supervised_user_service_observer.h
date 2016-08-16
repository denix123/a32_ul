// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_SERVICE_OBSERVER_H_
#define CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_SERVICE_OBSERVER_H_

class SupervisedUserServiceObserver {
 public:
  
  
  virtual void OnURLFilterChanged() {}

  
  
  virtual void OnCustodianInfoChanged() {}

 protected:
  virtual ~SupervisedUserServiceObserver() {}
};

#endif  
