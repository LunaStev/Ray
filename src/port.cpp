#include "raynet.h"
#include "sersetup.h"

#include "ser_frch.h"

void jump_start(void);

void interrupt isr_8250 (void);
void interrupt isr_16550 (void);

union   REGS    regs;
struct  SREGS   sregs;

que_t           inque, outque;

int                     uart;
enum {UART_8250, UART_16550} uart_type;
int                     irq;

int                     modem_starus = -1;
int                     line_status = -1;

void interrupt(*oldirqvect)(void);
int                     irqintnum;

int                     comport;

int                     baudbits;

void GetUart (void) {

}