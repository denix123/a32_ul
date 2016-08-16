// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_FAKE_NFC_ADAPTER_CLIENT_H_
#define CHROMEOS_DBUS_FAKE_NFC_ADAPTER_CLIENT_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/nfc_adapter_client.h"
#include "chromeos/dbus/nfc_client_helpers.h"

namespace chromeos {

class CHROMEOS_EXPORT FakeNfcAdapterClient : public NfcAdapterClient {
 public:
  
  static const char kAdapterPath0[];
  static const char kAdapterPath1[];

  
  struct Properties : public NfcAdapterClient::Properties {
    explicit Properties(const PropertyChangedCallback& callback);
    virtual ~Properties();

    
    virtual void Get(dbus::PropertyBase* property,
                     dbus::PropertySet::GetCallback callback) OVERRIDE;
    virtual void GetAll() OVERRIDE;
    virtual void Set(dbus::PropertyBase* property,
                     dbus::PropertySet::SetCallback callback) OVERRIDE;
  };

  FakeNfcAdapterClient();
  virtual ~FakeNfcAdapterClient();

  
  virtual void Init(dbus::Bus* bus) OVERRIDE;
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual std::vector<dbus::ObjectPath> GetAdapters() OVERRIDE;
  virtual Properties* GetProperties(
      const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void StartPollLoop(
      const dbus::ObjectPath& object_path,
      const std::string& mode,
      const base::Closure& callback,
      const nfc_client_helpers::ErrorCallback& error_callback) OVERRIDE;
  virtual void StopPollLoop(
      const dbus::ObjectPath& object_path,
      const base::Closure& callback,
      const nfc_client_helpers::ErrorCallback& error_callback) OVERRIDE;

  
  void SetAdapterPresent(bool present);
  void SetSecondAdapterPresent(bool present);

  
  
  
  
  
  void SetDevice(const dbus::ObjectPath& device_path);
  void SetTag(const dbus::ObjectPath& tag_path);

  
  
  
  
  void UnsetDevice(const dbus::ObjectPath& device_path);
  void UnsetTag(const dbus::ObjectPath& tag_path);

  
  
  
  
  
  
  
  
  void EnablePairingOnPoll(bool enabled);

 private:
  
  void OnPropertyChanged(const dbus::ObjectPath& object_path,
                         const std::string& property_name);

  
  ObserverList<Observer> observers_;

  
  scoped_ptr<Properties> properties_;
  scoped_ptr<Properties> second_properties_;

  
  bool present_;
  bool second_present_;

  
  
  bool start_pairing_on_poll_;

  
  
  bool device_pairing_;

  DISALLOW_COPY_AND_ASSIGN(FakeNfcAdapterClient);
};

}  

#endif  
