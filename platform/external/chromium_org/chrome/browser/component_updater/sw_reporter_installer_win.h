// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_COMPONENT_UPDATER_SW_REPORTER_INSTALLER_WIN_H_
#define CHROME_BROWSER_COMPONENT_UPDATER_SW_REPORTER_INSTALLER_WIN_H_

class PrefRegistrySimple;
class PrefService;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace component_updater {

class ComponentUpdateService;

void RegisterSwReporterComponent(ComponentUpdateService* cus,
                                 PrefService* prefs);

void RegisterPrefsForSwReporter(PrefRegistrySimple* registry);

void RegisterProfilePrefsForSwReporter(
    user_prefs::PrefRegistrySyncable* registry);

}  

#endif  
