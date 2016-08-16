// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_IN_MEMORY_CACHE_H_
#define NET_QUIC_QUIC_IN_MEMORY_CACHE_H_

#include <string>

#include "base/containers/hash_tables.h"
#include "base/files/file_util.h"
#include "base/memory/singleton.h"
#include "base/strings/string_piece.h"
#include "net/http/http_response_headers.h"

template <typename T> struct DefaultSingletonTraits;
class GURL;

namespace net {

extern base::FilePath::StringType g_quic_in_memory_cache_dir;

namespace test {
class QuicInMemoryCachePeer;
}  

class QuicServer;

class QuicInMemoryCache {
 public:
  enum SpecialResponseType {
    REGULAR_RESPONSE,  
    CLOSE_CONNECTION,  
    IGNORE_REQUEST,    
  };

  
  class Response {
   public:
    Response();
    ~Response();

    SpecialResponseType response_type() const { return response_type_; }
    const HttpResponseHeaders& headers() const { return *headers_.get(); }
    const base::StringPiece body() const { return base::StringPiece(body_); }

   private:
    friend class QuicInMemoryCache;

    void set_headers(scoped_refptr<HttpResponseHeaders> headers) {
      headers_ = headers;
    }
    void set_body(base::StringPiece body) {
      body.CopyToString(&body_);
    }

    SpecialResponseType response_type_;
    scoped_refptr<HttpResponseHeaders> headers_;
    std::string body_;

    DISALLOW_COPY_AND_ASSIGN(Response);
  };

  
  static QuicInMemoryCache* GetInstance();

  
  
  
  const Response* GetResponse(const GURL& url) const;

  
  
  void AddSimpleResponse(base::StringPiece path,
                         base::StringPiece version,
                         base::StringPiece response_code,
                         base::StringPiece response_detail,
                         base::StringPiece body);

  
  void AddResponse(const GURL& url,
                   scoped_refptr<HttpResponseHeaders> response_headers,
                   base::StringPiece response_body);

  
  void AddSpecialResponse(base::StringPiece path,
                          SpecialResponseType response_type);

 private:
  typedef base::hash_map<std::string, Response*> ResponseMap;
  friend struct DefaultSingletonTraits<QuicInMemoryCache>;
  friend class test::QuicInMemoryCachePeer;

  QuicInMemoryCache();
  ~QuicInMemoryCache();

  void ResetForTests();

  void Initialize();

  std::string GetKey(const GURL& url) const;

  
  ResponseMap responses_;

  DISALLOW_COPY_AND_ASSIGN(QuicInMemoryCache);
};

}  

#endif  
