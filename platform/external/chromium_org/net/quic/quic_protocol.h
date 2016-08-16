// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_PROTOCOL_H_
#define NET_QUIC_QUIC_PROTOCOL_H_

#include <stddef.h>
#include <limits>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/logging.h"
#include "base/strings/string_piece.h"
#include "net/base/int128.h"
#include "net/base/ip_endpoint.h"
#include "net/base/net_export.h"
#include "net/quic/iovector.h"
#include "net/quic/quic_bandwidth.h"
#include "net/quic/quic_time.h"

namespace net {

class QuicAckNotifier;
class QuicPacket;
struct QuicPacketHeader;

typedef uint64 QuicConnectionId;
typedef uint32 QuicStreamId;
typedef uint64 QuicStreamOffset;
typedef uint64 QuicPacketSequenceNumber;
typedef QuicPacketSequenceNumber QuicFecGroupNumber;
typedef uint64 QuicPublicResetNonceProof;
typedef uint8 QuicPacketEntropyHash;
typedef uint32 QuicHeaderId;
typedef uint32 QuicTag;
typedef std::vector<QuicTag> QuicTagVector;
typedef std::map<QuicTag, std::string> QuicTagValueMap;
typedef uint32 QuicPriority;

const QuicByteCount kDefaultMaxPacketSize = 1350;
const QuicByteCount kMaxPacketSize = 1452;
const QuicByteCount kDefaultTCPMSS = 1460;

const size_t kDefaultInitialWindow = 10;
const uint32 kMaxInitialWindow = 100;

const uint32 kDefaultFlowControlSendWindow = 16 * 1024;  

const size_t kMaxTcpCongestionWindow = 200;

const QuicByteCount kDefaultSocketReceiveBuffer = 256 * 1024;

const uint32 kMaxInitialRoundTripTimeUs = 15 * kNumMicrosPerSecond;

const size_t kDefaultMaxStreamsPerConnection = 100;

const size_t kPublicFlagsSize = 1;
const size_t kQuicVersionSize = 4;
const size_t kPrivateFlagsSize = 1;
const size_t kFecGroupSize = 1;

const bool kIncludeVersion = true;

const size_t kStartOfHashData = 0;

const QuicStreamId kMaxStreamIdDelta = 200;
const QuicHeaderId kMaxHeaderIdDelta = 200;

const QuicStreamId kCryptoStreamId = 1;

const QuicStreamId kHeadersStreamId = 3;

const int kMaxDelayedAckTimeMs = 25;

const int64 kDefaultInitialTimeoutSecs = 120;  
const int64 kMaximumIdleTimeoutSecs = 60 * 10;  
const int64 kDefaultMaxTimeForCryptoHandshakeSecs = 10;  

const int64 kPingTimeoutSecs = 15;  

const int kMinIntervalBetweenServerConfigUpdatesRTTs = 10;

const int kMinIntervalBetweenServerConfigUpdatesMs = 1000;

const float kMaxStreamsMultiplier = 1.1f;

const int kUFloat16ExponentBits = 5;
const int kUFloat16MaxExponent = (1 << kUFloat16ExponentBits) - 2;  
const int kUFloat16MantissaBits = 16 - kUFloat16ExponentBits;  
const int kUFloat16MantissaEffectiveBits = kUFloat16MantissaBits + 1;  
const uint64 kUFloat16MaxValue =  
    ((GG_UINT64_C(1) << kUFloat16MantissaEffectiveBits) - 1) <<
    kUFloat16MaxExponent;

enum TransmissionType {
  NOT_RETRANSMISSION,
  FIRST_TRANSMISSION_TYPE = NOT_RETRANSMISSION,
  HANDSHAKE_RETRANSMISSION,  
  ALL_UNACKED_RETRANSMISSION,  
  ALL_INITIAL_RETRANSMISSION,  
  LOSS_RETRANSMISSION,  
  RTO_RETRANSMISSION,  
  TLP_RETRANSMISSION,  
  LAST_TRANSMISSION_TYPE = TLP_RETRANSMISSION,
};

enum HasRetransmittableData {
  NO_RETRANSMITTABLE_DATA,
  HAS_RETRANSMITTABLE_DATA,
};

enum IsHandshake {
  NOT_HANDSHAKE,
  IS_HANDSHAKE
};

// Indicates FEC protection level for data being written.
enum FecProtection {
  MUST_FEC_PROTECT,  
  MAY_FEC_PROTECT    
};

enum FecPolicy {
  FEC_PROTECT_ALWAYS,   
  FEC_PROTECT_OPTIONAL  
};

enum QuicFrameType {
  
  
  PADDING_FRAME = 0,
  RST_STREAM_FRAME = 1,
  CONNECTION_CLOSE_FRAME = 2,
  GOAWAY_FRAME = 3,
  WINDOW_UPDATE_FRAME = 4,
  BLOCKED_FRAME = 5,
  STOP_WAITING_FRAME = 6,
  PING_FRAME = 7,

  
  
