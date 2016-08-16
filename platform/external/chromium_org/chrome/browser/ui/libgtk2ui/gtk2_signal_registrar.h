// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LIBGTK2UI_GTK2_SIGNAL_REGISTRAR_H_
#define CHROME_BROWSER_UI_LIBGTK2UI_GTK2_SIGNAL_REGISTRAR_H_

#include <glib.h>
#include <map>
#include <vector>

#include "base/basictypes.h"

typedef void (*GCallback) (void);
typedef struct _GObject GObject;
typedef struct _GtkWidget GtkWidget;

namespace libgtk2ui {

class Gtk2SignalRegistrar {
 public:
  Gtk2SignalRegistrar();
  ~Gtk2SignalRegistrar();

  
  glong Connect(gpointer instance, const gchar* detailed_signal,
                GCallback signal_handler, gpointer data);
  
  glong ConnectAfter(gpointer instance, const gchar* detailed_signal,
                     GCallback signal_handler, gpointer data);

  
  void DisconnectAll(gpointer instance);

 private:
  typedef std::vector<glong> HandlerList;
  typedef std::map<GObject*, HandlerList> HandlerMap;

  static void WeakNotifyThunk(gpointer data, GObject* where_the_object_was) {
    reinterpret_cast<Gtk2SignalRegistrar*>(data)->WeakNotify(
        where_the_object_was);
  }
  void WeakNotify(GObject* where_the_object_was);

  glong ConnectInternal(gpointer instance, const gchar* detailed_signal,
                        GCallback signal_handler, gpointer data, bool after);

  HandlerMap handler_lists_;

  DISALLOW_COPY_AND_ASSIGN(Gtk2SignalRegistrar);
};

}  

#endif  
