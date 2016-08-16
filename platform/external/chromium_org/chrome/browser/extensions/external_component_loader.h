// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTERNAL_COMPONENT_LOADER_H_
#define CHROME_BROWSER_EXTENSIONS_EXTERNAL_COMPONENT_LOADER_H_

#include <string>

#include "base/compiler_specific.h"
#include "chrome/browser/extensions/external_loader.h"
#include "chrome/browser/profiles/profile.h"

namespace extensions {

class Extension;

class ExternalComponentLoader : public ExternalLoader {
 public:
  explicit ExternalComponentLoader(Profile* profile);

  
  static bool IsModifiable(const extensions::Extension* extension);

 protected:
  virtual void StartLoading() OVERRIDE;

 private:
  friend class base::RefCountedThreadSafe<ExternalLoader>;
  virtual ~ExternalComponentLoader();

  
  
  Profile* profile_;
  DISALLOW_COPY_AND_ASSIGN(ExternalComponentLoader);
};

}  

#endif  
