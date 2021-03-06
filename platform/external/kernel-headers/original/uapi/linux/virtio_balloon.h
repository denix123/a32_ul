#ifndef _LINUX_VIRTIO_BALLOON_H
#define _LINUX_VIRTIO_BALLOON_H
/* This header is BSD licensed so anyone can use the definitions to implement
 * compatible drivers/servers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE. */
#include <linux/virtio_ids.h>
#include <linux/virtio_config.h>

#define VIRTIO_BALLOON_F_MUST_TELL_HOST	0 
#define VIRTIO_BALLOON_F_STATS_VQ	1 

#define VIRTIO_BALLOON_PFN_SHIFT 12

struct virtio_balloon_config
{
	
	__le32 num_pages;
	
	__le32 actual;
};

#define VIRTIO_BALLOON_S_SWAP_IN  0   
#define VIRTIO_BALLOON_S_SWAP_OUT 1   
#define VIRTIO_BALLOON_S_MAJFLT   2   
#define VIRTIO_BALLOON_S_MINFLT   3   
#define VIRTIO_BALLOON_S_MEMFREE  4   
#define VIRTIO_BALLOON_S_MEMTOT   5   
#define VIRTIO_BALLOON_S_NR       6

struct virtio_balloon_stat {
	__u16 tag;
	__u64 val;
} __attribute__((packed));

#endif 
