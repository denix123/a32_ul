// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_ERROR_MAP_H_
#define EXTENSIONS_BROWSER_ERROR_MAP_H_

#include <deque>
#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "extensions/browser/extension_error.h"

namespace extensions {

typedef std::deque<const ExtensionError*> ErrorList;

class ErrorMap {
 public:
  ErrorMap();
  ~ErrorMap();

  
  const ErrorList& GetErrorsForExtension(const std::string& extension_id) const;

  
  const ExtensionError* AddError(scoped_ptr<ExtensionError> error);

  
  void Remove(const std::string& extension_id);
  
  void RemoveErrorsForExtensionOfType(const std::string& extension_id,
                                      ExtensionError::Type type);
  
  void RemoveIncognitoErrors();
  
  void RemoveAllErrors();

  size_t size() const { return map_.size(); }

 private:
  
  
  class ExtensionEntry {
   public:
    ExtensionEntry();
    ~ExtensionEntry();

    
    void DeleteAllErrors();
    
    void DeleteIncognitoErrors();
    
    void DeleteErrorsOfType(ExtensionError::Type type);

    
    const ExtensionError* AddError(scoped_ptr<ExtensionError> error);

    const ErrorList* list() const { return &list_; }

   private:
    
    
    
    ErrorList list_;

    DISALLOW_COPY_AND_ASSIGN(ExtensionEntry);
  };
  typedef std::map<std::string, ExtensionEntry*> EntryMap;

  
  EntryMap map_;

  DISALLOW_COPY_AND_ASSIGN(ErrorMap);
};

}  

#endif  
