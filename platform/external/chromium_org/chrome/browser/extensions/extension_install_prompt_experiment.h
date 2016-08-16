// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_INSTALL_PROMPT_EXPERIMENT_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_INSTALL_PROMPT_EXPERIMENT_H_

#include "base/memory/ref_counted.h"

class ExtensionInstallPromptExperiment
    : public base::RefCounted<ExtensionInstallPromptExperiment> {
 public:
  ExtensionInstallPromptExperiment(unsigned int group_id, unsigned int flags);

  
  
  static ExtensionInstallPromptExperiment* Find();

  
  
  static ExtensionInstallPromptExperiment* ControlGroup();

  
  
  
  bool text_only() const;

  
  base::string16 GetExplanationText() const;

  
  base::string16 GetOkButtonText() const;

  
  base::string16 GetCancelButtonText() const;

  
  
  bool ShouldHighlightText(const base::string16& message) const;

  
  
  bool ShouldHighlightBackground(const base::string16& message) const;

  
  
  bool show_details_link() const;

  
  
  bool show_checkboxes() const;

  
  
  bool should_show_expandable_permission_list() const;

  
  
  bool should_show_inline_explanations() const;

  
  
  base::string16 GetInlineExplanation(const base::string16& message) const;

 private:
  friend class base::RefCounted<ExtensionInstallPromptExperiment>;
  ~ExtensionInstallPromptExperiment();

  
  const unsigned int group_id_;
  
  
  const unsigned int flags_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionInstallPromptExperiment);
};

#endif  
