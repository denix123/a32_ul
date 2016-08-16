// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_URL_FIXER_URL_FIXER_H_
#define COMPONENTS_URL_FIXER_URL_FIXER_H_

#include <string>

#include "base/strings/string16.h"
#include "url/gurl.h"

namespace base {
class FilePath;
}

namespace url {
struct Component;
struct Parsed;
}

namespace url_fixer {

std::string SegmentURL(const std::string& text, url::Parsed* parts);
base::string16 SegmentURL(const base::string16& text, url::Parsed* parts);

GURL FixupURL(const std::string& text, const std::string& desired_tld);

GURL FixupRelativeFile(const base::FilePath& base_dir,
                       const base::FilePath& text);

void OffsetComponent(int offset, url::Component* part);

bool IsEquivalentScheme(const std::string& scheme1, const std::string& scheme2);

extern const char* home_directory_override;

}  

#endif  
