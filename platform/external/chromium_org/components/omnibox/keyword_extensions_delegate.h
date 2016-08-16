// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_KEYWORD_EXTENSIONS_DELEGATE_H_
#define COMPONENTS_OMNIBOX_KEYWORD_EXTENSIONS_DELEGATE_H_

#include <string>

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/strings/string16.h"

class AutocompleteInput;
class KeywordProvider;
class TemplateURL;

class KeywordExtensionsDelegate {
 public:
  explicit KeywordExtensionsDelegate(KeywordProvider* provider);
  virtual ~KeywordExtensionsDelegate();

  
  
  virtual void IncrementInputId();

  
  virtual bool IsEnabledExtension(const std::string& extension_id);

  
  
  
  
  
  
  virtual bool Start(const AutocompleteInput& input,
                     bool minimal_changes,
                     const TemplateURL* template_url,
                     const base::string16& remaining_input);

  
  
  virtual void EnterExtensionKeywordMode(const std::string& extension_id);

  
  
  
  virtual void MaybeEndExtensionKeywordMode();

 private:
  DISALLOW_COPY_AND_ASSIGN(KeywordExtensionsDelegate);
};

#endif  
