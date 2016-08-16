// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_ACTION_VALUES_H_
#define TOOLS_GN_ACTION_VALUES_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "tools/gn/source_file.h"
#include "tools/gn/substitution_list.h"

class Target;

class ActionValues {
 public:
  ActionValues();
  ~ActionValues();

  
  const SourceFile& script() const { return script_; }
  void set_script(const SourceFile& s) { script_ = s; }

  
  SubstitutionList& args() { return args_; }
  const SubstitutionList& args() const { return args_; }

  
  
  SubstitutionList& outputs() { return outputs_; }
  const SubstitutionList& outputs() const { return outputs_; }

  
  void GetOutputsAsSourceFiles(const Target* target,
                               std::vector<SourceFile>* result) const;

  
  const SubstitutionPattern& depfile() const { return depfile_; }
  bool has_depfile() const { return !depfile_.ranges().empty(); }
  void set_depfile(const SubstitutionPattern& depfile) { depfile_ = depfile; }

 private:
  SourceFile script_;
  SubstitutionList args_;
  SubstitutionList outputs_;
  SubstitutionPattern depfile_;

  DISALLOW_COPY_AND_ASSIGN(ActionValues);
};

#endif  