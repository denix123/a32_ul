// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_APP_LIST_TEST_CHROME_APP_LIST_TEST_SUPPORT_H_
#define CHROME_BROWSER_UI_APP_LIST_TEST_CHROME_APP_LIST_TEST_SUPPORT_H_

namespace app_list {
class AppListModel;
}

class AppListService;
class AppListServiceImpl;
class Profile;

namespace test {

app_list::AppListModel* GetAppListModel(AppListService* service);

AppListService* GetAppListService();
AppListServiceImpl* GetAppListServiceImpl();

Profile* CreateSecondProfileAsync();

}  

#endif  
