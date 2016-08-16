// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_ACTION_TARGET_GENERATOR_H_
#define TOOLS_GN_ACTION_TARGET_GENERATOR_H_

#include "base/compiler_specific.h"
#include "tools/gn/target_generator.h"

class ActionTargetGenerator : public TargetGenerator {
 public:
  ActionTargetGenerator(Target* target,
                        Scope* scope,
                        const FunctionCallNode* function_call,
                        Target::OutputType type,
                        Err* err);
  virtual ~ActionTargetGenerator();

 protected:
  virtual void DoRun() OVERRIDE;

 private:
  bool FillScript();
  bool FillScriptArgs();
  bool FillDepfile();

  
  bool CheckOutputs();

  Target::OutputType output_type_;

  DISALLOW_COPY_AND_ASSIGN(ActionTargetGenerator);
};

#endif  