#include <stdint.h>

extern int main(void);

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void)
{
    uint32_t *pSrc;
    uint32_t *pDst;

    pSrc = &_etext;
    pDst = &_sdata;

    while(pDst < &_edata)
    {
        *pDst++ = *pSrc++;
    }

    pDst = &_sbss;

    while(pDst < &_ebss)
    {
        *pDst++ = 0;
    }

    main();

    while(1);
}