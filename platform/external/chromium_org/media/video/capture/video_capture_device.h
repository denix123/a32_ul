// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_VIDEO_CAPTURE_VIDEO_CAPTURE_DEVICE_H_
#define MEDIA_VIDEO_CAPTURE_VIDEO_CAPTURE_DEVICE_H_

#include <list>
#include <string>

#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/single_thread_task_runner.h"
#include "base/time/time.h"
#include "media/base/media_export.h"
#include "media/base/video_frame.h"
#include "media/video/capture/video_capture_types.h"

namespace media {

class MEDIA_EXPORT VideoCaptureDevice {
 public:
  
  
  
  
  
  
  
  
  class MEDIA_EXPORT Name {
   public:
    Name();
    Name(const std::string& name, const std::string& id);

#if defined(OS_WIN)
    
    enum CaptureApiType {
      MEDIA_FOUNDATION,
      DIRECT_SHOW,
      DIRECT_SHOW_WDM_CROSSBAR,
      API_TYPE_UNKNOWN
    };
#endif
#if defined(OS_MACOSX)
    
    enum CaptureApiType {
      AVFOUNDATION,
      QTKIT,
      DECKLINK,
      API_TYPE_UNKNOWN
    };
    
    enum TransportType {
      USB_OR_BUILT_IN,
      OTHER_TRANSPORT
    };
#endif
#if defined(OS_WIN) || defined(OS_MACOSX)
    Name(const std::string& name,
         const std::string& id,
         const CaptureApiType api_type);
#endif
#if defined(OS_MACOSX)
    Name(const std::string& name,
         const std::string& id,
         const CaptureApiType api_type,
         const TransportType transport_type);
#endif
    ~Name();

    
    const std::string& name() const { return device_name_; }

    
    
    const std::string& id() const { return unique_id_; }

    
    
    
    const std::string GetModel() const;

    
    const std::string GetNameAndModel() const;

    
    
    
    bool operator==(const Name& other) const {
      return other.id() == unique_id_;
    }
    bool operator<(const Name& other) const {
      return unique_id_ < other.id();
    }

#if defined(OS_WIN) || defined(OS_MACOSX)
    CaptureApiType capture_api_type() const {
      return capture_api_class_.capture_api_type();
    }
#endif
#if defined(OS_WIN)
    
    
    const std::string& capabilities_id() const {
      return capabilities_id_;
    }
    void set_capabilities_id(const std::string& id) {
      capabilities_id_ = id;
    }
#endif
#if defined(OS_MACOSX)
    TransportType transport_type() const {
      return transport_type_;
    }
    bool is_blacklisted() const {
      return is_blacklisted_;
    }
    void set_is_blacklisted(bool is_blacklisted) {
      is_blacklisted_ = is_blacklisted;
    }
#endif  

   private:
    std::string device_name_;
    std::string unique_id_;
#if defined(OS_WIN) || defined(OS_MACOSX)
    
    
    class CaptureApiClass {
     public:
      CaptureApiClass(): capture_api_type_(API_TYPE_UNKNOWN) {}
      CaptureApiClass(const CaptureApiType api_type)
          : capture_api_type_(api_type) {}
      CaptureApiType capture_api_type() const {
        DCHECK_NE(capture_api_type_, API_TYPE_UNKNOWN);
        return capture_api_type_;
      }
     private:
      CaptureApiType capture_api_type_;
    };

    CaptureApiClass capture_api_class_;
#endif
#if defined(OS_WIN)
    
    std::string capabilities_id_;
#endif
#if defined(OS_MACOSX)
    TransportType transport_type_;
    
    bool is_blacklisted_;
#endif
    
  };

  
  typedef std::list<Name> Names;

  class MEDIA_EXPORT Client {
   public:
    
    class Buffer : public base::RefCountedThreadSafe<Buffer> {
     public:
      int id() const { return id_; }
      void* data() const { return data_; }
      size_t size() const { return size_; }

     protected:
      friend class base::RefCountedThreadSafe<Buffer>;

      Buffer(int id, void* data, size_t size)
          : id_(id), data_(data), size_(size) {}
      virtual ~Buffer() {}

      const int id_;
      void* const data_;
      const size_t size_;
    };

    virtual ~Client() {}

    
    
    
    
    
    
    
    
    
    
    virtual scoped_refptr<Buffer> ReserveOutputBuffer(
        media::VideoFrame::Format format,
        const gfx::Size& dimensions) = 0;

    
    
    
    
    
    
    virtual void OnIncomingCapturedData(const uint8* data,
                                        int length,
                                        const VideoCaptureFormat& frame_format,
                                        int rotation,  
                                        base::TimeTicks timestamp) = 0;

    
    
    
    
    
    virtual void OnIncomingCapturedVideoFrame(
        const scoped_refptr<Buffer>& buffer,
        const VideoCaptureFormat& buffer_format,
        const scoped_refptr<media::VideoFrame>& frame,
        base::TimeTicks timestamp) = 0;

    
    
    virtual void OnError(const std::string& reason) = 0;

    
    virtual void OnLog(const std::string& message) {}
  };

  virtual ~VideoCaptureDevice();

  
  
  
  virtual void AllocateAndStart(const VideoCaptureParams& params,
                                scoped_ptr<Client> client) = 0;

  
  
  
  
  
  
  
  
  
  
  
  virtual void StopAndDeAllocate() = 0;

  
  
  int GetPowerLineFrequencyForLocation() const;

 protected:
  static const int kPowerLine50Hz = 50;
  static const int kPowerLine60Hz = 60;
};

}  

#endif  
