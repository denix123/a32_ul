// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_SPDY_FRAMER_H_
#define NET_SPDY_SPDY_FRAMER_H_

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "base/sys_byteorder.h"
#include "net/base/net_export.h"
#include "net/spdy/hpack_decoder.h"
#include "net/spdy/hpack_encoder.h"
#include "net/spdy/spdy_header_block.h"
#include "net/spdy/spdy_protocol.h"


typedef struct z_stream_s z_stream;  

namespace net {

class HttpProxyClientSocketPoolTest;
class HttpNetworkLayer;
class HttpNetworkTransactionTest;
class SpdyHttpStreamTest;
class SpdyNetworkTransactionTest;
class SpdyProxyClientSocketTest;
class SpdySessionTest;
class SpdyStreamTest;
class SpdyWebSocketStreamTest;
class WebSocketJobTest;

class SpdyFramer;
class SpdyFrameBuilder;
class SpdyFramerTest;

namespace test {

class TestSpdyVisitor;

}  

typedef std::map<std::string, std::string> SpdyHeaderBlock;

class NET_EXPORT_PRIVATE SettingsFlagsAndId {
 public:
  static SettingsFlagsAndId FromWireFormat(SpdyMajorVersion version,
                                           uint32 wire);

  SettingsFlagsAndId() : flags_(0), id_(0) {}

  
  SettingsFlagsAndId(uint8 flags, uint32 id);

  uint32 GetWireFormat(SpdyMajorVersion version) const;

  uint32 id() const { return id_; }
  uint8 flags() const { return flags_; }

 private:
  static void ConvertFlagsAndIdForSpdy2(uint32* val);

  uint8 flags_;
  uint32 id_;
};

typedef std::pair<SpdySettingsFlags, uint32> SettingsFlagsAndValue;
typedef std::map<SpdySettingsIds, SettingsFlagsAndValue> SettingsMap;

struct NET_EXPORT_PRIVATE SpdySettingsScratch {
  SpdySettingsScratch() { Reset(); }

  void Reset() {
    setting_buf_len = 0;
    last_setting_id = -1;
  }

  
  char setting_buf[8];

  
  size_t setting_buf_len;

  
  
  
  int last_setting_id;
};

struct NET_EXPORT_PRIVATE SpdyAltSvcScratch {
  SpdyAltSvcScratch();
  ~SpdyAltSvcScratch();

  void Reset() {
    max_age = 0;
    port = 0;
    pid_len = 0;
    host_len = 0;
    origin_len = 0;
    pid_buf_len = 0;
    host_buf_len = 0;
    origin_buf_len = 0;
    protocol_id.reset();
    host.reset();
    origin.reset();
  }

  uint32 max_age;
  uint16 port;
  uint8 pid_len;
  uint8 host_len;
  size_t origin_len;
  size_t pid_buf_len;
  size_t host_buf_len;
  size_t origin_buf_len;
  scoped_ptr<char[]> protocol_id;
  scoped_ptr<char[]> host;
  scoped_ptr<char[]> origin;
};

class NET_EXPORT_PRIVATE SpdyFramerVisitorInterface {
 public:
  virtual ~SpdyFramerVisitorInterface() {}

  
  virtual void OnError(SpdyFramer* framer) = 0;

  
  
  
  virtual void OnDataFrameHeader(SpdyStreamId stream_id,
                                 size_t length,
                                 bool fin) = 0;

  
  
  
  
  
  
  virtual void OnStreamFrameData(SpdyStreamId stream_id,
                                 const char* data,
                                 size_t len,
                                 bool fin) = 0;

  
  
  
  
  
  
  
  
  
  virtual bool OnControlFrameHeaderData(SpdyStreamId stream_id,
                                        const char* header_data,
                                        size_t len) = 0;

  
  
  
  virtual void OnSynStream(SpdyStreamId stream_id,
                           SpdyStreamId associated_stream_id,
                           SpdyPriority priority,
                           bool fin,
                           bool unidirectional) = 0;

  
  
  
  virtual void OnSynReply(SpdyStreamId stream_id, bool fin) = 0;

  
  virtual void OnRstStream(SpdyStreamId stream_id,
                           SpdyRstStreamStatus status) = 0;

  
  
