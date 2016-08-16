// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.




EVENT_TYPE(CANCELLED)

EVENT_TYPE(FAILED)

EVENT_TYPE(REQUEST_ALIVE)


EVENT_TYPE(HOST_RESOLVER_IMPL)

EVENT_TYPE(HOST_RESOLVER_IMPL_REQUEST)

EVENT_TYPE(HOST_RESOLVER_IMPL_IPV6_SUPPORTED)

EVENT_TYPE(HOST_RESOLVER_IMPL_CACHE_HIT)

EVENT_TYPE(HOST_RESOLVER_IMPL_HOSTS_HIT)

EVENT_TYPE(HOST_RESOLVER_IMPL_CREATE_JOB)

EVENT_TYPE(HOST_RESOLVER_IMPL_JOB)

EVENT_TYPE(HOST_RESOLVER_IMPL_JOB_EVICTED)

EVENT_TYPE(HOST_RESOLVER_IMPL_JOB_STARTED)

EVENT_TYPE(HOST_RESOLVER_IMPL_ATTEMPT_STARTED)

EVENT_TYPE(HOST_RESOLVER_IMPL_ATTEMPT_FINISHED)

EVENT_TYPE(HOST_RESOLVER_IMPL_JOB_ATTACH)

EVENT_TYPE(HOST_RESOLVER_IMPL_JOB_REQUEST_ATTACH)

EVENT_TYPE(HOST_RESOLVER_IMPL_JOB_REQUEST_DETACH)

EVENT_TYPE(HOST_RESOLVER_IMPL_PROC_TASK)

EVENT_TYPE(HOST_RESOLVER_IMPL_DNS_TASK)


EVENT_TYPE(PROXY_SCRIPT_DECIDER)

EVENT_TYPE(PROXY_SCRIPT_DECIDER_WAIT)

EVENT_TYPE(PROXY_SCRIPT_DECIDER_FETCH_PAC_SCRIPT)

EVENT_TYPE(PROXY_SCRIPT_DECIDER_HAS_NO_FETCHER)

EVENT_TYPE(PROXY_SCRIPT_DECIDER_FALLING_BACK_TO_NEXT_PAC_SOURCE)


EVENT_TYPE(PROXY_SERVICE)

EVENT_TYPE(PROXY_SERVICE_WAITING_FOR_INIT_PAC)

EVENT_TYPE(PROXY_SERVICE_RESOLVED_PROXY_LIST)

EVENT_TYPE(PROXY_CONFIG_CHANGED)

EVENT_TYPE(BAD_PROXY_LIST_REPORTED)


EVENT_TYPE(PROXY_LIST_FALLBACK)


EVENT_TYPE(PAC_JAVASCRIPT_ERROR)

EVENT_TYPE(PAC_JAVASCRIPT_ALERT)


EVENT_TYPE(WAITING_FOR_PROXY_RESOLVER_THREAD)

EVENT_TYPE(SUBMITTED_TO_RESOLVER_THREAD)


EVENT_TYPE(SOCKET_ALIVE)


EVENT_TYPE(TCP_CONNECT)

EVENT_TYPE(TCP_CONNECT_ATTEMPT)

EVENT_TYPE(TCP_ACCEPT)

EVENT_TYPE(SOCKET_IN_USE)

EVENT_TYPE(SOCKS_CONNECT)

EVENT_TYPE(SOCKS5_CONNECT)

EVENT_TYPE(SOCKS_HOSTNAME_TOO_BIG)

EVENT_TYPE(SOCKS_UNEXPECTEDLY_CLOSED_DURING_GREETING)
EVENT_TYPE(SOCKS_UNEXPECTEDLY_CLOSED_DURING_HANDSHAKE)

EVENT_TYPE(SOCKS_UNEXPECTED_VERSION)

EVENT_TYPE(SOCKS_SERVER_ERROR)

EVENT_TYPE(SOCKS_UNEXPECTED_AUTH)

EVENT_TYPE(SOCKS_UNKNOWN_ADDRESS_TYPE)

EVENT_TYPE(SSL_CONNECT)

EVENT_TYPE(SSL_SERVER_HANDSHAKE)

EVENT_TYPE(SSL_CLIENT_CERT_REQUESTED)

