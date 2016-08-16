// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_RENDERER_SCRIPT_CONTEXT_SET_H_
#define EXTENSIONS_RENDERER_SCRIPT_CONTEXT_SET_H_

#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/bind.h"
#include "v8/include/v8.h"

class GURL;

namespace base {
class ListValue;
}

namespace content {
class RenderView;
}

namespace v8 {
class Context;
}

namespace extensions {
class ScriptContext;

class ScriptContextSet {
 public:
  ScriptContextSet();
  ~ScriptContextSet();

  int size() const;

  
  void Add(ScriptContext* context);

  
  
  
  void Remove(ScriptContext* context);

  
  typedef std::set<ScriptContext*> ContextSet;
  ContextSet GetAll() const;

  
  
  ScriptContext* GetCurrent() const;

  
  
  ScriptContext* GetCalling() const;

  
  
  ScriptContext* GetByV8Context(v8::Handle<v8::Context> context) const;

  
  
  
  
  
  
  void ForEach(const std::string& extension_id,
               content::RenderView* render_view,
               const base::Callback<void(ScriptContext*)>& callback) const;
  
  void ForEach(content::RenderView* render_view,
               const base::Callback<void(ScriptContext*)>& callback) const {
    ForEach("", render_view, callback);
  }
  
  void ForEach(const std::string& extension_id,
               const base::Callback<void(ScriptContext*)>& callback) const {
    ForEach(extension_id, NULL, callback);
  }

  
  
  
  
  
  ContextSet OnExtensionUnloaded(const std::string& extension_id);

 private:
  ContextSet contexts_;

  DISALLOW_COPY_AND_ASSIGN(ScriptContextSet);
};

}  

#endif  
