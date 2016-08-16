// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_FAKE_NFC_TAG_CLIENT_H_
#define CHROMEOS_DBUS_FAKE_NFC_TAG_CLIENT_H_

#include "base/observer_list.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/nfc_client_helpers.h"
#include "chromeos/dbus/nfc_tag_client.h"

namespace chromeos {

class CHROMEOS_EXPORT FakeNfcTagClient : public NfcTagClient {
 public:
  
  static const char kTagPath[];

  
  static const int kDefaultSimulationTimeoutMilliseconds;

  struct Properties : public NfcTagClient::Properties {
    explicit Properties(const PropertyChangedCallback& callback);
    virtual ~Properties();

    
    virtual void Get(dbus::PropertyBase* property,
                     dbus::PropertySet::GetCallback callback) OVERRIDE;
    virtual void GetAll() OVERRIDE;
    virtual void Set(dbus::PropertyBase* property,
                     dbus::PropertySet::SetCallback callback) OVERRIDE;
  };

  FakeNfcTagClient();
  virtual ~FakeNfcTagClient();

  
  virtual void Init(dbus::Bus* bus) OVERRIDE;
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual std::vector<dbus::ObjectPath> GetTagsForAdapter(
      const dbus::ObjectPath& adapter_path) OVERRIDE;
  virtual Properties* GetProperties(
      const dbus::ObjectPath& object_path) OVERRIDE;
  virtual void Write(
      const dbus::ObjectPath& object_path,
      const base::DictionaryValue& attributes,
      const base::Closure& callback,
      const nfc_client_helpers::ErrorCallback& error_callback) OVERRIDE;

  
  
  
  
  
  void BeginPairingSimulation(int visibility_delay);

  
  
  
  
  void EndPairingSimulation();

  
  
  
  
  
  void EnableSimulationTimeout(int simulation_timeout);
  void DisableSimulationTimeout();

  
  
  
  
  void SetRecords(const std::vector<dbus::ObjectPath>& record_paths);

  
  
  
  void ClearRecords();

  
  bool tag_visible() const { return tag_visible_; }

 private:
  
  void OnPropertyChanged(const dbus::ObjectPath& object_path,
                         const std::string& property_name);

  
  void MakeTagVisible();

  
  void HandleSimulationTimeout();

  
  ObserverList<Observer> observers_;

  
  scoped_ptr<Properties> properties_;

  
  
  bool pairing_started_;

  
  
  bool tag_visible_;

  
  
  int simulation_timeout_;

  DISALLOW_COPY_AND_ASSIGN(FakeNfcTagClient);
};

}  

#endif  