EVENT_TYPE(SSL_GET_DOMAIN_BOUND_CERT)

EVENT_TYPE(SSL_CHANNEL_ID_REQUESTED)

EVENT_TYPE(SSL_CHANNEL_ID_PROVIDED)

EVENT_TYPE(SSL_CLIENT_CERT_PROVIDED)

EVENT_TYPE(SSL_HANDSHAKE_ERROR)
EVENT_TYPE(SSL_READ_ERROR)
EVENT_TYPE(SSL_WRITE_ERROR)

EVENT_TYPE(SSL_VERSION_FALLBACK)

EVENT_TYPE(SSL_VERIFICATION_MERGED)

EVENT_TYPE(SSL_NSS_ERROR)

EVENT_TYPE(SOCKET_BYTES_SENT)
EVENT_TYPE(SSL_SOCKET_BYTES_SENT)

EVENT_TYPE(SOCKET_BYTES_RECEIVED)
EVENT_TYPE(SSL_SOCKET_BYTES_RECEIVED)

EVENT_TYPE(SOCKET_READ_ERROR)
EVENT_TYPE(SOCKET_WRITE_ERROR)

EVENT_TYPE(SOCKET_CLOSED)

EVENT_TYPE(SSL_CERTIFICATES_RECEIVED)

EVENT_TYPE(SIGNED_CERTIFICATE_TIMESTAMPS_RECEIVED)

EVENT_TYPE(SIGNED_CERTIFICATE_TIMESTAMPS_CHECKED)


EVENT_TYPE(UDP_CONNECT)

EVENT_TYPE(UDP_LOCAL_ADDRESS)

EVENT_TYPE(UDP_BYTES_RECEIVED)
EVENT_TYPE(UDP_BYTES_SENT)

EVENT_TYPE(UDP_RECEIVE_ERROR)
EVENT_TYPE(UDP_SEND_ERROR)


EVENT_TYPE(SOCKET_POOL_CONNECT_JOB)

EVENT_TYPE(SOCKET_POOL_CONNECT_JOB_CONNECT)

EVENT_TYPE(CONNECT_JOB_SET_SOCKET)

EVENT_TYPE(SOCKET_POOL_CONNECT_JOB_TIMED_OUT)


EVENT_TYPE(SOCKET_POOL)

EVENT_TYPE(SOCKET_POOL_STALLED_MAX_SOCKETS)

EVENT_TYPE(SOCKET_POOL_STALLED_MAX_SOCKETS_PER_GROUP)

EVENT_TYPE(SOCKET_POOL_REUSED_AN_EXISTING_SOCKET)

EVENT_TYPE(TCP_CLIENT_SOCKET_POOL_REQUESTED_SOCKET)

EVENT_TYPE(TCP_CLIENT_SOCKET_POOL_REQUESTED_SOCKETS)


EVENT_TYPE(BACKUP_CONNECT_JOB_CREATED)

EVENT_TYPE(SOCKET_POOL_BOUND_TO_CONNECT_JOB)

EVENT_TYPE(SOCKET_POOL_BOUND_TO_SOCKET)

EVENT_TYPE(SOCKET_POOL_CONNECTING_N_SOCKETS)


EVENT_TYPE(URL_REQUEST_START_JOB)

EVENT_TYPE(URL_REQUEST_REDIRECTED)

EVENT_TYPE(URL_REQUEST_DELEGATE)

EVENT_TYPE(DELEGATE_INFO)

EVENT_TYPE(URL_REQUEST_JOB_BYTES_READ)
EVENT_TYPE(URL_REQUEST_JOB_FILTERED_BYTES_READ)

EVENT_TYPE(URL_REQUEST_SET_PRIORITY)

EVENT_TYPE(URL_REQUEST_REDIRECT_JOB)

EVENT_TYPE(URL_REQUEST_FAKE_RESPONSE_HEADERS_CREATED)


EVENT_TYPE(HTTP_CACHE_GET_BACKEND)

EVENT_TYPE(HTTP_CACHE_OPEN_ENTRY)

EVENT_TYPE(HTTP_CACHE_CREATE_ENTRY)

EVENT_TYPE(HTTP_CACHE_ADD_TO_ENTRY)

EVENT_TYPE(HTTP_CACHE_DOOM_ENTRY)

