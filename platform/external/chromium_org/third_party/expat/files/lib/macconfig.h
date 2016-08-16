/*================================================================
** Copyright 2000, Clark Cooper
** All rights reserved.
**
** This is free software. You are permitted to copy, distribute, or modify
** it under the terms of the MIT/X license (contained in the COPYING file
** with this distribution.)
**
*/

#ifndef MACCONFIG_H
#define MACCONFIG_H


#define BYTEORDER  4321

#undef HAVE_BCOPY

#define HAVE_MEMMOVE

#undef HAVE_MMAP

#undef HAVE_UNISTD_H

#define WORDS_BIGENDIAN

#undef XML_CONTEXT_BYTES

#define XML_DTD

#define XML_NS

#undef const

#define off_t  long

#undef size_t


#endif 
