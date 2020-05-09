#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/tcp.h>

int socket_connect(char *host, char *port){
	
	struct addrinfo hints, *res;    
	int sockfd;  

	 //get host info, make socket and connect it
	    memset(&hints, 0,sizeof hints);
	    hints.ai_family=AF_UNSPEC;
	    hints.ai_socktype = SOCK_STREAM;
	    getaddrinfo(host, port, &hints, &res);
	    sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	    printf("Connecting...\n");
	    connect(sockfd,res->ai_addr,res->ai_addrlen);
	    printf("Connected!\n");
	    char *header = "GET /KCID.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
	    send(sockfd,header,strlen(header),0);
	    printf("GET Sent...\n");
	return sockfd;
}

#define BUFFER_SIZE 4096

int main(int argc, char *argv){
	
char station_number;
char *port = "80";
char *host;
host = "www.n0gud.net";
char *message_fmt;
char buffer[BUFFER_SIZE];

//Creates a "menu" and asks user to choose a weather station.
printf("Choose a weather station from the following list: (Enter a-n)\n");
printf("(a) Ames\n(b) Burlington\n");
printf("(c) Cedar Rapids\n(d) Council Bluffs\n");
printf("(e) Davenport\n(f) Des Moines\n");
printf("(g) Dubuque\n(h) Fort Dodge\n");
printf("(i) Iowa City\n(j) Mason City\n");
printf("(k) Ottumwa\n(l) Sioux City\n");
printf("(m) Spencer\n(n) Waterloo\n");

int fd;

//Waits for user's choice to be a valid input.
fd = socket_connect(host, port);

do {

scanf(" %c", &station_number);
//After a-n is entered, choose the corresponding URL.
    switch(station_number){
    case 'a':
        //Get Ames URL
message_fmt = "GET /KAMW.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case 'b':
        //Get Burlington URL
message_fmt = "GET /KBRL.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'c':
	//Get Cedar Rapids URL
message_fmt = "GET /KCID.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'd':
        //Get Council Bluffs URL
message_fmt = "GET /KCFB.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'e':
        //Get Davenport URL
message_fmt = "GET /KDVN.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'f':
        //Get Des Moines URL
message_fmt = "GET /KDSM.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'g':
        //Get Dubuque URL
message_fmt = "GET /KDBQ.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'h':
        //Get Fort Dodge URL
message_fmt = "GET /KFOD.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'i':
        //Get Iowa City URL
message_fmt = "GET /KIOW.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'j':
        //Get Mason City URL
message_fmt = "GET /KMCW.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'k':
        //Get Ottumwa URL
message_fmt = "GET /KOTM.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'l':
        //Get Sioux City URL
message_fmt = "GET /KSUX.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'm':
        //Get Spencer URL
message_fmt = "GET /KSPW.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    case'n':
        //Get Waterloo URL
message_fmt = "GET /KALO.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
        break;

    default:
        printf("Invalid input. Your choice must be a-n.\n");
    break;
    }

  
} while ((station_number != 'a')&&(station_number != 'b')&&(station_number != 'c')&& 
         (station_number != 'd')&&(station_number != 'e')&&(station_number != 'f')&& 
         (station_number != 'g')&&(station_number != 'h')&&(station_number != 'i')&&
         (station_number != 'j')&&(station_number != 'k')&&(station_number != 'l')&&
         (station_number != 'm')&&(station_number != 'n'));

int byte_count;
byte_count = recv(fd,buffer,sizeof(buffer)-1,0); // <-- -1 to leave room for a null terminator
	buffer[byte_count] = 0; // <-- add the null terminator
	printf("recv()'d %d bytes of data in buf\n",byte_count);
	printf("%s",buffer);
	printf("\n");

//printf("From Server : %s", buffer); 

//Rest of main code starts here.....
//printf("Message: %s\n", message_fmt);


}// end of main
