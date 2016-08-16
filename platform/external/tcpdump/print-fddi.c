/*
 * Copyright (c) 1991, 1992, 1993, 1994, 1995, 1996, 1997
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef lint
static const char rcsid[] _U_ =
    "@(#) $Header: /tcpdump/master/tcpdump/print-fddi.c,v 1.66 2005-11-13 12:12:41 guy Exp $ (LBL)";
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <tcpdump-stdinc.h>

#include <pcap.h>
#include <stdio.h>
#include <string.h>

#include "interface.h"
#include "addrtoname.h"
#include "ethertype.h"

#include "ether.h"
#include "fddi.h"

#if defined(ultrix) || defined(__alpha) || defined(__bsdi) || defined(__NetBSD__) || defined(__linux__)
int	fddi_bitswap = 0;
#else
int	fddi_bitswap = 1;
#endif


static u_char fddi_bit_swap[] = {
	0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
	0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
	0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
	0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
	0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
	0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
	0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
	0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
	0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
	0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
	0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
	0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
	0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
	0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
	0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
	0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
	0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
	0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
	0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
	0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
	0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
	0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
	0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
	0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
	0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
	0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
	0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
	0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
	0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
	0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
	0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
	0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

static inline void
print_fddi_fc(u_char fc)
{
	switch (fc) {

	case FDDIFC_VOID:                         
		printf("void ");
		break;

	case FDDIFC_NRT:                          
		printf("nrt ");
		break;

	case FDDIFC_RT:                           
		printf("rt ");
		break;

	case FDDIFC_SMT_INFO:                     
		printf("info ");
		break;

	case FDDIFC_SMT_NSA:                      
		printf("nsa ");
		break;

	case FDDIFC_MAC_BEACON:                   
		printf("beacon ");
		break;

	case FDDIFC_MAC_CLAIM:                    
		printf("claim ");
		break;

	default:
		switch (fc & FDDIFC_CLFF) {

		case FDDIFC_MAC:
			printf("mac%1x ", fc & FDDIFC_ZZZZ);
			break;

		case FDDIFC_SMT:
			printf("smt%1x ", fc & FDDIFC_ZZZZ);
			break;

		case FDDIFC_LLC_ASYNC:
			printf("async%1x ", fc & FDDIFC_ZZZZ);
			break;

		case FDDIFC_LLC_SYNC:
			printf("sync%1x ", fc & FDDIFC_ZZZZ);
			break;

		case FDDIFC_IMP_ASYNC:
			printf("imp_async%1x ", fc & FDDIFC_ZZZZ);
			break;

		case FDDIFC_IMP_SYNC:
			printf("imp_sync%1x ", fc & FDDIFC_ZZZZ);
			break;

		default:
			printf("%02x ", fc);
			break;
		}
	}
}

static inline void
extract_fddi_addrs(const struct fddi_header *fddip, char *fsrc, char *fdst)
{
	register int i;

	if (fddi_bitswap) {
		for (i = 0; i < 6; ++i)
			fdst[i] = fddi_bit_swap[fddip->fddi_dhost[i]];
		for (i = 0; i < 6; ++i)
			fsrc[i] = fddi_bit_swap[fddip->fddi_shost[i]];
	}
	else {
		memcpy(fdst, (const char *)fddip->fddi_dhost, 6);
		memcpy(fsrc, (const char *)fddip->fddi_shost, 6);
	}
}

static inline void
fddi_hdr_print(register const struct fddi_header *fddip, register u_int length,
	   register const u_char *fsrc, register const u_char *fdst)
{
	const char *srcname, *dstname;

	srcname = etheraddr_string(fsrc);
	dstname = etheraddr_string(fdst);

	if (vflag)
		(void) printf("%02x %s %s %d: ",
		       fddip->fddi_fc,
		       srcname, dstname,
		       length);
	else if (qflag)
		printf("%s %s %d: ", srcname, dstname, length);
	else {
		(void) print_fddi_fc(fddip->fddi_fc);
		(void) printf("%s %s %d: ", srcname, dstname, length);
	}
}

static inline void
fddi_smt_print(const u_char *p _U_, u_int length _U_)
{
	printf("<SMT printer not yet implemented>");
}

void
fddi_print(const u_char *p, u_int length, u_int caplen)
{
	const struct fddi_header *fddip = (const struct fddi_header *)p;
	struct ether_header ehdr;
	u_short extracted_ethertype;

	if (caplen < FDDI_HDRLEN) {
		printf("[|fddi]");
		return;
	}

	extract_fddi_addrs(fddip, (char *)ESRC(&ehdr), (char *)EDST(&ehdr));

	if (eflag)
		fddi_hdr_print(fddip, length, ESRC(&ehdr), EDST(&ehdr));

	
	length -= FDDI_HDRLEN;
	p += FDDI_HDRLEN;
	caplen -= FDDI_HDRLEN;

	
	if ((fddip->fddi_fc & FDDIFC_CLFF) == FDDIFC_LLC_ASYNC) {
		
		if (llc_print(p, length, caplen, ESRC(&ehdr), EDST(&ehdr),
		    &extracted_ethertype) == 0) {
			if (!eflag)
				fddi_hdr_print(fddip, length + FDDI_HDRLEN,
				    ESRC(&ehdr), EDST(&ehdr));
			if (extracted_ethertype) {
				printf("(LLC %s) ",
			etherproto_string(htons(extracted_ethertype)));
			}
			if (!suppress_default_print)
				default_print(p, caplen);
		}
	} else if ((fddip->fddi_fc & FDDIFC_CLFF) == FDDIFC_SMT)
		fddi_smt_print(p, caplen);
	else {
		
		if (!eflag)
			fddi_hdr_print(fddip, length + FDDI_HDRLEN, ESRC(&ehdr),
			    EDST(&ehdr));
		if (!suppress_default_print)
			default_print(p, caplen);
	}
}

u_int
fddi_if_print(const struct pcap_pkthdr *h, register const u_char *p)
{
	fddi_print(p, h->len, h->caplen);

	return (FDDI_HDRLEN);
}