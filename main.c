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

int socket_connect(char *host, in_port_t port){
	struct hostent *hp;
	struct sockaddr_in addr;
	int on = 1, sock;     

	if((hp = gethostbyname(host)) == NULL){
		herror("gethostbyname");
		exit(1);
	}
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);

	//Assigning Port
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	//	
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // socket create and varification
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

	if(sock == -1){ //if this passes, the socket creation failed..
		perror("setsockopt");
		exit(1);
	}
	
	if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		exit(1);

	}
	return sock;
}

#define BUFFER_SIZE 1024

int main(int argc, char *argv){
	
char station_number;
int portno = 80;
char *host;
host = "w1.weather.gov";
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
fd = socket_connect(host, portno);

do {

scanf(" %c", &station_number);
//After a-n is entered, choose the corresponding URL.
    switch(station_number){
    case 'a':
        //Get Ames URL
message_fmt = "GET /xml/current_obs/KAMW.rss HTTP/1.0\r\nHost: www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case 'b':
        //Get Burlington URL
message_fmt = "GET /xml/current_obs/KBRL.rss HTTP/1.0\r\nHost: www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case'c':
	//Get Cedar Rapids URL
message_fmt = "GET /xml/current_obs/KCID.rss HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case'd':
        //Get Council Bluffs URL
message_fmt = "GET /xml/current_obs/KCBF.rss HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case'e':
        //Get Davenport URL
message_fmt = "GET /xml/current_obs/KDVN.rss HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case'f':
        //Get Des Moines URL
message_fmt = "GET /xml/current_obs/KDSM.rss HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case'g':
        //Get Dubuque URL
message_fmt = "GET /xml/current_obs/KDBQ.rss HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case'h':
        //Get Fort Dodge URL
message_fmt = "GET /xml/current_obs/KFOD.rss HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case'i':
        //Get Iowa City URL
message_fmt = "GET /xml/current_obs/KIOW.rss HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case'j':
        //Get Mason City URL
message_fmt = "GET /xml/current_obs/KMCW.rss HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case'k':
        //Get Ottumwa URL
message_fmt = "GET /xml/current_obs/KOTM.rss HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case'l':
        //Get Sioux City URL
message_fmt = "GET /xml/current_obs/KSUX.rss HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
        break;

    case'm':
        //Get Spencer URL
message_fmt = "GET /xml/current_obs/KSPW.rss HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent:/1.0\r\nAccept:*/*";
        break;

    case'n':
        //Get Waterloo URL
message_fmt = "GET /xml/current_obs/KALO.xml HTTP/1.0\r\nHost:www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept:*/*";
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


write(fd, message_fmt, strlen(message_fmt)); // write(fd, char[]*, len);
read(fd, buffer, sizeof(buffer)); 
/*read will read up to nbytes bytes of data into memory starting at buf. It returns the
number of bytes actually read, which may very well be less than nbytes. The case in
which read returns fewer than nbytes is often called a “short read” and is a common
source of errors. If read returns 0, this indicates an end of file. If it returns −1, this
indicates an error.*/

printf("From Server : %s", buffer); 

//Rest of main code starts here.....
printf("Message: %s\n", message_fmt);


}// end of main


//SCRATCHED THIS FOR NOW.
/*
	char state[3]; //includes \n
	printf("Please enter your State\nEX. (IA)\n");
	scanf("%s", state);	//Have them enter what state they want to display.
	printf("You entered: %s\n", state); //displays state
	
	// first what are we going to send and where are we going to send it? 
    int portno =        80;
    char *host;
    host = "https://w1.weather.gov/xml/current_obs/seek.php?state=ia&Find=Find\n";
    char *message_fmt = "GET /xml/current_obs/KCID.xml HTTP/1.0\r\nHost: www.weather.gov\r\nConnection: close\r\nUser-Agent: /1.0\r\nAccept: ";
    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total;
    char message[1024],response[4096];
    // fill in the parameters 
    sprintf(message,message_fmt,argv[1],argv[2]);
    printf("Request:\n%s\n",message);
    // create the socket 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");
    // lookup the ip address 
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");
    // fill in the structure 
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);
    // connect the socket 
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    // send the request //
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);
    // receive the response 
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0)
            error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);
    if (received == total)
        error("ERROR storing complete response from socket");
    // close the socket
    close(sockfd);
    // process response
    printf("Response:\n%s\n",response);
*/
