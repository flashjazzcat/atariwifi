#include <atari.h>
#include <stdio.h>
#include "sio.h"
#include "die.h"

unsigned char num_networks[4];

void main(void)
{
  printf("Scanning Networks:\n\n");
  OS.dcb.ddevic=0x70;
  OS.dcb.dunit=1;
  OS.dcb.dcomnd=0xFD; // do scan
  OS.dcb.dstats=0x40; // Peripheral->Computer
  OS.dcb.dbuf=num_networks;
  OS.dcb.dtimlo=0x0F; // 15 second timeout
  OS.dcb.dbyt=4;      // 4 byte response
  OS.dcb.daux=0;
  siov();

  printf("DSTATS: %d\n",OS.dcb.dstats);
  printf("Num networks: %d\n",num_networks[0]);

  printf("raw packet: %02x %02x %02x %02x",num_networks[0], num_networks[1], num_networks[2], num_networks[3]);
  die();
  
}
