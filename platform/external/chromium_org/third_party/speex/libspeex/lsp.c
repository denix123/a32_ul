/*---------------------------------------------------------------------------*\
Original copyright
	FILE........: lsp.c
	AUTHOR......: David Rowe
	DATE CREATED: 24/2/93

Heavily modified by Jean-Marc Valin (c) 2002-2006 (fixed-point, 
                       optimizations, additional functions, ...)

   This file contains functions for converting Linear Prediction
   Coefficients (LPC) to Line Spectral Pair (LSP) and back. Note that the
   LSP coefficients are not in radians format but in the x domain of the
   unit circle.

   Speex License:

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   
   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
   
   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
   
   - Neither the name of the Xiph.org Foundation nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
   
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <math.h>
#include "lsp.h"
#include "stack_alloc.h"
#include "math_approx.h"

#ifndef M_PI
#define M_PI           3.14159265358979323846  
#endif

#ifndef NULL
#define NULL 0
#endif

#ifdef FIXED_POINT

#define FREQ_SCALE 16384

#define ANGLE2X(a) (SHL16(spx_cos(a),2))

#define X2ANGLE(x) (spx_acos(x))

#ifdef BFIN_ASM
#include "lsp_bfin.h"
#endif

#else


#define FREQ_SCALE 1.
#define ANGLE2X(a) (spx_cos(a))
#define X2ANGLE(x) (acos(x))

#endif



#ifdef FIXED_POINT

#ifndef OVERRIDE_CHEB_POLY_EVA
static inline spx_word32_t cheb_poly_eva(
  spx_word16_t *coef, 
  spx_word16_t     x, 
  int              m, 
  char         *stack
)
{
    int i;
    spx_word16_t b0, b1;
    spx_word32_t sum;

    
    if (x>16383)
       x = 16383;
    if (x<-16383)
       x = -16383;

    
    b1=16384;
    b0=x;

    
    sum = ADD32(EXTEND32(coef[m]), EXTEND32(MULT16_16_P14(coef[m-1],x)));
    for(i=2;i<=m;i++)
    {
       spx_word16_t tmp=b0;
       b0 = SUB16(MULT16_16_Q13(x,b0), b1);
       b1 = tmp;
       sum = ADD32(sum, EXTEND32(MULT16_16_P14(coef[m-i],b0)));
    }
    
    return sum;
}
#endif

#else

static float cheb_poly_eva(spx_word32_t *coef, spx_word16_t x, int m, char *stack)
{
   int k;
   float b0, b1, tmp;

   
   b0=0; 
   b1=0; 

   x*=2;

   
   for(k=m;k>0;k--)
   {
      tmp=b0;                           
      b0=x*b0-b1+coef[m-k];    
      b1=tmp;                           
   }

   return(-b1+.5*x*b0+coef[m]);
}
#endif


#ifdef FIXED_POINT
#define SIGN_CHANGE(a,b) (((a)&0x70000000)^((b)&0x70000000)||(b==0))
#else
#define SIGN_CHANGE(a,b) (((a)*(b))<0.0)
#endif


int lpc_to_lsp (spx_coef_t *a,int lpcrdr,spx_lsp_t *freq,int nb,spx_word16_t delta, char *stack)


{
    spx_word16_t temp_xr,xl,xr,xm=0;
    spx_word32_t psuml,psumr,psumm,temp_psumr;
    int i,j,m,flag,k;
    VARDECL(spx_word32_t *Q);                 	
    VARDECL(spx_word32_t *P);
    VARDECL(spx_word16_t *Q16);         
    VARDECL(spx_word16_t *P16);
    spx_word32_t *px;                	
    spx_word32_t *qx;
    spx_word32_t *p;
    spx_word32_t *q;
    spx_word16_t *pt;                	
    int roots=0;              	
    flag = 1;                	
    m = lpcrdr/2;            	

    
    ALLOC(Q, (m+1), spx_word32_t);
    ALLOC(P, (m+1), spx_word32_t);


    px = P;                      
    qx = Q;
    p = px;
    q = qx;

#ifdef FIXED_POINT
    *px++ = LPC_SCALING;
    *qx++ = LPC_SCALING;
    for(i=0;i<m;i++){
       *px++ = SUB32(ADD32(EXTEND32(a[i]),EXTEND32(a[lpcrdr-i-1])), *p++);
       *qx++ = ADD32(SUB32(EXTEND32(a[i]),EXTEND32(a[lpcrdr-i-1])), *q++);
    }
    px = P;
    qx = Q;
    for(i=0;i<m;i++)
    {
       *px = PSHR32(*px,2);
       *qx = PSHR32(*qx,2);
       px++;
       qx++;
    }
    
    P[m] = PSHR32(P[m],3);
    Q[m] = PSHR32(Q[m],3);
#else
    *px++ = LPC_SCALING;
    *qx++ = LPC_SCALING;
    for(i=0;i<m;i++){
       *px++ = (a[i]+a[lpcrdr-1-i]) - *p++;
       *qx++ = (a[i]-a[lpcrdr-1-i]) + *q++;
    }
    px = P;
    qx = Q;
    for(i=0;i<m;i++){
       *px = 2**px;
       *qx = 2**qx;
       px++;
       qx++;
    }
#endif

    px = P;             	
    qx = Q;


    ALLOC(P16, m+1, spx_word16_t);
    ALLOC(Q16, m+1, spx_word16_t);

    for (i=0;i<m+1;i++)
    {
       P16[i] = P[i];
       Q16[i] = Q[i];
    }


    xr = 0;             	
    xl = FREQ_SCALE;               	

    for(j=0;j<lpcrdr;j++){
	if(j&1)            	
	    pt = Q16;
	else
	    pt = P16;

	psuml = cheb_poly_eva(pt,xl,m,stack);	
	flag = 1;
	while(flag && (xr >= -FREQ_SCALE)){
           spx_word16_t dd;
           
#ifdef FIXED_POINT
           dd = MULT16_16_Q15(delta,SUB16(FREQ_SCALE, MULT16_16_Q14(MULT16_16_Q14(xl,xl),14000)));
           if (psuml<512 && psuml>-512)
              dd = PSHR16(dd,1);
#else
           dd=delta*(1-.9*xl*xl);
           if (fabs(psuml)<.2)
              dd *= .5;
#endif
           xr = SUB16(xl, dd);                        	
	    psumr = cheb_poly_eva(pt,xr,m,stack);
	    temp_psumr = psumr;
	    temp_xr = xr;


	    if(SIGN_CHANGE(psumr,psuml))
            {
		roots++;

		psumm=psuml;
		for(k=0;k<=nb;k++){
#ifdef FIXED_POINT
		    xm = ADD16(PSHR16(xl,1),PSHR16(xr,1));        	
#else
                    xm = .5*(xl+xr);        	
#endif
		    psumm=cheb_poly_eva(pt,xm,m,stack);
		    
		    if(!SIGN_CHANGE(psumm,psuml))
                    {
			psuml=psumm;
			xl=xm;
		    } else {
			psumr=psumm;
			xr=xm;
		    }
		}

	       
	       freq[j] = X2ANGLE(xm);
	       xl = xm;
	       flag = 0;       		
	    }
	    else{
		psuml=temp_psumr;
		xl=temp_xr;
	    }
	}
    }
    return(roots);
}


#ifdef FIXED_POINT

void lsp_to_lpc(spx_lsp_t *freq,spx_coef_t *ak,int lpcrdr, char *stack)
{
    int i,j;
    spx_word32_t xout1,xout2,xin;
    spx_word32_t mult, a;
    VARDECL(spx_word16_t *freqn);
    VARDECL(spx_word32_t **xp);
    VARDECL(spx_word32_t *xpmem);
    VARDECL(spx_word32_t **xq);
    VARDECL(spx_word32_t *xqmem);
    int m = lpcrdr>>1;

    /* 
    
       Reconstruct P(z) and Q(z) by cascading second order polynomials
       in form 1 - 2cos(w)z(-1) + z(-2), where w is the LSP frequency.
       In the time domain this is:

       y(n) = x(n) - 2cos(w)x(n-1) + x(n-2)
    
       This is what the ALLOCS below are trying to do:

         int xp[m+1][lpcrdr+1+2]; // P matrix in QIMP
         int xq[m+1][lpcrdr+1+2]; // Q matrix in QIMP

       These matrices store the output of each stage on each row.  The
       final (m-th) row has the output of the final (m-th) cascaded
       2nd order filter.  The first row is the impulse input to the
       system (not written as it is known).

       The version below takes advantage of the fact that a lot of the
       outputs are zero or known, for example if we put an inpulse
       into the first section the "clock" it 10 times only the first 3
       outputs samples are non-zero (it's an FIR filter).
    */

    ALLOC(xp, (m+1), spx_word32_t*);
    ALLOC(xpmem, (m+1)*(lpcrdr+1+2), spx_word32_t);

    ALLOC(xq, (m+1), spx_word32_t*);
    ALLOC(xqmem, (m+1)*(lpcrdr+1+2), spx_word32_t);
    
    for(i=0; i<=m; i++) {
      xp[i] = xpmem + i*(lpcrdr+1+2);
      xq[i] = xqmem + i*(lpcrdr+1+2);
    }

    

    ALLOC(freqn, lpcrdr, spx_word16_t);
    for (i=0;i<lpcrdr;i++) 
       freqn[i] = ANGLE2X(freq[i]);

    #define QIMP  21   

    xin = SHL32(EXTEND32(1), (QIMP-1)); 
   
    
    
    for(i=0;i<=m;i++) {
     xp[i][1] = 0;
     xp[i][2] = xin;
     xp[i][2+2*i] = xin;
     xq[i][1] = 0;
     xq[i][2] = xin;
     xq[i][2+2*i] = xin;
    }

    

    xp[1][3] = -MULT16_32_Q14(freqn[0],xp[0][2]);
    xq[1][3] = -MULT16_32_Q14(freqn[1],xq[0][2]);

    xout1 = xout2 = 0;

    

    for(i=1;i<m;i++) {

      for(j=1;j<2*(i+1)-1;j++) {
	mult = MULT16_32_Q14(freqn[2*i],xp[i][j+1]);
	xp[i+1][j+2] = ADD32(SUB32(xp[i][j+2], mult), xp[i][j]);
	mult = MULT16_32_Q14(freqn[2*i+1],xq[i][j+1]);
	xq[i+1][j+2] = ADD32(SUB32(xq[i][j+2], mult), xq[i][j]);
      }

      

      mult = MULT16_32_Q14(freqn[2*i],xp[i][j+1]);
      xp[i+1][j+2] = SUB32(xp[i][j], mult);
      mult = MULT16_32_Q14(freqn[2*i+1],xq[i][j+1]);
      xq[i+1][j+2] = SUB32(xq[i][j], mult);
    }

    

    for(j=1;j<=lpcrdr;j++) {
      int shift = QIMP-13;

      
      a = PSHR32(xp[m][j+2] + xout1 + xq[m][j+2] - xout2, shift); 
      xout1 = xp[m][j+2];
      xout2 = xq[m][j+2];
      
      

      if (a < -32767) a = -32767;
      if (a > 32767) a = 32767;
      ak[j-1] = (short)a;
     
    }

}

