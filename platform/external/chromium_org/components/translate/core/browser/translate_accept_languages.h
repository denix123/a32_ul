// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_TRANSLATE_TRANSLATE_ACCEPT_LANGUAGES_H_
#define CHROME_BROWSER_TRANSLATE_TRANSLATE_ACCEPT_LANGUAGES_H_

#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/prefs/pref_change_registrar.h"

class PrefService;

namespace translate {

class TranslateAcceptLanguages {
 public:

  
  
  TranslateAcceptLanguages(PrefService* prefs,
                           const char* accept_languages_pref);
  virtual ~TranslateAcceptLanguages();

  
  
  static bool CanBeAcceptLanguage(const std::string& language);

  
  
  
  bool IsAcceptLanguage(const std::string& language);

 private:
  
  
  void InitAcceptLanguages(PrefService* prefs);

  
  std::set<std::string> accept_languages_;

  
  PrefChangeRegistrar pref_change_registrar_;

  
  const std::string accept_languages_pref_;

  DISALLOW_COPY_AND_ASSIGN(TranslateAcceptLanguages);
};

}  

#endif  
