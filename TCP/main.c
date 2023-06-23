#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <conio.h>
#include <string.h>

int main()
{


    struct sockaddr_in server; /*sockadder_in otomatik varolan bir struck*/
    char *message;
    char server_message[2000];
    unsigned int s; /*socketler unsigned int türündedir */
    WSADATA wsa;   /*WSADATA STRUCK TÜRÜNDE YAPI*/
    printf("\nInitializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {             /*WSAStartup ve MAKEWORD TAM ANLAMADIM */

        printf("Failed. Error Code : %d\n", WSAGetLastError());
        return 1;

    }

    printf("Initialized\n");
    s = socket(AF_INET , SOCK_STREAM , 0 );        /*AF_INET iNTERNET PROTOKULU SOCK_STREAM TCP TURU 0 PROTOKOL NUMARASI */ /*SOCKETLER UNSIGNED_INT TÜRÜNDE OLUR */
    if(s == INVALID_SOCKET)                                                 /*INVALID_SOCKET GEÇERSİZ SOKET UNSiGNED INT TÜRÜNDE*/
	{
		printf("Soket Oluşturulmadı : %d" , WSAGetLastError());
	}

	printf("Soket Olustu.\n");


	server.sin_addr.s_addr=inet_addr("127.0.0.1");      /*Serverın ip adresi*/
	server.sin_family=AF_INET;                          /*servera bağlantı şekli*/
	server.sin_port=htons(1470);                        /*port adresini little şeklinden big endiana çevirir*/
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)   /*Bağlantı kurar sockadrr özel bir struck sor !!! */
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");


	while(1){
            printf("Mesaji Giriniz");scanf("%s",message);
            if( send(s , message , strlen(message) , 0) < 0)  /*send mesaj yollama */
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

  if(recv(s , server_message , sizeof(server_message) , 0)<0)
	{
		printf("Error Server Message");
	}

	printf("Server Message:%s\n",server_message);
	if((strcmp(server_message,"123456789000000000000000000000000000"))==0){break;}
	}

    return 0;
}
