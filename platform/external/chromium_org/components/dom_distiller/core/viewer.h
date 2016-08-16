// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CORE_VIEWER_H_
#define COMPONENTS_DOM_DISTILLER_CORE_VIEWER_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "components/dom_distiller/core/distilled_page_prefs.h"
#include "ui/gfx/size.h"

namespace dom_distiller {

class DistilledArticleProto;
class DistilledPageProto;
class DomDistillerServiceInterface;
class ViewerHandle;
class ViewRequestDelegate;

namespace viewer {

const std::string GetUnsafeArticleHtml(
    const DistilledArticleProto* article_proto,
    const DistilledPagePrefs::Theme theme,
    const DistilledPagePrefs::FontFamily font_family);

const std::string GetUnsafePartialArticleHtml(
    const DistilledPageProto* page_proto,
    const DistilledPagePrefs::Theme theme,
    const DistilledPagePrefs::FontFamily font_family);

const std::string GetUnsafeIncrementalDistilledPageJs(
    const DistilledPageProto* page_proto,
    const bool is_last_page);

const std::string GetToggleLoadingIndicatorJs(const bool is_last_page);

const std::string GetErrorPageHtml(
    const DistilledPagePrefs::Theme theme,
    const DistilledPagePrefs::FontFamily font_family);

const std::string GetCss();

const std::string GetJavaScript();

scoped_ptr<ViewerHandle> CreateViewRequest(
    DomDistillerServiceInterface* dom_distiller_service,
    const std::string& path,
    ViewRequestDelegate* view_request_delegate,
    const gfx::Size& render_view_size);

const std::string GetDistilledPageFontFamilyJs(
    DistilledPagePrefs::FontFamily font);

const std::string GetDistilledPageThemeJs(DistilledPagePrefs::Theme theme);

}  

}  

#endif  