EVENT_TYPE(HTTP_CACHE_READ_INFO)
EVENT_TYPE(HTTP_CACHE_WRITE_INFO)

EVENT_TYPE(HTTP_CACHE_READ_DATA)
EVENT_TYPE(HTTP_CACHE_WRITE_DATA)


EVENT_TYPE(DISK_CACHE_ENTRY_IMPL)
EVENT_TYPE(DISK_CACHE_MEM_ENTRY_IMPL)

//     "index": <Index being read/written>,
//     "offset": <Offset being read/written>,
//     "buf_len": <Length of buffer being read to/written from>,
EVENT_TYPE(ENTRY_READ_DATA)
EVENT_TYPE(ENTRY_WRITE_DATA)

EVENT_TYPE(SPARSE_READ)
EVENT_TYPE(SPARSE_WRITE)

EVENT_TYPE(SPARSE_READ_CHILD_DATA)
EVENT_TYPE(SPARSE_WRITE_CHILD_DATA)

EVENT_TYPE(SPARSE_GET_RANGE)

EVENT_TYPE(SPARSE_DELETE_CHILDREN)

EVENT_TYPE(ENTRY_CLOSE)

EVENT_TYPE(ENTRY_DOOM)


EVENT_TYPE(HTTP_STREAM_REQUEST)

EVENT_TYPE(HTTP_STREAM_JOB)

EVENT_TYPE(HTTP_STREAM_REQUEST_BOUND_TO_JOB)

EVENT_TYPE(HTTP_STREAM_JOB_BOUND_TO_REQUEST)

EVENT_TYPE(HTTP_STREAM_REQUEST_PROTO)


EVENT_TYPE(HTTP_TRANSACTION_TUNNEL_SEND_REQUEST)

EVENT_TYPE(HTTP_TRANSACTION_SEND_TUNNEL_HEADERS)

EVENT_TYPE(HTTP_TRANSACTION_TUNNEL_READ_HEADERS)

EVENT_TYPE(HTTP_TRANSACTION_READ_TUNNEL_RESPONSE_HEADERS)

EVENT_TYPE(HTTP_TRANSACTION_SEND_REQUEST)

EVENT_TYPE(HTTP_TRANSACTION_SEND_REQUEST_HEADERS)

EVENT_TYPE(HTTP_TRANSACTION_SEND_REQUEST_BODY)

EVENT_TYPE(HTTP_TRANSACTION_SPDY_SEND_REQUEST_HEADERS)

EVENT_TYPE(HTTP_TRANSACTION_QUIC_SEND_REQUEST_HEADERS)

EVENT_TYPE(HTTP_TRANSACTION_READ_HEADERS)

EVENT_TYPE(HTTP_TRANSACTION_READ_RESPONSE_HEADERS)

EVENT_TYPE(HTTP_TRANSACTION_READ_BODY)

EVENT_TYPE(HTTP_TRANSACTION_DRAIN_BODY_FOR_AUTH_RESTART)

EVENT_TYPE(HTTP_TRANSACTION_RESTART_AFTER_ERROR)


EVENT_TYPE(SPDY_SESSION)

EVENT_TYPE(SPDY_SESSION_INITIALIZED)

EVENT_TYPE(SPDY_SESSION_SYN_STREAM)

EVENT_TYPE(SPDY_SESSION_PUSHED_SYN_STREAM)

EVENT_TYPE(SPDY_SESSION_SEND_HEADERS)

EVENT_TYPE(SPDY_SESSION_RECV_HEADERS)

EVENT_TYPE(SPDY_SESSION_SYN_REPLY)

EVENT_TYPE(SPDY_SESSION_SEND_SETTINGS)

EVENT_TYPE(SPDY_SESSION_RECV_SETTINGS)

EVENT_TYPE(SPDY_SESSION_RECV_SETTING)

EVENT_TYPE(SPDY_SESSION_RST_STREAM)

EVENT_TYPE(SPDY_SESSION_SEND_RST_STREAM)

EVENT_TYPE(SPDY_SESSION_PING)

EVENT_TYPE(SPDY_SESSION_GOAWAY)

EVENT_TYPE(SPDY_SESSION_RECEIVED_WINDOW_UPDATE_FRAME)

