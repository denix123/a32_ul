// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CONTENT_BROWSER_WALLET_WALLET_ADDRESS_H_
#define COMPONENTS_AUTOFILL_CONTENT_BROWSER_WALLET_WALLET_ADDRESS_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "components/autofill/core/browser/phone_number_i18n.h"

namespace base {
class DictionaryValue;
}

namespace autofill {

class AutofillProfile;
class AutofillType;

namespace wallet {


class Address {
 public:
  
  
  

  Address();

  
  explicit Address(const AutofillProfile& profile);

  Address(const std::string& country_name_code,
          const base::string16& recipient_name,
          const std::vector<base::string16>& street_address,
          const base::string16& locality_name,
          const base::string16& dependent_locality_name,
          const base::string16& administrative_area_name,
          const base::string16& postal_code_number,
          const base::string16& sorting_code,
          const base::string16& phone_number,
          const std::string& object_id,
          const std::string& language_code);

  ~Address();

  
  
  
  static scoped_ptr<Address> CreateAddress(
      const base::DictionaryValue& dictionary);

  
  
  
  
  
  static scoped_ptr<Address> CreateAddressWithID(
      const base::DictionaryValue& dictionary);

  
  
  static scoped_ptr<Address> CreateDisplayAddress(
      const base::DictionaryValue& dictionary);

  
  
  
  scoped_ptr<base::DictionaryValue> ToDictionaryWithID() const;

  
  
  scoped_ptr<base::DictionaryValue> ToDictionaryWithoutID() const;

  
  
  base::string16 DisplayName() const;

  
  
  base::string16 DisplayNameDetail() const;

  
  
  base::string16 DisplayPhoneNumber() const;

  
  base::string16 GetInfo(const AutofillType& type,
                         const std::string& app_locale) const;

  const std::string& country_name_code() const { return country_name_code_; }
  const base::string16& recipient_name() const { return recipient_name_; }
  const std::vector<base::string16>& street_address() const {
    return street_address_;
  }
  const base::string16& locality_name() const { return locality_name_; }
  const base::string16& administrative_area_name() const {
    return administrative_area_name_;
  }
  const base::string16& postal_code_number() const {
    return postal_code_number_;
  }
  const base::string16& phone_number() const { return phone_number_; }
  const std::string& object_id() const { return object_id_; }
  bool is_complete_address() const {
    return is_complete_address_;
  }
  const std::string& language_code() const { return language_code_; }

  void set_country_name_code(const std::string& country_name_code) {
    country_name_code_ = country_name_code;
  }
  void set_recipient_name(const base::string16& recipient_name) {
    recipient_name_ = recipient_name;
  }
  void set_street_address(const std::vector<base::string16>& street_address) {
    street_address_ = street_address;
  }
  void set_locality_name(const base::string16& locality_name) {
    locality_name_ = locality_name;
  }
  void set_dependent_locality_name(
        const base::string16& dependent_locality_name) {
    dependent_locality_name_ = dependent_locality_name;
  }
  void set_administrative_area_name(
      const base::string16& administrative_area_name) {
    administrative_area_name_ = administrative_area_name;
  }
  void set_postal_code_number(const base::string16& postal_code_number) {
    postal_code_number_ = postal_code_number;
  }
  void set_sorting_code(const base::string16& sorting_code) {
    sorting_code_ = sorting_code;
  }
  void SetPhoneNumber(const base::string16& phone_number);
  void set_object_id(const std::string& object_id) {
    object_id_ = object_id;
  }
  void set_is_complete_address(bool is_complete_address) {
    is_complete_address_ = is_complete_address;
  }
  void set_language_code(const std::string& language_code) {
    language_code_ = language_code;
  }

  
  
  
  
  bool EqualsIgnoreID(const Address& other) const;

  
  
  bool operator==(const Address& other) const;
  bool operator!=(const Address& other) const;

 private:
  
  base::string16 GetStreetAddressLine(size_t line) const;

  
  
  std::string country_name_code_;

  
  base::string16 recipient_name_;

  
  std::vector<base::string16> street_address_;

  
  
  
  base::string16 locality_name_;

  
  
  base::string16 dependent_locality_name_;

  
  
  
  base::string16 administrative_area_name_;

  
  
  base::string16 postal_code_number_;

  
  base::string16 sorting_code_;

  
  
  
  base::string16 phone_number_;

  
  i18n::PhoneObject phone_object_;

  
  std::string object_id_;

  
  bool is_complete_address_;

  
  
  std::string language_code_;

  
  DISALLOW_ASSIGN(Address);
};

}  
}  

#endif  
