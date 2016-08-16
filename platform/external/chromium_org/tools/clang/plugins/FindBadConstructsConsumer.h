// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/Attr.h"
#include "clang/AST/CXXInheritance.h"
#include "clang/AST/TypeLoc.h"
#include "clang/Basic/SourceManager.h"

#include "ChromeClassTester.h"
#include "Options.h"

namespace chrome_checker {

class FindBadConstructsConsumer : public ChromeClassTester {
 public:
  FindBadConstructsConsumer(clang::CompilerInstance& instance,
                            const Options& options);

  
  virtual void CheckChromeClass(clang::SourceLocation record_location,
                                clang::CXXRecordDecl* record);
  virtual void CheckChromeEnum(clang::SourceLocation enum_location,
                               clang::EnumDecl* enum_decl);

 private:
  
  enum RefcountIssue { None, ImplicitDestructor, PublicDestructor };

  void CheckCtorDtorWeight(clang::SourceLocation record_location,
                           clang::CXXRecordDecl* record);

  void CheckVirtualMethod(const clang::CXXMethodDecl* method,
                          bool warn_on_inline_bodies);

  bool InTestingNamespace(const clang::Decl* record);
  bool IsMethodInBannedOrTestingNamespace(const clang::CXXMethodDecl* method);

  void CheckOverriddenMethod(const clang::CXXMethodDecl* method);
  void CheckVirtualMethods(clang::SourceLocation record_location,
                           clang::CXXRecordDecl* record,
                           bool warn_on_inline_bodies);

  void CountType(const clang::Type* type,
                 int* trivial_member,
                 int* non_trivial_member,
                 int* templated_non_trivial_member);

  static RefcountIssue CheckRecordForRefcountIssue(
      const clang::CXXRecordDecl* record,
      clang::SourceLocation& loc);
  clang::DiagnosticsEngine::Level getErrorLevel();
  static bool IsRefCountedCallback(const clang::CXXBaseSpecifier* base,
                                   clang::CXXBasePath& path,
                                   void* user_data);
  static bool HasPublicDtorCallback(const clang::CXXBaseSpecifier* base,
                                    clang::CXXBasePath& path,
                                    void* user_data);
  void PrintInheritanceChain(const clang::CXXBasePath& path);
  unsigned DiagnosticForIssue(RefcountIssue issue);
  void CheckRefCountedDtors(clang::SourceLocation record_location,
                            clang::CXXRecordDecl* record);

  void CheckWeakPtrFactoryMembers(clang::SourceLocation record_location,
                                  clang::CXXRecordDecl* record);

  const Options options_;

  unsigned diag_method_requires_override_;
  unsigned diag_method_requires_virtual_;
  unsigned diag_no_explicit_dtor_;
  unsigned diag_public_dtor_;
  unsigned diag_protected_non_virtual_dtor_;
  unsigned diag_weak_ptr_factory_order_;
  unsigned diag_bad_enum_last_value_;
  unsigned diag_note_inheritance_;
  unsigned diag_note_implicit_dtor_;
  unsigned diag_note_public_dtor_;
  unsigned diag_note_protected_non_virtual_dtor_;
};

}  