EVENT_TYPE(SPDY_SESSION_SENT_WINDOW_UPDATE_FRAME)

EVENT_TYPE(SPDY_SESSION_UPDATE_SEND_WINDOW)

EVENT_TYPE(SPDY_SESSION_UPDATE_RECV_WINDOW)

EVENT_TYPE(SPDY_SESSION_SEND_CREDENTIAL)

EVENT_TYPE(SPDY_SESSION_SEND_DATA)

EVENT_TYPE(SPDY_SESSION_RECV_DATA)

EVENT_TYPE(SPDY_SESSION_RECV_PUSH_PROMISE)

EVENT_TYPE(SPDY_SESSION_STREAM_STALLED_BY_SESSION_SEND_WINDOW)

EVENT_TYPE(SPDY_SESSION_STREAM_STALLED_BY_STREAM_SEND_WINDOW)

EVENT_TYPE(SPDY_SESSION_CLOSE)

EVENT_TYPE(SPDY_SESSION_STALLED_MAX_STREAMS)

EVENT_TYPE(SPDY_SESSION_INITIAL_WINDOW_SIZE_NO_FLOW_CONTROL)

EVENT_TYPE(SPDY_SESSION_INITIAL_WINDOW_SIZE_OUT_OF_RANGE)

EVENT_TYPE(SPDY_SESSION_UPDATE_STREAMS_SEND_WINDOW_SIZE)


EVENT_TYPE(SPDY_SESSION_POOL_FOUND_EXISTING_SESSION)

EVENT_TYPE(SPDY_SESSION_POOL_FOUND_EXISTING_SESSION_FROM_IP_POOL)

EVENT_TYPE(SPDY_SESSION_POOL_CREATED_NEW_SESSION)

EVENT_TYPE(SPDY_SESSION_POOL_IMPORTED_SESSION_FROM_SOCKET)

EVENT_TYPE(SPDY_SESSION_POOL_REMOVE_SESSION)


EVENT_TYPE(SPDY_STREAM)

EVENT_TYPE(SPDY_STREAM_ADOPTED_PUSH_STREAM)

EVENT_TYPE(SPDY_STREAM_FLOW_CONTROL_UNSTALLED)

EVENT_TYPE(SPDY_STREAM_UPDATE_SEND_WINDOW)

EVENT_TYPE(SPDY_STREAM_UPDATE_RECV_WINDOW)

EVENT_TYPE(SPDY_STREAM_ERROR)


EVENT_TYPE(SPDY_PROXY_CLIENT_SESSION)


EVENT_TYPE(QUIC_SESSION)

EVENT_TYPE(QUIC_SESSION_CLOSE_ON_ERROR)

EVENT_TYPE(QUIC_SESSION_CERTIFICATE_VERIFIED)

EVENT_TYPE(QUIC_SESSION_PACKET_RECEIVED)

EVENT_TYPE(QUIC_SESSION_PACKET_SENT)

EVENT_TYPE(QUIC_SESSION_PACKET_RETRANSMITTED)

EVENT_TYPE(QUIC_SESSION_PACKET_HEADER_RECEIVED)

EVENT_TYPE(QUIC_SESSION_STREAM_FRAME_RECEIVED)

EVENT_TYPE(QUIC_SESSION_STREAM_FRAME_SENT)

EVENT_TYPE(QUIC_SESSION_ACK_FRAME_RECEIVED)

EVENT_TYPE(QUIC_SESSION_ACK_FRAME_SENT)

EVENT_TYPE(QUIC_SESSION_WINDOW_UPDATE_FRAME_RECEIVED)

EVENT_TYPE(QUIC_SESSION_WINDOW_UPDATE_FRAME_SENT)

EVENT_TYPE(QUIC_SESSION_BLOCKED_FRAME_RECEIVED)

EVENT_TYPE(QUIC_SESSION_BLOCKED_FRAME_SENT)

EVENT_TYPE(QUIC_SESSION_GOAWAY_FRAME_RECEIVED)

EVENT_TYPE(QUIC_SESSION_GOAWAY_FRAME_SENT)

EVENT_TYPE(QUIC_SESSION_PING_FRAME_RECEIVED)

EVENT_TYPE(QUIC_SESSION_PING_FRAME_SENT)

