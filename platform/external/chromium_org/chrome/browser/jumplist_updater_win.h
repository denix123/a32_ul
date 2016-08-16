// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_JUMPLIST_UPDATER_WIN_H_
#define CHROME_BROWSER_JUMPLIST_UPDATER_WIN_H_

#include <windows.h>
#include <shobjidl.h>

#include <string>
#include <vector>

#include "base/command_line.h"
#include "base/memory/ref_counted.h"
#include "base/win/scoped_comptr.h"
#include "third_party/skia/include/core/SkBitmap.h"

class ShellLinkItem : public base::RefCountedThreadSafe<ShellLinkItem> {
 public:
  ShellLinkItem();

  const std::wstring& title() const { return title_; }
  const std::wstring& icon_path() const { return icon_path_; }
  int icon_index() const { return icon_index_; }
  const SkBitmap& icon_data() const { return icon_data_; }

  std::wstring GetArguments() const;
  base::CommandLine* GetCommandLine();

  void set_title(const std::wstring& title) {
    title_ = title;
  }

  void set_icon(const std::wstring& path, int index) {
    icon_path_ = path;
    icon_index_ = index;
  }

  void set_icon_data(const SkBitmap& data) {
    icon_data_ = data;
  }

 private:
  friend class base::RefCountedThreadSafe<ShellLinkItem>;
  ~ShellLinkItem();

  
  base::CommandLine command_line_;

  
  std::wstring title_;

  
  std::wstring icon_path_;

  
  
  
  int icon_index_;

  
  
  
  SkBitmap icon_data_;

  DISALLOW_COPY_AND_ASSIGN(ShellLinkItem);
};

typedef std::vector<scoped_refptr<ShellLinkItem> > ShellLinkItemList;


class JumpListUpdater {
 public:
  explicit JumpListUpdater(const std::wstring& app_user_model_id);
  ~JumpListUpdater();

  
  static bool IsEnabled();

  
  
  size_t user_max_items() const { return user_max_items_; }

  
  
  
  bool BeginUpdate();

  
  bool CommitUpdate();

  
  bool AddTasks(const ShellLinkItemList& link_items);

  
  
  
  
  
  bool AddCustomCategory(const std::wstring& category_name,
                         const ShellLinkItemList& link_items,
                         size_t max_items);

 private:
  
  std::wstring app_user_model_id_;

  
  base::win::ScopedComPtr<ICustomDestinationList> destination_list_;

  
  
  size_t user_max_items_;

  DISALLOW_COPY_AND_ASSIGN(JumpListUpdater);
};

#endif  
