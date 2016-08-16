// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_FUNCTIONS_H_
#define TOOLS_GN_FUNCTIONS_H_

#include <map>
#include <string>
#include <vector>

#include "base/strings/string_piece.h"

class Err;
class BlockNode;
class FunctionCallNode;
class Label;
class ListNode;
class ParseNode;
class Scope;
class Token;
class Value;


namespace functions {

typedef Value (*SelfEvaluatingArgsFunction)(Scope* scope,
                                            const FunctionCallNode* function,
                                            const ListNode* args_list,
                                            Err* err);

typedef Value (*GenericBlockFunction)(Scope* scope,
                                      const FunctionCallNode* function,
                                      const std::vector<Value>& args,
                                      BlockNode* block,
                                      Err* err);

typedef Value(*ExecutedBlockFunction)(const FunctionCallNode* function,
                                      const std::vector<Value>& args,
                                      Scope* block_scope,
                                      Err* err);

typedef Value (*NoBlockFunction)(Scope* scope,
                                 const FunctionCallNode* function,
                                 const std::vector<Value>& args,
                                 Err* err);

extern const char kAction[];
extern const char kAction_HelpShort[];
extern const char kAction_Help[];
Value RunAction(Scope* scope,
                const FunctionCallNode* function,
                const std::vector<Value>& args,
                BlockNode* block,
                Err* err);

extern const char kActionForEach[];
extern const char kActionForEach_HelpShort[];
extern const char kActionForEach_Help[];
Value RunActionForEach(Scope* scope,
                       const FunctionCallNode* function,
                       const std::vector<Value>& args,
                       BlockNode* block,
                       Err* err);

extern const char kAssert[];
extern const char kAssert_HelpShort[];
extern const char kAssert_Help[];
Value RunAssert(Scope* scope,
                const FunctionCallNode* function,
                const std::vector<Value>& args,
                Err* err);

extern const char kConfig[];
extern const char kConfig_HelpShort[];
extern const char kConfig_Help[];
Value RunConfig(const FunctionCallNode* function,
                const std::vector<Value>& args,
                Scope* block_scope,
                Err* err);

extern const char kCopy[];
extern const char kCopy_HelpShort[];
extern const char kCopy_Help[];
Value RunCopy(const FunctionCallNode* function,
              const std::vector<Value>& args,
              Scope* block_scope,
              Err* err);

extern const char kDeclareArgs[];
extern const char kDeclareArgs_HelpShort[];
extern const char kDeclareArgs_Help[];
Value RunDeclareArgs(Scope* scope,
                     const FunctionCallNode* function,
                     const std::vector<Value>& args,
                     BlockNode* block,
                     Err* err);

extern const char kDefined[];
extern const char kDefined_HelpShort[];
extern const char kDefined_Help[];
Value RunDefined(Scope* scope,
                 const FunctionCallNode* function,
                 const ListNode* args_list,
                 Err* err);

extern const char kExecScript[];
extern const char kExecScript_HelpShort[];
extern const char kExecScript_Help[];
Value RunExecScript(Scope* scope,
                    const FunctionCallNode* function,
                    const std::vector<Value>& args,
                    Err* err);

extern const char kExecutable[];
extern const char kExecutable_HelpShort[];
extern const char kExecutable_Help[];
Value RunExecutable(Scope* scope,
                    const FunctionCallNode* function,
                    const std::vector<Value>& args,
                    BlockNode* block,
                    Err* err);

extern const char kForEach[];
extern const char kForEach_HelpShort[];
extern const char kForEach_Help[];
Value RunForEach(Scope* scope,
                 const FunctionCallNode* function,
                 const ListNode* args_list,
                 Err* err);

extern const char kGetEnv[];
extern const char kGetEnv_HelpShort[];
extern const char kGetEnv_Help[];
Value RunGetEnv(Scope* scope,
                const FunctionCallNode* function,
                const std::vector<Value>& args,
                Err* err);

extern const char kGetLabelInfo[];
extern const char kGetLabelInfo_HelpShort[];
extern const char kGetLabelInfo_Help[];
Value RunGetLabelInfo(Scope* scope,
                      const FunctionCallNode* function,
                      const std::vector<Value>& args,
                      Err* err);

extern const char kGetPathInfo[];
extern const char kGetPathInfo_HelpShort[];
extern const char kGetPathInfo_Help[];
Value RunGetPathInfo(Scope* scope,
                     const FunctionCallNode* function,
                     const std::vector<Value>& args,
                     Err* err);

extern const char kGetTargetOutputs[];
extern const char kGetTargetOutputs_HelpShort[];
extern const char kGetTargetOutputs_Help[];
Value RunGetTargetOutputs(Scope* scope,
                          const FunctionCallNode* function,
                          const std::vector<Value>& args,
                          Err* err);

extern const char kGroup[];
extern const char kGroup_HelpShort[];
extern const char kGroup_Help[];
Value RunGroup(Scope* scope,
               const FunctionCallNode* function,
               const std::vector<Value>& args,
               BlockNode* block,
               Err* err);

extern const char kImport[];
extern const char kImport_HelpShort[];
extern const char kImport_Help[];
Value RunImport(Scope* scope,
                const FunctionCallNode* function,
                const std::vector<Value>& args,
                Err* err);

extern const char kPrint[];
extern const char kPrint_HelpShort[];
extern const char kPrint_Help[];
Value RunPrint(Scope* scope,
               const FunctionCallNode* function,
               const std::vector<Value>& args,
               Err* err);

extern const char kProcessFileTemplate[];
extern const char kProcessFileTemplate_HelpShort[];
extern const char kProcessFileTemplate_Help[];
Value RunProcessFileTemplate(Scope* scope,
                             const FunctionCallNode* function,
                             const std::vector<Value>& args,
                             Err* err);

extern const char kReadFile[];
extern const char kReadFile_HelpShort[];
extern const char kReadFile_Help[];
Value RunReadFile(Scope* scope,
                  const FunctionCallNode* function,
                  const std::vector<Value>& args,
                  Err* err);

extern const char kRebasePath[];
extern const char kRebasePath_HelpShort[];
extern const char kRebasePath_Help[];
Value RunRebasePath(Scope* scope,
                    const FunctionCallNode* function,
                    const std::vector<Value>& args,
                    Err* err);

extern const char kSetDefaults[];
extern const char kSetDefaults_HelpShort[];
extern const char kSetDefaults_Help[];
Value RunSetDefaults(Scope* scope,
                     const FunctionCallNode* function,
                     const std::vector<Value>& args,
                     BlockNode* block,
                     Err* err);

extern const char kSetDefaultToolchain[];
extern const char kSetDefaultToolchain_HelpShort[];
extern const char kSetDefaultToolchain_Help[];
Value RunSetDefaultToolchain(Scope* scope,
                             const FunctionCallNode* function,
                             const std::vector<Value>& args,
                             Err* err);

extern const char kSetSourcesAssignmentFilter[];
extern const char kSetSourcesAssignmentFilter_HelpShort[];
extern const char kSetSourcesAssignmentFilter_Help[];
Value RunSetSourcesAssignmentFilter(Scope* scope,
                                    const FunctionCallNode* function,
                                    const std::vector<Value>& args,
                                    Err* err);

extern const char kSharedLibrary[];
extern const char kSharedLibrary_HelpShort[];
extern const char kSharedLibrary_Help[];
Value RunSharedLibrary(Scope* scope,
                       const FunctionCallNode* function,
                       const std::vector<Value>& args,
                       BlockNode* block,
                       Err* err);

extern const char kSourceSet[];
extern const char kSourceSet_HelpShort[];
extern const char kSourceSet_Help[];
Value RunSourceSet(Scope* scope,
                   const FunctionCallNode* function,
                   const std::vector<Value>& args,
                   BlockNode* block,
                   Err* err);

extern const char kStaticLibrary[];
extern const char kStaticLibrary_HelpShort[];
extern const char kStaticLibrary_Help[];
Value RunStaticLibrary(Scope* scope,
                       const FunctionCallNode* function,
                       const std::vector<Value>& args,
                       BlockNode* block,
                       Err* err);

extern const char kTemplate[];
extern const char kTemplate_HelpShort[];
extern const char kTemplate_Help[];
Value RunTemplate(Scope* scope,
                  const FunctionCallNode* function,
                  const std::vector<Value>& args,
                  BlockNode* block,
                  Err* err);

extern const char kTool[];
extern const char kTool_HelpShort[];
extern const char kTool_Help[];
Value RunTool(Scope* scope,
              const FunctionCallNode* function,
              const std::vector<Value>& args,
              BlockNode* block,
              Err* err);

extern const char kToolchain[];
extern const char kToolchain_HelpShort[];
extern const char kToolchain_Help[];
Value RunToolchain(Scope* scope,
                   const FunctionCallNode* function,
                   const std::vector<Value>& args,
                   BlockNode* block,
                   Err* err);

extern const char kToolchainArgs[];
extern const char kToolchainArgs_HelpShort[];
extern const char kToolchainArgs_Help[];
Value RunToolchainArgs(Scope* scope,
                       const FunctionCallNode* function,
                       const std::vector<Value>& args,
                       BlockNode* block,
                       Err* err);

extern const char kWriteFile[];
extern const char kWriteFile_HelpShort[];
extern const char kWriteFile_Help[];
Value RunWriteFile(Scope* scope,
                   const FunctionCallNode* function,
                   const std::vector<Value>& args,
                   Err* err);


struct FunctionInfo {
  FunctionInfo();
  FunctionInfo(SelfEvaluatingArgsFunction seaf,
               const char* in_help_short,
               const char* in_help,
               bool in_is_target);
  FunctionInfo(GenericBlockFunction gbf,
               const char* in_help_short,
               const char* in_help,
               bool in_is_target);
  FunctionInfo(ExecutedBlockFunction ebf,
               const char* in_help_short,
               const char* in_help,
               bool in_is_target);
  FunctionInfo(NoBlockFunction nbf,
               const char* in_help_short,
               const char* in_help,
               bool in_is_target);

