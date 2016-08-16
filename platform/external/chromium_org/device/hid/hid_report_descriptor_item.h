// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_HID_HID_REPORT_DESCRIPTOR_ITEM_H_
#define DEVICE_HID_HID_REPORT_DESCRIPTOR_ITEM_H_

#include "base/basictypes.h"

namespace device {

class HidReportDescriptorItem {
 private:
  friend class HidReportDescriptor;

  enum Type {
    kTypeMain = 0,
    kTypeGlobal = 1,
    kTypeLocal = 2,
    kTypeReserved = 3
  };

  enum MainTag {
    kMainTagDefault = 0x00,       
    kMainTagInput = 0x08,         
    kMainTagOutput = 0x09,        
    kMainTagFeature = 0x0B,       
    kMainTagCollection = 0x0A,    
    kMainTagEndCollection = 0x0C  
  };

  enum GlobalTag {
    kGlobalTagUsagePage = 0x00,        
    kGlobalTagLogicalMinimum = 0x01,   
    kGlobalTagLogicalMaximum = 0x02,   
    kGlobalTagPhysicalMinimum = 0x03,  
    kGlobalTagPhysicalMaximum = 0x04,  
    kGlobalTagUnitExponent = 0x05,     
    kGlobalTagUnit = 0x06,             
    kGlobalTagReportSize = 0x07,       
    kGlobalTagReportId = 0x08,         
    kGlobalTagReportCount = 0x09,      
    kGlobalTagPush = 0x0A,             
    kGlobalTagPop = 0x0B               
  };

  enum LocalTag {
    kLocalTagUsage = 0x00,              
    kLocalTagUsageMinimum = 0x01,       
    kLocalTagUsageMaximum = 0x02,       
    kLocalTagDesignatorIndex = 0x03,    
    kLocalTagDesignatorMinimum = 0x04,  
    kLocalTagDesignatorMaximum = 0x05,  
    kLocalTagStringIndex = 0x07,        
    kLocalTagStringMinimum = 0x08,      
    kLocalTagStringMaximum = 0x09,      
    kLocalTagDelimiter = 0x0A           
  };

  enum ReservedTag {
    kReservedTagLong = 0xF  
  };

 public:
  enum Tag {
    kTagDefault = kMainTagDefault << 2 | kTypeMain,
    kTagInput = kMainTagInput << 2 | kTypeMain,
    kTagOutput = kMainTagOutput << 2 | kTypeMain,
    kTagFeature = kMainTagFeature << 2 | kTypeMain,
    kTagCollection = kMainTagCollection << 2 | kTypeMain,
    kTagEndCollection = kMainTagEndCollection << 2 | kTypeMain,
    kTagUsagePage = kGlobalTagUsagePage << 2 | kTypeGlobal,
    kTagLogicalMinimum = kGlobalTagLogicalMinimum << 2 | kTypeGlobal,
    kTagLogicalMaximum = kGlobalTagLogicalMaximum << 2 | kTypeGlobal,
    kTagPhysicalMinimum = kGlobalTagPhysicalMinimum << 2 | kTypeGlobal,
    kTagPhysicalMaximum = kGlobalTagPhysicalMaximum << 2 | kTypeGlobal,
    kTagUnitExponent = kGlobalTagUnitExponent << 2 | kTypeGlobal,
    kTagUnit = kGlobalTagUnit << 2 | kTypeGlobal,
    kTagReportSize = kGlobalTagReportSize << 2 | kTypeGlobal,
    kTagReportId = kGlobalTagReportId << 2 | kTypeGlobal,
    kTagReportCount = kGlobalTagReportCount << 2 | kTypeGlobal,
    kTagPush = kGlobalTagPush << 2 | kTypeGlobal,
    kTagPop = kGlobalTagPop << 2 | kTypeGlobal,
    kTagUsage = kLocalTagUsage << 2 | kTypeLocal,
    kTagUsageMinimum = kLocalTagUsageMinimum << 2 | kTypeLocal,
    kTagUsageMaximum = kLocalTagUsageMaximum << 2 | kTypeLocal,
    kTagDesignatorIndex = kLocalTagDesignatorIndex << 2 | kTypeLocal,
    kTagDesignatorMinimum = kLocalTagDesignatorMinimum << 2 | kTypeLocal,
    kTagDesignatorMaximum = kLocalTagDesignatorMaximum << 2 | kTypeLocal,
    kTagStringIndex = kLocalTagStringIndex << 2 | kTypeLocal,
    kTagStringMinimum = kLocalTagStringMinimum << 2 | kTypeLocal,
    kTagStringMaximum = kLocalTagStringMaximum << 2 | kTypeLocal,
    kTagDelimiter = kLocalTagDelimiter << 2 | kTypeLocal,
    kTagLong = kReservedTagLong << 2 | kTypeReserved
  };

  
  
  
  
  
  struct ReportInfo {
    uint8_t data_or_constant : 1;
    uint8_t array_or_variable : 1;
    uint8_t absolute_or_relative : 1;
    uint8_t wrap : 1;
    uint8_t linear : 1;
    uint8_t preferred : 1;
    uint8_t null : 1;
    uint8_t reserved_1 : 1;
    uint8_t bit_field_or_buffer : 1;
    uint8_t reserved_2 : 1;
  };

  
  
  
  enum CollectionType {
    kCollectionTypePhysical,
    kCollectionTypeApplication,
    kCollectionTypeLogical,
    kCollectionTypeReport,
    kCollectionTypeNamedArray,
    kCollectionTypeUsageSwitch,
    kCollectionTypeUsageModifier,
    kCollectionTypeReserved,
    kCollectionTypeVendor
  };

 private:
  HidReportDescriptorItem(const uint8_t* bytes,
                          HidReportDescriptorItem* previous);

 public:
  ~HidReportDescriptorItem() {}

  
  
  HidReportDescriptorItem* previous() const {
    return previous_;
  };
  
  
  HidReportDescriptorItem* next() const {
    return next_;
  };
  
  
  
  HidReportDescriptorItem* parent() const {
    return parent_;
  };
  
  
  
  
  size_t GetDepth() const;
  Tag tag() const { return tag_; }
  
  bool IsLong() const;
  
  
  uint32_t GetShortData() const;

  static CollectionType GetCollectionTypeFromValue(uint32_t value);

 private:
  size_t GetHeaderSize() const;
  size_t payload_size() const { return payload_size_; }
  size_t GetSize() const;

  HidReportDescriptorItem* previous_;
  HidReportDescriptorItem* next_;
  HidReportDescriptorItem* parent_;
  Tag tag_;
  uint32_t shortData_;
  size_t payload_size_;
};

}  

#endif  
