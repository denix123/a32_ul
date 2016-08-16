/*
 * Copyright (c) 1982, 1986, 1988, 1990, 1993
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
 *	@(#)tcp_subr.c	8.1 (Berkeley) 6/10/93
 * tcp_subr.c,v 1.5 1994/10/08 22:39:58 phk Exp
 */

/*
 * Changes and additions relating to SLiRP
 * Copyright (c) 1995 Danny Gasparovski.
 *
 * Please read the file COPYRIGHT for the
 * terms and conditions of the copyright.
 */

#include <slirp.h>

#define TCP_DO_RFC1323 0

void
tcp_init(void)
{
	tcp_iss = 1;		
	tcb.so_next = tcb.so_prev = &tcb;
}

void
tcp_template(struct tcpcb *tp)
{
	struct socket *so = tp->t_socket;
	register struct tcpiphdr *n = &tp->t_template;

	n->ti_mbuf = NULL;
	n->ti_x1 = 0;
	n->ti_pr = IPPROTO_TCP;
	n->ti_len = htons(sizeof (struct tcpiphdr) - sizeof (struct ip));
	n->ti_src = so->so_faddr;
	n->ti_dst = so->so_laddr;
	n->ti_sport = so->so_fport;
	n->ti_dport = so->so_lport;

	n->ti_seq = 0;
	n->ti_ack = 0;
	n->ti_x2 = 0;
	n->ti_off = 5;
	n->ti_flags = 0;
	n->ti_win = 0;
	n->ti_sum = 0;
	n->ti_urp = 0;
}

void
tcp_respond(struct tcpcb *tp, struct tcpiphdr *ti, struct mbuf *m,
            tcp_seq ack, tcp_seq seq, int flags)
{
	register int tlen;
	int win = 0;

	DEBUG_CALL("tcp_respond");
	DEBUG_ARG("tp = %lx", (long)tp);
	DEBUG_ARG("ti = %lx", (long)ti);
	DEBUG_ARG("m = %lx", (long)m);
	DEBUG_ARG("ack = %u", ack);
	DEBUG_ARG("seq = %u", seq);
	DEBUG_ARG("flags = %x", flags);

	if (tp)
		win = sbspace(&tp->t_socket->so_rcv);
        if (m == NULL) {
		if ((m = m_get()) == NULL)
			return;
#ifdef TCP_COMPAT_42
		tlen = 1;
#else
		tlen = 0;
#endif
		m->m_data += IF_MAXLINKHDR;
		*mtod(m, struct tcpiphdr *) = *ti;
		ti = mtod(m, struct tcpiphdr *);
		flags = TH_ACK;
	} else {
		m->m_data = (caddr_t)ti;

		m->m_len = sizeof (struct tcpiphdr);
		tlen = 0;
#define xchg(a,b,type) { type t; t=a; a=b; b=t; }
		xchg(ti->ti_dst.s_addr, ti->ti_src.s_addr, u_int32_t);
		xchg(ti->ti_dport, ti->ti_sport, u_int16_t);
#undef xchg
	}
	ti->ti_len = htons((u_short)(sizeof (struct tcphdr) + tlen));
	tlen += sizeof (struct tcpiphdr);
	m->m_len = tlen;

        ti->ti_mbuf = NULL;
	ti->ti_x1 = 0;
	ti->ti_seq = htonl(seq);
	ti->ti_ack = htonl(ack);
	ti->ti_x2 = 0;
	ti->ti_off = sizeof (struct tcphdr) >> 2;
	ti->ti_flags = flags;
	if (tp)
		ti->ti_win = htons((u_int16_t) (win >> tp->rcv_scale));
	else
		ti->ti_win = htons((u_int16_t)win);
	ti->ti_urp = 0;
	ti->ti_sum = 0;
	ti->ti_sum = cksum(m, tlen);
	((struct ip *)ti)->ip_len = tlen;

	if(flags & TH_RST)
	  ((struct ip *)ti)->ip_ttl = MAXTTL;
	else
	  ((struct ip *)ti)->ip_ttl = IPDEFTTL;

	(void) ip_output((struct socket *)0, m);
}

