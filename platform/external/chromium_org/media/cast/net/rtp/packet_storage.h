// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_NET_RTP_SENDER_PACKET_STORAGE_PACKET_STORAGE_H_
#define MEDIA_CAST_NET_RTP_SENDER_PACKET_STORAGE_PACKET_STORAGE_H_

#include <deque>

#include "base/basictypes.h"
#include "media/cast/net/pacing/paced_sender.h"

namespace media {
namespace cast {

class PacketStorage {
 public:
  PacketStorage();
  virtual ~PacketStorage();

  
  void StoreFrame(uint32 frame_id, const SendPacketVector& packets);

  
  void ReleaseFrame(uint32 frame_id);

  
  
  
  const SendPacketVector* GetFrame8(uint8 frame_id_8bits) const;

  
  size_t GetNumberOfStoredFrames() const;

 private:
  std::deque<SendPacketVector> frames_;
  uint32 first_frame_id_in_list_;

  
  
  size_t zombie_count_;

  DISALLOW_COPY_AND_ASSIGN(PacketStorage);
};

}  
}  

#endif  
