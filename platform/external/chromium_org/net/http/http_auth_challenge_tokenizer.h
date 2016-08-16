// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_HTTP_AUTH_CHALLENGE_TOKENIZER_
#define NET_HTTP_HTTP_AUTH_CHALLENGE_TOKENIZER_

#include <string>

#include "net/base/net_export.h"
#include "net/http/http_util.h"

namespace net {

class NET_EXPORT_PRIVATE HttpAuthChallengeTokenizer {
 public:
  HttpAuthChallengeTokenizer(std::string::const_iterator begin,
                             std::string::const_iterator end);

  
  std::string challenge_text() const {
    return std::string(begin_, end_);
  }

  
  std::string::const_iterator scheme_begin() const { return scheme_begin_; }
  std::string::const_iterator scheme_end() const { return scheme_end_; }
  std::string scheme() const {
    return std::string(scheme_begin_, scheme_end_);
  }

  std::string::const_iterator params_begin() const { return params_begin_; }
  std::string::const_iterator params_end() const { return params_end_; }
  HttpUtil::NameValuePairsIterator param_pairs() const;
  std::string base64_param() const;

 private:
  void Init(std::string::const_iterator begin,
            std::string::const_iterator end);

  std::string::const_iterator begin_;
  std::string::const_iterator end_;

  std::string::const_iterator scheme_begin_;
  std::string::const_iterator scheme_end_;

  std::string::const_iterator params_begin_;
  std::string::const_iterator params_end_;
};

}  

#endif  
