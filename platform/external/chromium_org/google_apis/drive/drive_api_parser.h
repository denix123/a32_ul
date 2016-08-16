// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_DRIVE_DRIVE_API_PARSER_H_
#define GOOGLE_APIS_DRIVE_DRIVE_API_PARSER_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/strings/string_piece.h"
#include "base/time/time.h"
#include "url/gurl.h"

namespace base {
class Value;
template <class StructType>
class JSONValueConverter;

namespace internal {
template <class NestedType>
class RepeatedMessageConverter;
}  
}  

namespace google_apis {

class AboutResource {
 public:
  AboutResource();
  ~AboutResource();

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<AboutResource>* converter);

  
  static scoped_ptr<AboutResource> CreateFrom(const base::Value& value);

  
  int64 largest_change_id() const { return largest_change_id_; }
  
  int64 quota_bytes_total() const { return quota_bytes_total_; }
  
  int64 quota_bytes_used() const { return quota_bytes_used_; }
  
  const std::string& root_folder_id() const { return root_folder_id_; }

  void set_largest_change_id(int64 largest_change_id) {
    largest_change_id_ = largest_change_id;
  }
  void set_quota_bytes_total(int64 quota_bytes_total) {
    quota_bytes_total_ = quota_bytes_total;
  }
  void set_quota_bytes_used(int64 quota_bytes_used) {
    quota_bytes_used_ = quota_bytes_used;
  }
  void set_root_folder_id(const std::string& root_folder_id) {
    root_folder_id_ = root_folder_id;
  }

 private:
  friend class DriveAPIParserTest;
  FRIEND_TEST_ALL_PREFIXES(DriveAPIParserTest, AboutResourceParser);

  
  
  bool Parse(const base::Value& value);

  int64 largest_change_id_;
  int64 quota_bytes_total_;
  int64 quota_bytes_used_;
  std::string root_folder_id_;

  
};

class DriveAppIcon {
 public:
  enum IconCategory {
    UNKNOWN,          
    DOCUMENT,         
    APPLICATION,      
    SHARED_DOCUMENT,  
  };

  DriveAppIcon();
  ~DriveAppIcon();

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<DriveAppIcon>* converter);

  
  static scoped_ptr<DriveAppIcon> CreateFrom(const base::Value& value);

  
  IconCategory category() const { return category_; }

  
  int icon_side_length() const { return icon_side_length_; }

  
  const GURL& icon_url() const { return icon_url_; }

  void set_category(IconCategory category) {
    category_ = category;
  }
  void set_icon_side_length(int icon_side_length) {
    icon_side_length_ = icon_side_length;
  }
  void set_icon_url(const GURL& icon_url) {
    icon_url_ = icon_url;
  }

 private:
  
  
  bool Parse(const base::Value& value);

  
  
  static bool GetIconCategory(const base::StringPiece& category,
                              IconCategory* result);

  friend class base::internal::RepeatedMessageConverter<DriveAppIcon>;
  friend class AppResource;

  IconCategory category_;
  int icon_side_length_;
  GURL icon_url_;

  DISALLOW_COPY_AND_ASSIGN(DriveAppIcon);
};

