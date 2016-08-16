// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_EXTENSIONS_EXTENSION_ERROR_UI_UTIL_H_
#define CHROME_BROWSER_UI_WEBUI_EXTENSIONS_EXTENSION_ERROR_UI_UTIL_H_

#include "base/callback.h"

class Profile;

namespace base {
class DictionaryValue;
}

namespace extensions {
namespace error_ui_util {

typedef base::Callback<void(const base::DictionaryValue&)>
    RequestFileSourceCallback;

void HandleRequestFileSource(const base::DictionaryValue* args,
                             Profile* profile,
                             const RequestFileSourceCallback& response);

void HandleOpenDevTools(const base::DictionaryValue* args);

}  
}  

#endif  