EVENT_TYPE(QUIC_SESSION_STOP_WAITING_FRAME_RECEIVED)

EVENT_TYPE(QUIC_SESSION_STOP_WAITING_FRAME_SENT)

EVENT_TYPE(QUIC_SESSION_RST_STREAM_FRAME_RECEIVED)

EVENT_TYPE(QUIC_SESSION_RST_STREAM_FRAME_SENT)

EVENT_TYPE(QUIC_SESSION_CONGESTION_FEEDBACK_FRAME_RECEIVED)

EVENT_TYPE(QUIC_SESSION_CONGESTION_FEEDBACK_FRAME_SENT)

EVENT_TYPE(QUIC_SESSION_CONNECTION_CLOSE_FRAME_RECEIVED)

EVENT_TYPE(QUIC_SESSION_CONNECTION_CLOSE_FRAME_SENT)

EVENT_TYPE(QUIC_SESSION_PUBLIC_RESET_PACKET_RECEIVED)

EVENT_TYPE(QUIC_SESSION_VERSION_NEGOTIATION_PACKET_RECEIVED)

EVENT_TYPE(QUIC_SESSION_VERSION_NEGOTIATED)

EVENT_TYPE(QUIC_SESSION_PACKET_HEADER_REVIVED)

EVENT_TYPE(QUIC_SESSION_CRYPTO_HANDSHAKE_MESSAGE_RECEIVED)

EVENT_TYPE(QUIC_SESSION_CRYPTO_HANDSHAKE_MESSAGE_SENT)

EVENT_TYPE(QUIC_SESSION_CLOSED)


EVENT_TYPE(QUIC_HTTP_STREAM_SEND_REQUEST_HEADERS)

EVENT_TYPE(QUIC_HTTP_STREAM_READ_RESPONSE_HEADERS)


EVENT_TYPE(HTTP_STREAM_PARSER_READ_HEADERS)


EVENT_TYPE(SOCKET_STREAM_CONNECT)

EVENT_TYPE(SOCKET_STREAM_SENT)

EVENT_TYPE(SOCKET_STREAM_RECEIVED)


EVENT_TYPE(WEB_SOCKET_SEND_REQUEST_HEADERS)

EVENT_TYPE(WEB_SOCKET_READ_RESPONSE_HEADERS)


EVENT_TYPE(SOCKS5_GREET_WRITE)

EVENT_TYPE(SOCKS5_GREET_READ)

EVENT_TYPE(SOCKS5_HANDSHAKE_WRITE)

EVENT_TYPE(SOCKS5_HANDSHAKE_READ)


EVENT_TYPE(AUTH_PROXY)

EVENT_TYPE(AUTH_SERVER)


EVENT_TYPE(APPCACHE_DELIVERING_CACHED_RESPONSE)

EVENT_TYPE(APPCACHE_DELIVERING_FALLBACK_RESPONSE)

EVENT_TYPE(APPCACHE_DELIVERING_ERROR_RESPONSE)

EVENT_TYPE(APPCACHE_DELIVERING_EXECUTABLE_RESPONSE)


EVENT_TYPE(NETWORK_IP_ADDRESSES_CHANGED)

EVENT_TYPE(NETWORK_CONNECTIVITY_CHANGED)

EVENT_TYPE(NETWORK_CHANGED)

EVENT_TYPE(DNS_CONFIG_CHANGED)


EVENT_TYPE(THROTTLING_DISABLED_FOR_HOST)

EVENT_TYPE(THROTTLING_REJECTED_REQUEST)


EVENT_TYPE(DNS_TRANSACTION)

EVENT_TYPE(DNS_TRANSACTION_QUERY)

EVENT_TYPE(DNS_TRANSACTION_ATTEMPT)

EVENT_TYPE(DNS_TRANSACTION_TCP_ATTEMPT)

EVENT_TYPE(DNS_TRANSACTION_RESPONSE)



EVENT_TYPE(CHROME_EXTENSION_ABORTED_REQUEST)

EVENT_TYPE(CHROME_EXTENSION_REDIRECTED_REQUEST)

EVENT_TYPE(CHROME_EXTENSION_MODIFIED_HEADERS)

EVENT_TYPE(CHROME_EXTENSION_IGNORED_DUE_TO_CONFLICT)