#else

void lsp_to_lpc(spx_lsp_t *freq,spx_coef_t *ak,int lpcrdr, char *stack)


{
    int i,j;
    float xout1,xout2,xin1,xin2;
    VARDECL(float *Wp);
    float *pw,*n1,*n2,*n3,*n4=NULL;
    VARDECL(float *x_freq);
    int m = lpcrdr>>1;

    ALLOC(Wp, 4*m+2, float);
    pw = Wp;

    

    for(i=0;i<=4*m+1;i++){       	
	*pw++ = 0.0;
    }

    

    pw = Wp;
    xin1 = 1.0;
    xin2 = 1.0;

    ALLOC(x_freq, lpcrdr, float);
    for (i=0;i<lpcrdr;i++)
       x_freq[i] = ANGLE2X(freq[i]);


    for(j=0;j<=lpcrdr;j++){
       int i2=0;
	for(i=0;i<m;i++,i2+=2){
	    n1 = pw+(i*4);
	    n2 = n1 + 1;
	    n3 = n2 + 1;
	    n4 = n3 + 1;
	    xout1 = xin1 - 2.f*x_freq[i2] * *n1 + *n2;
	    xout2 = xin2 - 2.f*x_freq[i2+1] * *n3 + *n4;
	    *n2 = *n1;
	    *n4 = *n3;
	    *n1 = xin1;
	    *n3 = xin2;
	    xin1 = xout1;
	    xin2 = xout2;
	}
	xout1 = xin1 + *(n4+1);
	xout2 = xin2 - *(n4+2);
	if (j>0)
	   ak[j-1] = (xout1 + xout2)*0.5f;
	*(n4+1) = xin1;
	*(n4+2) = xin2;

	xin1 = 0.0;
	xin2 = 0.0;
    }

}
#endif


