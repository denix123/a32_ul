// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_SENT_ENTROPY_MANAGER_H_
#define NET_QUIC_QUIC_SENT_ENTROPY_MANAGER_H_

#include <deque>

#include "net/base/linked_hash_map.h"
#include "net/quic/quic_framer.h"
#include "net/quic/quic_protocol.h"

namespace net {

namespace test {
class QuicConnectionPeer;
}  

class NET_EXPORT_PRIVATE QuicSentEntropyManager {
 public:
  QuicSentEntropyManager();
  virtual ~QuicSentEntropyManager();

  
  void RecordPacketEntropyHash(QuicPacketSequenceNumber sequence_number,
                               QuicPacketEntropyHash entropy_hash);

  
  
  QuicPacketEntropyHash GetCumulativeEntropy(
      QuicPacketSequenceNumber sequence_number);

  
  
  
  bool IsValidEntropy(QuicPacketSequenceNumber largest_observed,
                      const SequenceNumberSet& missing_packets,
                      QuicPacketEntropyHash entropy_hash);

  
  void ClearEntropyBefore(QuicPacketSequenceNumber sequence_number);

 private:
  friend class test::QuicConnectionPeer;

  typedef std::deque<QuicPacketEntropyHash> SentEntropyMap;

  struct CumulativeEntropy {
    CumulativeEntropy() : sequence_number(0), entropy(0) {}

    QuicPacketSequenceNumber sequence_number;
    QuicPacketEntropyHash entropy;
  };

  
  QuicPacketSequenceNumber GetLargestPacketWithEntropy() const;
  QuicPacketSequenceNumber GetSmallestPacketWithEntropy() const;
  
  QuicPacketEntropyHash GetPacketEntropy(
      QuicPacketSequenceNumber sequence_number) const;

  
  void UpdateCumulativeEntropy(QuicPacketSequenceNumber sequence_number,
                               CumulativeEntropy* cumulative) const;

  
  SentEntropyMap packets_entropy_;
  QuicPacketSequenceNumber map_offset_;

  
  CumulativeEntropy last_valid_entropy_;

  
  CumulativeEntropy last_cumulative_entropy_;

  DISALLOW_COPY_AND_ASSIGN(QuicSentEntropyManager);
};

}  

#endif  
