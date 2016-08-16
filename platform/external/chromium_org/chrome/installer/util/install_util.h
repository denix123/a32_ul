// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_INSTALLER_UTIL_INSTALL_UTIL_H_
#define CHROME_INSTALLER_UTIL_INSTALL_UTIL_H_

#include <windows.h>
#include <tchar.h>

#include "base/basictypes.h"
#include "base/command_line.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/strings/string16.h"
#include "base/win/scoped_handle.h"
#include "chrome/installer/util/browser_distribution.h"
#include "chrome/installer/util/util_constants.h"

class WorkItemList;

namespace base {
class Version;
}

class InstallUtil {
 public:
  
  
  static base::string16 GetActiveSetupPath(BrowserDistribution* dist);

  
  
  static void TriggerActiveSetupCommand();

  
  static bool ExecuteExeAsAdmin(const base::CommandLine& cmd, DWORD* exit_code);

  
  
  
  static base::CommandLine GetChromeUninstallCmd(
      bool system_install,
      BrowserDistribution::Type distribution_type);

  
  
  
  
  
  static void GetChromeVersion(BrowserDistribution* dist,
                               bool system_install,
                               base::Version* version);

  
  
  
  
  
  
  static void GetCriticalUpdateVersion(BrowserDistribution* dist,
                                       bool system_install,
                                       base::Version* version);

  
  static bool IsOSSupported();

  
  
  
  
  
  static void AddInstallerResultItems(bool system_install,
                                      const base::string16& state_key,
                                      installer::InstallStatus status,
                                      int string_resource_id,
                                      const base::string16* const launch_cmd,
                                      WorkItemList* install_list);

  
  
  
  static void UpdateInstallerStage(bool system_install,
                                   const base::string16& state_key_path,
                                   installer::InstallerStage stage);

  
  
  
  static bool IsPerUserInstall(const wchar_t* const exe_path);

  
  
  static bool IsMultiInstall(BrowserDistribution* dist, bool system_install);

  
  
  
  
  static bool IsChromeSxSProcess();

  
  static bool IsFirstRunSentinelPresent();

  
  static bool GetEULASentinelFilePath(base::FilePath* path);

  
  static bool DeleteRegistryKey(HKEY root_key,
                                const base::string16& key_path,
                                REGSAM wow64_access);

  
  
  static bool DeleteRegistryValue(HKEY reg_root, const base::string16& key_path,
                                  REGSAM wow64_access,
                                  const base::string16& value_name);

  
  
  class RegistryValuePredicate {
   public:
    virtual ~RegistryValuePredicate() { }
    virtual bool Evaluate(const base::string16& value) const = 0;
  };

  
  enum ConditionalDeleteResult {
    NOT_FOUND,      
    DELETED,        
    DELETE_FAILED   
  };

  
  
  
  
  static ConditionalDeleteResult DeleteRegistryKeyIf(
      HKEY root_key,
      const base::string16& key_to_delete_path,
      const base::string16& key_to_test_path,
      REGSAM wow64_access,
      const wchar_t* value_name,
      const RegistryValuePredicate& predicate);

  
  
  
  static ConditionalDeleteResult DeleteRegistryValueIf(
      HKEY root_key,
      const wchar_t* key_path,
      REGSAM wow64_access,
      const wchar_t* value_name,
      const RegistryValuePredicate& predicate);

  
  class ValueEquals : public RegistryValuePredicate {
   public:
    explicit ValueEquals(const base::string16& value_to_match)
        : value_to_match_(value_to_match) { }
    virtual bool Evaluate(const base::string16& value) const OVERRIDE;
   protected:
    base::string16 value_to_match_;
   private:
    DISALLOW_COPY_AND_ASSIGN(ValueEquals);
  };

  
  static int GetInstallReturnCode(installer::InstallStatus install_status);

  
  static void MakeUninstallCommand(const base::string16& program,
                                   const base::string16& arguments,
                                   base::CommandLine* command_line);

  
  static base::string16 GetCurrentDate();

  
  
  
  
  class ProgramCompare : public RegistryValuePredicate {
   public:
    explicit ProgramCompare(const base::FilePath& path_to_match);
    virtual ~ProgramCompare();
    virtual bool Evaluate(const base::string16& value) const OVERRIDE;
    bool EvaluatePath(const base::FilePath& path) const;

   protected:
    static bool OpenForInfo(const base::FilePath& path, base::File* file);
    static bool GetInfo(const base::File& file,
                        BY_HANDLE_FILE_INFORMATION* info);

    base::FilePath path_to_match_;
    base::File file_;
    BY_HANDLE_FILE_INFORMATION file_info_;

   private:
    DISALLOW_COPY_AND_ASSIGN(ProgramCompare);
  };  

 private:
  DISALLOW_COPY_AND_ASSIGN(InstallUtil);
};


#endif  
