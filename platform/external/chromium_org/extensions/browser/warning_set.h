// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_WARNING_SET_H_
#define EXTENSIONS_BROWSER_WARNING_SET_H_

#include <set>
#include <string>
#include <vector>

#include "url/gurl.h"

namespace base {
class FilePath;
}

namespace extensions {

class ExtensionSet;

class Warning {
 public:
  enum WarningType {
    
    
    kInvalid = 0,
    
    kNetworkDelay,
    
    
    kNetworkConflict,
    
    
    kRedirectConflict,
    
    
    kRepeatedCacheFlushes,
    
    
    kDownloadFilenameConflict,
    kReloadTooFrequent,
    kMaxWarningType
  };

  
  Warning(const Warning& other);
  ~Warning();
  Warning& operator=(const Warning& other);

  
  static Warning CreateNetworkDelayWarning(
      const std::string& extension_id);
  static Warning CreateNetworkConflictWarning(
      const std::string& extension_id);
  static Warning CreateRedirectConflictWarning(
      const std::string& extension_id,
      const std::string& winning_extension_id,
      const GURL& attempted_redirect_url,
      const GURL& winning_redirect_url);
  static Warning CreateRequestHeaderConflictWarning(
      const std::string& extension_id,
      const std::string& winning_extension_id,
      const std::string& conflicting_header);
  static Warning CreateResponseHeaderConflictWarning(
      const std::string& extension_id,
      const std::string& winning_extension_id,
      const std::string& conflicting_header);
  static Warning CreateCredentialsConflictWarning(
      const std::string& extension_id,
      const std::string& winning_extension_id);
  static Warning CreateRepeatedCacheFlushesWarning(
      const std::string& extension_id);
  static Warning CreateDownloadFilenameConflictWarning(
      const std::string& losing_extension_id,
      const std::string& winning_extension_id,
      const base::FilePath& losing_filename,
      const base::FilePath& winning_filename);
  static Warning CreateReloadTooFrequentWarning(
      const std::string& extension_id);

  
  WarningType warning_type() const { return type_; }

  
  const std::string& extension_id() const { return extension_id_; }

  
  std::string GetLocalizedMessage(const ExtensionSet* extensions) const;

 private:
  
  
  
  
  Warning(WarningType type,
                   const std::string& extension_id,
                   int message_id,
                   const std::vector<std::string>& message_parameters);

  WarningType type_;
  std::string extension_id_;
  
  int message_id_;
  
  std::vector<std::string> message_parameters_;
};

bool operator<(const Warning& a, const Warning& b);

typedef std::set<Warning> WarningSet;

}  

#endif  
