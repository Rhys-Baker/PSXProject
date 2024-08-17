#include "spu.h"
#include "ps1/registers.h"

void initSPU(void) {
    BIU_DEV4_CTRL = 0x200931e1; // Configure bus

    SPU_CTRL = SPU_CTRL_CDDA | SPU_CTRL_UNMUTE | SPU_CTRL_ENABLE;
    SPU_MASTER_VOL_L = 0x3fff;
    SPU_MASTER_VOL_R = 0x3fff;
    SPU_CDDA_VOL_L = 0x7fff;
    SPU_CDDA_VOL_R = 0x7fff;
}