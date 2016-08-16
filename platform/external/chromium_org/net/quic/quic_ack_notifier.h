// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_ACK_NOTIFIER_H_
#define NET_QUIC_QUIC_ACK_NOTIFIER_H_

#include "base/memory/ref_counted.h"
#include "net/quic/quic_protocol.h"

namespace net {

class NET_EXPORT_PRIVATE QuicAckNotifier {
 public:
 class NET_EXPORT_PRIVATE DelegateInterface
     : public base::RefCounted<DelegateInterface> {
   public:
    DelegateInterface();
    
    
    
    
    
    
    virtual void OnAckNotification(int num_original_packets,
                                   int num_original_bytes,
                                   int num_retransmitted_packets,
                                   int num_retransmitted_bytes,
                                   QuicTime::Delta delta_largest_observed) = 0;
   protected:
    friend class base::RefCounted<DelegateInterface>;

    
    virtual ~DelegateInterface();
  };

  
  explicit QuicAckNotifier(DelegateInterface* delegate);
  virtual ~QuicAckNotifier();

  
  void AddSequenceNumber(const QuicPacketSequenceNumber& sequence_number,
                         int packet_payload_size);

  
  
  
  
  
  
  
  
  bool OnAck(QuicPacketSequenceNumber sequence_number,
             QuicTime::Delta delta_largest_observed);

  bool IsEmpty() { return sequence_numbers_.empty(); }

  
  
  
  void UpdateSequenceNumber(QuicPacketSequenceNumber old_sequence_number,
                            QuicPacketSequenceNumber new_sequence_number);

 private:
  struct PacketInfo {
    PacketInfo();
    explicit PacketInfo(int payload_size);

    int packet_payload_size;
  };

  
  
  
  scoped_refptr<DelegateInterface> delegate_;

  
  
  base::hash_map<QuicPacketSequenceNumber, PacketInfo> sequence_numbers_;

  
  
  int original_packet_count_;
  
  int original_byte_count_;
  
  int retransmitted_packet_count_;
  
  int retransmitted_byte_count_;

  DISALLOW_COPY_AND_ASSIGN(QuicAckNotifier);
};

};  

#endif  
