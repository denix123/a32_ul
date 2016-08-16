// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_CHROMEDRIVER_PERFORMANCE_LOGGER_H_
#define CHROME_TEST_CHROMEDRIVER_PERFORMANCE_LOGGER_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "chrome/test/chromedriver/capabilities.h"
#include "chrome/test/chromedriver/chrome/devtools_event_listener.h"
#include "chrome/test/chromedriver/command_listener.h"

class Log;
struct Session;


class PerformanceLogger : public DevToolsEventListener, public CommandListener {
 public:
  
  
  PerformanceLogger(Log* log, const Session* session);

  
  PerformanceLogger(Log* log,
                    const Session* session,
                    const PerfLoggingPrefs& prefs);

  
  virtual bool subscribes_to_browser() OVERRIDE;

  
  
  virtual Status OnConnected(DevToolsClient* client) OVERRIDE;

  
  virtual Status OnEvent(DevToolsClient* client,
                         const std::string& method,
                         const base::DictionaryValue& params) OVERRIDE;

  
  virtual Status BeforeCommand(const std::string& command_name) OVERRIDE;

 private:
  void AddLogEntry(Log::Level level,
                   const std::string& webview,
                   const std::string& method,
                   const base::DictionaryValue& params);

  void AddLogEntry(const std::string& webview,
                   const std::string& method,
                   const base::DictionaryValue& params);

  
  Status EnableInspectorDomains(DevToolsClient* client);

  
  Status HandleInspectorEvents(DevToolsClient* client,
                               const std::string& method,
                               const base::DictionaryValue& params);

  
  Status HandleTraceEvents(DevToolsClient* client,
                           const std::string& method,
                           const base::DictionaryValue& params);

  bool ShouldReportTracingError();
  Status StartTrace();  
  Status CollectTraceEvents();  
  Status IsTraceDone(bool* trace_done) const; 

  Log* log_;  
  const Session* session_;
  PerfLoggingPrefs prefs_;
  DevToolsClient* browser_client_; 
  bool trace_buffering_;  

  DISALLOW_COPY_AND_ASSIGN(PerformanceLogger);
};

#endif  
