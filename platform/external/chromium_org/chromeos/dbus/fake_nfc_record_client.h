// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_FAKE_NFC_RECORD_CLIENT_H_
#define CHROMEOS_DBUS_FAKE_NFC_RECORD_CLIENT_H_

#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/values.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/nfc_record_client.h"
#include "dbus/object_path.h"

namespace chromeos {

class CHROMEOS_EXPORT FakeNfcRecordClient : public NfcRecordClient {
 public:
  
  static const char kDeviceSmartPosterRecordPath[];
  static const char kDeviceTextRecordPath[];
  static const char kDeviceUriRecordPath[];
  static const char kTagRecordPath[];

  
  struct Properties : public NfcRecordClient::Properties {
    explicit Properties(const PropertyChangedCallback& callback);
    virtual ~Properties();

    
    virtual void Get(dbus::PropertyBase* property,
                     dbus::PropertySet::GetCallback callback) OVERRIDE;
    virtual void GetAll() OVERRIDE;
    virtual void Set(dbus::PropertyBase* property,
                     dbus::PropertySet::SetCallback callback) OVERRIDE;
  };

  FakeNfcRecordClient();
  virtual ~FakeNfcRecordClient();

  
  virtual void Init(dbus::Bus* bus) OVERRIDE;
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual std::vector<dbus::ObjectPath> GetRecordsForDevice(
      const dbus::ObjectPath& device_path) OVERRIDE;
  virtual std::vector<dbus::ObjectPath> GetRecordsForTag(
      const dbus::ObjectPath& tag_path) OVERRIDE;
  virtual Properties* GetProperties(
      const dbus::ObjectPath& object_path) OVERRIDE;

  
  void SetDeviceRecordsVisible(bool visible);
  void SetTagRecordsVisible(bool visible);

  
  
  
  
  
  
  bool WriteTagRecord(const base::DictionaryValue& attributes);

 private:
  
  void OnPropertyChanged(const dbus::ObjectPath& object_path,
                         const std::string& property_name);

  
  void OnPropertiesReceived(const dbus::ObjectPath& object_path);

  
  bool device_records_visible_;
  bool tag_records_visible_;

  
  ObserverList<Observer> observers_;

  
  scoped_ptr<Properties> device_smart_poster_record_properties_;
  scoped_ptr<Properties> device_text_record_properties_;
  scoped_ptr<Properties> device_uri_record_properties_;
  scoped_ptr<Properties> tag_record_properties_;

  DISALLOW_COPY_AND_ASSIGN(FakeNfcRecordClient);
};

}  

#endif  
