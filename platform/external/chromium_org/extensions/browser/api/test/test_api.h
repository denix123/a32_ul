// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_TEST_TEST_API_H_
#define EXTENSIONS_BROWSER_API_TEST_TEST_API_H_

#include "base/values.h"
#include "extensions/browser/extension_function.h"

template <typename T>
struct DefaultSingletonTraits;

namespace extensions {

class TestExtensionFunction : public SyncExtensionFunction {
 protected:
  virtual ~TestExtensionFunction();

  
  virtual bool RunSync() OVERRIDE;

  virtual bool RunSafe() = 0;
};

class TestNotifyPassFunction : public TestExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("test.notifyPass", UNKNOWN)

 protected:
  virtual ~TestNotifyPassFunction();

  
  virtual bool RunSafe() OVERRIDE;
};

class TestNotifyFailFunction : public TestExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("test.notifyFail", UNKNOWN)

 protected:
  virtual ~TestNotifyFailFunction();

  
  virtual bool RunSafe() OVERRIDE;
};

class TestLogFunction : public TestExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("test.log", UNKNOWN)

 protected:
  virtual ~TestLogFunction();

  
  virtual bool RunSafe() OVERRIDE;
};

class TestSendMessageFunction : public AsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("test.sendMessage", UNKNOWN)

  
  
  void Reply(const std::string& message);

  
  void ReplyWithError(const std::string& error);

 protected:
  virtual ~TestSendMessageFunction();

  
  virtual bool RunAsync() OVERRIDE;
};

class TestGetConfigFunction : public TestExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("test.getConfig", UNKNOWN)

  
  
  static void set_test_config_state(base::DictionaryValue* value);

 protected:
  
  
  
  
  class TestConfigState {
   public:
    static TestConfigState* GetInstance();

    void set_config_state(base::DictionaryValue* config_state) {
      config_state_ = config_state;
    }

    const base::DictionaryValue* config_state() { return config_state_; }

   private:
    friend struct DefaultSingletonTraits<TestConfigState>;
    TestConfigState();

    base::DictionaryValue* config_state_;

    DISALLOW_COPY_AND_ASSIGN(TestConfigState);
  };

  virtual ~TestGetConfigFunction();

  
  virtual bool RunSafe() OVERRIDE;
};

class TestWaitForRoundTripFunction : public TestExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("test.waitForRoundTrip", UNKNOWN)

 protected:
  virtual ~TestWaitForRoundTripFunction();

  
  virtual bool RunSafe() OVERRIDE;
};

}  

#endif  