  STREAM_FRAME,
  ACK_FRAME,
  CONGESTION_FEEDBACK_FRAME,
  NUM_FRAME_TYPES
};

enum QuicConnectionIdLength {
  PACKET_0BYTE_CONNECTION_ID = 0,
  PACKET_1BYTE_CONNECTION_ID = 1,
  PACKET_4BYTE_CONNECTION_ID = 4,
  PACKET_8BYTE_CONNECTION_ID = 8
};

enum InFecGroup {
  NOT_IN_FEC_GROUP,
  IN_FEC_GROUP,
};

enum QuicSequenceNumberLength {
  PACKET_1BYTE_SEQUENCE_NUMBER = 1,
  PACKET_2BYTE_SEQUENCE_NUMBER = 2,
  PACKET_4BYTE_SEQUENCE_NUMBER = 4,
  PACKET_6BYTE_SEQUENCE_NUMBER = 6
};

enum QuicSequenceNumberLengthFlags {
  PACKET_FLAGS_1BYTE_SEQUENCE = 0,  
  PACKET_FLAGS_2BYTE_SEQUENCE = 1,  
  PACKET_FLAGS_4BYTE_SEQUENCE = 1 << 1,  
  PACKET_FLAGS_6BYTE_SEQUENCE = 1 << 1 | 1,  
};

enum QuicPacketPublicFlags {
  PACKET_PUBLIC_FLAGS_NONE = 0,

  
  PACKET_PUBLIC_FLAGS_VERSION = 1 << 0,

  
  PACKET_PUBLIC_FLAGS_RST = 1 << 1,

  
  
  
  
  
  PACKET_PUBLIC_FLAGS_0BYTE_CONNECTION_ID = 0,
  PACKET_PUBLIC_FLAGS_1BYTE_CONNECTION_ID = 1 << 2,
  PACKET_PUBLIC_FLAGS_4BYTE_CONNECTION_ID = 1 << 3,
  PACKET_PUBLIC_FLAGS_8BYTE_CONNECTION_ID = 1 << 3 | 1 << 2,

  
  
  
  
  
  PACKET_PUBLIC_FLAGS_1BYTE_SEQUENCE = PACKET_FLAGS_1BYTE_SEQUENCE << 4,
  PACKET_PUBLIC_FLAGS_2BYTE_SEQUENCE = PACKET_FLAGS_2BYTE_SEQUENCE << 4,
  PACKET_PUBLIC_FLAGS_4BYTE_SEQUENCE = PACKET_FLAGS_4BYTE_SEQUENCE << 4,
  PACKET_PUBLIC_FLAGS_6BYTE_SEQUENCE = PACKET_FLAGS_6BYTE_SEQUENCE << 4,

  
  PACKET_PUBLIC_FLAGS_MAX = (1 << 6) - 1
};

enum QuicPacketPrivateFlags {
  PACKET_PRIVATE_FLAGS_NONE = 0,

  
  PACKET_PRIVATE_FLAGS_ENTROPY = 1 << 0,

  
  PACKET_PRIVATE_FLAGS_FEC_GROUP = 1 << 1,

  
  PACKET_PRIVATE_FLAGS_FEC = 1 << 2,

  
  PACKET_PRIVATE_FLAGS_MAX = (1 << 3) - 1
};

enum QuicVersion {
  
  QUIC_VERSION_UNSUPPORTED = 0,

