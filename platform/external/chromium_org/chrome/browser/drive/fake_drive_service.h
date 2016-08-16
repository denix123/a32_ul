// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_DRIVE_FAKE_DRIVE_SERVICE_H_
#define CHROME_BROWSER_DRIVE_FAKE_DRIVE_SERVICE_H_

#include "base/files/file_path.h"
#include "chrome/browser/drive/drive_service_interface.h"

namespace base {
class DictionaryValue;
}

namespace google_apis {
class AboutResource;
class ChangeResource;
class FileResource;
}

namespace drive {

class FakeDriveService : public DriveServiceInterface {
 public:
  class ChangeObserver {
   public:
    virtual ~ChangeObserver() {}
    virtual void OnNewChangeAvailable() = 0;
  };

  FakeDriveService();
  virtual ~FakeDriveService();

  
  bool LoadAppListForDriveApi(const std::string& relative_path);

  
  void AddApp(const std::string& app_id,
              const std::string& app_name,
              const std::string& product_id,
              const std::string& create_url);

  
  void RemoveAppByProductId(const std::string& product_id);

  
  bool HasApp(const std::string& app_id) const;

  
  
  void set_offline(bool offline) { offline_ = offline; }

  
  
  void set_never_return_all_file_list(bool value) {
    never_return_all_file_list_ = value;
  }

  
  
  void set_default_max_results(int default_max_results) {
    default_max_results_ = default_max_results;
  }

  
  
  void set_share_url_base(const GURL& share_url_base) {
    share_url_base_ = share_url_base;
  }

  
  void SetQuotaValue(int64 used, int64 total);

  
  const google_apis::AboutResource& about_resource() const {
    return *about_resource_;
  }

  
  
  int file_list_load_count() const { return file_list_load_count_; }

  
  
  int change_list_load_count() const { return change_list_load_count_; }

  
  
  int directory_load_count() const { return directory_load_count_; }

  
  
  int about_resource_load_count() const {
    return about_resource_load_count_;
  }

  
  
  int app_list_load_count() const { return app_list_load_count_; }

  
  
  int blocked_file_list_load_count() const {
    return blocked_file_list_load_count_;
  }

  
  
