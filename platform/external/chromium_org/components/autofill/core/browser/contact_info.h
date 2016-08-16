// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CORE_BROWSER_CONTACT_INFO_H_
#define COMPONENTS_AUTOFILL_CORE_BROWSER_CONTACT_INFO_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/strings/string16.h"
#include "components/autofill/core/browser/form_group.h"

namespace autofill {

class NameInfo : public FormGroup {
 public:
  NameInfo();
  NameInfo(const NameInfo& info);
  virtual ~NameInfo();

  NameInfo& operator=(const NameInfo& info);

  
  
  bool ParsedNamesAreEqual(const NameInfo& info);

  
  virtual base::string16 GetRawInfo(ServerFieldType type) const OVERRIDE;
  virtual void SetRawInfo(ServerFieldType type,
                          const base::string16& value) OVERRIDE;
  virtual base::string16 GetInfo(const AutofillType& type,
                                 const std::string& app_locale) const OVERRIDE;
  virtual bool SetInfo(const AutofillType& type,
                       const base::string16& value,
                       const std::string& app_locale) OVERRIDE;

 private:
  
  virtual void GetSupportedTypes(
      ServerFieldTypeSet* supported_types) const OVERRIDE;

  
  
  base::string16 FullName() const;

  
  
  base::string16 MiddleInitial() const;

  
  void SetFullName(const base::string16& full);

  base::string16 given_;
  base::string16 middle_;
  base::string16 family_;
  base::string16 full_;
};

class EmailInfo : public FormGroup {
 public:
  EmailInfo();
  EmailInfo(const EmailInfo& info);
  virtual ~EmailInfo();

  EmailInfo& operator=(const EmailInfo& info);

  
  virtual base::string16 GetRawInfo(ServerFieldType type) const OVERRIDE;
  virtual void SetRawInfo(ServerFieldType type,
                          const base::string16& value) OVERRIDE;

 private:
  
  virtual void GetSupportedTypes(
      ServerFieldTypeSet* supported_types) const OVERRIDE;

  base::string16 email_;
};

class CompanyInfo : public FormGroup {
 public:
  CompanyInfo();
  CompanyInfo(const CompanyInfo& info);
  virtual ~CompanyInfo();

  CompanyInfo& operator=(const CompanyInfo& info);

  
  virtual base::string16 GetRawInfo(ServerFieldType type) const OVERRIDE;
  virtual void SetRawInfo(ServerFieldType type,
                          const base::string16& value) OVERRIDE;

 private:
  
  virtual void GetSupportedTypes(
      ServerFieldTypeSet* supported_types) const OVERRIDE;

  base::string16 company_name_;
};

}  

#endif  