  QUIC_VERSION_16 = 16,  
  QUIC_VERSION_18 = 18,  
  QUIC_VERSION_19 = 19,  
  QUIC_VERSION_21 = 21,  
  QUIC_VERSION_22 = 22,  
  QUIC_VERSION_23 = 23,  
};

static const QuicVersion kSupportedQuicVersions[] = {QUIC_VERSION_23,
                                                     QUIC_VERSION_22,
                                                     QUIC_VERSION_21,
                                                     QUIC_VERSION_19,
                                                     QUIC_VERSION_18,
                                                     QUIC_VERSION_16};

typedef std::vector<QuicVersion> QuicVersionVector;

NET_EXPORT_PRIVATE QuicVersionVector QuicSupportedVersions();

// QuicTag is written to and read from the wire, but we prefer to use
NET_EXPORT_PRIVATE QuicTag QuicVersionToQuicTag(const QuicVersion version);

NET_EXPORT_PRIVATE QuicVersion QuicTagToQuicVersion(const QuicTag version_tag);

NET_EXPORT_PRIVATE std::string QuicVersionToString(const QuicVersion version);

NET_EXPORT_PRIVATE std::string QuicVersionVectorToString(
    const QuicVersionVector& versions);

// Version and Crypto tags are written to the wire with a big-endian
// the client hello tag (CHLO) will be written as the

NET_EXPORT_PRIVATE QuicTag MakeQuicTag(char a, char b, char c, char d);

NET_EXPORT_PRIVATE bool ContainsQuicTag(const QuicTagVector& tag_vector,
                                        QuicTag tag);

NET_EXPORT_PRIVATE size_t GetPacketHeaderSize(const QuicPacketHeader& header);

NET_EXPORT_PRIVATE size_t GetPacketHeaderSize(
    QuicConnectionIdLength connection_id_length,
    bool include_version,
    QuicSequenceNumberLength sequence_number_length,
    InFecGroup is_in_fec_group);

NET_EXPORT_PRIVATE size_t GetStartOfFecProtectedData(
    QuicConnectionIdLength connection_id_length,
    bool include_version,
    QuicSequenceNumberLength sequence_number_length);
NET_EXPORT_PRIVATE size_t GetStartOfEncryptedData(
    QuicConnectionIdLength connection_id_length,
    bool include_version,
    QuicSequenceNumberLength sequence_number_length);

enum QuicRstStreamErrorCode {
  QUIC_STREAM_NO_ERROR = 0,

  
  QUIC_ERROR_PROCESSING_STREAM,
  
  QUIC_MULTIPLE_TERMINATION_OFFSETS,
  
  QUIC_BAD_APPLICATION_PAYLOAD,
  
  
  QUIC_STREAM_CONNECTION_ERROR,
  
  QUIC_STREAM_PEER_GOING_AWAY,
  
  QUIC_STREAM_CANCELLED,
  
  QUIC_RST_FLOW_CONTROL_ACCOUNTING,

  
  QUIC_STREAM_LAST_ERROR,
};

NET_EXPORT_PRIVATE QuicRstStreamErrorCode AdjustErrorForVersion(
    QuicRstStreamErrorCode error_code,
    QuicVersion version);

enum QuicErrorCode {
  QUIC_NO_ERROR = 0,

  
  QUIC_INTERNAL_ERROR = 1,
  
  QUIC_STREAM_DATA_AFTER_TERMINATION = 2,
  
  QUIC_INVALID_PACKET_HEADER = 3,
  
  QUIC_INVALID_FRAME_DATA = 4,
  
  QUIC_MISSING_PAYLOAD = 48,
  
  QUIC_INVALID_FEC_DATA = 5,
  
  QUIC_INVALID_STREAM_DATA = 46,
  
  QUIC_UNENCRYPTED_STREAM_DATA = 61,
  
  QUIC_INVALID_RST_STREAM_DATA = 6,
  
  QUIC_INVALID_CONNECTION_CLOSE_DATA = 7,
  
  QUIC_INVALID_GOAWAY_DATA = 8,
  
  QUIC_INVALID_WINDOW_UPDATE_DATA = 57,
  
  QUIC_INVALID_BLOCKED_DATA = 58,
  
  QUIC_INVALID_STOP_WAITING_DATA = 60,
  
  QUIC_INVALID_ACK_DATA = 9,
  
  QUIC_INVALID_CONGESTION_FEEDBACK_DATA = 47,
  
  QUIC_INVALID_VERSION_NEGOTIATION_PACKET = 10,
  
  QUIC_INVALID_PUBLIC_RST_PACKET = 11,
  
  QUIC_DECRYPTION_FAILURE = 12,
  
  QUIC_ENCRYPTION_FAILURE = 13,
  
