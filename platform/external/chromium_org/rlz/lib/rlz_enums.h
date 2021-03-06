// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef RLZ_LIB_RLZ_ENUMS_H_
#define RLZ_LIB_RLZ_ENUMS_H_

namespace rlz_lib {

enum AccessPoint {
  NO_ACCESS_POINT = 0,

  
  IE_DEFAULT_SEARCH,  
  IE_HOME_PAGE,       
  IETB_SEARCH_BOX,    
  QUICK_SEARCH_BOX,   
                      
  GD_DESKBAND,        
  GD_SEARCH_GADGET,   
  GD_WEB_SERVER,      
  GD_OUTLOOK,         
  CHROME_OMNIBOX,     
  CHROME_HOME_PAGE,   
  FFTB2_BOX,          
  FFTB3_BOX,          
  PINYIN_IME_BHO,     
  IGOOGLE_WEBPAGE,    

  
  MOBILE_IDLE_SCREEN_BLACKBERRY,
  MOBILE_IDLE_SCREEN_WINMOB,
  MOBILE_IDLE_SCREEN_SYMBIAN,

  FF_HOME_PAGE,       
  FF_SEARCH_BOX,      
  IE_BROWSED_PAGE,    
  QSB_WIN_BOX,        
                      
  WEBAPPS_CALENDAR,   
  WEBAPPS_DOCS,       
  WEBAPPS_GMAIL,      

  IETB_LINKDOCTOR,    
  FFTB_LINKDOCTOR,    
  IETB7_SEARCH_BOX,   
  TB8_SEARCH_BOX,     
  CHROME_FRAME,       

  
  PARTNER_AP_1,
  PARTNER_AP_2,
  PARTNER_AP_3,
  PARTNER_AP_4,
  PARTNER_AP_5,

  CHROME_MAC_OMNIBOX,  
  CHROME_MAC_HOME_PAGE,

  CHROMEOS_OMNIBOX,    
  CHROMEOS_HOME_PAGE,  
  CHROMEOS_APP_LIST,   

  
  CHROME_IOS_OMNIBOX_TABLET,
  CHROME_IOS_OMNIBOX_MOBILE,

  CHROME_APP_LIST,     
  CHROME_MAC_APP_LIST, 
                       

  
  
  
  UNDEFINED_AP_Q,
  UNDEFINED_AP_R,
  UNDEFINED_AP_S,
  UNDEFINED_AP_T,
  UNDEFINED_AP_U,
  UNDEFINED_AP_V,
  UNDEFINED_AP_W,
  UNDEFINED_AP_X,
  UNDEFINED_AP_Y,
  UNDEFINED_AP_Z,

  PACK_AP0,
  PACK_AP1,
  PACK_AP2,
  PACK_AP3,
  PACK_AP4,
  PACK_AP5,
  PACK_AP6,
  PACK_AP7,
  PACK_AP8,
  PACK_AP9,
  PACK_AP10,
  PACK_AP11,
  PACK_AP12,
  PACK_AP13,

  
  
  LAST_ACCESS_POINT
};

enum Product {
  IE_TOOLBAR = 1,
  TOOLBAR_NOTIFIER,
  PACK,
  DESKTOP,
  CHROME,
  FF_TOOLBAR,
  QSB_WIN,
  WEBAPPS,
  PINYIN_IME,
  PARTNER
  
};

enum Event {
  INVALID_EVENT = 0,
  INSTALL = 1,    
  SET_TO_GOOGLE,  
  FIRST_SEARCH,   
  REPORT_RLS,     
  
  
  ACTIVATE,       
  LAST_EVENT
};

}  

#endif  
