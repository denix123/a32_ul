// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_NET_STRING_UTIL_H__
#define NET_BASE_NET_STRING_UTIL_H__

#include <string>

#include "base/strings/string16.h"


namespace net {

extern const char* const kCharsetLatin1;

bool ConvertToUtf8(const std::string& text, const char* charset,
                   std::string* output);

bool ConvertToUtf8AndNormalize(const std::string& text, const char* charset,
                               std::string* output);

bool ConvertToUTF16(const std::string& text, const char* charset,
                    base::string16* output);

bool ConvertToUTF16WithSubstitutions(const std::string& text,
                                     const char* charset,
                                     base::string16* output);

}  

#endif  