struct tcpcb *
tcp_newtcpcb(struct socket *so)
{
	register struct tcpcb *tp;

	tp = (struct tcpcb *)malloc(sizeof(*tp));
	if (tp == NULL)
		return ((struct tcpcb *)0);

	memset((char *) tp, 0, sizeof(struct tcpcb));
	tp->seg_next = tp->seg_prev = (struct tcpiphdr*)tp;
	tp->t_maxseg = TCP_MSS;

	tp->t_flags = TCP_DO_RFC1323 ? (TF_REQ_SCALE|TF_REQ_TSTMP) : 0;
	tp->t_socket = so;

	tp->t_srtt = TCPTV_SRTTBASE;
	tp->t_rttvar = TCPTV_SRTTDFLT << 2;
	tp->t_rttmin = TCPTV_MIN;

	TCPT_RANGESET(tp->t_rxtcur,
	    ((TCPTV_SRTTBASE >> 2) + (TCPTV_SRTTDFLT << 2)) >> 1,
	    TCPTV_MIN, TCPTV_REXMTMAX);

	tp->snd_cwnd = TCP_MAXWIN << TCP_MAX_WINSHIFT;
	tp->snd_ssthresh = TCP_MAXWIN << TCP_MAX_WINSHIFT;
	tp->t_state = TCPS_CLOSED;

	so->so_tcpcb = tp;

	return (tp);
}

struct tcpcb *tcp_drop(struct tcpcb *tp, int err)
{

	DEBUG_CALL("tcp_drop");
	DEBUG_ARG("tp = %lx", (long)tp);
	DEBUG_ARG("errno = %d", errno);

	if (TCPS_HAVERCVDSYN(tp->t_state)) {
		tp->t_state = TCPS_CLOSED;
		(void) tcp_output(tp);
		STAT(tcpstat.tcps_drops++);
	} else
		STAT(tcpstat.tcps_conndrops++);
	return (tcp_close(tp));
}

struct tcpcb *
tcp_close(struct tcpcb *tp)
{
	register struct tcpiphdr *t;
	struct socket *so = tp->t_socket;
	register struct mbuf *m;

	DEBUG_CALL("tcp_close");
	DEBUG_ARG("tp = %lx", (long )tp);

	
	t = tcpfrag_list_first(tp);
	while (!tcpfrag_list_end(t, tp)) {
		t = tcpiphdr_next(t);
		m = tcpiphdr_prev(t)->ti_mbuf;
		remque(tcpiphdr2qlink(tcpiphdr_prev(t)));
		m_freem(m);
	}
	
	free(tp);
        so->so_tcpcb = NULL;
	soisfdisconnected(so);
	
	if (so == tcp_last_so)
		tcp_last_so = &tcb;
	closesocket(so->s);
	sbfree(&so->so_rcv);
	sbfree(&so->so_snd);
	sofree(so);
	STAT(tcpstat.tcps_closed++);
	return ((struct tcpcb *)0);
}

#ifdef notdef
void
tcp_drain()
{
	
}

void
tcp_quench(i, errno)

	int errno;
{
	struct tcpcb *tp = intotcpcb(inp);

	if (tp)
		tp->snd_cwnd = tp->t_maxseg;
}

#endif 


void
tcp_sockclosed(struct tcpcb *tp)
{

	DEBUG_CALL("tcp_sockclosed");
	DEBUG_ARG("tp = %lx", (long)tp);

	switch (tp->t_state) {

	case TCPS_CLOSED:
	case TCPS_LISTEN:
	case TCPS_SYN_SENT:
		tp->t_state = TCPS_CLOSED;
		tp = tcp_close(tp);
		break;

	case TCPS_SYN_RECEIVED:
	case TCPS_ESTABLISHED:
		tp->t_state = TCPS_FIN_WAIT_1;
		break;

	case TCPS_CLOSE_WAIT:
		tp->t_state = TCPS_LAST_ACK;
		break;
	}
	if (tp && tp->t_state >= TCPS_FIN_WAIT_2)
		soisfdisconnected(tp->t_socket);
	if (tp)
		tcp_output(tp);
}

