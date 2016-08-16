// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_DECLARATIVE_DECLARATIVE_API_H_
#define EXTENSIONS_BROWSER_API_DECLARATIVE_DECLARATIVE_API_H_

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "extensions/browser/api/declarative/rules_registry.h"
#include "extensions/browser/extension_function.h"

namespace extensions {

class RulesFunction : public AsyncExtensionFunction {
 public:
  RulesFunction();

 protected:
  virtual ~RulesFunction();

  
  virtual bool HasPermission() OVERRIDE;
  virtual bool RunAsync() OVERRIDE;

  
  
  
  virtual bool RunAsyncOnCorrectThread() = 0;

  scoped_refptr<RulesRegistry> rules_registry_;
};

class EventsEventAddRulesFunction : public RulesFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("events.addRules", EVENTS_ADDRULES)

 protected:
  virtual ~EventsEventAddRulesFunction() {}

  
  virtual bool RunAsyncOnCorrectThread() OVERRIDE;
};

class EventsEventRemoveRulesFunction : public RulesFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("events.removeRules", EVENTS_REMOVERULES)

 protected:
  virtual ~EventsEventRemoveRulesFunction() {}

  
  virtual bool RunAsyncOnCorrectThread() OVERRIDE;
};

class EventsEventGetRulesFunction : public RulesFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("events.getRules", EVENTS_GETRULES)

 protected:
  virtual ~EventsEventGetRulesFunction() {}

  
  virtual bool RunAsyncOnCorrectThread() OVERRIDE;
};

}  

#endif  
