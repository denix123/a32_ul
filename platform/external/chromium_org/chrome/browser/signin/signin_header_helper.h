// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_SIGNIN_HEADER_HELPER_H_
#define CHROME_BROWSER_SIGNIN_SIGNIN_HEADER_HELPER_H_

#include <string>

namespace net {
class URLRequest;
}
class GURL;
class ProfileIOData;

namespace signin {

enum ProfileMode {
  PROFILE_MODE_DEFAULT = 0,
  
  PROFILE_MODE_INCOGNITO_DISABLED = 1 << 0,
  
  PROFILE_MODE_ADD_ACCOUNT_DISABLED = 1 << 1
};

enum GAIAServiceType {
  GAIA_SERVICE_TYPE_NONE = 0,                 
  GAIA_SERVICE_TYPE_SIGNOUT,                  
  GAIA_SERVICE_TYPE_INCOGNITO,                
  GAIA_SERVICE_TYPE_ADDSESSION,               
  GAIA_SERVICE_TYPE_REAUTH,                   
  GAIA_SERVICE_TYPE_SIGNUP,                   
  GAIA_SERVICE_TYPE_DEFAULT,                  
};

struct ManageAccountsParams {
  
  GAIAServiceType service_type;
  
  std::string email;
  
  bool is_saml;
  
  
  std::string continue_url;
  
  bool is_same_tab;
  
  int child_id;
  
  int route_id;

  ManageAccountsParams();
};

bool AppendMirrorRequestHeaderIfPossible(
    net::URLRequest* request,
    const GURL& redirect_url,
    ProfileIOData* io_data);

void ProcessMirrorResponseHeaderIfExists(
    net::URLRequest* request,
    ProfileIOData* io_data,
    int child_id,
    int route_id);

};  

#endif  
