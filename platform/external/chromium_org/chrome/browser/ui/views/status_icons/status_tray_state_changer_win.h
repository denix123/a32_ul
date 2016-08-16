// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_STATUS_ICONS_STATUS_TRAY_STATE_CHANGER_WIN_H_
#define CHROME_BROWSER_UI_VIEWS_STATUS_ICONS_STATUS_TRAY_STATE_CHANGER_WIN_H_

#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "base/threading/non_thread_safe.h"
#include "base/win/iunknown_impl.h"
#include "base/win/scoped_comptr.h"

enum NOTIFYITEM_PREFERENCE {
  
  PREFERENCE_SHOW_WHEN_ACTIVE = 0,
  
  PREFERENCE_SHOW_NEVER = 1,
  
  PREFERENCE_SHOW_ALWAYS = 2
};

struct NOTIFYITEM {
  PWSTR exe_name;    
  PWSTR tip;         
                     
  HICON icon;        
  HWND hwnd;         
  DWORD preference;  
                     
  UINT id;           
                     
  GUID guid;         
                     
};

class __declspec(uuid("D782CCBA-AFB0-43F1-94DB-FDA3779EACCB")) INotificationCB
    : public IUnknown {
 public:
  virtual HRESULT STDMETHODCALLTYPE
      Notify(ULONG event, NOTIFYITEM* notify_item) = 0;
};

class StatusTrayStateChangerWin : public INotificationCB,
                                  public base::win::IUnknownImpl,
                                  public base::NonThreadSafe {
 public:
  StatusTrayStateChangerWin(UINT icon_id, HWND window);

  
  
  
  
  void EnsureTrayIconVisible();

  
  virtual ULONG STDMETHODCALLTYPE AddRef() OVERRIDE;
  virtual ULONG STDMETHODCALLTYPE Release() OVERRIDE;
  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, PVOID*) OVERRIDE;

  
  
  
  
  
  virtual HRESULT STDMETHODCALLTYPE Notify(ULONG, NOTIFYITEM*);

 protected:
  virtual ~StatusTrayStateChangerWin();

 private:
  friend class StatusTrayStateChangerWinTest;

  enum InterfaceVersion {
    INTERFACE_VERSION_LEGACY = 0,
    INTERFACE_VERSION_WIN8,
    INTERFACE_VERSION_UNKNOWN
  };

  
  
  bool CreateTrayNotify();

  
  
  
  scoped_ptr<NOTIFYITEM> RegisterCallback();

  
  
  
  
  bool RegisterCallbackWin8();
  bool RegisterCallbackLegacy();

  
  void SendNotifyItemUpdate(scoped_ptr<NOTIFYITEM> notify_item);

  
  
  base::win::ScopedComPtr<IUnknown> tray_notify_;
  InterfaceVersion interface_version_;

  
  const UINT icon_id_;
  
  
  const HWND window_;
  
  
  base::string16 file_name_;

  
  
  
  
  
  
  scoped_ptr<NOTIFYITEM> notify_item_;

  DISALLOW_COPY_AND_ASSIGN(StatusTrayStateChangerWin);
};

#endif  
