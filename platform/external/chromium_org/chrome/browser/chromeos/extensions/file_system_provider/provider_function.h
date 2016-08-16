// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_SYSTEM_PROVIDER_PROVIDER_FUNCTION_H_
#define CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_SYSTEM_PROVIDER_PROVIDER_FUNCTION_H_

#include <string>

#include "base/files/file.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "chrome/common/extensions/api/file_system_provider.h"

namespace base {
class DictionaryValue;
}  

namespace chromeos {
namespace file_system_provider {

class RequestManager;
class RequestValue;

}  
}  

namespace extensions {

extern const char kNotFoundErrorName[];
extern const char kSecurityErrorName[];

extern const char kEmptyNameErrorMessage[];
extern const char kEmptyIdErrorMessage[];
extern const char kMountFailedErrorMessage[];
extern const char kUnmountFailedErrorMessage[];
extern const char kResponseFailedErrorMessage[];

base::DictionaryValue* CreateError(const std::string& name,
                                   const std::string& message);

base::File::Error ProviderErrorToFileError(
    api::file_system_provider::ProviderError error);

class FileSystemProviderInternalFunction : public ChromeSyncExtensionFunction {
 public:
  FileSystemProviderInternalFunction();

 protected:
  virtual ~FileSystemProviderInternalFunction() {}

  
  void RejectRequest(
      scoped_ptr<chromeos::file_system_provider::RequestValue> value,
      base::File::Error error);

  
  
  
  
  void FulfillRequest(
      scoped_ptr<chromeos::file_system_provider::RequestValue> value,
      bool has_more);

  
  
  
  virtual bool RunWhenValid() = 0;

  
  virtual bool RunSync() OVERRIDE;

 private:
  
  
  bool Parse();

  
  void SetErrorResponse(const std::string& name, const std::string& message);

  int request_id_;
  chromeos::file_system_provider::RequestManager* request_manager_;
};

}  

#endif  
