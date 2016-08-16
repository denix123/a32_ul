// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_TASK_MANAGER_TASK_MANAGER_BROWSERTEST_UTIL_H_
#define CHROME_BROWSER_TASK_MANAGER_TASK_MANAGER_BROWSERTEST_UTIL_H_

#include "base/strings/string16.h"

namespace task_manager {
namespace browsertest_util {

void WaitForTaskManagerRows(int resource_count,
                            const base::string16& title_pattern);

base::string16 MatchTab(const char* title);         
base::string16 MatchAnyTab();                       
base::string16 MatchAboutBlankTab();                
base::string16 MatchExtension(const char* title);   
base::string16 MatchAnyExtension();                 
base::string16 MatchApp(const char* title);         
base::string16 MatchAnyApp();                       
base::string16 MatchWebView(const char* title);     
base::string16 MatchAnyWebView();                   
base::string16 MatchBackground(const char* title);  
base::string16 MatchAnyBackground();                
base::string16 MatchPrint(const char* title);       
base::string16 MatchAnyPrint();                     

}  
}  

#endif  
