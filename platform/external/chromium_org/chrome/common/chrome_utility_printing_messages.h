// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>
#include <vector>

#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_platform_file.h"
#include "printing/backend/print_backend.h"
#include "printing/page_range.h"
#include "printing/pdf_render_settings.h"
#include "printing/pwg_raster_settings.h"

#define IPC_MESSAGE_START ChromeUtilityPrintingMsgStart

#if defined(ENABLE_FULL_PRINTING)

IPC_STRUCT_TRAITS_BEGIN(printing::PrinterCapsAndDefaults)
  IPC_STRUCT_TRAITS_MEMBER(printer_capabilities)
  IPC_STRUCT_TRAITS_MEMBER(caps_mime_type)
  IPC_STRUCT_TRAITS_MEMBER(printer_defaults)
  IPC_STRUCT_TRAITS_MEMBER(defaults_mime_type)
IPC_STRUCT_TRAITS_END()

IPC_ENUM_TRAITS_MAX_VALUE(printing::ColorModel, printing::PROCESSCOLORMODEL_RGB)

IPC_STRUCT_TRAITS_BEGIN(printing::PrinterSemanticCapsAndDefaults::Paper)
  IPC_STRUCT_TRAITS_MEMBER(display_name)
  IPC_STRUCT_TRAITS_MEMBER(vendor_id)
  IPC_STRUCT_TRAITS_MEMBER(size_um)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(printing::PrinterSemanticCapsAndDefaults)
  IPC_STRUCT_TRAITS_MEMBER(collate_capable)
  IPC_STRUCT_TRAITS_MEMBER(collate_default)
  IPC_STRUCT_TRAITS_MEMBER(copies_capable)
  IPC_STRUCT_TRAITS_MEMBER(duplex_capable)
  IPC_STRUCT_TRAITS_MEMBER(duplex_default)
  IPC_STRUCT_TRAITS_MEMBER(color_changeable)
  IPC_STRUCT_TRAITS_MEMBER(color_default)
  IPC_STRUCT_TRAITS_MEMBER(color_model)
  IPC_STRUCT_TRAITS_MEMBER(bw_model)
  IPC_STRUCT_TRAITS_MEMBER(papers)
  IPC_STRUCT_TRAITS_MEMBER(default_paper)
  IPC_STRUCT_TRAITS_MEMBER(dpis)
  IPC_STRUCT_TRAITS_MEMBER(default_dpi)
IPC_STRUCT_TRAITS_END()

IPC_ENUM_TRAITS(printing::PwgRasterTransformType)

IPC_STRUCT_TRAITS_BEGIN(printing::PwgRasterSettings)
  IPC_STRUCT_TRAITS_MEMBER(odd_page_transform)
  IPC_STRUCT_TRAITS_MEMBER(rotate_all_pages)
  IPC_STRUCT_TRAITS_MEMBER(reverse_page_order)
IPC_STRUCT_TRAITS_END()


#if defined(OS_WIN)
IPC_MESSAGE_CONTROL2(ChromeUtilityMsg_RenderPDFPagesToMetafiles,
                     IPC::PlatformFileForTransit, 
                     printing::PdfRenderSettings )

IPC_MESSAGE_CONTROL2(ChromeUtilityMsg_RenderPDFPagesToMetafiles_GetPage,
                     int ,
                     IPC::PlatformFileForTransit )

IPC_MESSAGE_CONTROL0(ChromeUtilityMsg_RenderPDFPagesToMetafiles_Stop)
#endif  

IPC_MESSAGE_CONTROL4(ChromeUtilityMsg_RenderPDFPagesToPWGRaster,
                     IPC::PlatformFileForTransit, 
                     printing::PdfRenderSettings, 
                     
                     printing::PwgRasterSettings,
                     IPC::PlatformFileForTransit )

IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_GetPrinterCapsAndDefaults,
                     std::string )

IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_GetPrinterSemanticCapsAndDefaults,
                     std::string )


#if defined(OS_WIN)
IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_RenderPDFPagesToMetafiles_PageCount,
                     int )

IPC_MESSAGE_CONTROL2(ChromeUtilityHostMsg_RenderPDFPagesToMetafiles_PageDone,
                     bool ,
                     double )
#endif  

IPC_MESSAGE_CONTROL0(ChromeUtilityHostMsg_RenderPDFPagesToPWGRaster_Succeeded)

IPC_MESSAGE_CONTROL0(ChromeUtilityHostMsg_RenderPDFPagesToPWGRaster_Failed)

IPC_MESSAGE_CONTROL2(ChromeUtilityHostMsg_GetPrinterCapsAndDefaults_Succeeded,
                     std::string ,
                     printing::PrinterCapsAndDefaults)

IPC_MESSAGE_CONTROL2(
    ChromeUtilityHostMsg_GetPrinterSemanticCapsAndDefaults_Succeeded,
    std::string ,
    printing::PrinterSemanticCapsAndDefaults)

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_GetPrinterCapsAndDefaults_Failed,
                     std::string )

IPC_MESSAGE_CONTROL1(
  ChromeUtilityHostMsg_GetPrinterSemanticCapsAndDefaults_Failed,
  std::string )

#endif  
