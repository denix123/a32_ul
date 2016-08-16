// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_MIDI_HOST_H_
#define CONTENT_BROWSER_MEDIA_MIDI_HOST_H_

#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "content/common/content_export.h"
#include "content/public/browser/browser_message_filter.h"
#include "content/public/browser/browser_thread.h"
#include "media/midi/midi_manager.h"

namespace media {
class MidiManager;
class MidiMessageQueue;
}

namespace content {

class CONTENT_EXPORT MidiHost
    : public BrowserMessageFilter,
      public media::MidiManagerClient {
 public:
  
  MidiHost(int renderer_process_id, media::MidiManager* midi_manager);

  
  virtual void OnDestruct() const OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual void CompleteStartSession(int client_id,
                                    media::MidiResult result) OVERRIDE;
  virtual void ReceiveMidiData(uint32 port,
                               const uint8* data,
                               size_t length,
                               double timestamp) OVERRIDE;
  virtual void AccumulateMidiBytesSent(size_t n) OVERRIDE;

  
  void OnStartSession(int client_id);

  
  void OnSendData(uint32 port,
                  const std::vector<uint8>& data,
                  double timestamp);

 private:
  FRIEND_TEST_ALL_PREFIXES(MidiHostTest, IsValidWebMIDIData);
  friend class base::DeleteHelper<MidiHost>;
  friend class BrowserThread;

  virtual ~MidiHost();

  
  
  
  
  
  static bool IsValidWebMIDIData(const std::vector<uint8>& data);

  int renderer_process_id_;

  
  
  bool has_sys_ex_permission_;

  
  
  
  
  
  media::MidiManager* const midi_manager_;

  
  ScopedVector<media::MidiMessageQueue> received_messages_queues_;

  
  
  size_t sent_bytes_in_flight_;

  
  
  size_t bytes_sent_since_last_acknowledgement_;

  
  base::Lock in_flight_lock_;

  DISALLOW_COPY_AND_ASSIGN(MidiHost);
};

}  

#endif  