class AppResource {
 public:
  ~AppResource();
  AppResource();

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<AppResource>* converter);

  
  static scoped_ptr<AppResource> CreateFrom(const base::Value& value);

  
  const std::string& application_id() const { return application_id_; }

  
  const std::string& name() const { return name_; }

  
  
  
  const std::string& object_type() const { return object_type_; }

  
  const std::string& product_id() const { return product_id_; }

  
  bool supports_create() const { return supports_create_; }

  
  bool is_removable() const { return removable_; }

  
  const GURL& create_url() const { return create_url_; }

  
  
  
  const ScopedVector<std::string>& primary_mimetypes() const {
    return primary_mimetypes_;
  }

  
  
  
  const ScopedVector<std::string>& secondary_mimetypes() const {
    return secondary_mimetypes_;
  }

  
  
  
  const ScopedVector<std::string>& primary_file_extensions() const {
    return primary_file_extensions_;
  }

  
  
  
  const ScopedVector<std::string>& secondary_file_extensions() const {
    return secondary_file_extensions_;
  }

  
  
  
  const ScopedVector<DriveAppIcon>& icons() const {
    return icons_;
  }

  void set_application_id(const std::string& application_id) {
    application_id_ = application_id;
  }
  void set_name(const std::string& name) { name_ = name; }
  void set_object_type(const std::string& object_type) {
    object_type_ = object_type;
  }
  void set_product_id(const std::string& id) { product_id_ = id; }
  void set_supports_create(bool supports_create) {
    supports_create_ = supports_create;
  }
  void set_removable(bool removable) { removable_ = removable; }
  void set_primary_mimetypes(
      ScopedVector<std::string> primary_mimetypes) {
    primary_mimetypes_ = primary_mimetypes.Pass();
  }
  void set_secondary_mimetypes(
      ScopedVector<std::string> secondary_mimetypes) {
    secondary_mimetypes_ = secondary_mimetypes.Pass();
  }
  void set_primary_file_extensions(
      ScopedVector<std::string> primary_file_extensions) {
    primary_file_extensions_ = primary_file_extensions.Pass();
  }
  void set_secondary_file_extensions(
      ScopedVector<std::string> secondary_file_extensions) {
    secondary_file_extensions_ = secondary_file_extensions.Pass();
  }
  void set_icons(ScopedVector<DriveAppIcon> icons) {
    icons_ = icons.Pass();
  }
  void set_create_url(const GURL& url) {
    create_url_ = url;
  }

 private:
  friend class base::internal::RepeatedMessageConverter<AppResource>;
  friend class AppList;

  
  
  bool Parse(const base::Value& value);

  std::string application_id_;
  std::string name_;
  std::string object_type_;
  std::string product_id_;
  bool supports_create_;
  bool removable_;
  GURL create_url_;
  ScopedVector<std::string> primary_mimetypes_;
  ScopedVector<std::string> secondary_mimetypes_;
  ScopedVector<std::string> primary_file_extensions_;
  ScopedVector<std::string> secondary_file_extensions_;
  ScopedVector<DriveAppIcon> icons_;

  DISALLOW_COPY_AND_ASSIGN(AppResource);
};

class AppList {
 public:
  AppList();
  ~AppList();

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<AppList>* converter);

  
  static scoped_ptr<AppList> CreateFrom(const base::Value& value);

  
  const std::string& etag() const { return etag_; }

  
  const ScopedVector<AppResource>& items() const { return items_; }

  void set_etag(const std::string& etag) {
    etag_ = etag;
  }
  void set_items(ScopedVector<AppResource> items) {
    items_ = items.Pass();
  }

 private:
  friend class DriveAPIParserTest;
  FRIEND_TEST_ALL_PREFIXES(DriveAPIParserTest, AppListParser);

  
  
  bool Parse(const base::Value& value);

  std::string etag_;
  ScopedVector<AppResource> items_;

  DISALLOW_COPY_AND_ASSIGN(AppList);
};

class ParentReference {
 public:
  ParentReference();
  ~ParentReference();

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<ParentReference>* converter);

  
  static scoped_ptr<ParentReference> CreateFrom(const base::Value& value);

  
  const std::string& file_id() const { return file_id_; }

  
  const GURL& parent_link() const { return parent_link_; }

  void set_file_id(const std::string& file_id) { file_id_ = file_id; }
  void set_parent_link(const GURL& parent_link) {
    parent_link_ = parent_link;
  }

 private:
  
  
  bool Parse(const base::Value& value);

  std::string file_id_;
  GURL parent_link_;
};

class FileLabels {
 public:
  FileLabels();
  ~FileLabels();

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<FileLabels>* converter);

  
  static scoped_ptr<FileLabels> CreateFrom(const base::Value& value);

  
  bool is_trashed() const { return trashed_; }

  void set_trashed(bool trashed) { trashed_ = trashed; }

 private:
  friend class FileResource;

  
  
  bool Parse(const base::Value& value);

  bool trashed_;
};