  virtual void OnSettings(bool clear_persisted) {}

  
  
  virtual void OnSetting(SpdySettingsIds id, uint8 flags, uint32 value) = 0;

  
  virtual void OnSettingsAck() {}

  
  virtual void OnSettingsEnd() = 0;

  
  virtual void OnPing(SpdyPingId unique_id, bool is_ack) = 0;

  
  virtual void OnGoAway(SpdyStreamId last_accepted_stream_id,
                        SpdyGoAwayStatus status) = 0;

  
  
  
  virtual void OnHeaders(SpdyStreamId stream_id, bool fin, bool end) = 0;

  
  virtual void OnWindowUpdate(SpdyStreamId stream_id,
                              uint32 delta_window_size) = 0;

  
  
  
  
  
  
  
  virtual bool OnGoAwayFrameData(const char* goaway_data, size_t len);

  
  
  
  
  
  
  
  
  virtual bool OnRstStreamFrameData(const char* rst_stream_data, size_t len);

  
  virtual void OnBlocked(SpdyStreamId stream_id) {}

  
  
  
  virtual void OnPushPromise(SpdyStreamId stream_id,
                             SpdyStreamId promised_stream_id,
                             bool end) = 0;

  
  
  
  virtual void OnContinuation(SpdyStreamId stream_id, bool end) = 0;

  
  virtual void OnAltSvc(SpdyStreamId stream_id,
                        uint32 max_age,
                        uint16 port,
                        base::StringPiece protocol_id,
                        base::StringPiece host,
                        base::StringPiece origin) {}

  
  virtual void OnPriority(SpdyStreamId stream_id,
                          SpdyStreamId parent_stream_id,
                          uint8 weight,
                          bool exclusive) {}

  
  
  
  
  virtual bool OnUnknownFrame(SpdyStreamId stream_id, int frame_type) = 0;
};

class NET_EXPORT_PRIVATE SpdyFramerDebugVisitorInterface {
 public:
  virtual ~SpdyFramerDebugVisitorInterface() {}

  
  
  
  
  virtual void OnSendCompressedFrame(SpdyStreamId stream_id,
                                     SpdyFrameType type,
                                     size_t payload_len,
                                     size_t frame_len) {}

  
  
  
  virtual void OnReceiveCompressedFrame(SpdyStreamId stream_id,
                                        SpdyFrameType type,
                                        size_t frame_len) {}
};

class NET_EXPORT_PRIVATE SpdyFramer {
 public:
  
  
  
  enum SpdyState {
    SPDY_ERROR,
    SPDY_RESET,
    SPDY_AUTO_RESET,
    SPDY_READING_COMMON_HEADER,
    SPDY_CONTROL_FRAME_PAYLOAD,
    SPDY_READ_PADDING_LENGTH,
    SPDY_CONSUME_PADDING,
    SPDY_IGNORE_REMAINING_PAYLOAD,
    SPDY_FORWARD_STREAM_FRAME,
    SPDY_CONTROL_FRAME_BEFORE_HEADER_BLOCK,
    SPDY_CONTROL_FRAME_HEADER_BLOCK,
    SPDY_GOAWAY_FRAME_PAYLOAD,
    SPDY_RST_STREAM_FRAME_PAYLOAD,
    SPDY_SETTINGS_FRAME_PAYLOAD,
    SPDY_ALTSVC_FRAME_PAYLOAD,
  };

  
  enum SpdyError {
    SPDY_NO_ERROR,
    SPDY_INVALID_CONTROL_FRAME,        
    SPDY_CONTROL_PAYLOAD_TOO_LARGE,    
    SPDY_ZLIB_INIT_FAILURE,            
    SPDY_UNSUPPORTED_VERSION,          
    SPDY_DECOMPRESS_FAILURE,           
    SPDY_COMPRESS_FAILURE,             
    SPDY_GOAWAY_FRAME_CORRUPT,         
    SPDY_RST_STREAM_FRAME_CORRUPT,     
    SPDY_INVALID_DATA_FRAME_FLAGS,     
    SPDY_INVALID_CONTROL_FRAME_FLAGS,  
    SPDY_UNEXPECTED_FRAME,             

