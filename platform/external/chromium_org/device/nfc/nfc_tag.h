// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_NFC_NFC_TAG_H_
#define DEVICE_NFC_NFC_TAG_H_

#include "device/nfc/nfc_tag_technology.h"

namespace device {

class NfcTag {
 public:
  
  enum TagType {
    kTagType1,
    kTagType2,
    kTagType3,
    kTagType4,
    kTagTypeUnknown,
  };

  
  
  enum Protocol {
    kProtocolFelica,
    kProtocolIsoDep,
    kProtocolJewel,
    kProtocolMifare,
    kProtocolNfcDep,
    kProtocolUnknown
  };

  
  class Observer {
   public:
    virtual ~Observer() {}

    
    virtual void TagTypeChanged(NfcTag* tag, TagType type) {}

    
    virtual void TagWritePermissionChanged(NfcTag* tag, bool read_only) {}

    
    virtual void TagSupportedProtocolChanged(NfcTag* tag, Protocol protocol) {}

    
    
    virtual void TagReady(NfcTag* tag) {}
  };

  virtual ~NfcTag();

  
  
  
  virtual void AddObserver(Observer* observer) = 0;
  virtual void RemoveObserver(Observer* observer) = 0;

  
  virtual std::string GetIdentifier() const = 0;

  
  virtual TagType GetType() const = 0;

  // Returns true, if this tag is read-only and cannot be written to.
  virtual bool IsReadOnly() const = 0;

  
  virtual Protocol GetSupportedProtocol() const = 0;

  
  virtual NfcTagTechnology::TechnologyTypeMask
      GetSupportedTechnologies() const = 0;

  
  
  virtual bool IsReady() const = 0;

  
  
  
  
  
  virtual NfcNdefTagTechnology* GetNdefTagTechnology() = 0;

 protected:
  NfcTag();

 private:
  DISALLOW_COPY_AND_ASSIGN(NfcTag);
};

}  

#endif  
