#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <bios.h>
#include <mem.h>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include <alloc.h>
#include <Z:\98PG202\c\NETBIOS.H>
#include <Z:\98PG202\c\ca\GRAPH3.H>
NCB send_ncb,delete_name_ncb;
NCB recv_ncb;
void NETBIOS (NCB far  *ncb_ptr);
	void net_delete_name(char *name) ;
char destination[16];
int connect_num;
void interrupt (*int_5C_vector)(void);
struct
	 {
	char machine_name[16];
	 }machine;
char netbios_name[16];
char *filename;
unsigned char netbios_name_number;
union REGS regs,regs;
struct SREGS sregs;
int i;
struct
	{
	char msg[150];
	}struct_send;
struct
		{
	 unsigned int request_length;
	 unsigned char subfunction;
	 unsigned char buffer_connect_num;
	}request_buffer;

struct
		 {
	unsigned int reply_length;
	unsigned long object_id;
	unsigned int object_type;
	char object_name[48];
	char login_time[7];
	int reserved;
	}reply_buffer;
char reply_buffer2[50];
NCB add_name_ncb;

void main()
{
int in ;
	clrscr();
	net_delete_name("Database_Engin2");
	int_5C_vector = getvect(0X5C);
		if(int_5C_vector ==(void far *) NULL)
	 printf("Error");
	 else
	 printf("Net Bios Installed\n");

	 //  To get the Machine Name

	 regs.x.dx =FP_OFF( (void far *)&machine);
	 sregs.ds =FP_SEG( (void far *)&machine);

	 regs.x.ax =0x5E00;
	 int86x(0x21,&regs,&regs,&sregs);
	 if (regs.h.ch ==0)
			printf("Error No Machine Name\n");
	 else
	 {
			netbios_name_number =regs.h.cl;
			printf("The Machine Name is %s\n",machine.machine_name);
	 }

 //To get the user Name

 regs.h.ah =0xDC;
 int86(0x21,&regs,&regs);
 connect_num =regs.h.al;
 printf("The Connection Number is %d\n ", connect_num);

 request_buffer.request_length =2;
 request_buffer.subfunction =0x16;
 request_buffer.buffer_connect_num =connect_num;
 reply_buffer.reply_length =61;
 regs.h.ah =0xE3;
 sregs.ds =FP_SEG( (void far *)&request_buffer);
 regs.x.si =FP_OFF( (void far *)&request_buffer);
 sregs.es =FP_SEG( (void far *)&reply_buffer);
 regs.x.di =FP_OFF( (void far *)&reply_buffer);

 int86x(0x21,&regs,&regs,&sregs);
 printf("The User Id is %s\n",reply_buffer.object_name);
 regs.h.ah =0xEA;
 regs.h.al =1;
 regs.x.bx =0;
 sregs.es =FP_SEG( (void far *)&reply_buffer2);
 regs.x.di =FP_OFF( (void far *)&reply_buffer2);
 int86x(0x21,&regs,&regs,&sregs);
 if (regs.x.bx ==0)
 printf("Not A Netware Lan\n");
 else
	printf("This is a Netware Lan\n");


// To add a name to local name table

strcpy(netbios_name,"Database_Engin2");
while (strlen(netbios_name) < 15)
		strcat(netbios_name," ");

		memset(&add_name_ncb,0,sizeof(NCB));
		add_name_ncb.NCB_COMMAND =ADD_NAME;
		strcpy(add_name_ncb.NCB_NAME,netbios_name);

		sregs.es = FP_SEG((void far*)&add_name_ncb);
		regs.x.bx =FP_OFF((void far *)&add_name_ncb);
		int86x(0x5C,&regs,&regs,&sregs);

		while(add_name_ncb.NCB_CMD_CPLT == 0xFF)
		 ;

		if(add_name_ncb.NCB_CMD_CPLT != 0)
		{
			printf("Error Could not add to name table\n");
		 }

		FrontScreen();
		P = Menu(2,menu2);
		//outtextxy(maxx/2,maxy/2,itoa(P,str,10));
		if (P==0)
		Computer(machine.machine_name);


		// PROCEDURE TO RECEIVE MACHINE NAME FROM THREE COMPUTERS

		 for(i=1;i<=3;i++)         //receiving the machine name from the
								 // computers three
	 {
		memset(&recv_ncb,0,sizeof(NCB));
		recv_ncb.NCB_COMMAND =RECEIVE_DATAGRAM;
		recv_ncb.NCB_NUM = add_name_ncb.NCB_NUM;
		recv_ncb.NCB_BUFFER_PTR =(void far *)&machine;
		recv_ncb.NCB_LENGTH =sizeof(machine);

		sregs.es = FP_SEG((void far*)&recv_ncb);
		regs.x.bx =FP_OFF((void far *)&recv_ncb);
		int86x(0x5C,&regs,&regs,&sregs);
		while(recv_ncb.NCB_CMD_CPLT == 0Xff)
		;
		switch(i)
		{
			 case 1:Computer2(machine.machine_name);
				 break;
			 case 2:Computer1(machine.machine_name);
				 break;
			 case 3:Computer3(machine.machine_name);
				 break;
		}

		 //	printf("%s\n" ,machine.machine_name);
		if (recv_ncb.NCB_CMD_CPLT != 0)
		{
			printf("Error,Could Not Receive Message\n");
			exit(1);
		}
		}

// PROCEDURE TO SEND FILE NAME TO THREE COMPUTERS

		P = Menu(3,menu1);
		//if(P==0)
		filename=Send();
		strcpy(struct_send.msg,filename);
		strcpy(destination,"Bllot3         ");
		memset(&send_ncb,0,sizeof(NCB));
		send_ncb.NCB_COMMAND =SEND_DATAGRAM;
		send_ncb.NCB_NUM = add_name_ncb.NCB_NUM;
		send_ncb.NCB_BUFFER_PTR =(void far *)&struct_send;
		send_ncb.NCB_LENGTH =sizeof(struct_send);
		strcpy(send_ncb.NCB_CALLNAME,destination);
		sregs.es = FP_SEG((void far*)&send_ncb);
		regs.x.bx =FP_OFF((void far *)&send_ncb);
		int86x(0x5C,&regs,&regs,&sregs);

		while(send_ncb.NCB_CMD_CPLT == 0Xff);

		if (send_ncb.NCB_CMD_CPLT != 0)
		{
			printf("Error,Could Not Send Message\n");

		}

		closegraph();
		delay(4000);
// PROCEDURE TO RECEIVE ACK FROM THREE COMPUTERS

/*	 for(i=1;i<=1;i++)         //receiving the machine name from the
								 // computers three
	 {
		memset(&recv_ncb,0,sizeof(NCB));
		recv_ncb.NCB_COMMAND =RECEIVE_DATAGRAM;
		recv_ncb.NCB_NUM = add_name_ncb.NCB_NUM;
		recv_ncb.NCB_BUFFER_PTR =(void far *)&machine;
		recv_ncb.NCB_LENGTH =sizeof(machine);

		sregs.es = FP_SEG((void far*)&recv_ncb);
		regs.x.bx =FP_OFF((void far *)&recv_ncb);
		int86x(0x5C,&regs,&regs,&sregs);
		while(recv_ncb.NCB_CMD_CPLT == 0Xff)
		;
	switch(i)
		{
			 case 1:Computer2(machine.machine_name);
				 break;
			 case 2:Computer1(machine.machine_name);
				 break;
			 case 3:Computer3(machine.machine_name);
				 break;
		}


		if (recv_ncb.NCB_CMD_CPLT != 0)
		{
			printf("Error,Could Not Receive Message\n");
			exit(1);
		}

	}
*/
		net_delete_name("Database_Engin2");
		exit(1);
} //End of main



	void NETBIOS (NCB far * ncb_ptr)
	{
		struct SREGS sregs;
		union REGS regs;
		sregs.es =FP_SEG(ncb_ptr);
		regs.x.bx =FP_OFF(ncb_ptr);
		int86x(0x5C,&regs,&regs,&sregs);
	}
	void net_delete_name(char *name)
	{
	 memset(&delete_name_ncb,0,sizeof(NCB));
	 delete_name_ncb.NCB_COMMAND =DELETE_NAME;
	 strcpy(delete_name_ncb.NCB_NAME,name);
	 sregs.es=FP_SEG((void far *) &delete_name_ncb);
	 regs.x.bx =FP_OFF((void far *) &delete_name_ncb);
	 int86x(0x5c,&regs,&regs,&sregs);
	 }