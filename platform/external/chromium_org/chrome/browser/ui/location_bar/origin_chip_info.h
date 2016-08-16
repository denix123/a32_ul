// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LOCATION_BAR_ORIGIN_CHIP_INFO_H_
#define CHROME_BROWSER_UI_LOCATION_BAR_ORIGIN_CHIP_INFO_H_

#include "base/strings/string16.h"
#include "chrome/browser/ui/toolbar/toolbar_model.h"
#include "extensions/browser/extension_icon_image.h"

class GURL;
class Profile;

namespace content {
class WebContents;
}

class OriginChipInfo {
 public:
  
  
  
  OriginChipInfo(extensions::IconImage::Observer* owner, Profile* profile);
  ~OriginChipInfo();

  
  
  bool Update(const content::WebContents* web_contents,
              const ToolbarModel* toolbar_model);

  
  const base::string16& label() const { return label_; }

  
  base::string16 Tooltip() const;

  
  
  
  
  int icon() const { return icon_; }

  
  const GURL& displayed_url() const { return displayed_url_; }

  
  ToolbarModel::SecurityLevel security_level() const { return security_level_; }

  
  bool is_url_malware() const { return is_url_malware_; }

 private:
  
  extensions::IconImage::Observer* owner_;

  Profile* profile_;

  
  
  GURL displayed_url_;
  ToolbarModel::SecurityLevel security_level_;
  bool is_url_malware_;

  
  base::string16 label_;
  int icon_;

  
  
  scoped_ptr<extensions::IconImage> extension_icon_image_;

  DISALLOW_COPY_AND_ASSIGN(OriginChipInfo);
};

class OriginChip {
 public:
  
  
  
  static bool IsMalware(const GURL& url, const content::WebContents* tab);

  
  
  static base::string16 LabelFromURLForProfile(const GURL& provided_url,
                                               Profile* profile);
};

#endif  
