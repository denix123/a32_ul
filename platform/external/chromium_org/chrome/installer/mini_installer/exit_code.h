// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_INSTALLER_MINI_INSTALLER_EXIT_CODE_H_
#define CHROME_INSTALLER_MINI_INSTALLER_EXIT_CODE_H_

namespace mini_installer {

enum ExitCode {
  SUCCESS_EXIT_CODE = 0,
  GENERIC_ERROR = 1,
  
  
  
  
  GENERIC_INITIALIZATION_FAILURE = 101,
  GENERIC_UNPACKING_FAILURE = 102,
  GENERIC_SETUP_FAILURE = 103,
};

}  

#endif  