    LAST_ERROR,  
  };

  
  static const SpdyStreamId kInvalidStream;

  
  
  
  static const size_t kHeaderDataChunkMaxSize;

  
  static void WriteHeaderBlock(SpdyFrameBuilder* frame,
                               const SpdyMajorVersion spdy_version,
                               const SpdyHeaderBlock* headers);

  
  
  static size_t GetSerializedLength(
      const SpdyMajorVersion spdy_version,
      const SpdyHeaderBlock* headers);

  
  explicit SpdyFramer(SpdyMajorVersion version);
  virtual ~SpdyFramer();

  
  
  
  
  void set_visitor(SpdyFramerVisitorInterface* visitor) {
    visitor_ = visitor;
  }

  
  
  
  void set_debug_visitor(SpdyFramerDebugVisitorInterface* debug_visitor) {
    debug_visitor_ = debug_visitor;
  }

  
  
  
  size_t ProcessInput(const char* data, size_t len);

  
  
  void Reset();

  
  SpdyError error_code() const { return error_code_; }
  SpdyState state() const { return state_; }
  bool HasError() const { return state_ == SPDY_ERROR; }

  
  
  
  
  size_t ParseHeaderBlockInBuffer(const char* header_data,
                                size_t header_length,
                                SpdyHeaderBlock* block) const;

  
  SpdySerializedFrame* SerializeData(const SpdyDataIR& data) const;
  
  
  SpdySerializedFrame* SerializeDataFrameHeaderWithPaddingLengthField(
      const SpdyDataIR& data) const;

  
  SpdySerializedFrame* SerializeSynStream(const SpdySynStreamIR& syn_stream);

  
  SpdySerializedFrame* SerializeSynReply(const SpdySynReplyIR& syn_reply);

  SpdySerializedFrame* SerializeRstStream(
      const SpdyRstStreamIR& rst_stream) const;

  
  
  SpdySerializedFrame* SerializeSettings(const SpdySettingsIR& settings) const;

  
  
  SpdySerializedFrame* SerializePing(const SpdyPingIR& ping) const;

  
  
  
  
  SpdySerializedFrame* SerializeGoAway(const SpdyGoAwayIR& goaway) const;

  
  
  SpdySerializedFrame* SerializeHeaders(const SpdyHeadersIR& headers);

  
  
  SpdySerializedFrame* SerializeWindowUpdate(
      const SpdyWindowUpdateIR& window_update) const;

  
  
  
  
  SpdySerializedFrame* SerializeBlocked(const SpdyBlockedIR& blocked) const;

  
  
  
  
  SpdySerializedFrame* SerializePushPromise(
      const SpdyPushPromiseIR& push_promise);

  
  
  
  
  
  SpdySerializedFrame* SerializeContinuation(
      const SpdyContinuationIR& continuation);

  
  
  SpdySerializedFrame* SerializeAltSvc(const SpdyAltSvcIR& altsvc);

  
  
