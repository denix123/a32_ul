// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSION_FUNCTION_H_
#define EXTENSIONS_BROWSER_EXTENSION_FUNCTION_H_

#include <list>
#include <string>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/process/process.h"
#include "base/sequenced_task_runner_helpers.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/common/console_message_level.h"
#include "extensions/browser/extension_function_histogram_value.h"
#include "extensions/browser/info_map.h"
#include "extensions/common/extension.h"
#include "extensions/common/features/feature.h"
#include "ipc/ipc_message.h"

class ExtensionFunction;
class UIThreadExtensionFunction;
class IOThreadExtensionFunction;

namespace base {
class ListValue;
class Value;
}

namespace content {
class BrowserContext;
class RenderFrameHost;
class RenderViewHost;
class WebContents;
}

namespace extensions {
class ExtensionFunctionDispatcher;
class ExtensionMessageFilter;
class QuotaLimitHeuristic;
}

namespace IPC {
class Sender;
}

#ifdef NDEBUG
#define EXTENSION_FUNCTION_VALIDATE(test) \
  do {                                    \
    if (!(test)) {                        \
      this->bad_message_ = true;          \
      return ValidationFailure(this);     \
    }                                     \
  } while (0)
#else   
#define EXTENSION_FUNCTION_VALIDATE(test) CHECK(test)
#endif  

#define EXTENSION_FUNCTION_ERROR(error) \
  do {                                  \
    error_ = error;                     \
    this->bad_message_ = true;          \
    return ValidationFailure(this);     \
  } while (0)

#define DECLARE_EXTENSION_FUNCTION(name, histogramvalue) \
  public: static const char* function_name() { return name; } \
  public: static extensions::functions::HistogramValue histogram_value() \
    { return extensions::functions::histogramvalue; }

struct ExtensionFunctionDeleteTraits {
 public:
  static void Destruct(const ExtensionFunction* x);
};