  QUIC_PACKET_TOO_LARGE = 14,
  
  QUIC_PACKET_FOR_NONEXISTENT_STREAM = 15,
  
  QUIC_PEER_GOING_AWAY = 16,
  
  QUIC_INVALID_STREAM_ID = 17,
  
  QUIC_INVALID_PRIORITY = 49,
  
  QUIC_TOO_MANY_OPEN_STREAMS = 18,
  
  QUIC_TOO_MANY_UNFINISHED_STREAMS = 66,
  
  QUIC_PUBLIC_RESET = 19,
  
  QUIC_INVALID_VERSION = 20,

  

  
  QUIC_INVALID_HEADER_ID = 22,
  
  QUIC_INVALID_NEGOTIATED_VALUE = 23,
  
  QUIC_DECOMPRESSION_FAILURE = 24,
  
  QUIC_CONNECTION_TIMED_OUT = 25,
  
  QUIC_CONNECTION_OVERALL_TIMED_OUT = 67,
  
  QUIC_ERROR_MIGRATING_ADDRESS = 26,
  
  QUIC_PACKET_WRITE_ERROR = 27,
  
  QUIC_PACKET_READ_ERROR = 51,
  
  QUIC_INVALID_STREAM_FRAME = 50,
  
  QUIC_INVALID_HEADERS_STREAM_DATA = 56,
  
  QUIC_FLOW_CONTROL_RECEIVED_TOO_MUCH_DATA = 59,
  
  QUIC_FLOW_CONTROL_SENT_TOO_MUCH_DATA = 63,
  
  QUIC_FLOW_CONTROL_INVALID_WINDOW = 64,
  
  QUIC_CONNECTION_IP_POOLED = 62,

  

  
  QUIC_HANDSHAKE_FAILED = 28,
  
  QUIC_CRYPTO_TAGS_OUT_OF_ORDER = 29,
  
  QUIC_CRYPTO_TOO_MANY_ENTRIES = 30,
  
  QUIC_CRYPTO_INVALID_VALUE_LENGTH = 31,
  
  QUIC_CRYPTO_MESSAGE_AFTER_HANDSHAKE_COMPLETE = 32,
  
  QUIC_INVALID_CRYPTO_MESSAGE_TYPE = 33,
  
  QUIC_INVALID_CRYPTO_MESSAGE_PARAMETER = 34,
  
  QUIC_INVALID_CHANNEL_ID_SIGNATURE = 52,
  
  QUIC_CRYPTO_MESSAGE_PARAMETER_NOT_FOUND = 35,
  
  
  QUIC_CRYPTO_MESSAGE_PARAMETER_NO_OVERLAP = 36,
  
  
  QUIC_CRYPTO_MESSAGE_INDEX_NOT_FOUND = 37,
  
  QUIC_CRYPTO_INTERNAL_ERROR = 38,
  
  QUIC_CRYPTO_VERSION_NOT_SUPPORTED = 39,
  
  
  QUIC_CRYPTO_NO_SUPPORT = 40,
  
  QUIC_CRYPTO_TOO_MANY_REJECTS = 41,
  
  QUIC_PROOF_INVALID = 42,
  
  QUIC_CRYPTO_DUPLICATE_TAG = 43,
  
  
  QUIC_CRYPTO_ENCRYPTION_LEVEL_INCORRECT = 44,
  
  QUIC_CRYPTO_SERVER_CONFIG_EXPIRED = 45,
  
  QUIC_CRYPTO_SYMMETRIC_KEY_SETUP_FAILED = 53,
  
  
  QUIC_CRYPTO_MESSAGE_WHILE_VALIDATING_CLIENT_HELLO = 54,
  
  QUIC_CRYPTO_UPDATE_BEFORE_HANDSHAKE_COMPLETE = 65,
  
  
  QUIC_VERSION_NEGOTIATION_MISMATCH = 55,

  
  QUIC_LAST_ERROR = 68,
};

struct NET_EXPORT_PRIVATE QuicPacketPublicHeader {
  QuicPacketPublicHeader();
  explicit QuicPacketPublicHeader(const QuicPacketPublicHeader& other);
  ~QuicPacketPublicHeader();

  
  
