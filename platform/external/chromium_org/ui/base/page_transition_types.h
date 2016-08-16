// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_PAGE_TRANSITION_TYPES_H_
#define UI_BASE_PAGE_TRANSITION_TYPES_H_

#include "base/basictypes.h"
#include "ui/base/ui_base_export.h"

namespace ui {

enum PageTransition {

#define PAGE_TRANSITION(label, value) PAGE_TRANSITION_ ## label = value,
#include "ui/base/page_transition_types_list.h"
#undef PAGE_TRANSITION

};

UI_BASE_EXPORT bool PageTransitionCoreTypeIs(PageTransition lhs,
                                             PageTransition rhs);

UI_BASE_EXPORT PageTransition PageTransitionStripQualifier(
    PageTransition type);

bool PageTransitionIsValidType(int32 type);

UI_BASE_EXPORT PageTransition PageTransitionFromInt(int32 type);

UI_BASE_EXPORT bool PageTransitionIsMainFrame(PageTransition type);

UI_BASE_EXPORT bool PageTransitionIsRedirect(PageTransition type);

UI_BASE_EXPORT bool PageTransitionIsNewNavigation(PageTransition type);

UI_BASE_EXPORT int32 PageTransitionGetQualifier(PageTransition type);

UI_BASE_EXPORT bool PageTransitionIsWebTriggerable(PageTransition type);

UI_BASE_EXPORT const char* PageTransitionGetCoreTransitionString(
    PageTransition type);

#if defined(CONTENT_IMPLEMENTATION)
class DontUseOperatorEquals;

DontUseOperatorEquals operator==(PageTransition, PageTransition);
DontUseOperatorEquals operator==(PageTransition, int);
DontUseOperatorEquals operator==(int, PageTransition);
#endif  

}  

#endif  
