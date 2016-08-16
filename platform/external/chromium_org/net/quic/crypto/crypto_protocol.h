// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_CRYPTO_PROTOCOL_H_
#define NET_QUIC_CRYPTO_CRYPTO_PROTOCOL_H_

#include <string>

#include "net/base/net_export.h"
#include "net/quic/quic_protocol.h"

// Version and Crypto tags are written to the wire with a big-endian
// the client hello tag (CHLO) will be written as the
#define TAG(a, b, c, d) \
    static_cast<QuicTag>((d << 24) + (c << 16) + (b << 8) + a)

namespace net {

typedef std::string ServerConfigID;

const QuicTag kCHLO = TAG('C', 'H', 'L', 'O');   
const QuicTag kSHLO = TAG('S', 'H', 'L', 'O');   
const QuicTag kSCFG = TAG('S', 'C', 'F', 'G');   
const QuicTag kREJ  = TAG('R', 'E', 'J', '\0');  
const QuicTag kCETV = TAG('C', 'E', 'T', 'V');   
                                                 
const QuicTag kPRST = TAG('P', 'R', 'S', 'T');   
const QuicTag kSCUP = TAG('S', 'C', 'U', 'P');   

const QuicTag kP256 = TAG('P', '2', '5', '6');   
const QuicTag kC255 = TAG('C', '2', '5', '5');   

const QuicTag kNULL = TAG('N', 'U', 'L', 'N');   
const QuicTag kAESG = TAG('A', 'E', 'S', 'G');   
const QuicTag kCC12 = TAG('C', 'C', '1', '2');   

const QuicTag kSRBF = TAG('S', 'R', 'B', 'F');   

const QuicTag kQBIC = TAG('Q', 'B', 'I', 'C');   

const QuicTag kTBBR = TAG('T', 'B', 'B', 'R');   
const QuicTag kRENO = TAG('R', 'E', 'N', 'O');   
const QuicTag kIW10 = TAG('I', 'W', '1', '0');   
const QuicTag kPACE = TAG('P', 'A', 'C', 'E');   

const QuicTag kNACK = TAG('N', 'A', 'C', 'K');   
const QuicTag kTIME = TAG('T', 'I', 'M', 'E');   

const QuicTag kFHDR = TAG('F', 'H', 'D', 'R');   

const QuicTag kX509 = TAG('X', '5', '0', '9');   
                                                 
const QuicTag kX59R = TAG('X', '5', '9', 'R');   
                                                 
const QuicTag kCHID = TAG('C', 'H', 'I', 'D');   

const QuicTag kVER  = TAG('V', 'E', 'R', '\0');  
const QuicTag kNONC = TAG('N', 'O', 'N', 'C');   
const QuicTag kKEXS = TAG('K', 'E', 'X', 'S');   
const QuicTag kAEAD = TAG('A', 'E', 'A', 'D');   
                                                 
const QuicTag kCGST = TAG('C', 'G', 'S', 'T');   
                                                 
const QuicTag kCOPT = TAG('C', 'O', 'P', 'T');   
const QuicTag kLOSS = TAG('L', 'O', 'S', 'A');   
const QuicTag kICSL = TAG('I', 'C', 'S', 'L');   
                                                 
const QuicTag kKATO = TAG('K', 'A', 'T', 'O');   
const QuicTag kMSPC = TAG('M', 'S', 'P', 'C');   
const QuicTag kIRTT = TAG('I', 'R', 'T', 'T');   
const QuicTag kSWND = TAG('S', 'W', 'N', 'D');   
                                                 
const QuicTag kSNI  = TAG('S', 'N', 'I', '\0');  
                                                 
const QuicTag kPUBS = TAG('P', 'U', 'B', 'S');   
const QuicTag kSCID = TAG('S', 'C', 'I', 'D');   
const QuicTag kORBT = TAG('O', 'B', 'I', 'T');   
const QuicTag kPDMD = TAG('P', 'D', 'M', 'D');   
const QuicTag kPROF = TAG('P', 'R', 'O', 'F');   
const QuicTag kCCS  = TAG('C', 'C', 'S', 0);     
const QuicTag kCCRT = TAG('C', 'C', 'R', 'T');   
const QuicTag kEXPY = TAG('E', 'X', 'P', 'Y');   
const QuicTag kIFCW = TAG('I', 'F', 'C', 'W');   
                                                 
const QuicTag kSFCW = TAG('S', 'F', 'C', 'W');   
                                                 
const QuicTag kCFCW = TAG('C', 'F', 'C', 'W');   
                                                 
const QuicTag kUAID = TAG('U', 'A', 'I', 'D');   

const QuicTag kRREJ = TAG('R', 'R', 'E', 'J');   
                                                 

const QuicTag kCADR = TAG('C', 'A', 'D', 'R');   

const QuicTag kCIDK = TAG('C', 'I', 'D', 'K');   
const QuicTag kCIDS = TAG('C', 'I', 'D', 'S');   

const QuicTag kRNON = TAG('R', 'N', 'O', 'N');   
const QuicTag kRSEQ = TAG('R', 'S', 'E', 'Q');   

const QuicTag kPAD  = TAG('P', 'A', 'D', '\0');  

const QuicTag kServerNonceTag =
    TAG('S', 'N', 'O', 0);  
const QuicTag kSourceAddressTokenTag =
    TAG('S', 'T', 'K', 0);  
const QuicTag kCertificateTag =
    TAG('C', 'R', 'T', 255);  

#undef TAG

const size_t kMaxEntries = 128;  

const size_t kNonceSize = 32;  

const size_t kOrbitSize = 8;  

const char kProofSignatureLabel[] = "QUIC server config signature";

const size_t kClientHelloMinimumSize = 1024;

}  

#endif  