  QuicConnectionId connection_id;
  QuicConnectionIdLength connection_id_length;
  bool reset_flag;
  bool version_flag;
  QuicSequenceNumberLength sequence_number_length;
  QuicVersionVector versions;
};

struct NET_EXPORT_PRIVATE QuicPacketHeader {
  QuicPacketHeader();
  explicit QuicPacketHeader(const QuicPacketPublicHeader& header);

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicPacketHeader& s);

  QuicPacketPublicHeader public_header;
  bool fec_flag;
  bool entropy_flag;
  QuicPacketEntropyHash entropy_hash;
  QuicPacketSequenceNumber packet_sequence_number;
  InFecGroup is_in_fec_group;
  QuicFecGroupNumber fec_group;
};

struct NET_EXPORT_PRIVATE QuicPublicResetPacket {
  QuicPublicResetPacket();
  explicit QuicPublicResetPacket(const QuicPacketPublicHeader& header);

  QuicPacketPublicHeader public_header;
  QuicPublicResetNonceProof nonce_proof;
  QuicPacketSequenceNumber rejected_sequence_number;
  IPEndPoint client_address;
};

enum QuicVersionNegotiationState {
  START_NEGOTIATION = 0,
  
  
  
  
  
  NEGOTIATION_IN_PROGRESS,
  
  
  
  NEGOTIATED_VERSION
};

typedef QuicPacketPublicHeader QuicVersionNegotiationPacket;

struct NET_EXPORT_PRIVATE QuicPaddingFrame {
};

struct NET_EXPORT_PRIVATE QuicPingFrame {
};

struct NET_EXPORT_PRIVATE QuicStreamFrame {
  QuicStreamFrame();
  QuicStreamFrame(const QuicStreamFrame& frame);
  QuicStreamFrame(QuicStreamId stream_id,
                  bool fin,
                  QuicStreamOffset offset,
                  IOVector data);

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicStreamFrame& s);

  
  
  std::string* GetDataAsString() const;

  QuicStreamId stream_id;
  bool fin;
  QuicStreamOffset offset;  
  IOVector data;

  
  
  QuicAckNotifier* notifier;
};

typedef std::set<QuicPacketSequenceNumber> SequenceNumberSet;
typedef std::list<QuicPacketSequenceNumber> SequenceNumberList;

typedef std::list<
    std::pair<QuicPacketSequenceNumber, QuicTime> > PacketTimeList;

struct NET_EXPORT_PRIVATE QuicStopWaitingFrame {
  QuicStopWaitingFrame();
  ~QuicStopWaitingFrame();

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicStopWaitingFrame& s);
  
  
  QuicPacketEntropyHash entropy_hash;
  
  QuicPacketSequenceNumber least_unacked;
};

struct NET_EXPORT_PRIVATE QuicAckFrame {
  QuicAckFrame();
  ~QuicAckFrame();

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicAckFrame& s);

  
  
  QuicPacketEntropyHash entropy_hash;

  
  
  
  
  
  
  
  
  QuicPacketSequenceNumber largest_observed;

  
  
  QuicTime::Delta delta_time_largest_observed;

  
  
  
  SequenceNumberSet missing_packets;

  
  bool is_truncated;

  
  
  SequenceNumberSet revived_packets;

  
  PacketTimeList received_packet_times;
};

bool NET_EXPORT_PRIVATE IsAwaitingPacket(
    const QuicAckFrame& ack_frame,
    QuicPacketSequenceNumber sequence_number);

void NET_EXPORT_PRIVATE InsertMissingPacketsBetween(
    QuicAckFrame* ack_frame,
    QuicPacketSequenceNumber lower,
    QuicPacketSequenceNumber higher);

enum CongestionFeedbackType {
  kTCP,  
};

enum CongestionControlType {
  kCubic,
  kReno,
  kBBR,
};

enum LossDetectionType {
  kNack,  
  kTime,  
};

struct NET_EXPORT_PRIVATE CongestionFeedbackMessageTCP {
  CongestionFeedbackMessageTCP();

  QuicByteCount receive_window;
};

struct NET_EXPORT_PRIVATE QuicCongestionFeedbackFrame {
  QuicCongestionFeedbackFrame();
  ~QuicCongestionFeedbackFrame();

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicCongestionFeedbackFrame& c);

  CongestionFeedbackType type;
  
  
  CongestionFeedbackMessageTCP tcp;
};

