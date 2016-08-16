// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_DRIVE_DRIVE_API_UTIL_H_
#define CHROME_BROWSER_DRIVE_DRIVE_API_UTIL_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "google_apis/drive/drive_common_callbacks.h"
#include "google_apis/drive/gdata_errorcode.h"

class GURL;

namespace base {
class FilePath;
class Value;
}  

namespace google_apis {
class ChangeList;
class ChangeResource;
class FileList;
class FileResource;
class ResourceEntry;
class ResourceList;
}  

namespace drive {
namespace util {

const char kGoogleDocumentMimeType[] = "application/vnd.google-apps.document";
const char kGoogleDrawingMimeType[] = "application/vnd.google-apps.drawing";
const char kGooglePresentationMimeType[] =
    "application/vnd.google-apps.presentation";
const char kGoogleSpreadsheetMimeType[] =
    "application/vnd.google-apps.spreadsheet";
const char kGoogleTableMimeType[] = "application/vnd.google-apps.table";
const char kGoogleFormMimeType[] = "application/vnd.google-apps.form";
const char kDriveFolderMimeType[] = "application/vnd.google-apps.folder";

std::string EscapeQueryStringValue(const std::string& str);

std::string TranslateQuery(const std::string& original_query);

std::string ExtractResourceIdFromUrl(const GURL& url);

std::string CanonicalizeResourceId(const std::string& resource_id);

scoped_ptr<google_apis::ResourceEntry>
ConvertFileResourceToResourceEntry(
    const google_apis::FileResource& file_resource);

scoped_ptr<google_apis::ResourceEntry>
ConvertChangeResourceToResourceEntry(
    const google_apis::ChangeResource& change_resource);

scoped_ptr<google_apis::ResourceList>
ConvertFileListToResourceList(const google_apis::FileList& file_list);

scoped_ptr<google_apis::ResourceList>
ConvertChangeListToResourceList(const google_apis::ChangeList& change_list);

std::string GetMd5Digest(const base::FilePath& file_path);

std::string GetHostedDocumentExtension(const std::string& mime_type);

bool IsKnownHostedDocumentMimeType(const std::string& mime_type);

bool HasHostedDocumentExtension(const base::FilePath& path);

}  
}  

#endif  
