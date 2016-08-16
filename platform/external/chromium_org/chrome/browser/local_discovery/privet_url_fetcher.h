// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_LOCAL_DISCOVERY_PRIVET_URL_FETCHER_H_
#define CHROME_BROWSER_LOCAL_DISCOVERY_PRIVET_URL_FETCHER_H_

#include <string>

#include "base/files/file_util.h"
#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "net/url_request/url_fetcher.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "net/url_request/url_request_context_getter.h"
#include "url/gurl.h"

namespace base {
class FilePath;
}

namespace local_discovery {

const int kPrivetHTTPCodeInternalFailure = -1;

class PrivetURLFetcher : public net::URLFetcherDelegate {
 public:
  enum ErrorType {
    JSON_PARSE_ERROR,
    URL_FETCH_ERROR,
    RESPONSE_CODE_ERROR,
    RETRY_ERROR,
    TOKEN_ERROR
  };

  typedef base::Callback<void(const std::string& )> TokenCallback;

  class Delegate {
   public:
    virtual ~Delegate() {}

    
    
    virtual void OnNeedPrivetToken(
        PrivetURLFetcher* fetcher,
        const TokenCallback& callback);

    
    virtual std::string GetAuthToken();

    virtual void OnError(PrivetURLFetcher* fetcher, ErrorType error) = 0;
    virtual void OnParsedJson(PrivetURLFetcher* fetcher,
                              const base::DictionaryValue& value,
                              bool has_error) = 0;

    
    
    
    virtual bool OnRawData(PrivetURLFetcher* fetcher,
                           bool response_is_file,
                           const std::string& data_string,
                           const base::FilePath& data_file);
  };

  PrivetURLFetcher(
      const GURL& url,
      net::URLFetcher::RequestType request_type,
      net::URLRequestContextGetter* request_context,
      Delegate* delegate);

  virtual ~PrivetURLFetcher();

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  static void SetTokenForHost(const std::string& host,
                              const std::string& token);

  static void ResetTokenMapForTests();

  void DoNotRetryOnTransientError();

  void SendEmptyPrivetToken();

  void V3Mode();

  
  
  void SetByteRange(int start, int end);

  
  
  void SaveResponseToFile();

  void Start();

  void SetUploadData(const std::string& upload_content_type,
                     const std::string& upload_data);

  void SetUploadFilePath(const std::string& upload_content_type,
                         const base::FilePath& upload_file_path);

  const GURL& url() const { return url_fetcher_->GetOriginalURL(); }
  int response_code() const { return url_fetcher_->GetResponseCode(); }

 private:
  void OnURLFetchCompleteParseData(const net::URLFetcher* source);
  bool OnURLFetchCompleteDoNotParseData(const net::URLFetcher* source);

  std::string GetHostString();  
  std::string GetPrivetAccessToken();
  void Try();
  void ScheduleRetry(int timeout_seconds);
  bool PrivetErrorTransient(const std::string& error);
  void RequestTokenRefresh();
  void RefreshToken(const std::string& token);

  GURL url_;
  net::URLFetcher::RequestType request_type_;
  scoped_refptr<net::URLRequestContextGetter> request_context_;
  Delegate* delegate_;

  bool do_not_retry_on_transient_error_;
  bool send_empty_privet_token_;
  bool has_byte_range_;
  bool make_response_file_;
  bool v3_mode_;

  int byte_range_start_;
  int byte_range_end_;

  int tries_;
  std::string upload_data_;
  std::string upload_content_type_;
  base::FilePath upload_file_path_;
  scoped_ptr<net::URLFetcher> url_fetcher_;

  base::WeakPtrFactory<PrivetURLFetcher> weak_factory_;
  DISALLOW_COPY_AND_ASSIGN(PrivetURLFetcher);
};

}  

#endif  