  const base::FilePath& last_cancelled_file() const {
    return last_cancelled_file_;
  }

  
  static GURL GetFakeLinkUrl(const std::string& resource_id);

  
  
  
  void set_open_url_format(const std::string& url_format) {
    open_url_format_ = url_format;
  }

  
  virtual void Initialize(const std::string& account_id) OVERRIDE;
  virtual void AddObserver(DriveServiceObserver* observer) OVERRIDE;
  virtual void RemoveObserver(DriveServiceObserver* observer) OVERRIDE;
  virtual bool CanSendRequest() const OVERRIDE;
  virtual std::string GetRootResourceId() const OVERRIDE;
  virtual bool HasAccessToken() const OVERRIDE;
  virtual void RequestAccessToken(
      const google_apis::AuthStatusCallback& callback) OVERRIDE;
  virtual bool HasRefreshToken() const OVERRIDE;
  virtual void ClearAccessToken() OVERRIDE;
  virtual void ClearRefreshToken() OVERRIDE;
  virtual google_apis::CancelCallback GetAllFileList(
      const google_apis::FileListCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback GetFileListInDirectory(
      const std::string& directory_resource_id,
      const google_apis::FileListCallback& callback) OVERRIDE;
  
  
  virtual google_apis::CancelCallback Search(
      const std::string& search_query,
      const google_apis::FileListCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback SearchByTitle(
      const std::string& title,
      const std::string& directory_resource_id,
      const google_apis::FileListCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback GetChangeList(
      int64 start_changestamp,
      const google_apis::ChangeListCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback GetRemainingChangeList(
      const GURL& next_link,
      const google_apis::ChangeListCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback GetRemainingFileList(
      const GURL& next_link,
      const google_apis::FileListCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback GetFileResource(
      const std::string& resource_id,
      const google_apis::FileResourceCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback GetShareUrl(
      const std::string& resource_id,
      const GURL& embed_origin,
      const google_apis::GetShareUrlCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback GetAboutResource(
      const google_apis::AboutResourceCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback GetAppList(
      const google_apis::AppListCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback DeleteResource(
      const std::string& resource_id,
      const std::string& etag,
      const google_apis::EntryActionCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback TrashResource(
      const std::string& resource_id,
      const google_apis::EntryActionCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback DownloadFile(
      const base::FilePath& local_cache_path,
      const std::string& resource_id,
      const google_apis::DownloadActionCallback& download_action_callback,
      const google_apis::GetContentCallback& get_content_callback,
      const google_apis::ProgressCallback& progress_callback) OVERRIDE;
  virtual google_apis::CancelCallback CopyResource(
      const std::string& resource_id,
      const std::string& parent_resource_id,
      const std::string& new_title,
      const base::Time& last_modified,
      const google_apis::FileResourceCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback UpdateResource(
      const std::string& resource_id,
      const std::string& parent_resource_id,
      const std::string& new_title,
      const base::Time& last_modified,
      const base::Time& last_viewed_by_me,
      const google_apis::FileResourceCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback AddResourceToDirectory(
      const std::string& parent_resource_id,
      const std::string& resource_id,
      const google_apis::EntryActionCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback RemoveResourceFromDirectory(
      const std::string& parent_resource_id,
      const std::string& resource_id,
      const google_apis::EntryActionCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback AddNewDirectory(
      const std::string& parent_resource_id,
      const std::string& directory_title,
      const AddNewDirectoryOptions& options,
      const google_apis::FileResourceCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback InitiateUploadNewFile(
      const std::string& content_type,
      int64 content_length,
      const std::string& parent_resource_id,
      const std::string& title,
      const InitiateUploadNewFileOptions& options,
      const google_apis::InitiateUploadCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback InitiateUploadExistingFile(
      const std::string& content_type,
      int64 content_length,
      const std::string& resource_id,
      const InitiateUploadExistingFileOptions& options,
      const google_apis::InitiateUploadCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback ResumeUpload(
      const GURL& upload_url,
      int64 start_position,
      int64 end_position,
      int64 content_length,
      const std::string& content_type,
      const base::FilePath& local_file_path,
      const google_apis::drive::UploadRangeCallback& callback,
      const google_apis::ProgressCallback& progress_callback) OVERRIDE;
  virtual google_apis::CancelCallback GetUploadStatus(
      const GURL& upload_url,
      int64 content_length,
      const google_apis::drive::UploadRangeCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback AuthorizeApp(
      const std::string& resource_id,
      const std::string& app_id,
      const google_apis::AuthorizeAppCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback UninstallApp(
      const std::string& app_id,
      const google_apis::EntryActionCallback& callback) OVERRIDE;
  virtual google_apis::CancelCallback AddPermission(
      const std::string& resource_id,
      const std::string& email,
      google_apis::drive::PermissionRole role,
      const google_apis::EntryActionCallback& callback) OVERRIDE;

  
  
  
  void AddNewFile(const std::string& content_type,
                  const std::string& content_data,
                  const std::string& parent_resource_id,
                  const std::string& title,
                  bool shared_with_me,
                  const google_apis::FileResourceCallback& callback);

  
  
  
  
  void AddNewFileWithResourceId(
      const std::string& resource_id,
      const std::string& content_type,
      const std::string& content_data,
      const std::string& parent_resource_id,
      const std::string& title,
      bool shared_with_me,
      const google_apis::FileResourceCallback& callback);

  
  
  google_apis::CancelCallback AddNewDirectoryWithResourceId(
      const std::string& resource_id,
      const std::string& parent_resource_id,
      const std::string& directory_title,
      const AddNewDirectoryOptions& options,
      const google_apis::FileResourceCallback& callback);

  
  
  
  void SetLastModifiedTime(
      const std::string& resource_id,
      const base::Time& last_modified_time,
      const google_apis::FileResourceCallback& callback);

  
  google_apis::GDataErrorCode SetUserPermission(
      const std::string& resource_id,
      google_apis::drive::PermissionRole user_permission);

  void AddChangeObserver(ChangeObserver* observer);
  void RemoveChangeObserver(ChangeObserver* observer);

 private:
  struct EntryInfo;
  struct UploadSession;

  
  
  EntryInfo* FindEntryByResourceId(const std::string& resource_id);

  
  
  std::string GetNewResourceId();

  
  void AddNewChangestamp(google_apis::ChangeResource* change);

  
  void UpdateETag(google_apis::FileResource* file);

  
  
  
  const EntryInfo* AddNewEntry(
      const std::string& resource_id,
      const std::string& content_type,
      const std::string& content_data,
      const std::string& parent_resource_id,
      const std::string& title,
      bool shared_with_me);

  
  
  
  
  
  void GetChangeListInternal(
      int64 start_changestamp,
      const std::string& search_query,
      const std::string& directory_resource_id,
      int start_offset,
      int max_results,
      int* load_counter,
      const google_apis::ChangeListCallback& callback);

  
  GURL GetNewUploadSessionUrl();

  void NotifyObservers();

  typedef std::map<std::string, EntryInfo*> EntryInfoMap;
  EntryInfoMap entries_;
  scoped_ptr<google_apis::AboutResource> about_resource_;
  scoped_ptr<base::DictionaryValue> app_info_value_;
  std::map<GURL, UploadSession> upload_sessions_;
  int64 published_date_seq_;
  int64 next_upload_sequence_number_;
  int default_max_results_;
  int resource_id_count_;
  int file_list_load_count_;
  int change_list_load_count_;
  int directory_load_count_;
  int about_resource_load_count_;
  int app_list_load_count_;
  int blocked_file_list_load_count_;
  bool offline_;
  bool never_return_all_file_list_;
  base::FilePath last_cancelled_file_;
  GURL share_url_base_;
  std::string app_json_template_;
  std::string open_url_format_;

  ObserverList<ChangeObserver> change_observers_;

  base::WeakPtrFactory<FakeDriveService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(FakeDriveService);
};

}  

#endif  
