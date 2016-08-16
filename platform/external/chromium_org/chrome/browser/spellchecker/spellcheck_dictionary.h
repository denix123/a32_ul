// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SPELLCHECKER_SPELLCHECK_DICTIONARY_H_
#define CHROME_BROWSER_SPELLCHECKER_SPELLCHECK_DICTIONARY_H_

#include "base/basictypes.h"

class SpellcheckDictionary {
 public:
  SpellcheckDictionary() {}
  virtual ~SpellcheckDictionary() {}

  virtual void Load() = 0;

 protected:
  DISALLOW_COPY_AND_ASSIGN(SpellcheckDictionary);
};

#endif  