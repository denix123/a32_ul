// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_TEMPLATE_H_
#define TOOLS_GN_TEMPLATE_H_

#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"

class BlockNode;
class Err;
class FunctionCallNode;
class LocationRange;
class Scope;
class Value;

class Template : public base::RefCountedThreadSafe<Template> {
 public:
  
  Template(const Scope* scope, const FunctionCallNode* def);

  
  Template(scoped_ptr<Scope> closure, const FunctionCallNode* def);

  
  
  Value Invoke(Scope* scope,
               const FunctionCallNode* invocation,
               const std::vector<Value>& args,
               BlockNode* block,
               Err* err) const;

  
  LocationRange GetDefinitionRange() const;

 private:
  friend class base::RefCountedThreadSafe<Template>;

  Template();
  ~Template();

  scoped_ptr<Scope> closure_;
  const FunctionCallNode* definition_;
};

#endif  