int tcp_fconnect(struct socket *so)
{
  int ret=0;

  DEBUG_CALL("tcp_fconnect");
  DEBUG_ARG("so = %lx", (long )so);

  if( (ret=so->s=socket(AF_INET,SOCK_STREAM,0)) >= 0) {
    int opt, s=so->s;
    struct sockaddr_in addr;

    fd_nonblock(s);
    opt = 1;
    setsockopt(s,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,sizeof(opt ));
    opt = 1;
    setsockopt(s,SOL_SOCKET,SO_OOBINLINE,(char *)&opt,sizeof(opt ));

    addr.sin_family = AF_INET;
    if ((so->so_faddr.s_addr & htonl(0xffffff00)) == special_addr.s_addr) {
      
      switch(ntohl(so->so_faddr.s_addr) & 0xff) {
      case CTL_DNS:
	addr.sin_addr = dns_addr;
	break;
      case CTL_ALIAS:
      default:
	addr.sin_addr = loopback_addr;
	break;
      }
    } else
      addr.sin_addr = so->so_faddr;
    addr.sin_port = so->so_fport;

    DEBUG_MISC((dfd, " connect()ing, addr.sin_port=%d, "
		"addr.sin_addr.s_addr=%.16s\n",
		ntohs(addr.sin_port), inet_ntoa(addr.sin_addr)));
    
    ret = connect(s,(struct sockaddr *)&addr,sizeof (addr));

    soisfconnecting(so);
  }

  return(ret);
}

void
tcp_connect(struct socket *inso)
{
	struct socket *so;
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	struct tcpcb *tp;
	int s, opt;

	DEBUG_CALL("tcp_connect");
	DEBUG_ARG("inso = %lx", (long)inso);

	if (inso->so_state & SS_FACCEPTONCE) {
		
		so = inso;
	} else {
		if ((so = socreate()) == NULL) {
			
			closesocket(accept(inso->s,(struct sockaddr *)&addr,&addrlen));
			return;
		}
		if (tcp_attach(so) < 0) {
			free(so); 
			return;
		}
		so->so_laddr = inso->so_laddr;
		so->so_lport = inso->so_lport;
	}

	(void) tcp_mss(sototcpcb(so), 0);

	if ((s = accept(inso->s,(struct sockaddr *)&addr,&addrlen)) < 0) {
		tcp_close(sototcpcb(so)); 
		return;
	}
	fd_nonblock(s);
	opt = 1;
	setsockopt(s,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,sizeof(int));
	opt = 1;
	setsockopt(s,SOL_SOCKET,SO_OOBINLINE,(char *)&opt,sizeof(int));
	opt = 1;
	setsockopt(s,IPPROTO_TCP,TCP_NODELAY,(char *)&opt,sizeof(int));

	so->so_fport = addr.sin_port;
	so->so_faddr = addr.sin_addr;
	
	if (so->so_faddr.s_addr == 0 || so->so_faddr.s_addr == loopback_addr.s_addr)
	   so->so_faddr = alias_addr;

	
	if (inso->so_state & SS_FACCEPTONCE) {
		closesocket(so->s); 
		so->so_state = SS_NOFDREF; 
					   
	}
	so->s = s;

	so->so_iptos = tcp_tos(so);
	tp = sototcpcb(so);

	tcp_template(tp);

	

 
	STAT(tcpstat.tcps_connattempt++);

	tp->t_state = TCPS_SYN_SENT;
	tp->t_timer[TCPT_KEEP] = TCPTV_KEEP_INIT;
	tp->iss = tcp_iss;
	tcp_iss += TCP_ISSINCR/2;
	tcp_sendseqinit(tp);
	tcp_output(tp);
}

int
tcp_attach(struct socket *so)
{
	if ((so->so_tcpcb = tcp_newtcpcb(so)) == NULL)
	   return -1;

	insque(so, &tcb);

	return 0;
}

static const struct tos_t tcptos[] = {
	  {0, 20, IPTOS_THROUGHPUT, 0},	
	  {21, 21, IPTOS_LOWDELAY,  EMU_FTP},	
	  {0, 23, IPTOS_LOWDELAY, 0},	
	  {0, 80, IPTOS_THROUGHPUT, 0},	
	  {0, 513, IPTOS_LOWDELAY, EMU_RLOGIN|EMU_NOCONNECT},	
	  {0, 514, IPTOS_LOWDELAY, EMU_RSH|EMU_NOCONNECT},	
	  {0, 544, IPTOS_LOWDELAY, EMU_KSH},		
	  {0, 543, IPTOS_LOWDELAY, 0},	
	  {0, 6667, IPTOS_THROUGHPUT, EMU_IRC},	
	  {0, 6668, IPTOS_THROUGHPUT, EMU_IRC},	
	  {0, 7070, IPTOS_LOWDELAY, EMU_REALAUDIO }, 
	  {0, 113, IPTOS_LOWDELAY, EMU_IDENT }, 
	  {0, 0, 0, 0}
};

