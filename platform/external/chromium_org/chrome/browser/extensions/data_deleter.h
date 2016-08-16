// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_DATA_DELETER_H_
#define CHROME_BROWSER_EXTENSIONS_DATA_DELETER_H_

#include <string>
#include "base/basictypes.h"
#include "base/callback_forward.h"

class Profile;

namespace extensions {

class Extension;

class DataDeleter {
 public:
  
  
  
  
  
  
  
  static void StartDeleting(Profile* profile,
                            const Extension* extenion,
                            const base::Closure& callback);

  DISALLOW_COPY_AND_ASSIGN(DataDeleter);
};

}  

#endif  