class ExtensionFunction
    : public base::RefCountedThreadSafe<ExtensionFunction,
                                        ExtensionFunctionDeleteTraits> {
 public:
  enum ResponseType {
    
    SUCCEEDED,
    
    FAILED,
    
    BAD_MESSAGE
  };

  typedef base::Callback<void(ResponseType type,
                              const base::ListValue& results,
                              const std::string& error)> ResponseCallback;

  ExtensionFunction();

  virtual UIThreadExtensionFunction* AsUIThreadExtensionFunction();
  virtual IOThreadExtensionFunction* AsIOThreadExtensionFunction();

  
  
  
  
  
  
  
  virtual bool HasPermission();

  
  
  
  
  class ResponseValueObject {
   public:
    virtual ~ResponseValueObject() {}

    
    virtual bool Apply() = 0;
  };
  typedef scoped_ptr<ResponseValueObject> ResponseValue;

  
  
  
  class ResponseActionObject {
   public:
    virtual ~ResponseActionObject() {}

    virtual void Execute() = 0;
  };
  typedef scoped_ptr<ResponseActionObject> ResponseAction;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual ResponseAction Run() WARN_UNUSED_RESULT = 0;

  
  
  
  
  
  virtual bool ShouldSkipQuotaLimiting() const;

  
  
  
  
  
  
  virtual void GetQuotaLimitHeuristics(
      extensions::QuotaLimitHeuristics* heuristics) const {}

  
  
  virtual void OnQuotaExceeded(const std::string& violation_error);

  
  virtual void SetArgs(const base::ListValue* args);

  
  void SetResult(base::Value* result);

  
  void SetResultList(scoped_ptr<base::ListValue> results);

  
  const base::ListValue* GetResultList() const;

  
  virtual std::string GetError() const;

  
  virtual void SetError(const std::string& error);

  
  void set_bad_message(bool bad_message) { bad_message_ = bad_message; }

  
  void set_name(const std::string& name) { name_ = name; }
  const std::string& name() const { return name_; }

  void set_profile_id(void* profile_id) { profile_id_ = profile_id; }
  void* profile_id() const { return profile_id_; }

  void set_extension(
      const scoped_refptr<const extensions::Extension>& extension) {
    extension_ = extension;
  }
  const extensions::Extension* extension() const { return extension_.get(); }
  const std::string& extension_id() const { return extension_->id(); }

  void set_request_id(int request_id) { request_id_ = request_id; }
  int request_id() { return request_id_; }

  void set_source_url(const GURL& source_url) { source_url_ = source_url; }
  const GURL& source_url() { return source_url_; }

  void set_has_callback(bool has_callback) { has_callback_ = has_callback; }
  bool has_callback() { return has_callback_; }

  void set_include_incognito(bool include) { include_incognito_ = include; }
  bool include_incognito() const { return include_incognito_; }

  void set_user_gesture(bool user_gesture) { user_gesture_ = user_gesture; }
  bool user_gesture() const { return user_gesture_; }

  void set_histogram_value(
      extensions::functions::HistogramValue histogram_value) {
    histogram_value_ = histogram_value; }
  extensions::functions::HistogramValue histogram_value() const {
    return histogram_value_; }

  void set_response_callback(const ResponseCallback& callback) {
    response_callback_ = callback;
  }

  void set_source_tab_id(int source_tab_id) { source_tab_id_ = source_tab_id; }
  int source_tab_id() const { return source_tab_id_; }

  void set_source_context_type(extensions::Feature::Context type) {
    source_context_type_ = type;
  }
  extensions::Feature::Context source_context_type() const {
    return source_context_type_;
  }

 protected:
  friend struct ExtensionFunctionDeleteTraits;

  
  
  
  ResponseValue NoArguments();
  
  
  
  ResponseValue OneArgument(base::Value* arg);
  
  
  
  
  ResponseValue TwoArguments(base::Value* arg1, base::Value* arg2);
  
  
  
  
  ResponseValue ArgumentList(scoped_ptr<base::ListValue> results);
  
  ResponseValue Error(const std::string& error);
  
  
  
  
  ResponseValue Error(const std::string& format, const std::string& s1);
  ResponseValue Error(const std::string& format,
                      const std::string& s1,
                      const std::string& s2);
  ResponseValue Error(const std::string& format,
                      const std::string& s1,
                      const std::string& s2,
                      const std::string& s3);
  
  ResponseValue BadMessage();

  
  
  
  ResponseAction RespondNow(ResponseValue result);
  
  ResponseAction RespondLater();

  
  
  
  static ResponseAction ValidationFailure(ExtensionFunction* function);

  
  
  void Respond(ResponseValue result);

  virtual ~ExtensionFunction();

  
  virtual void Destruct() const = 0;

  
  
  
  
  
  virtual void SendResponse(bool success) = 0;

  
  void SendResponseImpl(bool success);

  
  
  bool HasOptionalArgument(size_t index);

  
  int request_id_;

  
  void* profile_id_;

  
  scoped_refptr<const extensions::Extension> extension_;

  
  std::string name_;

  
  GURL source_url_;

  
  
  bool has_callback_;

  
  
  
  
  bool include_incognito_;

  
  bool user_gesture_;

  
  scoped_ptr<base::ListValue> args_;

  
  
  scoped_ptr<base::ListValue> results_;

  
  
  std::string error_;

  
  
  bool bad_message_;

  
  
  extensions::functions::HistogramValue histogram_value_;

  
  ResponseCallback response_callback_;

  
  int source_tab_id_;

  
  extensions::Feature::Context source_context_type_;

 private:
  void OnRespondingLater(ResponseValue response);

  DISALLOW_COPY_AND_ASSIGN(ExtensionFunction);
};

class UIThreadExtensionFunction : public ExtensionFunction {
 public:
  
  
  
  class DelegateForTests {
   public:
    virtual void OnSendResponse(UIThreadExtensionFunction* function,
                                bool success,
                                bool bad_message) = 0;
  };

  UIThreadExtensionFunction();

  virtual UIThreadExtensionFunction* AsUIThreadExtensionFunction() OVERRIDE;

  void set_test_delegate(DelegateForTests* delegate) {
    delegate_ = delegate;
  }

  
  
  virtual bool OnMessageReceived(const IPC::Message& message);

  
  
  void set_browser_context(content::BrowserContext* context) {
    context_ = context;
  }
  content::BrowserContext* browser_context() const { return context_; }