  SelfEvaluatingArgsFunction self_evaluating_args_runner;
  GenericBlockFunction generic_block_runner;
  ExecutedBlockFunction executed_block_runner;
  NoBlockFunction no_block_runner;

  const char* help_short;
  const char* help;

  bool is_target;
};

typedef std::map<base::StringPiece, FunctionInfo> FunctionInfoMap;

const FunctionInfoMap& GetFunctions();

Value RunFunction(Scope* scope,
                  const FunctionCallNode* function,
                  const ListNode* args_list,
                  BlockNode* block,  
                  Err* err);

}  


bool EnsureNotProcessingImport(const ParseNode* node,
                               const Scope* scope,
                               Err* err);

bool EnsureNotProcessingBuildConfig(const ParseNode* node,
                                    const Scope* scope,
                                    Err* err);

bool FillTargetBlockScope(const Scope* scope,
                          const FunctionCallNode* function,
                          const std::string& target_type,
                          const BlockNode* block,
                          const std::vector<Value>& args,
                          Scope* block_scope,
                          Err* err);

void FillNeedsBlockError(const FunctionCallNode* function, Err* err);

bool EnsureSingleStringArg(const FunctionCallNode* function,
                           const std::vector<Value>& args,
                           Err* err);

const Label& ToolchainLabelForScope(const Scope* scope);

Label MakeLabelForScope(const Scope* scope,
                        const FunctionCallNode* function,
                        const std::string& name);

#endif  