struct NET_EXPORT_PRIVATE QuicRstStreamFrame {
  QuicRstStreamFrame();
  QuicRstStreamFrame(QuicStreamId stream_id,
                     QuicRstStreamErrorCode error_code,
                     QuicStreamOffset bytes_written);

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicRstStreamFrame& r);

  QuicStreamId stream_id;
  QuicRstStreamErrorCode error_code;
  std::string error_details;

  
  
  
  
  QuicStreamOffset byte_offset;
};

struct NET_EXPORT_PRIVATE QuicConnectionCloseFrame {
  QuicConnectionCloseFrame();

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicConnectionCloseFrame& c);

  QuicErrorCode error_code;
  std::string error_details;
};

struct NET_EXPORT_PRIVATE QuicGoAwayFrame {
  QuicGoAwayFrame();
  QuicGoAwayFrame(QuicErrorCode error_code,
                  QuicStreamId last_good_stream_id,
                  const std::string& reason);

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicGoAwayFrame& g);

  QuicErrorCode error_code;
  QuicStreamId last_good_stream_id;
  std::string reason_phrase;
};

struct NET_EXPORT_PRIVATE QuicWindowUpdateFrame {
  QuicWindowUpdateFrame() {}
  QuicWindowUpdateFrame(QuicStreamId stream_id, QuicStreamOffset byte_offset);

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicWindowUpdateFrame& w);

  
  
  QuicStreamId stream_id;

  
  
  QuicStreamOffset byte_offset;
};

struct NET_EXPORT_PRIVATE QuicBlockedFrame {
  QuicBlockedFrame() {}
  explicit QuicBlockedFrame(QuicStreamId stream_id);

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicBlockedFrame& b);

  
  
  QuicStreamId stream_id;
};

enum EncryptionLevel {
  ENCRYPTION_NONE = 0,
  ENCRYPTION_INITIAL = 1,
  ENCRYPTION_FORWARD_SECURE = 2,

  NUM_ENCRYPTION_LEVELS,
};

struct NET_EXPORT_PRIVATE QuicFrame {
  QuicFrame();
  explicit QuicFrame(QuicPaddingFrame* padding_frame);
  explicit QuicFrame(QuicStreamFrame* stream_frame);
  explicit QuicFrame(QuicAckFrame* frame);

  
  explicit QuicFrame(QuicCongestionFeedbackFrame* frame);

  explicit QuicFrame(QuicRstStreamFrame* frame);
  explicit QuicFrame(QuicConnectionCloseFrame* frame);
  explicit QuicFrame(QuicStopWaitingFrame* frame);
  explicit QuicFrame(QuicPingFrame* frame);
  explicit QuicFrame(QuicGoAwayFrame* frame);
  explicit QuicFrame(QuicWindowUpdateFrame* frame);
  explicit QuicFrame(QuicBlockedFrame* frame);

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicFrame& frame);

  QuicFrameType type;
  union {
    QuicPaddingFrame* padding_frame;
    QuicStreamFrame* stream_frame;
    QuicAckFrame* ack_frame;

    
    QuicCongestionFeedbackFrame* congestion_feedback_frame;
    QuicStopWaitingFrame* stop_waiting_frame;

    QuicPingFrame* ping_frame;
    QuicRstStreamFrame* rst_stream_frame;
    QuicConnectionCloseFrame* connection_close_frame;
    QuicGoAwayFrame* goaway_frame;
    QuicWindowUpdateFrame* window_update_frame;
    QuicBlockedFrame* blocked_frame;
  };
};

typedef std::vector<QuicFrame> QuicFrames;

struct NET_EXPORT_PRIVATE QuicFecData {
  QuicFecData();

  
  
  
  QuicFecGroupNumber fec_group;
  base::StringPiece redundancy;
};

class NET_EXPORT_PRIVATE QuicData {
 public:
  QuicData(const char* buffer, size_t length);
  QuicData(char* buffer, size_t length, bool owns_buffer);
  virtual ~QuicData();

  base::StringPiece AsStringPiece() const {
    return base::StringPiece(data(), length());
  }

  const char* data() const { return buffer_; }
  size_t length() const { return length_; }

 private:
  const char* buffer_;
  size_t length_;
  bool owns_buffer_;

  DISALLOW_COPY_AND_ASSIGN(QuicData);
};