  SpdySerializedFrame* SerializePriority(const SpdyPriorityIR& priority);

  
  SpdySerializedFrame* SerializeFrame(const SpdyFrameIR& frame);

  
  
  
  
  
  
  
  
  
  

  
  
  
  
  
  SpdyFrame* CompressFrame(const SpdyFrame& frame);

  
  void set_enable_compression(bool value) {
    enable_compression_ = value;
  }

  
  void set_display_protocol(const std::string& protocol) {
    display_protocol_ = protocol;
  }

  
  size_t GetDataFrameMinimumSize() const;
  size_t GetControlFrameHeaderSize() const;
  size_t GetSynStreamMinimumSize() const;
  size_t GetSynReplyMinimumSize() const;
  size_t GetRstStreamMinimumSize() const;
  size_t GetSettingsMinimumSize() const;
  size_t GetPingSize() const;
  size_t GetGoAwayMinimumSize() const;
  size_t GetHeadersMinimumSize() const;
  size_t GetWindowUpdateSize() const;
  size_t GetBlockedSize() const;
  size_t GetPushPromiseMinimumSize() const;
  size_t GetContinuationMinimumSize() const;
  size_t GetAltSvcMinimumSize() const;
  size_t GetPrioritySize() const;

  
  size_t GetFrameMinimumSize() const;

  
  size_t GetFrameMaximumSize() const;

  
  size_t GetControlFrameMaximumSize() const;

  
  size_t GetDataFrameMaximumPayload() const;

  
  size_t GetPrefixLength(SpdyFrameType type) const;

  
  static const char* StateToString(int state);
  static const char* ErrorCodeToString(int error_code);
  static const char* StatusCodeToString(int status_code);
  static const char* FrameTypeToString(SpdyFrameType type);

  SpdyMajorVersion protocol_version() const { return spdy_version_; }

  bool probable_http_response() const { return probable_http_response_; }

  SpdyStreamId expect_continuation() const { return expect_continuation_; }

  SpdyPriority GetLowestPriority() const {
    return spdy_version_ < SPDY3 ? 3 : 7;
  }

  SpdyPriority GetHighestPriority() const { return 0; }

  
  
  uint8 MapPriorityToWeight(SpdyPriority priority);
  SpdyPriority MapWeightToPriority(uint8 weight);

  
  
  
  bool IncrementallyDecompressControlFrameHeaderData(
      SpdyStreamId stream_id,
      const char* data,
      size_t len);