#ifdef CONFIG_QEMU
static
#endif
struct emu_t *tcpemu = NULL;

u_int8_t
tcp_tos(struct socket *so)
{
	int i = 0;
	struct emu_t *emup;

	while(tcptos[i].tos) {
		if ((tcptos[i].fport && (ntohs(so->so_fport) == tcptos[i].fport)) ||
		    (tcptos[i].lport && (ntohs(so->so_lport) == tcptos[i].lport))) {
			so->so_emu = tcptos[i].emu;
			return tcptos[i].tos;
		}
		i++;
	}

	
	for (emup = tcpemu; emup; emup = emup->next) {
		if ((emup->fport && (ntohs(so->so_fport) == emup->fport)) ||
		    (emup->lport && (ntohs(so->so_lport) == emup->lport))) {
			so->so_emu = emup->emu;
			return emup->tos;
		}
	}

	return 0;
}

#if 0
int do_echo = -1;
#endif

int
tcp_emu(struct socket *so, struct mbuf *m)
{
	u_int n1, n2, n3, n4, n5, n6;
        char buff[257];
	u_int32_t laddr;
	u_int lport;
	char *bptr;

	DEBUG_CALL("tcp_emu");
	DEBUG_ARG("so = %lx", (long)so);
	DEBUG_ARG("m = %lx", (long)m);

	switch(so->so_emu) {
		int x, i;

	 case EMU_IDENT:

		{
			struct socket *tmpso;
			struct sockaddr_in addr;
			socklen_t addrlen = sizeof(struct sockaddr_in);
			struct sbuf *so_rcv = &so->so_rcv;

			memcpy(so_rcv->sb_wptr, m->m_data, m->m_len);
			so_rcv->sb_wptr += m->m_len;
			so_rcv->sb_rptr += m->m_len;
			m->m_data[m->m_len] = 0; 
			if (strchr(m->m_data, '\r') || strchr(m->m_data, '\n')) {
				if (sscanf(so_rcv->sb_data, "%u%*[ ,]%u", &n1, &n2) == 2) {
					HTONS(n1);
					HTONS(n2);
					
					for (tmpso = tcb.so_next; tmpso != &tcb; tmpso = tmpso->so_next) {
						if (tmpso->so_laddr.s_addr == so->so_laddr.s_addr &&
						    tmpso->so_lport == n2 &&
						    tmpso->so_faddr.s_addr == so->so_faddr.s_addr &&
						    tmpso->so_fport == n1) {
							if (getsockname(tmpso->s,
								(struct sockaddr *)&addr, &addrlen) == 0)
							   n2 = ntohs(addr.sin_port);
							break;
						}
					}
				}
                                so_rcv->sb_cc = snprintf(so_rcv->sb_data,
                                                         so_rcv->sb_datalen,
                                                         "%d,%d\r\n", n1, n2);
				so_rcv->sb_rptr = so_rcv->sb_data;
				so_rcv->sb_wptr = so_rcv->sb_data + so_rcv->sb_cc;
			}
			m_free(m);
			return 0;
		}

#if 0
	 case EMU_RLOGIN:
		{
			int i, i2, n;
			char *ptr;
			char args[100];
			char term[100];
			struct sbuf *so_snd = &so->so_snd;
			struct sbuf *so_rcv = &so->so_rcv;

			
			if (ntohs(so->so_lport) > 1023 || ntohs(so->so_lport) < 512 ||
			    (m->m_len + so_rcv->sb_wptr) > (so_rcv->sb_data + so_rcv->sb_datalen)) {
				memcpy(so_snd->sb_wptr, "Permission denied\n", 18);
				so_snd->sb_wptr += 18;
				so_snd->sb_cc += 18;
				tcp_sockclosed(sototcpcb(so));
				m_free(m);
				return 0;
			}

			
			memcpy(so_rcv->sb_wptr, m->m_data, m->m_len);
			so_rcv->sb_wptr += m->m_len;
			so_rcv->sb_rptr += m->m_len;
			m_free(m);

			n = 0;
			ptr = so_rcv->sb_data;
			args[0] = 0;
			term[0] = 0;
			while (ptr < so_rcv->sb_wptr) {
				if (*ptr++ == 0) {
					n++;
					if (n == 2) {
						sprintf(args, "rlogin -l %s %s",
							ptr, inet_ntoa(so->so_faddr));
					} else if (n == 3) {
						i2 = so_rcv->sb_wptr - ptr;
						for (i = 0; i < i2; i++) {
							if (ptr[i] == '/') {
								ptr[i] = 0;
#ifdef HAVE_SETENV
								sprintf(term, "%s", ptr);
#else
								sprintf(term, "TERM=%s", ptr);
#endif
								ptr[i] = '/';
								break;
							}
						}
					}
				}
			}

			if (n != 4)
			   return 0;

			
#ifdef HAVE_SETENV
			setenv("TERM", term, 1);
#else
			putenv(term);
#endif
			fork_exec(so, args, 2);
			term[0] = 0;
			so->so_emu = 0;

			
			so_snd->sb_wptr[0] = 0;
			so_snd->sb_wptr++;
			so_snd->sb_cc++;

			return 0;
		}

	 case EMU_RSH:
		{
			int  n;
			char *ptr;
			char *user;
			char *args;
			struct sbuf *so_snd = &so->so_snd;
			struct sbuf *so_rcv = &so->so_rcv;

			
			if (ntohs(so->so_lport) > 1023 || ntohs(so->so_lport) < 512 ||
			    (m->m_len + so_rcv->sb_wptr) > (so_rcv->sb_data + so_rcv->sb_datalen)) {
				memcpy(so_snd->sb_wptr, "Permission denied\n", 18);
				so_snd->sb_wptr += 18;
				so_snd->sb_cc += 18;
				tcp_sockclosed(sototcpcb(so));
				m_free(m);
				return 0;
			}

			
			memcpy(so_rcv->sb_wptr, m->m_data, m->m_len);
			so_rcv->sb_wptr += m->m_len;
			so_rcv->sb_rptr += m->m_len;
			m_free(m);

			n = 0;
			ptr = so_rcv->sb_data;
			user="";
			args="";
			if (so->extra==NULL) {
				struct socket *ns;
				struct tcpcb* tp;
				int port=atoi(ptr);
				if (port <= 0) return 0;
                if (port > 1023 || port < 512) {
                  memcpy(so_snd->sb_wptr, "Permission denied\n", 18);
                  so_snd->sb_wptr += 18;
                  so_snd->sb_cc += 18;
                  tcp_sockclosed(sototcpcb(so));
                  return 0;
                }
				if ((ns=socreate()) == NULL)
                  return 0;
				if (tcp_attach(ns)<0) {
                  free(ns);
                  return 0;
				}

				ns->so_laddr=so->so_laddr;
				ns->so_lport=htons(port);

				(void) tcp_mss(sototcpcb(ns), 0);

				ns->so_faddr=so->so_faddr;
				ns->so_fport=htons(IPPORT_RESERVED-1); 

				if (ns->so_faddr.s_addr == 0 ||
					ns->so_faddr.s_addr == loopback_addr.s_addr)
                  ns->so_faddr = alias_addr;

				ns->so_iptos = tcp_tos(ns);
				tp = sototcpcb(ns);

				tcp_template(tp);

				

                

				STAT(tcpstat.tcps_connattempt++);

				tp->t_state = TCPS_SYN_SENT;
				tp->t_timer[TCPT_KEEP] = TCPTV_KEEP_INIT;
				tp->iss = tcp_iss;
				tcp_iss += TCP_ISSINCR/2;
				tcp_sendseqinit(tp);
				tcp_output(tp);
				so->extra=ns;
			}
			while (ptr < so_rcv->sb_wptr) {
              if (*ptr++ == 0) {
                n++;
                if (n == 2) {
                  user=ptr;
                } else if (n == 3) {
                  args=ptr;
                }
              }
			}

			if (n != 4)
              return 0;

			rsh_exec(so,so->extra, user, inet_ntoa(so->so_faddr), args);
			so->so_emu = 0;
			so->extra=NULL;

			
			so_snd->sb_wptr[0] = 0;
			so_snd->sb_wptr++;
			so_snd->sb_cc++;

			return 0;
		}

	 case EMU_CTL:
		{
			int num;
			struct sbuf *so_snd = &so->so_snd;
			struct sbuf *so_rcv = &so->so_rcv;

			if (!so->so_m) {
			  int rxlen;
			  char *rxdata;
			  rxdata=mtod(m, char *);
			  for (rxlen=m->m_len; rxlen; rxlen--) {
			    if (*rxdata++ & 0x80) {
			      so->so_m = m;
			      return 0;
			    }
			  }
			} 

			sbappendsb(so_rcv, m);

			
			if (so_snd->sb_cc == 0)
			   so_snd->sb_wptr = so_snd->sb_rptr = so_snd->sb_data;

			if (do_echo == -1) {
				if (m->m_len == 1) do_echo = 1;
				else do_echo = 0;
			}
			if (do_echo) {
			  sbappendsb(so_snd, m);
			  m_free(m);
			  tcp_output(sototcpcb(so)); 
			} else
			  m_free(m);

			num = 0;
			while (num < so->so_rcv.sb_cc) {
				if (*(so->so_rcv.sb_rptr + num) == '\n' ||
				    *(so->so_rcv.sb_rptr + num) == '\r') {
					int n;

					*(so_rcv->sb_rptr + num) = 0;
					if (ctl_password && !ctl_password_ok) {
						
						if (sscanf(so_rcv->sb_rptr, "pass %256s", buff) == 1) {
							if (strcmp(buff, ctl_password) == 0) {
								ctl_password_ok = 1;
								n = sprintf(so_snd->sb_wptr,
									    "Password OK.\r\n");
								goto do_prompt;
							}
						}
						n = sprintf(so_snd->sb_wptr,
					 "Error: Password required, log on with \"pass PASSWORD\"\r\n");
						goto do_prompt;
					}
					cfg_quitting = 0;
					n = do_config(so_rcv->sb_rptr, so, PRN_SPRINTF);
					if (!cfg_quitting) {
						
do_prompt:
						so_snd->sb_cc += n;
						so_snd->sb_wptr += n;
						
						n = sprintf(so_snd->sb_wptr, "Slirp> ");
						so_snd->sb_cc += n;
						so_snd->sb_wptr += n;
					}
					
					so_rcv->sb_cc = 0;
					so_rcv->sb_wptr = so_rcv->sb_rptr = so_rcv->sb_data;
					tcp_output(sototcpcb(so)); 
				}
				num++;
			}
			return 0;
		}
#endif
        case EMU_FTP: 
                *(m->m_data+m->m_len) = 0; 
		if ((bptr = (char *)strstr(m->m_data, "ORT")) != NULL) {
			x = sscanf(bptr, "ORT %u,%u,%u,%u,%u,%u\r\n%256[^\177]",
				   &n1, &n2, &n3, &n4, &n5, &n6, buff);
			if (x < 6)
			   return 1;

			laddr = htonl((n1 << 24) | (n2 << 16) | (n3 << 8) | (n4));
			lport = htons((n5 << 8) | (n6));

			if ((so = solisten(0, laddr, lport, SS_FACCEPTONCE)) == NULL)
			   return 1;

			n6 = ntohs(so->so_fport);

			n5 = (n6 >> 8) & 0xff;
			n6 &= 0xff;

			laddr = ntohl(so->so_faddr.s_addr);

			n1 = ((laddr >> 24) & 0xff);
			n2 = ((laddr >> 16) & 0xff);
			n3 = ((laddr >> 8)  & 0xff);
			n4 =  (laddr & 0xff);

			m->m_len = bptr - m->m_data; 
                        m->m_len += snprintf(bptr, m->m_hdr.mh_size - m->m_len,
                                             "ORT %d,%d,%d,%d,%d,%d\r\n%s",
                                             n1, n2, n3, n4, n5, n6, x==7?buff:"");
			return 1;
		} else if ((bptr = (char *)strstr(m->m_data, "27 Entering")) != NULL) {
			x = sscanf(bptr, "27 Entering Passive Mode (%u,%u,%u,%u,%u,%u)\r\n%256[^\177]",
				   &n1, &n2, &n3, &n4, &n5, &n6, buff);
			if (x < 6)
			   return 1;

			laddr = htonl((n1 << 24) | (n2 << 16) | (n3 << 8) | (n4));
			lport = htons((n5 << 8) | (n6));

			if ((so = solisten(0, laddr, lport, SS_FACCEPTONCE)) == NULL)
			   return 1;

			n6 = ntohs(so->so_fport);

			n5 = (n6 >> 8) & 0xff;
			n6 &= 0xff;

			laddr = ntohl(so->so_faddr.s_addr);

			n1 = ((laddr >> 24) & 0xff);
			n2 = ((laddr >> 16) & 0xff);
			n3 = ((laddr >> 8)  & 0xff);
			n4 =  (laddr & 0xff);

			m->m_len = bptr - m->m_data; 
			m->m_len += snprintf(bptr, m->m_hdr.mh_size - m->m_len,
                                             "27 Entering Passive Mode (%d,%d,%d,%d,%d,%d)\r\n%s",
                                             n1, n2, n3, n4, n5, n6, x==7?buff:"");

			return 1;
		}

		return 1;

	 case EMU_KSH:
		so->so_emu = 0;
		for (lport = 0, i = 0; i < m->m_len-1; ++i) {
			if (m->m_data[i] < '0' || m->m_data[i] > '9')
				return 1;       
			lport *= 10;
			lport += m->m_data[i] - '0';
		}
		if (m->m_data[m->m_len-1] == '\0' && lport != 0 &&
		    (so = solisten(0, so->so_laddr.s_addr, htons(lport), SS_FACCEPTONCE)) != NULL)
                    m->m_len = snprintf(m->m_data, m->m_hdr.mh_size, "%d",
                                        ntohs(so->so_fport)) + 1;
		return 1;

	 case EMU_IRC:
		*(m->m_data+m->m_len) = 0; 
		if ((bptr = (char *)strstr(m->m_data, "DCC")) == NULL)
			 return 1;

		
		if (sscanf(bptr, "DCC CHAT %256s %u %u", buff, &laddr, &lport) == 3) {
			if ((so = solisten(0, htonl(laddr), htons(lport), SS_FACCEPTONCE)) == NULL)
				return 1;

			m->m_len = bptr - m->m_data; 
                        m->m_len += snprintf(bptr, m->m_hdr.mh_size,
                                             "DCC CHAT chat %lu %u%c\n",
                                             (unsigned long)ntohl(so->so_faddr.s_addr),
                                             ntohs(so->so_fport), 1);
		} else if (sscanf(bptr, "DCC SEND %256s %u %u %u", buff, &laddr, &lport, &n1) == 4) {
			if ((so = solisten(0, htonl(laddr), htons(lport), SS_FACCEPTONCE)) == NULL)
				return 1;

			m->m_len = bptr - m->m_data; 
                        m->m_len += snprintf(bptr, m->m_hdr.mh_size,
                                             "DCC SEND %s %lu %u %u%c\n", buff,
                                             (unsigned long)ntohl(so->so_faddr.s_addr),
                                             ntohs(so->so_fport), n1, 1);
		} else if (sscanf(bptr, "DCC MOVE %256s %u %u %u", buff, &laddr, &lport, &n1) == 4) {
			if ((so = solisten(0, htonl(laddr), htons(lport), SS_FACCEPTONCE)) == NULL)
				return 1;

			m->m_len = bptr - m->m_data; 
                        m->m_len += snprintf(bptr, m->m_hdr.mh_size,
                                             "DCC MOVE %s %lu %u %u%c\n", buff,
                                             (unsigned long)ntohl(so->so_faddr.s_addr),
                                             ntohs(so->so_fport), n1, 1);
		}
		return 1;

	 case EMU_REALAUDIO:

		bptr = m->m_data;
		while (bptr < m->m_data + m->m_len) {
			u_short p;
			static int ra = 0;
			char ra_tbl[4];

			ra_tbl[0] = 0x50;
			ra_tbl[1] = 0x4e;
			ra_tbl[2] = 0x41;
			ra_tbl[3] = 0;

			switch (ra) {
			 case 0:
			 case 2:
			 case 3:
				if (*bptr++ != ra_tbl[ra]) {
					ra = 0;
					continue;
				}
				break;

			 case 1:
				if (*bptr == 0x50) {
					ra = 1;
					bptr++;
					continue;
				} else if (*bptr++ != ra_tbl[ra]) {
					ra = 0;
					continue;
				}
				break;

			 case 4:
				bptr++;
				break;

			 case 5:
				if (*(bptr + 1) == 0x02)
				   bptr += 8;
				else
				   bptr += 4;
				break;

			 case 6:
				lport = (((u_char*)bptr)[0] << 8)
				+ ((u_char *)bptr)[1];
				if (lport < 6970)
				   lport += 256;   
				if (lport < 6970 || lport > 7170)
				   return 1;       

				
				for (p = 6970; p < 7071; p++) {
					if (udp_listen( htons(p),
						       so->so_laddr.s_addr,
						       htons(lport),
						       SS_FACCEPTONCE)) {
						break;
					}
				}
				if (p == 7071)
				   p = 0;
				*(u_char *)bptr++ = (p >> 8) & 0xff;
				*(u_char *)bptr++ = p & 0xff;
				ra = 0;
				return 1;   
				break;

			 default:
				ra = 0;
			}
			ra++;
		}
		return 1;

	 default:
		
		so->so_emu = 0;
		return 1;
	}
}

