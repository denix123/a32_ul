// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_CRYPTO_HANDSHAKE_MESSAGE_H_
#define NET_QUIC_CRYPTO_CRYPTO_HANDSHAKE_MESSAGE_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/quic/quic_protocol.h"

namespace net {

class NET_EXPORT_PRIVATE CryptoHandshakeMessage {
 public:
  CryptoHandshakeMessage();
  CryptoHandshakeMessage(const CryptoHandshakeMessage& other);
  ~CryptoHandshakeMessage();

  CryptoHandshakeMessage& operator=(const CryptoHandshakeMessage& other);

  
  void Clear();

  
  
  const QuicData& GetSerialized() const;

  
  void MarkDirty();

  
  
  template<class T> void SetValue(QuicTag tag, const T& v) {
    tag_value_map_[tag] =
        std::string(reinterpret_cast<const char*>(&v), sizeof(v));
  }

  
  
  template<class T> void SetVector(QuicTag tag, const std::vector<T>& v) {
    if (v.empty()) {
      tag_value_map_[tag] = std::string();
    } else {
      tag_value_map_[tag] = std::string(reinterpret_cast<const char*>(&v[0]),
                                        v.size() * sizeof(T));
    }
  }

  
  QuicTag tag() const { return tag_; }
  
  void set_tag(QuicTag tag) { tag_ = tag; }

  const QuicTagValueMap& tag_value_map() const { return tag_value_map_; }

  
  
  void SetTaglist(QuicTag tag, ...);

  void SetStringPiece(QuicTag tag, base::StringPiece value);

  
  void Erase(QuicTag tag);

  
  
  
  
  
  QuicErrorCode GetTaglist(QuicTag tag, const QuicTag** out_tags,
                           size_t* out_len) const;

  bool GetStringPiece(QuicTag tag, base::StringPiece* out) const;

  
  
  
  QuicErrorCode GetNthValue24(QuicTag tag,
                              unsigned index,
                              base::StringPiece* out) const;
  QuicErrorCode GetUint16(QuicTag tag, uint16* out) const;
  QuicErrorCode GetUint32(QuicTag tag, uint32* out) const;
  QuicErrorCode GetUint64(QuicTag tag, uint64* out) const;

  
  
  size_t size() const;

  
  
  
  
  
  
  
  void set_minimum_size(size_t min_bytes);

  size_t minimum_size() const;

  
  
  std::string DebugString() const;

 private:
  
  
  
  
  
  
  
  QuicErrorCode GetPOD(QuicTag tag, void* out, size_t len) const;

  std::string DebugStringInternal(size_t indent) const;

  QuicTag tag_;
  QuicTagValueMap tag_value_map_;

  size_t minimum_size_;

  
  
  mutable scoped_ptr<QuicData> serialized_;
};

}  

#endif  
