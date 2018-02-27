# FPGA_USB_high_speed_comm
USB high speed communication with fpga using FT245 protocol

High speed usb communication protocol is configured in FPGA. The communication is mediated using FT232H chip board in FT245 usb high speed mode with speeds upto 400 Mbps actual transfer rates. The protocol and pin details are in the application note: http://www.ftdichip.com/Support/Documents/TechnicalNotes/TN_167_FIFO_Basics.pdf. 
Exact timing synchronization requirements are maintained by using the clocking the FPGA with clk out of the FT board. The purpose of this porject was to implement the high speed data transfer from PC to FPGA at very high speeds. This would prove extremely useful in cases where quick pattern updates are required. Here I am talking about my another project (https://github.com/mdnoaman/fpga_sequencer) which only uses UART communication protocol which is limited to somewhat lower speeds around 500 Kbps.

A quick solution is to store all the different patterns and trigger them one by one addressing different part of the inner block memory. However, the precious block ram which in general is quite limited would set a limit on the size of pattern data.
Among varius other possibilities like gigabit ethernet, USB3 etc. here the idea is to use widely accessible USB high speed protocol just keep simple and cost effective. An FT232H chip is available below 10 euros from ebay.
The Top.v and const.ucf files are the HDL files which is adapted for our FPGA board and communication pins. The files are self instructive and can easily be modified for different boards.

This repository also aims for PC side communication software using C++. The program is mainly adapted from the application note of FT232H chip which uses ftd2xx.h library for C++ programs. The C file is also shared along with the HDL files.
To able to successfully establish communication from PC side, you need to download the relevant files from FT232H homepage and follow the basic working instruction.txt file. I could see transfer speeds reaching above 30 MBps. An effort is going on to use Python with Tkinter package as a front end and C++ for backend development.

