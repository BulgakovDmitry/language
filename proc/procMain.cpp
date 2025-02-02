#include "proc.h"
#include "procAsm.h"

int main(void)
{
    SPU* spu = spuInit();  
    asembler(spu); 
    run(spu);
    spuDelete(spu);
    DBG(SUCCESS;)
    return 0;
}
