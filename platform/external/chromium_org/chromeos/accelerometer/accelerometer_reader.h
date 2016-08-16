// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_ACCELEROMETER_ACCELEROMETER_READER_H_
#define CHROMEOS_ACCELEROMETER_ACCELEROMETER_READER_H_

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chromeos/chromeos_export.h"
#include "ui/accelerometer/accelerometer_types.h"

namespace base {
class TaskRunner;
}

namespace chromeos {

class CHROMEOS_EXPORT AccelerometerReader {
 public:
  
  struct ConfigurationData {
    ConfigurationData();
    ~ConfigurationData();

    
    size_t count;

    
    size_t length;

    
    bool has[ui::ACCELEROMETER_SOURCE_COUNT];

    
    float scale[ui::ACCELEROMETER_SOURCE_COUNT][3];

    
    int index[ui::ACCELEROMETER_SOURCE_COUNT][3];
  };
  typedef base::RefCountedData<ConfigurationData> Configuration;
  typedef base::RefCountedData<char[12]> Reading;

  
  class Delegate {
   public:
    virtual void HandleAccelerometerUpdate(
        const ui::AccelerometerUpdate& update) = 0;
  };

  AccelerometerReader(scoped_refptr<base::TaskRunner> blocking_task_runner,
                      Delegate* delegate);
  ~AccelerometerReader();

 private:
  
  
  void OnInitialized(scoped_refptr<Configuration> configuration, bool success);

  
  
  void TriggerRead();

  
  
  
  void OnDataRead(scoped_refptr<Reading> reading, bool success);

  
  scoped_refptr<base::TaskRunner> task_runner_;

  
  Delegate* delegate_;

  
  ui::AccelerometerUpdate update_;

  
  scoped_refptr<Configuration> configuration_;

  base::WeakPtrFactory<AccelerometerReader> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(AccelerometerReader);
};

}  

#endif  
