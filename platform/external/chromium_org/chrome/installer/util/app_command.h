// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_INSTALLER_UTIL_APP_COMMAND_H_
#define CHROME_INSTALLER_UTIL_APP_COMMAND_H_

#include <windows.h>

#include "base/strings/string16.h"

class WorkItemList;

namespace base {
namespace win {
class RegKey;
}
}

namespace installer {

class AppCommand {
 public:
  AppCommand();
  
  
  explicit AppCommand(const base::string16& command_line);
  

  
  bool Initialize(const base::win::RegKey& key);

  
  
  void AddWorkItems(HKEY predefined_root,
                    const base::string16& command_path,
                    WorkItemList* item_list) const;

  
  
  
  const base::string16& command_line() const { return command_line_; }
  void set_command_line(const base::string16& command_line) {
    command_line_ = command_line;
  }

  bool sends_pings() const { return sends_pings_; }
  void set_sends_pings(bool sends_pings) { sends_pings_ = sends_pings; }

  bool is_web_accessible() const { return is_web_accessible_; }
  void set_is_web_accessible(bool is_web_accessible) {
    is_web_accessible_ = is_web_accessible;
  }

  bool is_auto_run_on_os_upgrade() const { return is_auto_run_on_os_upgrade_; }
  void set_is_auto_run_on_os_upgrade(bool is_auto_run_on_os_upgrade) {
    is_auto_run_on_os_upgrade_ = is_auto_run_on_os_upgrade;
  }

  bool is_run_as_user() const { return is_run_as_user_; }
  void set_is_run_as_user(bool is_run_as_user) {
    is_run_as_user_ = is_run_as_user;
  }

 protected:
  base::string16 command_line_;
  bool sends_pings_;
  bool is_web_accessible_;
  bool is_auto_run_on_os_upgrade_;
  bool is_run_as_user_;

 private:
  struct NamedBoolVar {
    bool AppCommand::* data;
    const wchar_t* name;
  };

  static const NamedBoolVar kNameBoolVars[];
};

}  

#endif  