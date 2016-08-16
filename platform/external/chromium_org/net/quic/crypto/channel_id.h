// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_CHANNEL_ID_H_
#define NET_QUIC_CRYPTO_CHANNEL_ID_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/quic/quic_types.h"

namespace net {

class NET_EXPORT_PRIVATE ChannelIDKey {
 public:
  virtual ~ChannelIDKey() {}

  
  
  virtual bool Sign(base::StringPiece signed_data,
                    std::string* out_signature) const = 0;

  
  virtual std::string SerializeKey() const = 0;
};

class ChannelIDSourceCallback {
 public:
  virtual ~ChannelIDSourceCallback() {}

  
  
  
  
  virtual void Run(scoped_ptr<ChannelIDKey>* channel_id_key) = 0;
};

class NET_EXPORT_PRIVATE ChannelIDSource {
 public:
  virtual ~ChannelIDSource() {}

  
  
  
  
  
  
  
  
  virtual QuicAsyncStatus GetChannelIDKey(
      const std::string& hostname,
      scoped_ptr<ChannelIDKey>* channel_id_key,
      ChannelIDSourceCallback* callback) = 0;
};

class NET_EXPORT_PRIVATE ChannelIDVerifier {
 public:
  
  
  
  static const char kContextStr[];
  
  
  
  static const char kClientToServerStr[];

  
  
  static bool Verify(base::StringPiece key,
                     base::StringPiece signed_data,
                     base::StringPiece signature);

  
  
  
  
  static bool VerifyRaw(base::StringPiece key,
                        base::StringPiece signed_data,
                        base::StringPiece signature,
                        bool is_channel_id_signature);

 private:
  DISALLOW_COPY_AND_ASSIGN(ChannelIDVerifier);
};

}  

#endif  
