// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_OMNIBOX_OMNIBOX_LOG_H_
#define CHROME_BROWSER_OMNIBOX_OMNIBOX_LOG_H_

#include <stddef.h>

#include "base/strings/string16.h"
#include "base/time/time.h"
#include "components/metrics/proto/omnibox_event.pb.h"
#include "components/metrics/proto/omnibox_input_type.pb.h"
#include "components/omnibox/autocomplete_provider.h"
#include "components/sessions/session_id.h"

class AutocompleteResult;

struct OmniboxLog {
  OmniboxLog(
      const base::string16& text,
      bool just_deleted_text,
      metrics::OmniboxInputType::Type input_type,
      bool is_popup_open,
      size_t selected_index,
      bool is_paste_and_go,
      SessionID::id_type tab_id,
      metrics::OmniboxEventProto::PageClassification
          current_page_classification,
      base::TimeDelta elapsed_time_since_user_first_modified_omnibox,
      size_t completed_length,
      base::TimeDelta elapsed_time_since_last_change_to_default_match,
      const AutocompleteResult& result);
  ~OmniboxLog();

  
  base::string16 text;

  
  
  bool just_deleted_text;

  
  metrics::OmniboxInputType::Type input_type;

  
  bool is_popup_open;

  
  
  size_t selected_index;

  
  
  bool is_paste_and_go;

  
  
  SessionID::id_type tab_id;

  
  
  metrics::OmniboxEventProto::PageClassification current_page_classification;

  
  
  
  
  
  
  
  
  base::TimeDelta elapsed_time_since_user_first_modified_omnibox;

  
  
  
  
  
  size_t completed_length;

  
  
  
  
  
  base::TimeDelta elapsed_time_since_last_change_to_default_match;

  
  const AutocompleteResult& result;

  
  
  
  ProvidersInfo providers_info;
};

#endif  
