#define PEL_WRITE_ADR   0x3c8
#define PEL_DATA        0x3c9

#define I_ColorBlack(r, g, b) {outp(PEL_WRITE_ADR, 0); outp(PEL_DATA, r); outp(PEL_DATA, g); outp(PEL_DATA, b);};

#define MAXNETNODES     8
#define MAXPLAYERS      4

#define CMD_SEND    1
#define CMD_GET     2

#define RAYCOM_ID       0x12345678l

typedef struct {
    long    id;
    short   intnum;

    short   command;
    short   remotenode;
    short   datalength;

    short   numnodes;
    short   ticdup;
};
