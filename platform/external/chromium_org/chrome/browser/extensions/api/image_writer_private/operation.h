// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_IMAGE_WRITER_PRIVATE_OPERATION_H_
#define CHROME_BROWSER_EXTENSIONS_API_IMAGE_WRITER_PRIVATE_OPERATION_H_

#include "base/callback.h"
#include "base/files/file.h"
#include "base/files/scoped_temp_dir.h"
#include "base/md5.h"
#include "base/memory/ref_counted_memory.h"
#include "base/memory/weak_ptr.h"
#include "base/task/cancelable_task_tracker.h"
#include "base/timer/timer.h"
#include "chrome/browser/extensions/api/image_writer_private/image_writer_utility_client.h"
#include "chrome/common/extensions/api/image_writer_private.h"
#include "third_party/zlib/google/zip_reader.h"

namespace image_writer_api = extensions::api::image_writer_private;

namespace base {
class FilePath;
}  

namespace extensions {
namespace image_writer {

const int kProgressComplete = 100;

class OperationManager;

class Operation : public base::RefCountedThreadSafe<Operation> {
 public:
  typedef base::Callback<void(bool, const std::string&)> StartWriteCallback;
  typedef base::Callback<void(bool, const std::string&)> CancelWriteCallback;
  typedef std::string ExtensionId;

  Operation(base::WeakPtr<OperationManager> manager,
            const ExtensionId& extension_id,
            const std::string& device_path);

  
  void Start();

  
  
  
  void Cancel();

  
  void Abort();

  
  int GetProgress();
  image_writer_api::Stage GetStage();

#if !defined(OS_CHROMEOS)
  
  
  
  static void SetUtilityClientForTesting(
      scoped_refptr<ImageWriterUtilityClient> client);
#endif

 protected:
  virtual ~Operation();

  
  
  virtual void StartImpl() = 0;

  
  
  void Unzip(const base::Closure& continuation);

  
  void Write(const base::Closure& continuation);

  
  void VerifyWrite(const base::Closure& continuation);

  
  void Finish();

  
  
  
  virtual void Error(const std::string& error_message);

  
  
  void SetProgress(int progress);
  
  
  void SetStage(image_writer_api::Stage stage);

  
  bool IsCancelled();

  
  
  
  void AddCleanUpFunction(const base::Closure& callback);

  
  
  void CompleteAndContinue(const base::Closure& continuation);

  
  
  
  
  
  
  void GetMD5SumOfFile(
      const base::FilePath& file,
      int64 file_size,
      int progress_offset,
      int progress_scale,
      const base::Callback<void(const std::string&)>& callback);

  base::WeakPtr<OperationManager> manager_;
  const ExtensionId extension_id_;

  base::FilePath image_path_;
  base::FilePath device_path_;

  
  base::ScopedTempDir temp_dir_;

 private:
  friend class base::RefCountedThreadSafe<Operation>;

#if !defined(OS_CHROMEOS)
  
  
  
  void StartUtilityClient();

  
  
  void StopUtilityClient();

  
  virtual void WriteImageProgress(int64 total_bytes, int64 curr_bytes);

  scoped_refptr<ImageWriterUtilityClient> image_writer_client_;
#endif

#if defined(OS_CHROMEOS)
  
  void UnmountVolumes(const base::Closure& continuation);
  
  void UnmountVolumesCallback(const base::Closure& continuation, bool success);
  
  
  void StartWriteOnUIThread(const std::string& target_path,
                            const base::Closure& continuation);
  void OnBurnFinished(const base::Closure& continuation,
                      const std::string& target_path,
                      bool success,
                      const std::string& error);
  void OnBurnProgress(const std::string& target_path,
                      int64 num_bytes_burnt,
                      int64 total_size);
  void OnBurnError();
#endif

  
  void MD5Chunk(base::File file,
                int64 bytes_processed,
                int64 bytes_total,
                int progress_offset,
                int progress_scale,
                const base::Callback<void(const std::string&)>& callback);

  
  void OnUnzipFailure();
  void OnUnzipProgress(int64 total_bytes, int64 progress_bytes);

  
  void CleanUp();

  
  
  image_writer_api::Stage stage_;
  int progress_;

  
  
  base::MD5Context md5_context_;

  
  zip::ZipReader zip_reader_;

  
  
  std::vector<base::Closure> cleanup_functions_;
};

}  
}  

#endif  
