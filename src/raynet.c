#include "raynet.h"
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <dos.h>

#include "ser_frch.h"

#define Ray

extern  int      myargc;
extern  char    **myargv;

raycom_t    raycom;
int         vectorishooked;


int CheckParm(char *check) {
    int     i;

    for(i = 1; i<myargc; i++)
        if( !stricmp(check, myargv[i]) )
            return i;
    return 0;
}

void LunchRay(void) {
    char    *newargs[99];
    char    aadrstring[10];
    long    flatadr;
    int     p;
    unsigned char   far     *vector;

    raycom.id = RAYCOM_ID;

    p = CheckParm("-vector");

    if(p) {
        raycom.intnum = sscanf("0x%x", _argv[p + 1]);
    } else {
        for(raycom.intnum = 0x60; raycom.intnum <= 0x66; raycom.intnum++) {
            vector = *(char far * far *)(raycom.intnum * 4);
            if( !vector || *vector == 0xcf )
                break;
        } if(raycom.intnum == 0x67) {
            printf(STR_WARNING);
            raycom.intnum = 0x66;
        }
    }

    printf(STR_COMM"\n", raycom.intnum);

    oldrayvect = getvect(raycom.intnum);
    setvect(raycom.intnum, NetISR);
    vectorishooked = 1;

    memcpy(newargs, myargv, (myargc + 1) * 2);
    newargs[myargc] = "-net";
    flatadr = (long)_DS*16 + (unsigned) & raycom;
    sprintf(adrstring, "%lu", flatadr);
    newargs[myargc + 1] = adrstring;
    newargs[myargc + 2] = NULL;

    if(!access("ray.exe", 0))
        spawnv(P_WAIT, "ray");

    #ifdef Ray
    printf(STR_RETURNED"\n");
    #else
    printf("Returned from DOOM\n");
    #endif
}