int
tcp_ctl(struct socket *so)
{
	struct sbuf *sb = &so->so_snd;
	int command;
 	struct ex_list *ex_ptr;
	int do_pty;
        

	DEBUG_CALL("tcp_ctl");
	DEBUG_ARG("so = %lx", (long )so);

#if 0
	if (ctl_addr.s_addr && (ctl_addr.s_addr == -1 || (so->so_laddr.s_addr != ctl_addr.s_addr))) {
		sb->sb_cc = sprintf(sb->sb_wptr,"Error: Permission denied.\r\n");
		sb->sb_wptr += sb->sb_cc;
		return 0;
	}
#endif
	command = (ntohl(so->so_faddr.s_addr) & 0xff);

	switch(command) {
	default: 

		for (ex_ptr = exec_list; ex_ptr; ex_ptr = ex_ptr->ex_next) {
			if (ex_ptr->ex_fport == so->so_fport &&
			    command == ex_ptr->ex_addr) {
				if (ex_ptr->ex_pty == 3) {
					so->s = -1;
					so->extra = (void *)ex_ptr->ex_exec;
					return 1;
				}
				do_pty = ex_ptr->ex_pty;
				goto do_exec;
			}
		}

		

		
	case CTL_ALIAS:
          sb->sb_cc = snprintf(sb->sb_wptr, sb->sb_datalen - (sb->sb_wptr - sb->sb_data),
                               "Error: No application configured.\r\n");
	  sb->sb_wptr += sb->sb_cc;
	  return(0);

	do_exec:
		DEBUG_MISC((dfd, " executing %s \n",ex_ptr->ex_exec));
		return(fork_exec(so, ex_ptr->ex_exec, do_pty));

#if 0
	case CTL_CMD:
	   for (tmpso = tcb.so_next; tmpso != &tcb; tmpso = tmpso->so_next) {
	     if (tmpso->so_emu == EMU_CTL &&
		 !(tmpso->so_tcpcb?
		   (tmpso->so_tcpcb->t_state & (TCPS_TIME_WAIT|TCPS_LAST_ACK))
		   :0)) {
	       
	       sb->sb_cc = sprintf(sb->sb_wptr,"Sorry, already connected.\r\n");
	       sb->sb_wptr += sb->sb_cc;
	       return 0;
	     }
	   }
	   so->so_emu = EMU_CTL;
	   ctl_password_ok = 0;
	   sb->sb_cc = sprintf(sb->sb_wptr, "Slirp command-line ready (type \"help\" for help).\r\nSlirp> ");
	   sb->sb_wptr += sb->sb_cc;
	   do_echo=-1;
	   return(2);
#endif
	}
}