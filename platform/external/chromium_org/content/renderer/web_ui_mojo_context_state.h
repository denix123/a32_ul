// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_WEB_UI_MOJO_CONTEXT_STATE_H_
#define CONTENT_RENDERER_WEB_UI_MOJO_CONTEXT_STATE_H_

#include <set>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "gin/modules/module_registry_observer.h"
#include "v8/include/v8.h"

namespace blink {
class WebFrame;
class WebURLResponse;
}

namespace gin {
class ContextHolder;
struct PendingModule;
}

namespace content {

class ResourceFetcher;
class WebUIRunner;

class WebUIMojoContextState : public gin::ModuleRegistryObserver {
 public:
  WebUIMojoContextState(blink::WebFrame* frame,
                        v8::Handle<v8::Context> context);
  virtual ~WebUIMojoContextState();

  void Run();

  
  bool module_added() const { return module_added_; }

 private:
  class Loader;

  
  
  void FetchModules(const std::vector<std::string>& ids);

  
  void FetchModule(const std::string& module);

  
  void OnFetchModuleComplete(ResourceFetcher* fetcher,
                             const blink::WebURLResponse& response,
                             const std::string& data);

  
  virtual void OnDidAddPendingModule(
      const std::string& id,
      const std::vector<std::string>& dependencies) OVERRIDE;

  
  blink::WebFrame* frame_;

  
  bool module_added_;

  
  scoped_ptr<WebUIRunner> runner_;

  
  ScopedVector<ResourceFetcher> module_fetchers_;

  
  std::set<std::string> fetched_modules_;

  DISALLOW_COPY_AND_ASSIGN(WebUIMojoContextState);
};

}  

#endif  
