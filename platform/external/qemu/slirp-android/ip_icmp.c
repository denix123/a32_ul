/*
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)ip_icmp.c	8.2 (Berkeley) 1/4/94
 * ip_icmp.c,v 1.7 1995/05/30 08:09:42 rgrimes Exp
 */

#include "slirp.h"
#include "ip_icmp.h"
#include "android/sockets.h"

#ifdef LOG_ENABLED
struct icmpstat icmpstat;
#endif

static const char icmp_ping_msg[] = "This is a pseudo-PING packet used by Slirp to emulate ICMP ECHO-REQUEST packets.\n";

static const int icmp_flush[19] = {
   0,
		         1,
		         1,
   1,
   1,
       1,
		         1,
		         1,
           0,
   1,
 1,
 1,
 1,
     0,
 0,
          0,
    0,
     0,
 0
};

void
icmp_input(struct mbuf *m, int hlen)
{
  register struct icmp *icp;
  register struct ip *ip=mtod(m, struct ip *);
  int icmplen=ip->ip_len;
  

  DEBUG_CALL("icmp_input");
  DEBUG_ARG("m = %lx", (long )m);
  DEBUG_ARG("m_len = %d", m->m_len);

  STAT(icmpstat.icps_received++);

  if (icmplen < ICMP_MINLEN) {          
    STAT(icmpstat.icps_tooshort++);
  freeit:
    m_freem(m);
    goto end_error;
  }

  m->m_len -= hlen;
  m->m_data += hlen;
  icp = mtod(m, struct icmp *);
  if (cksum(m, icmplen)) {
    STAT(icmpstat.icps_checksum++);
    goto freeit;
  }
  m->m_len += hlen;
  m->m_data -= hlen;

  
  

  DEBUG_ARG("icmp_type = %d", icp->icmp_type);
  switch (icp->icmp_type) {
  case ICMP_ECHO:
    icp->icmp_type = ICMP_ECHOREPLY;
    ip->ip_len += hlen;	             
    if (ip_geth(ip->ip_dst) == alias_addr_ip) {
      icmp_reflect(m);
    } else {
      struct socket *so;
      SockAddress  addr;
      uint32_t     addr_ip;
      uint16_t     addr_port;

      if ((so = socreate()) == NULL) goto freeit;
      if(udp_attach(so) == -1) {
	DEBUG_MISC((dfd,"icmp_input udp_attach errno = %d-%s\n",
		    errno,errno_str));
	sofree(so);
	m_free(m);
	goto end_error;
      }
      so->so_m = m;
      so->so_faddr_ip   = ip_geth(ip->ip_dst);
      so->so_faddr_port = 7;
      so->so_laddr_ip   = ip_geth(ip->ip_src);
      so->so_laddr_port = 9;
      so->so_iptos = ip->ip_tos;
      so->so_type = IPPROTO_ICMP;
      so->so_state = SS_ISFCONNECTED;

      
      if ((so->so_faddr_ip & 0xffffff00) == special_addr_ip) {
        
        int  low = so->so_faddr_ip & 0xff;

        if (low >= CTL_DNS && low < CTL_DNS + dns_addr_count)
            addr_ip = dns_addr[low - CTL_DNS];
        else
            addr_ip = loopback_addr_ip;
      } else {
            addr_ip = so->so_faddr_ip;
      }
      addr_port = so->so_faddr_port;

      sock_address_init_inet( &addr, addr_ip, addr_port );

      if(socket_sendto(so->s, icmp_ping_msg, strlen(icmp_ping_msg), &addr) < 0) {
        DEBUG_MISC((dfd,"icmp_input udp sendto tx errno = %d-%s\n",
                    errno,errno_str));
        icmp_error(m, ICMP_UNREACH,ICMP_UNREACH_NET, 0,errno_str);
        udp_detach(so);
      }
    } 
    break;
  case ICMP_UNREACH:
    
  case ICMP_TIMXCEED:
  case ICMP_PARAMPROB:
  case ICMP_SOURCEQUENCH:
  case ICMP_TSTAMP:
  case ICMP_MASKREQ:
  case ICMP_REDIRECT:
    STAT(icmpstat.icps_notsupp++);
    m_freem(m);
    break;

  default:
    STAT(icmpstat.icps_badtype++);
    m_freem(m);
  } 

end_error:
  
  return;
}



