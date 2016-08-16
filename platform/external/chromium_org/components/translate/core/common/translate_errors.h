// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_COMMON_TRANSLATE_ERRORS_H_
#define COMPONENTS_TRANSLATE_CORE_COMMON_TRANSLATE_ERRORS_H_

#include "base/basictypes.h"

namespace translate {


class TranslateErrors {
 public:
  enum Type {
    NONE = 0,
    NETWORK,                  
    INITIALIZATION_ERROR,     
    UNKNOWN_LANGUAGE,         
    UNSUPPORTED_LANGUAGE,     
                              
    IDENTICAL_LANGUAGES,      
    TRANSLATION_ERROR,        
                              
    TRANSLATION_TIMEOUT,      
    UNEXPECTED_SCRIPT_ERROR,  
    BAD_ORIGIN,               
    SCRIPT_LOAD_ERROR,        
    TRANSLATE_ERROR_MAX,
  };

 private:
  TranslateErrors() {}

  DISALLOW_COPY_AND_ASSIGN(TranslateErrors);
};

}  

#endif  
