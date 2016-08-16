// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_MIDI_MIDI_MANAGER_H_
#define MEDIA_MIDI_MIDI_MANAGER_H_

#include <map>
#include <set>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "base/time/time.h"
#include "media/base/media_export.h"
#include "media/midi/midi_port_info.h"
#include "media/midi/midi_result.h"

namespace base {
class SingleThreadTaskRunner;
}  

namespace media {

class MEDIA_EXPORT MidiManagerClient {
 public:
  virtual ~MidiManagerClient() {}

  
  
  virtual void CompleteStartSession(int client_id, MidiResult result) = 0;

  
  
  
  
  
  
  virtual void ReceiveMidiData(uint32 port_index,
                               const uint8* data,
                               size_t length,
                               double timestamp) = 0;

  
  
  
  
  virtual void AccumulateMidiBytesSent(size_t n) = 0;
};

class MEDIA_EXPORT MidiManager {
 public:
  static const size_t kMaxPendingClientCount = 128;

  MidiManager();
  virtual ~MidiManager();

  
  
  static MidiManager* Create();

  
  
  
  
  
  
  
  void StartSession(MidiManagerClient* client, int client_id);

  
  void EndSession(MidiManagerClient* client);

  
  
  
  
  
  
  
  
  
  virtual void DispatchSendMidiData(MidiManagerClient* client,
                                    uint32 port_index,
                                    const std::vector<uint8>& data,
                                    double timestamp);

  
  
  
  const MidiPortInfoList& input_ports() const { return input_ports_; }

  
  
  
  const MidiPortInfoList& output_ports() const { return output_ports_; }

 protected:
  friend class MidiManagerUsb;

  
  
  
  
  
  
  
  
  
  virtual void StartInitialization();

  
  
  
  
  void CompleteInitialization(MidiResult result);

  void AddInputPort(const MidiPortInfo& info);
  void AddOutputPort(const MidiPortInfo& info);

  
  
  
  void ReceiveMidiData(uint32 port_index,
                       const uint8* data,
                       size_t length,
                       double timestamp);

  void ReceiveMidiData(uint32 port_index,
                       const uint8* data,
                       size_t length,
                       base::TimeTicks time) {
    ReceiveMidiData(port_index, data, length,
                    (time - base::TimeTicks()).InSecondsF());
  }

  size_t clients_size_for_testing() const { return clients_.size(); }
  size_t pending_clients_size_for_testing() const {
    return pending_clients_.size();
  }

 private:
  void CompleteInitializationInternal(MidiResult result);

  
  typedef std::set<MidiManagerClient*> ClientList;
  ClientList clients_;

  
  typedef std::multimap<MidiManagerClient*, int> PendingClientMap;
  PendingClientMap pending_clients_;

  
  
  scoped_refptr<base::SingleThreadTaskRunner> session_thread_runner_;

  
  bool initialized_;

  
  
  MidiResult result_;

  
  
  base::Lock lock_;

  MidiPortInfoList input_ports_;
  MidiPortInfoList output_ports_;

  DISALLOW_COPY_AND_ASSIGN(MidiManager);
};

}  

#endif  
