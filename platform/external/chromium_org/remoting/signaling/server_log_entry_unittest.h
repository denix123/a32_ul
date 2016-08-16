// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <map>
#include <set>
#include <string>

namespace buzz {
class XmlElement;
}  

namespace remoting {

extern const char kJabberClientNamespace[];
extern const char kChromotingNamespace[];

buzz::XmlElement* GetLogElementFromStanza(buzz::XmlElement* stanza);

buzz::XmlElement* GetSingleLogEntryFromStanza(buzz::XmlElement* stanza);

bool VerifyStanza(
    const std::map<std::string, std::string>& key_value_pairs,
    const std::set<std::string> keys,
    const buzz::XmlElement* elem,
    std::string* error);

}  
