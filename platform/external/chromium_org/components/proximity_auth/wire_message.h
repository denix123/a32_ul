// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PROXIMITY_AUTH_WIRE_MESSAGE_H
#define COMPONENTS_PROXIMITY_AUTH_WIRE_MESSAGE_H

#include <string>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"

namespace proximity_auth {

class WireMessage {
 public:
  virtual ~WireMessage();

  
  
  
  
  static scoped_ptr<WireMessage> Deserialize(
      const std::string& serialized_message,
      bool* is_incomplete_message);

  
  virtual std::string Serialize() const;

  const std::string& permit_id() const { return permit_id_; }
  const std::string& payload() const { return payload_; }

 protected:
  
  WireMessage(const std::string& permit_id, const std::string& payload);

 private:
  
  
  const std::string permit_id_;

  
  const std::string payload_;

  DISALLOW_COPY_AND_ASSIGN(WireMessage);
};

}  

#endif  