  void SetRenderViewHost(content::RenderViewHost* render_view_host);
  content::RenderViewHost* render_view_host() const {
    return render_view_host_;
  }
  void SetRenderFrameHost(content::RenderFrameHost* render_frame_host);
  content::RenderFrameHost* render_frame_host() const {
    return render_frame_host_;
  }

  void set_dispatcher(const base::WeakPtr<
      extensions::ExtensionFunctionDispatcher>& dispatcher) {
    dispatcher_ = dispatcher;
  }
  extensions::ExtensionFunctionDispatcher* dispatcher() const {
    return dispatcher_.get();
  }

  
  
  virtual content::WebContents* GetAssociatedWebContents();

 protected:
  
  void WriteToConsole(content::ConsoleMessageLevel level,
                      const std::string& message);

  friend struct content::BrowserThread::DeleteOnThread<
      content::BrowserThread::UI>;
  friend class base::DeleteHelper<UIThreadExtensionFunction>;

  virtual ~UIThreadExtensionFunction();

  virtual void SendResponse(bool success) OVERRIDE;

  
  void SetTransferredBlobUUIDs(const std::vector<std::string>& blob_uuids);

  
  base::WeakPtr<extensions::ExtensionFunctionDispatcher> dispatcher_;

  
  content::RenderViewHost* render_view_host_;

  
  
  
  content::RenderFrameHost* render_frame_host_;

  
  content::BrowserContext* context_;

 private:
  class RenderHostTracker;

  virtual void Destruct() const OVERRIDE;

  
  IPC::Sender* GetIPCSender();
  int GetRoutingID();

  scoped_ptr<RenderHostTracker> tracker_;

  DelegateForTests* delegate_;

  
  std::vector<std::string> transferred_blob_uuids_;
};

class IOThreadExtensionFunction : public ExtensionFunction {
 public:
  IOThreadExtensionFunction();

  virtual IOThreadExtensionFunction* AsIOThreadExtensionFunction() OVERRIDE;

  void set_ipc_sender(
      base::WeakPtr<extensions::ExtensionMessageFilter> ipc_sender,
      int routing_id) {
    ipc_sender_ = ipc_sender;
    routing_id_ = routing_id;
  }

  base::WeakPtr<extensions::ExtensionMessageFilter> ipc_sender_weak() const {
    return ipc_sender_;
  }

  int routing_id() const { return routing_id_; }

  void set_extension_info_map(const extensions::InfoMap* extension_info_map) {
    extension_info_map_ = extension_info_map;
  }
  const extensions::InfoMap* extension_info_map() const {
    return extension_info_map_.get();
  }

 protected:
  friend struct content::BrowserThread::DeleteOnThread<
      content::BrowserThread::IO>;
  friend class base::DeleteHelper<IOThreadExtensionFunction>;

  virtual ~IOThreadExtensionFunction();

  virtual void Destruct() const OVERRIDE;

  virtual void SendResponse(bool success) OVERRIDE;

 private:
  base::WeakPtr<extensions::ExtensionMessageFilter> ipc_sender_;
  int routing_id_;

  scoped_refptr<const extensions::InfoMap> extension_info_map_;
};

class AsyncExtensionFunction : public UIThreadExtensionFunction {
 public:
  AsyncExtensionFunction();

 protected:
  virtual ~AsyncExtensionFunction();

  
  
  
  
  
  virtual bool RunAsync() = 0;

  
  static bool ValidationFailure(AsyncExtensionFunction* function);

 private:
  virtual ResponseAction Run() OVERRIDE;
};

class SyncExtensionFunction : public UIThreadExtensionFunction {
 public:
  SyncExtensionFunction();

 protected:
  virtual ~SyncExtensionFunction();

  
  
  
  
  virtual bool RunSync() = 0;

  
  static bool ValidationFailure(SyncExtensionFunction* function);

 private:
  virtual ResponseAction Run() OVERRIDE;
};

class SyncIOThreadExtensionFunction : public IOThreadExtensionFunction {
 public:
  SyncIOThreadExtensionFunction();

 protected:
  virtual ~SyncIOThreadExtensionFunction();

  
  
  
  
  
  virtual bool RunSync() = 0;

  
  static bool ValidationFailure(SyncIOThreadExtensionFunction* function);

 private:
  virtual ResponseAction Run() OVERRIDE;
};

#endif  