#define ICMP_MAXDATALEN (IP_MSS-28)
void
icmp_error(struct mbuf *msrc, u_char type, u_char code, int minsize,
           const char *message)
{
  unsigned hlen, shlen, s_ip_len;
  register struct ip *ip;
  register struct icmp *icp;
  register struct mbuf *m;

  DEBUG_CALL("icmp_error");
  DEBUG_ARG("msrc = %lx", (long )msrc);
  DEBUG_ARG("msrc_len = %d", msrc->m_len);

  if(type!=ICMP_UNREACH && type!=ICMP_TIMXCEED) goto end_error;

  
  if(!msrc) goto end_error;
  ip = mtod(msrc, struct ip *);
#ifdef DEBUG
  { char bufa[20], bufb[20];
    strcpy(bufa, inet_iptostr(ip_geth(ip->ip_src)));
    strcpy(bufb, inet_iptostr(ip_geth(ip->ip_dst)));
    DEBUG_MISC((dfd, " %.16s to %.16s\n", bufa, bufb));
  }
#endif
  if(ip->ip_off & IP_OFFMASK) goto end_error;    

  shlen=ip->ip_hl << 2;
  s_ip_len=ip->ip_len;
  if(ip->ip_p == IPPROTO_ICMP) {
    icp = (struct icmp *)((char *)ip + shlen);
    if(icp->icmp_type>18 || icmp_flush[icp->icmp_type]) goto end_error;
  }

  
  if(!(m=m_get())) goto end_error;               
  { int new_m_size;
    new_m_size=sizeof(struct ip )+ICMP_MINLEN+msrc->m_len+ICMP_MAXDATALEN;
    if(new_m_size>m->m_size) m_inc(m, new_m_size);
  }
  memcpy(m->m_data, msrc->m_data, msrc->m_len);
  m->m_len = msrc->m_len;                        

  
  ip  = mtod(m, struct ip *);
  hlen= sizeof(struct ip );     

  
  m->m_data += hlen;
  m->m_len -= hlen;

  icp = mtod(m, struct icmp *);

  if(minsize) s_ip_len=shlen+ICMP_MINLEN;   
  else if(s_ip_len>ICMP_MAXDATALEN)         
    s_ip_len=ICMP_MAXDATALEN;

  m->m_len=ICMP_MINLEN+s_ip_len;        

  

  icp->icmp_type = type;
  icp->icmp_code = code;
  icp->icmp_id = 0;
  icp->icmp_seq = 0;

  memcpy(&icp->icmp_ip, msrc->m_data, s_ip_len);   
  HTONS(icp->icmp_ip.ip_len);
  HTONS(icp->icmp_ip.ip_id);
  HTONS(icp->icmp_ip.ip_off);

#ifdef DEBUG
  if(message) {           
    int message_len;
    char *cpnt;
    message_len=strlen(message);
    if(message_len>ICMP_MAXDATALEN) message_len=ICMP_MAXDATALEN;
    cpnt=(char *)m->m_data+m->m_len;
    memcpy(cpnt, message, message_len);
    m->m_len+=message_len;
  }
#endif

  icp->icmp_cksum = 0;
  icp->icmp_cksum = cksum(m, m->m_len);

  m->m_data -= hlen;
  m->m_len += hlen;

  
  ip->ip_hl = hlen >> 2;
  ip->ip_len = m->m_len;

  ip->ip_tos=((ip->ip_tos & 0x1E) | 0xC0);  

  ip->ip_ttl = MAXTTL;
  ip->ip_p = IPPROTO_ICMP;
  ip->ip_dst = ip->ip_src;    
  ip->ip_src = ip_setn(alias_addr_ip);

  (void ) ip_output((struct socket *)NULL, m);

  STAT(icmpstat.icps_reflect++);

end_error:
  return;
}
#undef ICMP_MAXDATALEN

void
icmp_reflect(struct mbuf *m)
{
  register struct ip *ip = mtod(m, struct ip *);
  int hlen = ip->ip_hl << 2;
  int optlen = hlen - sizeof(struct ip );
  register struct icmp *icp;

  m->m_data += hlen;
  m->m_len -= hlen;
  icp = mtod(m, struct icmp *);

  icp->icmp_cksum = 0;
  icp->icmp_cksum = cksum(m, ip->ip_len - hlen);

  m->m_data -= hlen;
  m->m_len += hlen;

  
  if (optlen > 0) {
    memmove((caddr_t)(ip + 1), (caddr_t)ip + hlen,
	    (unsigned )(m->m_len - hlen));
    hlen -= optlen;
    ip->ip_hl = hlen >> 2;
    ip->ip_len -= optlen;
    m->m_len -= optlen;
  }

  ip->ip_ttl = MAXTTL;
  { 
    ipaddr_t icmp_dst;
    icmp_dst   = ip->ip_dst;
    ip->ip_dst = ip->ip_src;
    ip->ip_src = icmp_dst;
  }

  (void ) ip_output((struct socket *)NULL, m);

  STAT(icmpstat.icps_reflect++);
}