class NET_EXPORT_PRIVATE QuicPacket : public QuicData {
 public:
  static QuicPacket* NewDataPacket(
      char* buffer,
      size_t length,
      bool owns_buffer,
      QuicConnectionIdLength connection_id_length,
      bool includes_version,
      QuicSequenceNumberLength sequence_number_length) {
    return new QuicPacket(buffer, length, owns_buffer, connection_id_length,
                          includes_version, sequence_number_length, false);
  }

  static QuicPacket* NewFecPacket(
      char* buffer,
      size_t length,
      bool owns_buffer,
      QuicConnectionIdLength connection_id_length,
      bool includes_version,
      QuicSequenceNumberLength sequence_number_length) {
    return new QuicPacket(buffer, length, owns_buffer, connection_id_length,
                          includes_version, sequence_number_length, true);
  }

  base::StringPiece FecProtectedData() const;
  base::StringPiece AssociatedData() const;
  base::StringPiece BeforePlaintext() const;
  base::StringPiece Plaintext() const;

  bool is_fec_packet() const { return is_fec_packet_; }

  char* mutable_data() { return buffer_; }

 private:
  QuicPacket(char* buffer,
             size_t length,
             bool owns_buffer,
             QuicConnectionIdLength connection_id_length,
             bool includes_version,
             QuicSequenceNumberLength sequence_number_length,
             bool is_fec_packet);

  char* buffer_;
  const bool is_fec_packet_;
  const QuicConnectionIdLength connection_id_length_;
  const bool includes_version_;
  const QuicSequenceNumberLength sequence_number_length_;

  DISALLOW_COPY_AND_ASSIGN(QuicPacket);
};

class NET_EXPORT_PRIVATE QuicEncryptedPacket : public QuicData {
 public:
  QuicEncryptedPacket(const char* buffer, size_t length);
  QuicEncryptedPacket(char* buffer, size_t length, bool owns_buffer);

  
  QuicEncryptedPacket* Clone() const;

  
  
  
  
  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicEncryptedPacket& s);

 private:
  DISALLOW_COPY_AND_ASSIGN(QuicEncryptedPacket);
};

class NET_EXPORT_PRIVATE RetransmittableFrames {
 public:
  RetransmittableFrames();
  ~RetransmittableFrames();

  
  
  
  const QuicFrame& AddStreamFrame(QuicStreamFrame* stream_frame);
  
  const QuicFrame& AddNonStreamFrame(const QuicFrame& frame);
  const QuicFrames& frames() const { return frames_; }

  IsHandshake HasCryptoHandshake() const {
    return has_crypto_handshake_;
  }

  void set_encryption_level(EncryptionLevel level);
  EncryptionLevel encryption_level() const {
    return encryption_level_;
  }

 private:
  QuicFrames frames_;
  EncryptionLevel encryption_level_;
  IsHandshake has_crypto_handshake_;
  
  std::vector<std::string*> stream_data_;

  DISALLOW_COPY_AND_ASSIGN(RetransmittableFrames);
};

struct NET_EXPORT_PRIVATE SerializedPacket {
  SerializedPacket(QuicPacketSequenceNumber sequence_number,
                   QuicSequenceNumberLength sequence_number_length,
                   QuicPacket* packet,
                   QuicPacketEntropyHash entropy_hash,
                   RetransmittableFrames* retransmittable_frames);
  ~SerializedPacket();

  QuicPacketSequenceNumber sequence_number;
  QuicSequenceNumberLength sequence_number_length;
  QuicPacket* packet;
  QuicPacketEntropyHash entropy_hash;
  RetransmittableFrames* retransmittable_frames;

  
  std::set<QuicAckNotifier*> notifiers;
};

struct NET_EXPORT_PRIVATE TransmissionInfo {
  
  TransmissionInfo();

  
  
  TransmissionInfo(RetransmittableFrames* retransmittable_frames,
                   QuicSequenceNumberLength sequence_number_length);

  
  
  TransmissionInfo(RetransmittableFrames* retransmittable_frames,
                   QuicSequenceNumberLength sequence_number_length,
                   TransmissionType transmission_type,
                   SequenceNumberList* all_transmissions);

  RetransmittableFrames* retransmittable_frames;
  QuicSequenceNumberLength sequence_number_length;
  
  QuicTime sent_time;
  
  QuicByteCount bytes_sent;
  size_t nack_count;
  
  TransmissionType transmission_type;
  
  
  SequenceNumberList* all_transmissions;
  
  bool in_flight;
  
  bool is_unackable;
};

}  

#endif  
