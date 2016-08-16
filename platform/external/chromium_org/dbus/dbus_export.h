// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DBUS_DBUS_EXPORT_H_
#define DBUS_DBUS_EXPORT_H_


#if defined(WIN32)
#error dbus support is not currently expected to work on windows
#endif  

#if defined(COMPONENT_BUILD)

#if defined(DBUS_IMPLEMENTATION)
#define CHROME_DBUS_EXPORT __attribute__((visibility("default")))
#else
#define CHROME_DBUS_EXPORT
#endif

#else  

#define CHROME_DBUS_EXPORT

#endif  

#endif  
