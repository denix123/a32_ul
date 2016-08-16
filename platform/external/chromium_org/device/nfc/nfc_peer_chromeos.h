// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_NFC_NFC_PEER_CHROMEOS_H_
#define DEVICE_NFC_NFC_PEER_CHROMEOS_H_

#include <map>

#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chromeos/dbus/nfc_record_client.h"
#include "dbus/object_path.h"
#include "device/nfc/nfc_ndef_record.h"
#include "device/nfc/nfc_peer.h"

namespace chromeos {

class NfcPeerChromeOS : public device::NfcPeer,
                        public NfcRecordClient::Observer {
 public:
  
  virtual void AddObserver(device::NfcPeer::Observer* observer) OVERRIDE;
  virtual void RemoveObserver(device::NfcPeer::Observer* observer) OVERRIDE;
  virtual std::string GetIdentifier() const OVERRIDE;
  virtual const device::NfcNdefMessage& GetNdefMessage() const OVERRIDE;
  virtual void PushNdef(const device::NfcNdefMessage& message,
                        const base::Closure& callback,
                        const ErrorCallback& error_callback) OVERRIDE;
  virtual void StartHandover(HandoverType handover_type,
                             const base::Closure& callback,
                             const ErrorCallback& error_callback) OVERRIDE;

 private:
  friend class NfcAdapterChromeOS;

  
  typedef std::map<dbus::ObjectPath, device::NfcNdefRecord*> NdefRecordMap;

  explicit NfcPeerChromeOS(const dbus::ObjectPath& object_path);
  virtual ~NfcPeerChromeOS();

  
  virtual void RecordAdded(const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void RecordRemoved(const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void RecordPropertiesReceived(
      const dbus::ObjectPath& object_path) OVERRIDE;

  
  void OnPushNdef(const base::Closure& callback);
  void OnPushNdefError(const ErrorCallback& error_callback,
                       const std::string& error_name,
                       const std::string& error_message);

  
  
  void AddRecord(const dbus::ObjectPath& object_path);

  
  dbus::ObjectPath object_path_;

  
  NdefRecordMap records_;

  
  device::NfcNdefMessage message_;

  
  ObserverList<device::NfcPeer::Observer> observers_;

  
  
  base::WeakPtrFactory<NfcPeerChromeOS> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(NfcPeerChromeOS);
};

}  

#endif  
