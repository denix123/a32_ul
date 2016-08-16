// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SHELL_DBUS_APPLICATION_LOADER_LINUX_H_
#define MOJO_SHELL_DBUS_APPLICATION_LOADER_LINUX_H_

#include <map>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "mojo/application_manager/application_loader.h"
#include "mojo/public/cpp/system/core.h"
#include "url/gurl.h"

namespace dbus {
class Bus;
}  

namespace mojo {
namespace shell {

class Context;

class DBusApplicationLoader : public ApplicationLoader {
 public:
  DBusApplicationLoader(Context* context);
  virtual ~DBusApplicationLoader();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void Load(ApplicationManager* manager,
                    const GURL& url,
                    scoped_refptr<LoadCallbacks> callbacks) OVERRIDE;

  virtual void OnApplicationError(ApplicationManager* manager,
                                  const GURL& url) OVERRIDE;

 private:
  class LoadContext;

  
  void ForgetService(const GURL& url);

  Context* const context_;
  scoped_refptr<dbus::Bus> bus_;

  typedef std::map<GURL, LoadContext*> LoadContextMap;
  LoadContextMap url_to_load_context_;

  DISALLOW_COPY_AND_ASSIGN(DBusApplicationLoader);
};

}  
}  

#endif  
