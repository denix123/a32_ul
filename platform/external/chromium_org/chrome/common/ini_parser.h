// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_INI_PARSER_H_
#define CHROME_COMMON_INI_PARSER_H_

#include <string>

#include "base/basictypes.h"
#include "base/values.h"

class INIParser {
 public:
  INIParser();
  virtual ~INIParser();

  
  void Parse(const std::string& content);

 private:
  virtual void HandleTriplet(const std::string& section,
                             const std::string& key,
                             const std::string& value) = 0;

  bool used_;
};

class DictionaryValueINIParser : public INIParser {
 public:
  DictionaryValueINIParser();
  virtual ~DictionaryValueINIParser();

  const base::DictionaryValue& root() const { return root_; }

 private:
  
  virtual void HandleTriplet(const std::string& section,
                             const std::string& key,
                             const std::string& value) OVERRIDE;

  base::DictionaryValue root_;

  DISALLOW_COPY_AND_ASSIGN(DictionaryValueINIParser);
};

#endif  
