// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_USB_USB_DEVICE_HANDLE_IMPL_H_
#define DEVICE_USB_USB_DEVICE_HANDLE_IMPL_H_

#include <map>
#include <vector>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/strings/string16.h"
#include "base/threading/thread_checker.h"
#include "device/usb/usb_device_handle.h"
#include "net/base/io_buffer.h"
#include "third_party/libusb/src/libusb/libusb.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace device {

class UsbContext;
struct UsbConfigDescriptor;
class UsbDeviceImpl;

typedef libusb_device_handle* PlatformUsbDeviceHandle;
typedef libusb_iso_packet_descriptor* PlatformUsbIsoPacketDescriptor;
typedef libusb_transfer* PlatformUsbTransferHandle;

class UsbDeviceHandleImpl : public UsbDeviceHandle {
 public:
  virtual scoped_refptr<UsbDevice> GetDevice() const OVERRIDE;
  virtual void Close() OVERRIDE;
  virtual bool ClaimInterface(int interface_number) OVERRIDE;
  virtual bool ReleaseInterface(int interface_number) OVERRIDE;
  virtual bool SetInterfaceAlternateSetting(int interface_number,
                                            int alternate_setting) OVERRIDE;
  virtual bool ResetDevice() OVERRIDE;
  virtual bool GetStringDescriptor(uint8 string_id,
                                   base::string16* string) OVERRIDE;

  virtual void ControlTransfer(UsbEndpointDirection direction,
                               TransferRequestType request_type,
                               TransferRecipient recipient,
                               uint8 request,
                               uint16 value,
                               uint16 index,
                               net::IOBuffer* buffer,
                               size_t length,
                               unsigned int timeout,
                               const UsbTransferCallback& callback) OVERRIDE;

  virtual void BulkTransfer(UsbEndpointDirection direction,
                            uint8 endpoint,
                            net::IOBuffer* buffer,
                            size_t length,
                            unsigned int timeout,
                            const UsbTransferCallback& callback) OVERRIDE;

  virtual void InterruptTransfer(UsbEndpointDirection direction,
                                 uint8 endpoint,
                                 net::IOBuffer* buffer,
                                 size_t length,
                                 unsigned int timeout,
                                 const UsbTransferCallback& callback) OVERRIDE;

  virtual void IsochronousTransfer(
      UsbEndpointDirection direction,
      uint8 endpoint,
      net::IOBuffer* buffer,
      size_t length,
      unsigned int packets,
      unsigned int packet_length,
      unsigned int timeout,
      const UsbTransferCallback& callback) OVERRIDE;

  PlatformUsbDeviceHandle handle() const { return handle_; }

 protected:
  friend class UsbDeviceImpl;

  
  UsbDeviceHandleImpl(scoped_refptr<UsbContext> context,
                      UsbDeviceImpl* device,
                      PlatformUsbDeviceHandle handle,
                      const UsbConfigDescriptor& config);

  virtual ~UsbDeviceHandleImpl();

 private:
  class InterfaceClaimer;
  struct Transfer;

  
  
  void RefreshEndpointMap();

  
  
  scoped_refptr<InterfaceClaimer> GetClaimedInterfaceForEndpoint(
      unsigned char endpoint);

  
  
  
  
  void PostOrSubmitTransfer(PlatformUsbTransferHandle handle,
                            UsbTransferType transfer_type,
                            net::IOBuffer* buffer,
                            size_t length,
                            const UsbTransferCallback& callback);

  
  
  
  void SubmitTransfer(PlatformUsbTransferHandle handle,
                      UsbTransferType transfer_type,
                      net::IOBuffer* buffer,
                      const size_t length,
                      scoped_refptr<base::SingleThreadTaskRunner> task_runner,
                      const UsbTransferCallback& callback);

  static void LIBUSB_CALL
      PlatformTransferCallback(PlatformUsbTransferHandle handle);

  
  
  void CompleteTransfer(PlatformUsbTransferHandle transfer);

  bool GetSupportedLanguages();

  
  void InternalClose();

  UsbDeviceImpl* device_;

  PlatformUsbDeviceHandle handle_;

  const UsbConfigDescriptor& config_;

  std::vector<uint16> languages_;
  std::map<uint8, base::string16> strings_;

  typedef std::map<int, scoped_refptr<InterfaceClaimer> > ClaimedInterfaceMap;
  ClaimedInterfaceMap claimed_interfaces_;

  typedef std::map<PlatformUsbTransferHandle, Transfer> TransferMap;
  TransferMap transfers_;

  
  typedef std::map<int, int> EndpointMap;
  EndpointMap endpoint_map_;

  
  
  scoped_refptr<UsbContext> context_;

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(UsbDeviceHandleImpl);
};

}  

#endif  
