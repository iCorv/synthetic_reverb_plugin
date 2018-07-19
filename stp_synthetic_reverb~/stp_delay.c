#include "stp_delay.h"

stp_delay *stp_delay_new(long _buffer_size)
{
    stp_delay *x = (stp_delay *)malloc(sizeof(stp_delay));
    x-> buffer_size = _buffer_size;
    x-> buffer = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    x-> circ_p = x-> buffer;
    x-> s = .0;
    x-> delay_in_samples = .0;
    x-> q = 0;
    return x;
}

void stp_delay_free(stp_delay *x)
{
    free(x->buffer);
    free(x);
}

void stp_delay_perform(stp_delay *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize)
{
    int i = 0;
    while(i < vectorSize)
    {
        *(x->circ_p) = in[i];
        x-> s = tapi(x-> buffer_size, x->delay_in_samples, x-> buffer, x-> circ_p);
        //out[i] = 0.5 * (in[i] + (x-> s));
        out[i] = (x-> s);
        cdelay(x->buffer_size, x->buffer, &(x->circ_p));
        i++;
    }
}

void stp_delay_setDelay(stp_delay *x, float _delay_in_samples)
{
    if (_delay_in_samples < 0 || _delay_in_samples >= ((x-> buffer_size) - 1))
        _delay_in_samples = 0;
    x->delay_in_samples = _delay_in_samples ;
}

float tap(long D, float *w, float *p, int i)                   /* usage: si = tap2(D, w, q, i); */   /* i=0,1,...,D */
{
    return w[(p - w + i) % ((D) + 1)];
}

float tapi(long D, float d, float *w, float *p)                   /* usage: sd = tapi(D, w, p, d); */
/* d = desired non-integer delay */
/* p = circular pointer to w */
{
    int i, j;
    float si, sj;
    
    i = floor(d);                       /* interpolate between si and sj */
    j = (i + 1) % ((D) + 1);                 /* if i=D, then j=0 otherwise, j=i+1 */
    
    si = tap(D, w, p, i);              /* si(n) = x(n-i) */
    sj = tap(D, w, p, j);              /* sj(n) = x(n-j) */
    //printf("%f \n", si);
    return si + ((d) - i) * (sj - si);
}

void wrap(long M, float *w, float **p)
{
    if (*p > w + M)
        *p -= M + 1;          /* when *p=w+M+1, it wraps around to *p=w */
    
    if (*p < w)
        *p += M + 1;          /* when *p=w-1, it wraps around to *p=w+M */
}

void cdelay(long D, float *w, float **p)
{
    (*p)--;                      /* decrement pointer and wrap modulo-D+1 */
    wrap(D, w, p);               /* when *p=w-1, it wraps around to *p=w+D */
}

