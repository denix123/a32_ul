// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_SIGNALING_SERVER_LOG_ENTRY_H_
#define REMOTING_SIGNALING_SERVER_LOG_ENTRY_H_

#include <map>
#include <string>

#include "base/memory/scoped_ptr.h"

namespace buzz {
class XmlElement;
}  

namespace remoting {

class ServerLogEntry {
 public:
  
  enum Mode {
    IT2ME,
    ME2ME
  };

  ServerLogEntry();
  ~ServerLogEntry();

  
  void Set(const std::string& key, const std::string& value);

  
  void AddCpuField();

  
  void AddModeField(Mode mode);

  
  void AddRoleField(const char* role);

  
  void AddEventNameField(const char* name);

  
  
  
  static scoped_ptr<buzz::XmlElement> MakeStanza();

  
  scoped_ptr<buzz::XmlElement> ToStanza() const;

 private:
  typedef std::map<std::string, std::string> ValuesMap;

  ValuesMap values_map_;
};

}  

#endif  
