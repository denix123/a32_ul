// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_BROWSER_CHROMEOS_NET_DELAY_NETWORK_CALL_H_
#define CHROME_BROWSER_CHROMEOS_NET_DELAY_NETWORK_CALL_H_

namespace base {

template <typename T>
class Callback;

typedef Callback<void(void)> Closure;

class TimeDelta;

}  

namespace chromeos {

extern const unsigned kDefaultNetworkRetryDelayMS;

void DelayNetworkCall(const base::Closure& callback, base::TimeDelta retry);

}  

#endif  
