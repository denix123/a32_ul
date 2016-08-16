// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LIBGTK2UI_GCONF_LISTENER_H_
#define CHROME_BROWSER_UI_LIBGTK2UI_GCONF_LISTENER_H_

#include <gconf/gconf-client.h>
#include <gtk/gtk.h>

#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "chrome/browser/ui/libgtk2ui/gtk2_signal.h"

namespace libgtk2ui {
class Gtk2UI;

class GConfListener {
 public:
  
  explicit GConfListener(Gtk2UI* delegate);
  ~GConfListener();

 private:
  
  CHROMEG_CALLBACK_2(GConfListener, void, OnChangeNotification,
                     GConfClient*, guint, GConfEntry*);

  void GetAndRegister(const char* key_to_subscribe,
                      const base::Callback<void(GConfValue*)>& initial_setter);

  
  
  bool HandleGError(GError* error, const char* key);

  
  
  void ParseAndStoreButtonValue(GConfValue* gconf_value);
  void ParseAndStoreMiddleClickValue(GConfValue* gconf_value);

  Gtk2UI* delegate_;

  
  
  GConfClient* client_;

  DISALLOW_COPY_AND_ASSIGN(GConfListener);
};

}  

#endif  
