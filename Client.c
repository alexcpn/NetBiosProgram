


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
#include <Z:\98PG202\C\NETBIOS.H>

void NETBIOS (NCB far  *ncb_ptr);
void net_delete_name(char *name);

int connect_num;
void interrupt (*int_5C_vector)(void);
struct
{
	char machine_name[16];
	}machine;
char netbios_name[16];
char machine_name2[16];
unsigned char netbios_name_number;
union REGS regs,regs;
struct SREGS sregs;
NCB delete_name_ncb;

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
struct
	{
		char msg[150];
	} struct_send;

struct
	{
		int Column[150] ;
	 }row;

NCB add_name_ncb;
NCB recv_ncb;
NCB send_ncb;
char destination[16];
char sql_message[40] ="Hi Do you get me";
int i;

void main(int argc, char *argv[])
{
	 int in ;
	clrscr();
	net_delete_name("Database_Engin2");
	int_5C_vector = getvect(0X5C);
		if(int_5C_vector ==(void far *) NULL)
	 printf("Error");
	 else
	 //printf("Net Bios Installed\n");
		i=0;
	 //  To get the Machine Name

	 regs.x.dx =FP_OFF( (void far *)&machine);
	 sregs.ds =FP_SEG( (void far *)&machine);

	 regs.x.ax =0x5E00;
	 int86x(0x21,&regs,&regs,&sregs);
	 if (regs.h.ch ==0)
			printf("Error No Machine Name\n");
	 else
	 {
			//netbios_name_number =regs.h.cl;
			//printf("The Machine Name is %s\n",machine.machine_name);
			i=0;
	 }


 //To get the user Name

 regs.h.ah =0xDC;
 int86(0x21,&regs,&regs);
 connect_num =regs.h.al;
// printf("The Connection Number is %d\n ", connect_num);

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
// printf("The User Id is %s\n",reply_buffer.object_name);


// To add a name to local name table

		strcpy(netbios_name,"Bllot3");
		while (strlen(netbios_name) < 15)
		strcat(netbios_name," ");

		memset(&add_name_ncb,0,sizeof(NCB));
		add_name_ncb.NCB_COMMAND =ADD_GROUP_NAME;
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

		 //printf("Press Any Key To Send\n");
		 //getch();



// PROCEDURE TO SEND TO ANOTHER COMPUTER

		strcpy(destination,"Database_Engin2");
		memset(&send_ncb,0,sizeof(NCB));
		send_ncb.NCB_COMMAND =SEND_DATAGRAM;
		send_ncb.NCB_NUM = add_name_ncb.NCB_NUM;
		send_ncb.NCB_BUFFER_PTR =(void far *)&machine;
		send_ncb.NCB_LENGTH =sizeof(machine);
		strcpy(send_ncb.NCB_CALLNAME,destination);
		sregs.es = FP_SEG((void far*)&send_ncb);
		regs.x.bx =FP_OFF((void far *)&send_ncb);
		int86x(0x5C,&regs,&regs,&sregs);

		while(send_ncb.NCB_CMD_CPLT == 0Xff);
		//printf("Send Successfull\n");
		if (send_ncb.NCB_CMD_CPLT != 0)
		{
			//printf("Error,Could Not Send Message\n");
			//exit(1);
		}

		// PROCEDURE TO RECEIVE TO ANOTHER COMPUTER


		memset(&recv_ncb,0,sizeof(NCB));
		recv_ncb.NCB_COMMAND =RECEIVE_DATAGRAM;
		recv_ncb.NCB_NUM = add_name_ncb.NCB_NUM;
		recv_ncb.NCB_BUFFER_PTR =(void far *)&struct_send;
		recv_ncb.NCB_LENGTH =sizeof(struct_send);

		sregs.es = FP_SEG((void far*)&recv_ncb);
		regs.x.bx =FP_OFF((void far *)&recv_ncb);
		int86x(0x5C,&regs,&regs,&sregs);

		//	printf("%d\n" ,sql_response.aircraft_count);
		//	printf("Waiting To Receive\n");



		while(recv_ncb.NCB_CMD_CPLT == 0Xff)   ;


		 if (recv_ncb.NCB_CMD_CPLT != 0)
		 {
			printf("Error,Could Not Receive Message\n");
			//exit(1);
		}



		execv(struct_send.msg,argv);
		net_delete_name("Bllot3         ");

//getch();
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
			sregs.es = FP_SEG((void far*)&delete_name_ncb);
			regs.x.bx =FP_OFF((void far *)&delete_name_ncb);
			int86x(0x5C,&regs,&regs,&sregs);
	}