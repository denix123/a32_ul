// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_BLUETOOTH_BLUETOOTH_EXTENSION_FUNCTION_H_
#define EXTENSIONS_BROWSER_API_BLUETOOTH_BLUETOOTH_EXTENSION_FUNCTION_H_

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "extensions/browser/extension_function.h"

namespace device {

class BluetoothAdapter;

}  

namespace extensions {
namespace core_api {

class BluetoothExtensionFunction : public AsyncExtensionFunction {
 public:
  BluetoothExtensionFunction();

 protected:
  virtual ~BluetoothExtensionFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void RunOnAdapterReady(scoped_refptr<device::BluetoothAdapter> adapter);

  
  
  virtual bool DoWork(scoped_refptr<device::BluetoothAdapter> adapter) = 0;

  DISALLOW_COPY_AND_ASSIGN(BluetoothExtensionFunction);
};

}  
}  

#endif  
