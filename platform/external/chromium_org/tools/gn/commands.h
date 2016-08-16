// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_COMMANDS_H_
#define TOOLS_GN_COMMANDS_H_

#include <map>
#include <string>
#include <vector>

#include "base/strings/string_piece.h"

class BuildSettings;
class Setup;
class Target;


namespace commands {

typedef int (*CommandRunner)(const std::vector<std::string>&);

extern const char kArgs[];
extern const char kArgs_HelpShort[];
extern const char kArgs_Help[];
int RunArgs(const std::vector<std::string>& args);

extern const char kCheck[];
extern const char kCheck_HelpShort[];
extern const char kCheck_Help[];
int RunCheck(const std::vector<std::string>& args);

extern const char kDesc[];
extern const char kDesc_HelpShort[];
extern const char kDesc_Help[];
int RunDesc(const std::vector<std::string>& args);

extern const char kGen[];
extern const char kGen_HelpShort[];
extern const char kGen_Help[];
int RunGen(const std::vector<std::string>& args);

extern const char kFormat[];
extern const char kFormat_HelpShort[];
extern const char kFormat_Help[];
int RunFormat(const std::vector<std::string>& args);

extern const char kHelp[];
extern const char kHelp_HelpShort[];
extern const char kHelp_Help[];
int RunHelp(const std::vector<std::string>& args);

extern const char kLs[];
extern const char kLs_HelpShort[];
extern const char kLs_Help[];
int RunLs(const std::vector<std::string>& args);

extern const char kRefs[];
extern const char kRefs_HelpShort[];
extern const char kRefs_Help[];
int RunRefs(const std::vector<std::string>& args);


struct CommandInfo {
  CommandInfo();
  CommandInfo(const char* in_help_short,
              const char* in_help,
              CommandRunner in_runner);

  const char* help_short;
  const char* help;
  CommandRunner runner;
};

typedef std::map<base::StringPiece, CommandInfo> CommandInfoMap;

const CommandInfoMap& GetCommands();


const Target* ResolveTargetFromCommandLineString(
    Setup* setup,
    const std::string& label_string);

bool ResolveTargetsFromCommandLinePattern(
    Setup* setup,
    const std::string& label_pattern,
    bool all_toolchains,
    std::vector<const Target*>* matches);

bool CheckPublicHeaders(const BuildSettings* build_settings,
                        const std::vector<const Target*>& all_targets,
                        const std::vector<const Target*>& to_check,
                        bool force_check);

}  

#endif  
