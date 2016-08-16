// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_CLOUD_DEVICES_COMMON_CAPABILITY_INTERFACES_H_
#define COMPONENTS_CLOUD_DEVICES_COMMON_CAPABILITY_INTERFACES_H_


#include <vector>

#include "base/logging.h"
#include "base/numerics/safe_conversions.h"
#include "components/cloud_devices/common/cloud_device_description.h"

namespace base {
class DictionaryValue;
}

namespace cloud_devices {


template <class Option, class Traits>
class ListCapability {
 public:
  ListCapability();
  ~ListCapability();

  bool LoadFrom(const CloudDeviceDescription& description);
  void SaveTo(CloudDeviceDescription* description) const;

  void Reset() { options_.clear(); }

  bool IsValid() const;

  bool empty() const { return options_.empty(); }

  size_t size() const { return options_.size(); }

  const Option& operator[](size_t i) const { return options_[i]; }

  bool Contains(const Option& option) const {
    return std::find(options_.begin(), options_.end(), option) !=
           options_.end();
  }

  void AddOption(const Option& option) { options_.push_back(option); }

 private:
  typedef std::vector<Option> OptionVector;
  OptionVector options_;

  DISALLOW_COPY_AND_ASSIGN(ListCapability);
};

template <class Option, class Traits>
class SelectionCapability {
 public:
  SelectionCapability();
  ~SelectionCapability();

  bool LoadFrom(const CloudDeviceDescription& description);
  void SaveTo(CloudDeviceDescription* description) const;

  void Reset() {
    options_.clear();
    default_idx_ = -1;
  }

  bool IsValid() const;

  bool empty() const { return options_.empty(); }

  size_t size() const { return options_.size(); }

  const Option& operator[](size_t i) const { return options_[i]; }

  bool Contains(const Option& option) const {
    return std::find(options_.begin(), options_.end(), option) !=
           options_.end();
  }

  const Option& GetDefault() const {
    CHECK_GE(default_idx_, 0);
    return options_[default_idx_];
  }

  void AddOption(const Option& option) { AddDefaultOption(option, false); }

  void AddDefaultOption(const Option& option, bool is_default) {
    if (is_default) {
      DCHECK_EQ(default_idx_, -1);
      
      default_idx_ = base::checked_cast<int>(size());
    }
    options_.push_back(option);
  }

 private:
  typedef std::vector<Option> OptionVector;

  OptionVector options_;
  int default_idx_;

  DISALLOW_COPY_AND_ASSIGN(SelectionCapability);
};

template <class Traits>
class BooleanCapability {
 public:
  BooleanCapability();
  ~BooleanCapability();

  bool LoadFrom(const CloudDeviceDescription& description);
  void SaveTo(CloudDeviceDescription* description) const;

  void Reset() { default_value_ = false; }

  void set_default_value(bool value) { default_value_ = value; }

  bool default_value() const { return default_value_; }

 private:
  bool default_value_;

  DISALLOW_COPY_AND_ASSIGN(BooleanCapability);
};

template <class Traits>
class EmptyCapability {
 public:
  EmptyCapability() {};
  ~EmptyCapability() {};

  bool LoadFrom(const CloudDeviceDescription& description);
  void SaveTo(CloudDeviceDescription* description) const;

 private:
  DISALLOW_COPY_AND_ASSIGN(EmptyCapability);
};

template <class Option, class Traits>
class ValueCapability {
 public:
  ValueCapability();
  ~ValueCapability();

  bool LoadFrom(const CloudDeviceDescription& description);
  void SaveTo(CloudDeviceDescription* description) const;

  void Reset() { value_ = Option(); }

  bool IsValid() const;

  const Option& value() const { return value_; }

  void set_value(const Option& value) { value_ = value; }

 private:
  Option value_;

  DISALLOW_COPY_AND_ASSIGN(ValueCapability);
};

template <class Option, class Traits>
class TicketItem {
 public:
  TicketItem();
  ~TicketItem();

  bool LoadFrom(const CloudDeviceDescription& description);
  void SaveTo(CloudDeviceDescription* description) const;

  void Reset() { value_ = Option(); }

  bool IsValid() const;

  const Option& value() const { return value_; }

  void set_value(const Option& value) { value_ = value; }

 private:
  Option value_;

  DISALLOW_COPY_AND_ASSIGN(TicketItem);
};

}  

#endif  
