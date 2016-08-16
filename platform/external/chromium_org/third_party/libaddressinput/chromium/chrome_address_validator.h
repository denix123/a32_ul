// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_CHROME_ADDRESS_VALIDATOR_H_
#define THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_CHROME_ADDRESS_VALIDATOR_H_

#include <map>
#include <string>
#include <vector>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "third_party/libaddressinput/src/cpp/include/libaddressinput/address_field.h"
#include "third_party/libaddressinput/src/cpp/include/libaddressinput/address_validator.h"
#include "third_party/libaddressinput/src/cpp/include/libaddressinput/callback.h"
#include "third_party/libaddressinput/src/cpp/include/libaddressinput/preload_supplier.h"

namespace i18n {
namespace addressinput {
class AddressNormalizer;
class Source;
class Storage;
struct AddressData;
}
}

namespace autofill {

class InputSuggester;

class LoadRulesListener {
 public:
  virtual ~LoadRulesListener() {}

  
  
  
  
  
  
  
  virtual void OnAddressValidationRulesLoaded(const std::string& region_code,
                                              bool success) = 0;
};

class AddressValidator {
 public:
  
  enum Status {
    
    
    SUCCESS,

    
    
    RULES_UNAVAILABLE,

    
    RULES_NOT_READY
  };

  
  AddressValidator(scoped_ptr< ::i18n::addressinput::Source> source,
                   scoped_ptr< ::i18n::addressinput::Storage> storage,
                   LoadRulesListener* load_rules_listener);

  virtual ~AddressValidator();

  
  
  
  
  
  
  
  
  
  
  virtual void LoadRules(const std::string& region_code);

  
  
  
  
  
  
  virtual Status ValidateAddress(
      const ::i18n::addressinput::AddressData& address,
      const ::i18n::addressinput::FieldProblemMap* filter,
      ::i18n::addressinput::FieldProblemMap* problems) const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual Status GetSuggestions(
      const ::i18n::addressinput::AddressData& user_input,
      ::i18n::addressinput::AddressField focused_field,
      size_t suggestion_limit,
      std::vector< ::i18n::addressinput::AddressData>* suggestions) const;

  
  
  
  virtual bool CanonicalizeAdministrativeArea(
      ::i18n::addressinput::AddressData* address) const;

 protected:
  
  AddressValidator();

  
  
  virtual base::TimeDelta GetBaseRetryPeriod() const;

 private:
  
  void Validated(bool success,
                 const ::i18n::addressinput::AddressData&,
                 const ::i18n::addressinput::FieldProblemMap&);

  
  
  void RulesLoaded(bool success, const std::string& region_code, int);

  
  void RetryLoadRules(const std::string& region_code);

  
  const scoped_ptr< ::i18n::addressinput::PreloadSupplier> supplier_;

  
  const scoped_ptr<InputSuggester> input_suggester_;

  
  const scoped_ptr< ::i18n::addressinput::AddressNormalizer> normalizer_;

  
  const scoped_ptr<const ::i18n::addressinput::AddressValidator> validator_;

  
  
  const scoped_ptr<const ::i18n::addressinput::AddressValidator::Callback>
      validated_;

  
  const scoped_ptr<const ::i18n::addressinput::PreloadSupplier::Callback>
      rules_loaded_;

  
  
  LoadRulesListener* const load_rules_listener_;

  
  std::map<std::string, int> attempts_number_;

  
  
  
  base::WeakPtrFactory<AddressValidator> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(AddressValidator);
};

}  

#endif  
