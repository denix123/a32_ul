/*
 * Dealing with Unicode
 *
 * Copyright (C) 2013 Red Hat, Inc.
 *
 * Authors:
 *  Markus Armbruster <armbru@redhat.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or
 * later.  See the COPYING file in the top-level directory.
 */

#include "qemu-common.h"

int mod_utf8_codepoint(const char *s, size_t n, char **end)
{
    static int min_cp[5] = { 0x80, 0x800, 0x10000, 0x200000, 0x4000000 };
    const unsigned char *p;
    unsigned byte, mask, len, i;
    int cp;

    if (n == 0 || *s == 0) {
        
        *end = (char *)s;
        return -1;
    }

    p = (const unsigned char *)s;
    byte = *p++;
    if (byte < 0x80) {
        cp = byte;              
    } else if (byte >= 0xFE) {
        cp = -1;                
    } else if ((byte & 0x40) == 0) {
        cp = -1;                
    } else {
        
        len = 0;
        for (mask = 0x80; byte & mask; mask >>= 1) {
            len++;
        }
        assert(len > 1 && len < 7);
        cp = byte & (mask - 1);
        for (i = 1; i < len; i++) {
            byte = i < n ? *p : 0;
            if ((byte & 0xC0) != 0x80) {
                cp = -1;        
                goto out;
            }
            p++;
            cp <<= 6;
            cp |= byte & 0x3F;
        }
        if (cp > 0x10FFFF) {
            cp = -1;            
        } else if ((cp >= 0xFDD0 && cp <= 0xFDEF)
                   || (cp & 0xFFFE) == 0xFFFE) {
            cp = -1;            
        } else if (cp >= 0xD800 && cp <= 0xDFFF) {
            cp = -1;            
        } else if (cp < min_cp[len - 2] && !(cp == 0 && len == 2)) {
            cp = -1;            
        }
    }

out:
    *end = (char *)p;
    return cp;
}