class ImageMediaMetadata {
 public:
  ImageMediaMetadata();
  ~ImageMediaMetadata();

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<ImageMediaMetadata>* converter);

  
  static scoped_ptr<ImageMediaMetadata> CreateFrom(const base::Value& value);

  
  int width() const { return width_; }
  
  int height() const { return height_; }
  
  int rotation() const { return rotation_; }

  void set_width(int width) { width_ = width; }
  void set_height(int height) { height_ = height; }
  void set_rotation(int rotation) { rotation_ = rotation; }

 private:
  friend class FileResource;

  
  
  bool Parse(const base::Value& value);

  int width_;
  int height_;
  int rotation_;
};


class FileResource {
 public:
  
  struct OpenWithLink {
    std::string app_id;
    GURL open_url;
  };

  FileResource();
  ~FileResource();

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<FileResource>* converter);

  
  static scoped_ptr<FileResource> CreateFrom(const base::Value& value);

  
  
  
  bool IsDirectory() const;

  
  
  
  
  bool IsHostedDocument() const;

  
  const std::string& file_id() const { return file_id_; }

  
  const std::string& etag() const { return etag_; }

  
  const std::string& title() const { return title_; }

  
  const std::string& mime_type() const { return mime_type_; }

  
  const FileLabels& labels() const { return labels_; }

  
  const ImageMediaMetadata& image_media_metadata() const {
    return image_media_metadata_;
  }

  
  const base::Time& created_date() const { return created_date_; }

  
  const base::Time& modified_date() const { return modified_date_; }

  
  const base::Time& last_viewed_by_me_date() const {
    return last_viewed_by_me_date_;
  }

  
  const base::Time& shared_with_me_date() const {
    return shared_with_me_date_;
  }

  
  bool shared() const { return shared_; }

  
  const std::string& md5_checksum() const { return md5_checksum_; }

  
  int64 file_size() const { return file_size_; }

  
  
  const GURL& alternate_link() const { return alternate_link_; }

  
  const std::vector<ParentReference>& parents() const { return parents_; }

  
  const std::vector<OpenWithLink>& open_with_links() const {
    return open_with_links_;
  }

  void set_file_id(const std::string& file_id) {
    file_id_ = file_id;
  }
  void set_etag(const std::string& etag) {
    etag_ = etag;
  }
  void set_title(const std::string& title) {
    title_ = title;
  }
  void set_mime_type(const std::string& mime_type) {
    mime_type_ = mime_type;
  }
  FileLabels* mutable_labels() {
    return &labels_;
  }
  ImageMediaMetadata* mutable_image_media_metadata() {
    return &image_media_metadata_;
  }
  void set_created_date(const base::Time& created_date) {
    created_date_ = created_date;
  }
  void set_modified_date(const base::Time& modified_date) {
    modified_date_ = modified_date;
  }
  void set_last_viewed_by_me_date(const base::Time& last_viewed_by_me_date) {
    last_viewed_by_me_date_ = last_viewed_by_me_date;
  }
  void set_shared_with_me_date(const base::Time& shared_with_me_date) {
    shared_with_me_date_ = shared_with_me_date;
  }
  void set_shared(bool shared) {
    shared_ = shared;
  }
  void set_md5_checksum(const std::string& md5_checksum) {
    md5_checksum_ = md5_checksum;
  }
  void set_file_size(int64 file_size) {
    file_size_ = file_size;
  }
  void set_alternate_link(const GURL& alternate_link) {
    alternate_link_ = alternate_link;
  }
  std::vector<ParentReference>* mutable_parents() { return &parents_; }
  std::vector<OpenWithLink>* mutable_open_with_links() {
    return &open_with_links_;
  }

 private:
  friend class base::internal::RepeatedMessageConverter<FileResource>;
  friend class ChangeResource;
  friend class FileList;

  
  
  bool Parse(const base::Value& value);

  std::string file_id_;
  std::string etag_;
  std::string title_;
  std::string mime_type_;
  FileLabels labels_;
  ImageMediaMetadata image_media_metadata_;
  base::Time created_date_;
  base::Time modified_date_;
  base::Time last_viewed_by_me_date_;
  base::Time shared_with_me_date_;
  bool shared_;
  std::string md5_checksum_;
  int64 file_size_;
  GURL alternate_link_;
  std::vector<ParentReference> parents_;
  std::vector<OpenWithLink> open_with_links_;
};