EVENT_TYPE(CHROME_EXTENSION_PROVIDE_AUTH_CREDENTIALS)



EVENT_TYPE(CHROME_POLICY_ABORTED_REQUEST)


EVENT_TYPE(CERT_VERIFIER_REQUEST)

EVENT_TYPE(CERT_VERIFIER_JOB)

EVENT_TYPE(CERT_VERIFIER_REQUEST_BOUND_TO_JOB)


EVENT_TYPE(DOWNLOAD_STARTED)

EVENT_TYPE(DOWNLOAD_URL_REQUEST)


EVENT_TYPE(DOWNLOAD_ITEM_ACTIVE)

EVENT_TYPE(DOWNLOAD_ITEM_SAFETY_STATE_UPDATED)

EVENT_TYPE(DOWNLOAD_ITEM_UPDATED)

EVENT_TYPE(DOWNLOAD_ITEM_RENAMED)

EVENT_TYPE(DOWNLOAD_ITEM_INTERRUPTED)

EVENT_TYPE(DOWNLOAD_ITEM_RESUMED)

EVENT_TYPE(DOWNLOAD_ITEM_COMPLETING)

EVENT_TYPE(DOWNLOAD_ITEM_FINISHED)

EVENT_TYPE(DOWNLOAD_ITEM_CANCELED)


EVENT_TYPE(DOWNLOAD_FILE_OPENED)

EVENT_TYPE(DOWNLOAD_STREAM_DRAINED)

EVENT_TYPE(DOWNLOAD_FILE_RENAMED)

EVENT_TYPE(DOWNLOAD_FILE_CLOSED)

EVENT_TYPE(DOWNLOAD_FILE_DETACHED)

EVENT_TYPE(DOWNLOAD_FILE_DELETED)

EVENT_TYPE(DOWNLOAD_FILE_ERROR)

EVENT_TYPE(DOWNLOAD_FILE_ANNOTATED)


EVENT_TYPE(FILE_STREAM_ALIVE)

EVENT_TYPE(FILE_STREAM_SOURCE)

EVENT_TYPE(FILE_STREAM_BOUND_TO_OWNER)

EVENT_TYPE(FILE_STREAM_OPEN)

EVENT_TYPE(FILE_STREAM_ERROR)


EVENT_TYPE(FTP_COMMAND_SENT)

EVENT_TYPE(FTP_CONTROL_CONNECTION)

EVENT_TYPE(FTP_DATA_CONNECTION)

EVENT_TYPE(FTP_CONTROL_RESPONSE)


EVENT_TYPE(SIMPLE_CACHE_ENTRY)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_SET_KEY)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_OPEN_CALL)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_OPEN_BEGIN)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_OPEN_END)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_CREATE_CALL)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_CREATE_OPTIMISTIC)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_CREATE_BEGIN)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_CREATE_END)

//     "index": <Index being read/written>,
//     "offset": <Offset being read/written>,
//     "buf_len": <Length of buffer being read to/written from>,
EVENT_TYPE(SIMPLE_CACHE_ENTRY_READ_CALL)

//     "index": <Index being read/written>,
//     "offset": <Offset being read/written>,
//     "buf_len": <Length of buffer being read to/written from>,
EVENT_TYPE(SIMPLE_CACHE_ENTRY_READ_BEGIN)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_READ_END)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_CHECKSUM_BEGIN)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_CHECKSUM_END)

//     "index": <Index being read/written>,
//     "offset": <Offset being read/written>,
//     "buf_len": <Length of buffer being read to/written from>,
EVENT_TYPE(SIMPLE_CACHE_ENTRY_WRITE_CALL)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_WRITE_OPTIMISTIC)

//     "index": <Index being read/written>,
//     "offset": <Offset being read/written>,
//     "buf_len": <Length of buffer being read to/written from>,
EVENT_TYPE(SIMPLE_CACHE_ENTRY_WRITE_BEGIN)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_WRITE_END)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_DOOM_CALL)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_DOOM_BEGIN)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_DOOM_END)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_CLOSE_CALL)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_CLOSE_BEGIN)

EVENT_TYPE(SIMPLE_CACHE_ENTRY_CLOSE_END)

EVENT_TYPE(IPV6_REACHABILITY_CHECK)