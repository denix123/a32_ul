// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_ERROR_REPORTER_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_ERROR_REPORTER_H_

#include <string>
#include <vector>

#include "base/observer_list.h"
#include "base/strings/string16.h"

namespace base {
class MessageLoop;
class FilePath;
}

namespace content {
class BrowserContext;
}

class ExtensionErrorReporter {
 public:
  class Observer {
   public:
    virtual ~Observer() {}

    
    virtual void OnLoadFailure(content::BrowserContext* browser_context,
                               const base::FilePath& extension_path,
                               const std::string& error) = 0;
  };

  
  
  static void Init(bool enable_noisy_errors);

  
  static ExtensionErrorReporter* GetInstance();

  
  
  
  
  
  void ReportLoadError(const base::FilePath& extension_path,
                       const std::string& error,
                       content::BrowserContext* browser_context,
                       bool be_noisy);

  
  
  void ReportError(const base::string16& message, bool be_noisy);

  
  const std::vector<base::string16>* GetErrors();

  
  void ClearErrors();

  void AddObserver(Observer* observer);

  void RemoveObserver(Observer* observer);

 private:
  static ExtensionErrorReporter* instance_;

  explicit ExtensionErrorReporter(bool enable_noisy_errors);
  ~ExtensionErrorReporter();

  base::MessageLoop* ui_loop_;
  std::vector<base::string16> errors_;
  bool enable_noisy_errors_;

  ObserverList<Observer> observers_;
};

#endif  