#ifdef FIXED_POINT

void lsp_enforce_margin(spx_lsp_t *lsp, int len, spx_word16_t margin)
{
   int i;
   spx_word16_t m = margin;
   spx_word16_t m2 = 25736-margin;
  
   if (lsp[0]<m)
      lsp[0]=m;
   if (lsp[len-1]>m2)
      lsp[len-1]=m2;
   for (i=1;i<len-1;i++)
   {
      if (lsp[i]<lsp[i-1]+m)
         lsp[i]=lsp[i-1]+m;

      if (lsp[i]>lsp[i+1]-m)
         lsp[i]= SHR16(lsp[i],1) + SHR16(lsp[i+1]-m,1);
   }
}


void lsp_interpolate(spx_lsp_t *old_lsp, spx_lsp_t *new_lsp, spx_lsp_t *interp_lsp, int len, int subframe, int nb_subframes)
{
   int i;
   spx_word16_t tmp = DIV32_16(SHL32(EXTEND32(1 + subframe),14),nb_subframes);
   spx_word16_t tmp2 = 16384-tmp;
   for (i=0;i<len;i++)
   {
      interp_lsp[i] = MULT16_16_P14(tmp2,old_lsp[i]) + MULT16_16_P14(tmp,new_lsp[i]);
   }
}

#else

void lsp_enforce_margin(spx_lsp_t *lsp, int len, spx_word16_t margin)
{
   int i;
   if (lsp[0]<LSP_SCALING*margin)
      lsp[0]=LSP_SCALING*margin;
   if (lsp[len-1]>LSP_SCALING*(M_PI-margin))
      lsp[len-1]=LSP_SCALING*(M_PI-margin);
   for (i=1;i<len-1;i++)
   {
      if (lsp[i]<lsp[i-1]+LSP_SCALING*margin)
         lsp[i]=lsp[i-1]+LSP_SCALING*margin;

      if (lsp[i]>lsp[i+1]-LSP_SCALING*margin)
         lsp[i]= .5f* (lsp[i] + lsp[i+1]-LSP_SCALING*margin);
   }
}


void lsp_interpolate(spx_lsp_t *old_lsp, spx_lsp_t *new_lsp, spx_lsp_t *interp_lsp, int len, int subframe, int nb_subframes)
{
   int i;
   float tmp = (1.0f + subframe)/nb_subframes;
   for (i=0;i<len;i++)
   {
      interp_lsp[i] = (1-tmp)*old_lsp[i] + tmp*new_lsp[i];
   }
}

#endif
