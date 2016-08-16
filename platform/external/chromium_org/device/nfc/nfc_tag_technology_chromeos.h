// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_NFC_NFC_TAG_TECHNOLOGY_CHROMEOS_H_
#define DEVICE_NFC_NFC_TAG_TECHNOLOGY_CHROMEOS_H_

#include <map>

#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chromeos/dbus/nfc_record_client.h"
#include "device/nfc/nfc_tag_technology.h"

namespace chromeos {

class NfcTagChromeOS;

class NfcNdefTagTechnologyChromeOS : public device::NfcNdefTagTechnology,
                                     public NfcRecordClient::Observer {
 public:
  virtual ~NfcNdefTagTechnologyChromeOS();

  
  virtual void AddObserver(device::NfcNdefTagTechnology::Observer* observer)
    OVERRIDE;
  virtual void RemoveObserver(device::NfcNdefTagTechnology::Observer* observer)
    OVERRIDE;
  virtual const device::NfcNdefMessage& GetNdefMessage() const OVERRIDE;
  virtual void WriteNdef(const device::NfcNdefMessage& message,
                         const base::Closure& callback,
                         const ErrorCallback& error_callback) OVERRIDE;

  
  virtual void RecordAdded(const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void RecordRemoved(const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void RecordPropertiesReceived(
      const dbus::ObjectPath& object_path) OVERRIDE;

 private:
  friend class NfcTagChromeOS;

  
  typedef std::map<dbus::ObjectPath, device::NfcNdefRecord*> NdefRecordMap;

  explicit NfcNdefTagTechnologyChromeOS(NfcTagChromeOS* tag);

  
  void OnWriteNdefMessage(const base::Closure& callback);
  void OnWriteNdefMessageError(const ErrorCallback& error_callback,
                               const std::string& error_name,
                               const std::string& error_message);

  
  
  void AddRecord(const dbus::ObjectPath& object_path);

  
  NdefRecordMap records_;

  
  
  
  device::NfcNdefMessage message_;

  
  ObserverList<device::NfcNdefTagTechnology::Observer> observers_;

  
  
  dbus::ObjectPath object_path_;

  
  
  base::WeakPtrFactory<NfcNdefTagTechnologyChromeOS> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(NfcNdefTagTechnologyChromeOS);
};

}  

#endif  
