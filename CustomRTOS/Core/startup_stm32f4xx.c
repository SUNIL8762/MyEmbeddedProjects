extern int main(void);

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void)
{
    uint32_t size;
    uint32_t *pDst;
    uint32_t *pSrc;

    size = (uint32_t)&_edata - (uint32_t)&_sdata;

    pSrc = &_etext;
    pDst = &_sdata;

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = *pSrc++;
    }

    size = (uint32_t)&_ebss - (uint32_t)&_sbss;

    pDst = &_sbss;

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = 0;
    }

    main();
}