/***********************************************************
Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#ifndef XVLIBINT_H
#define XVLIBINT_H

#define NEED_REPLIES

#ifndef SDL_INCLUDED_XLIBINT_H
#define SDL_INCLUDED_XLIBINT_H 1
#include <X11/Xlibint.h>
#endif

#include "../extensions/Xvproto.h"
#include "../extensions/Xvlib.h"

#if !defined(UNIXCPP)
#define XvGetReq(name, req) \
        WORD64ALIGN\
	if ((dpy->bufptr + SIZEOF(xv##name##Req)) > dpy->bufmax)\
		_XFlush(dpy);\
	req = (xv##name##Req *)(dpy->last_req = dpy->bufptr);\
	req->reqType = info->codes->major_opcode;\
        req->xvReqType = xv_##name; \
        req->length = (SIZEOF(xv##name##Req))>>2;\
	dpy->bufptr += SIZEOF(xv##name##Req);\
	dpy->request++

#else  
#define XvGetReq(name, req) \
        WORD64ALIGN\
	if ((dpy->bufptr + SIZEOF(xvnameReq)) > dpy->bufmax)\
		_XFlush(dpy);\
	req = (xvnameReq *)(dpy->last_req = dpy->bufptr);\
	req->reqType = info->codes->major_opcode;\
	req->xvReqType = xv_name;\
	req->length = (SIZEOF(xvnameReq))>>2;\
	dpy->bufptr += SIZEOF(xvnameReq);\
	dpy->request++
#endif


#endif 