class FileList {
 public:
  FileList();
  ~FileList();

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<FileList>* converter);

  
  static bool HasFileListKind(const base::Value& value);

  
  static scoped_ptr<FileList> CreateFrom(const base::Value& value);

  
  
  const GURL& next_link() const { return next_link_; }

  
  const ScopedVector<FileResource>& items() const { return items_; }
  ScopedVector<FileResource>* mutable_items() { return &items_; }

  void set_next_link(const GURL& next_link) {
    next_link_ = next_link;
  }

 private:
  friend class DriveAPIParserTest;
  FRIEND_TEST_ALL_PREFIXES(DriveAPIParserTest, FileListParser);

  
  
  bool Parse(const base::Value& value);

  GURL next_link_;
  ScopedVector<FileResource> items_;

  DISALLOW_COPY_AND_ASSIGN(FileList);
};

class ChangeResource {
 public:
  ChangeResource();
  ~ChangeResource();

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<ChangeResource>* converter);

  
  static scoped_ptr<ChangeResource> CreateFrom(const base::Value& value);

  
  
  int64 change_id() const { return change_id_; }

  
  const std::string& file_id() const { return file_id_; }

  
  bool is_deleted() const { return deleted_; }

  
  const FileResource* file() const { return file_.get(); }
  FileResource* mutable_file() { return file_.get(); }

  
  const base::Time& modification_date() const { return modification_date_; }

  void set_change_id(int64 change_id) {
    change_id_ = change_id;
  }
  void set_file_id(const std::string& file_id) {
    file_id_ = file_id;
  }
  void set_deleted(bool deleted) {
    deleted_ = deleted;
  }
  void set_file(scoped_ptr<FileResource> file) {
    file_ = file.Pass();
  }
  void set_modification_date(const base::Time& modification_date) {
    modification_date_ = modification_date;
  }

 private:
  friend class base::internal::RepeatedMessageConverter<ChangeResource>;
  friend class ChangeList;

  
  
  bool Parse(const base::Value& value);

  int64 change_id_;
  std::string file_id_;
  bool deleted_;
  scoped_ptr<FileResource> file_;
  base::Time modification_date_;

  DISALLOW_COPY_AND_ASSIGN(ChangeResource);
};

class ChangeList {
 public:
  ChangeList();
  ~ChangeList();

  
  
  static void RegisterJSONConverter(
      base::JSONValueConverter<ChangeList>* converter);

  
  static bool HasChangeListKind(const base::Value& value);

  
  static scoped_ptr<ChangeList> CreateFrom(const base::Value& value);

  
  
  const GURL& next_link() const { return next_link_; }

  
  int64 largest_change_id() const { return largest_change_id_; }

  
  const ScopedVector<ChangeResource>& items() const { return items_; }
  ScopedVector<ChangeResource>* mutable_items() { return &items_; }

  void set_next_link(const GURL& next_link) {
    next_link_ = next_link;
  }
  void set_largest_change_id(int64 largest_change_id) {
    largest_change_id_ = largest_change_id;
  }

 private:
  friend class DriveAPIParserTest;
  FRIEND_TEST_ALL_PREFIXES(DriveAPIParserTest, ChangeListParser);

  
  
  bool Parse(const base::Value& value);

  GURL next_link_;
  int64 largest_change_id_;
  ScopedVector<ChangeResource> items_;

  DISALLOW_COPY_AND_ASSIGN(ChangeList);
};

}  

#endif  
