// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_FILTER_MOCK_FILTER_CONTEXT_H_
#define NET_FILTER_MOCK_FILTER_CONTEXT_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "net/filter/filter.h"
#include "url/gurl.h"

namespace net {

class URLRequestContext;

class MockFilterContext : public FilterContext {
 public:
  MockFilterContext();
  virtual ~MockFilterContext();

  void SetMimeType(const std::string& mime_type) { mime_type_ = mime_type; }
  void SetURL(const GURL& gurl) { gurl_ = gurl; }
  void SetContentDisposition(const std::string& disposition) {
    content_disposition_ = disposition;
  }
  void SetRequestTime(const base::Time time) { request_time_ = time; }
  void SetCached(bool is_cached) { is_cached_content_ = is_cached; }
  void SetDownload(bool is_download) { is_download_ = is_download; }
  void SetResponseCode(int response_code) { response_code_ = response_code; }
  void SetSdchResponse(bool is_sdch_response) {
    is_sdch_response_ = is_sdch_response;
  }
  URLRequestContext* GetModifiableURLRequestContext() const {
    return context_.get();
  }

  
  
  
  void NukeUnstableInterfaces();

  virtual bool GetMimeType(std::string* mime_type) const OVERRIDE;

  
  
  virtual bool GetURL(GURL* gurl) const OVERRIDE;

  
  
  virtual bool GetContentDisposition(std::string* disposition) const OVERRIDE;

  
  virtual base::Time GetRequestTime() const OVERRIDE;

  
  virtual bool IsCachedContent() const OVERRIDE;

  
  virtual bool IsDownload() const OVERRIDE;

  
  virtual bool SdchResponseExpected() const OVERRIDE;

  
  virtual int64 GetByteReadCount() const OVERRIDE;

  virtual int GetResponseCode() const OVERRIDE;

  
  virtual const URLRequestContext* GetURLRequestContext() const OVERRIDE;

  virtual void RecordPacketStats(StatisticSelector statistic) const OVERRIDE {}

 private:
  int buffer_size_;
  std::string mime_type_;
  std::string content_disposition_;
  GURL gurl_;
  base::Time request_time_;
  bool is_cached_content_;
  bool is_download_;
  bool is_sdch_response_;
  bool ok_to_call_get_url_;
  int response_code_;
  scoped_ptr<URLRequestContext> context_;

  DISALLOW_COPY_AND_ASSIGN(MockFilterContext);
};

}  

#endif  
