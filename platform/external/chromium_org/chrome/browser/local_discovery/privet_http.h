// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_LOCAL_DISCOVERY_PRIVET_HTTP_H_
#define CHROME_BROWSER_LOCAL_DISCOVERY_PRIVET_HTTP_H_

#include <string>

#include "base/callback.h"
#include "chrome/browser/local_discovery/privet_url_fetcher.h"
#include "net/base/host_port_pair.h"

namespace base {
class RefCountedBytes;
}

namespace gfx {
class Size;
}

namespace printing {
class PdfRenderSettings;
}

namespace local_discovery {

class PWGRasterConverter;
class PrivetHTTPClient;

class PrivetJSONOperation {
 public:
  
  typedef base::Callback<void(
      const base::DictionaryValue* )> ResultCallback;

  virtual ~PrivetJSONOperation() {}

  virtual void Start() = 0;

  virtual PrivetHTTPClient* GetHTTPClient() = 0;
};

class PrivetHTTPClient {
 public:
  virtual ~PrivetHTTPClient() {}

  
  virtual const std::string& GetName() = 0;

  
  virtual scoped_ptr<PrivetJSONOperation> CreateInfoOperation(
      const PrivetJSONOperation::ResultCallback& callback) = 0;

  
  virtual scoped_ptr<PrivetURLFetcher> CreateURLFetcher(
      const GURL& url,
      net::URLFetcher::RequestType request_type,
      PrivetURLFetcher::Delegate* delegate) = 0;

  virtual void RefreshPrivetToken(
      const PrivetURLFetcher::TokenCallback& token_callback) = 0;
};

class PrivetDataReadOperation {
 public:
  enum ResponseType {
    RESPONSE_TYPE_ERROR,
    RESPONSE_TYPE_STRING,
    RESPONSE_TYPE_FILE
  };

  
  typedef base::Callback<void(
      ResponseType ,
      const std::string& ,
      const base::FilePath& )> ResultCallback;

  virtual ~PrivetDataReadOperation() {}

  virtual void Start() = 0;

  virtual void SetDataRange(int range_start, int range_end) = 0;

  virtual void SaveDataToFile() = 0;

  virtual PrivetHTTPClient* GetHTTPClient() = 0;
};

class PrivetRegisterOperation {
 public:
  enum FailureReason {
    FAILURE_NETWORK,
    FAILURE_HTTP_ERROR,
    FAILURE_JSON_ERROR,
    FAILURE_MALFORMED_RESPONSE,
    FAILURE_TOKEN,
    FAILURE_RETRY
  };

  class Delegate {
   public:
    ~Delegate() {}

    
    virtual void OnPrivetRegisterClaimToken(
        PrivetRegisterOperation* operation,
        const std::string& token,
        const GURL& url) = 0;

    
    
    
    
    
    
    virtual void OnPrivetRegisterError(PrivetRegisterOperation* operation,
                                       const std::string& action,
                                       FailureReason reason,
                                       int printer_http_code,
                                       const base::DictionaryValue* json) = 0;

    
    virtual void OnPrivetRegisterDone(PrivetRegisterOperation* operation,
                                      const std::string& device_id) = 0;
  };

  virtual ~PrivetRegisterOperation() {}

  virtual void Start() = 0;
  
  virtual void Cancel() = 0;
  virtual void CompleteRegistration() = 0;

  virtual PrivetHTTPClient* GetHTTPClient() = 0;
};

class PrivetLocalPrintOperation {
 public:
  class Delegate {
   public:
    virtual ~Delegate() {}
    virtual void OnPrivetPrintingDone(
        const PrivetLocalPrintOperation* print_operation) = 0;
    virtual void OnPrivetPrintingError(
        const PrivetLocalPrintOperation* print_operation, int http_code) = 0;
  };

  virtual ~PrivetLocalPrintOperation() {}

  virtual void Start() = 0;


  
  virtual void SetData(const scoped_refptr<base::RefCountedBytes>& data) = 0;

  
  
  virtual void SetTicket(const std::string& ticket) = 0;
  
  virtual void SetCapabilities(const std::string& capabilities) = 0;
  
  virtual void SetUsername(const std::string& username) = 0;
  virtual void SetJobname(const std::string& jobname) = 0;
  
  
  virtual void SetOffline(bool offline) = 0;
  
  virtual void SetPageSize(const gfx::Size& page_size) = 0;

  
  virtual void SetPWGRasterConverterForTesting(
      scoped_ptr<PWGRasterConverter> pwg_raster_converter) = 0;

  virtual PrivetHTTPClient* GetHTTPClient() = 0;
};

class PrivetV1HTTPClient {
 public:
  virtual ~PrivetV1HTTPClient() {}

  static scoped_ptr<PrivetV1HTTPClient> CreateDefault(
      scoped_ptr<PrivetHTTPClient> info_client);

  
  virtual const std::string& GetName() = 0;

  
  virtual scoped_ptr<PrivetJSONOperation> CreateInfoOperation(
      const PrivetJSONOperation::ResultCallback& callback) = 0;

  
  virtual scoped_ptr<PrivetRegisterOperation> CreateRegisterOperation(
      const std::string& user,
      PrivetRegisterOperation::Delegate* delegate) = 0;

  
  virtual scoped_ptr<PrivetJSONOperation> CreateCapabilitiesOperation(
      const PrivetJSONOperation::ResultCallback& callback) = 0;

  
  virtual scoped_ptr<PrivetLocalPrintOperation> CreateLocalPrintOperation(
      PrivetLocalPrintOperation::Delegate* delegate) = 0;
};

}  
#endif  
