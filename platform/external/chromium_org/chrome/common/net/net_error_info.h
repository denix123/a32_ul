// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_NET_NET_ERROR_INFO_H_
#define CHROME_COMMON_NET_NET_ERROR_INFO_H_

namespace chrome_common_net {

enum NetworkErrorPageEvent {
  NETWORK_ERROR_PAGE_SHOWN,                      

  NETWORK_ERROR_PAGE_RELOAD_BUTTON_SHOWN,        
  NETWORK_ERROR_PAGE_RELOAD_BUTTON_CLICKED,      
  NETWORK_ERROR_PAGE_RELOAD_BUTTON_ERROR,        
                                                 

  NETWORK_ERROR_PAGE_LOAD_STALE_BUTTON_SHOWN,    
  NETWORK_ERROR_PAGE_LOAD_STALE_BUTTON_CLICKED,  
  NETWORK_ERROR_PAGE_LOAD_STALE_BUTTON_ERROR,    

  NETWORK_ERROR_PAGE_MORE_BUTTON_CLICKED,        

  NETWORK_ERROR_PAGE_BROWSER_INITIATED_RELOAD,   

  NETWORK_ERROR_PAGE_EVENT_MAX,
};

enum DnsProbeStatus {
  
  
  DNS_PROBE_POSSIBLE,

  
  
  
  DNS_PROBE_NOT_RUN,

  
  
  
  DNS_PROBE_STARTED,

  

  
  DNS_PROBE_FINISHED_INCONCLUSIVE,

  
  DNS_PROBE_FINISHED_NO_INTERNET,

  
  DNS_PROBE_FINISHED_BAD_CONFIG,

  
  DNS_PROBE_FINISHED_NXDOMAIN,

  DNS_PROBE_MAX
};

const char* DnsProbeStatusToString(int status);

bool DnsProbeStatusIsFinished(DnsProbeStatus status);

void RecordEvent(NetworkErrorPageEvent event);

extern const char kDnsProbeErrorDomain[];

}  

#endif  
