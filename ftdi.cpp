#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "ftd2xx.h"
int main(int argc, char* argv[])
{
FT_HANDLE fthandle;
FT_STATUS status;
 status = FT_Open(0, &fthandle);

if(status != FT_OK)
{
printf("open status not ok %d\n", status);
return 0;
}
status = FT_ResetDevice(fthandle);
 if(status != FT_OK)
 printf("reset status not ok %d\n", status);
UCHAR Mask = 0xFF; // Set data bus to outputs
UCHAR mode = 0;
UCHAR mode1 = 0x40; // Configure FT2232H into 0x40 Sync FIFO mode
status = FT_SetBitMode(fthandle, Mask, mode); // reset MPSSE
status = FT_SetBitMode(fthandle, Mask, mode1); // configure FT2232H into Sync FIFO mode
if(status != FT_OK)
 printf("mode status not ok %d\n", status);
DWORD data_out = 0xAA;
DWORD data_written;
INT loop;
UCHAR data_buf[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0b11000100};

clock_t t = clock();
for (loop=1;loop<10;loop++)
{
status = FT_Write(fthandle, &data_buf, sizeof(data_buf), &data_written);
//printf("loop number %d\n", loop);
}

t = clock() - t;

float tm = (float)t/CLOCKS_PER_SEC;
int pkt_sz = data_written;
int file_sz = data_written*loop/(1024*1024);
float rate = (float) file_sz/tm;


//printf("file size %d  (%f MBps).\n",data_written,CLOCKS_PER_SEC);
 if(status != FT_OK)
 printf("status not ok %d\n", status);
 else
 printf("output data \n");
printf ("It took %d clicks (%f seconds).\n",t,tm);
printf("packet size = %d Byte  .\n",pkt_sz);
printf("total file size = %d MByte  .\n",file_sz);
printf("Data transfer rate = ");
printf("%.2f",rate);
printf("MBps\n");


 status = FT_Close(fthandle);
 return 0;
}