 protected:
  
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest, BasicCompression);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest, ControlFrameSizesAreValidated);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest, HeaderCompression);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest, DecompressUncompressedFrame);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest, ExpandBuffer_HeapSmash);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest, HugeHeaderBlock);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest, UnclosedStreamDataCompressors);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest,
                           UnclosedStreamDataCompressorsOneByteAtATime);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest,
                           UncompressLargerThanFrameBufferInitialSize);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest, ReadLargeSettingsFrame);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest,
                           ReadLargeSettingsFrameInSmallChunks);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest, ControlFrameAtMaxSizeLimit);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest, ControlFrameTooLarge);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest,
                           TooLargeHeadersFrameUsesContinuation);
  FRIEND_TEST_ALL_PREFIXES(SpdyFramerTest,
                           TooLargePushPromiseFrameUsesContinuation);
  friend class net::HttpNetworkLayer;  
  friend class net::HttpNetworkTransactionTest;
  friend class net::HttpProxyClientSocketPoolTest;
  friend class net::SpdyHttpStreamTest;
  friend class net::SpdyNetworkTransactionTest;
  friend class net::SpdyProxyClientSocketTest;
  friend class net::SpdySessionTest;
  friend class net::SpdyStreamTest;
  friend class net::SpdyWebSocketStreamTest;
  friend class net::WebSocketJobTest;
  friend class test::TestSpdyVisitor;

 private:
  
  
  size_t ProcessCommonHeader(const char* data, size_t len);
  size_t ProcessControlFramePayload(const char* data, size_t len);
  size_t ProcessControlFrameBeforeHeaderBlock(const char* data, size_t len);
  
  
  
  size_t ProcessControlFrameHeaderBlock(const char* data,
                                        size_t len,
                                        bool is_hpack_header_block);
  size_t ProcessFramePaddingLength(const char* data, size_t len);
  size_t ProcessFramePadding(const char* data, size_t len);
  size_t ProcessDataFramePayload(const char* data, size_t len);
  size_t ProcessGoAwayFramePayload(const char* data, size_t len);
  size_t ProcessRstStreamFramePayload(const char* data, size_t len);
  size_t ProcessSettingsFramePayload(const char* data, size_t len);
  size_t ProcessAltSvcFramePayload(const char* data, size_t len);
  size_t ProcessIgnoredControlFramePayload( size_t len);

  
  
  
  
  
  void DeliverHpackBlockAsSpdy3Block();

  
  void ProcessControlFrameHeader(uint16 control_frame_type_field);
  
  bool ProcessSetting(const char* data);

  
  
  size_t GetSerializedLength(const SpdyHeaderBlock& headers);

  
  z_stream* GetHeaderCompressor();
  z_stream* GetHeaderDecompressor();

  
  HpackEncoder* GetHpackEncoder();
  HpackDecoder* GetHpackDecoder();

  size_t GetNumberRequiredContinuationFrames(size_t size);

  void WritePayloadWithContinuation(SpdyFrameBuilder* builder,
                                    const std::string& hpack_encoding,
                                    SpdyStreamId stream_id,
                                    SpdyFrameType type);

 private:
  
  
  
  bool IncrementallyDeliverControlFrameHeaderData(SpdyStreamId stream_id,
                                                  const char* data,
                                                  size_t len);

  
  
  
  
  
  
  size_t UpdateCurrentFrameBuffer(const char** data, size_t* len,
                                  size_t max_bytes);

  void WriteHeaderBlockToZ(const SpdyHeaderBlock* headers,
                           z_stream* out) const;

  void SerializeNameValueBlockWithoutCompression(
      SpdyFrameBuilder* builder,
      const SpdyNameValueBlock& name_value_block) const;

  
  void SerializeNameValueBlock(
      SpdyFrameBuilder* builder,
      const SpdyFrameWithNameValueBlockIR& frame);

  
  void set_error(SpdyError error);

  
  
  
  
  size_t GetControlFrameBufferMaxSize() const {
    
    
    
    if (spdy_version_ == SPDY2) {
      return 64 * 1024;
    }
    if (spdy_version_ == SPDY3) {
      return 16 * 1024 * 1024;
    }
    
    return (1<<14) - 1;
  }

  
  
  size_t GetHeaderFragmentMaxSize() const {
    return GetControlFrameBufferMaxSize() >> 4;  
  }

  
  
  
  
  static const size_t kControlFrameBufferSize;

  SpdyState state_;
  SpdyState previous_state_;
  SpdyError error_code_;

  
  
  
  size_t remaining_data_length_;

  
  size_t remaining_padding_payload_length_;

  
  
  
  size_t remaining_control_header_;

  scoped_ptr<char[]> current_frame_buffer_;
  
  size_t current_frame_buffer_length_;

  
  SpdyFrameType current_frame_type_;

  
  uint8 current_frame_flags_;

  
  uint32 current_frame_length_;

  
  SpdyStreamId current_frame_stream_id_;

  
  
  
  SpdySettingsScratch settings_scratch_;

  SpdyAltSvcScratch altsvc_scratch_;

  bool enable_compression_;  
  
  scoped_ptr<z_stream> header_compressor_;
  scoped_ptr<z_stream> header_decompressor_;

  scoped_ptr<HpackEncoder> hpack_encoder_;
  scoped_ptr<HpackDecoder> hpack_decoder_;

  SpdyFramerVisitorInterface* visitor_;
  SpdyFramerDebugVisitorInterface* debug_visitor_;

  std::string display_protocol_;

  
  const SpdyMajorVersion spdy_version_;

  
  
  
  
  
  
  bool syn_frame_processed_;

  
  
  
  
  
  bool probable_http_response_;

  
  
  
  
  SpdyStreamId expect_continuation_;

  
  
  
  
  bool end_stream_when_done_;
};

}  

#endif  
