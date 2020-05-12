/*
Nick Sueppel, Keegan Hutchins, Alan Milliman
Weather Observation Retriever
Created 5/12/2020
*/

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

//Function to create the socket
int socket_connect(char *host, char *port, char *header){
	
	struct addrinfo hints, *res;    
	int sockfd;  

	 //Gets the host information, then makes and connects the socket.
	    memset(&hints, 0,sizeof hints);
	    hints.ai_family=AF_UNSPEC;
	    hints.ai_socktype = SOCK_STREAM;
	    getaddrinfo(host, port, &hints, &res);
	    sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	    printf("Connecting...\n");
	    connect(sockfd,res->ai_addr,res->ai_addrlen);
	    printf("Connected!\n");
	    send(sockfd,header,strlen(header),0);
	    printf("GET Sent...\n");
	return sockfd;
}

/*      Work-in-progress function to maximize effiency.
	
	//Would replace the set of while loops at the bottom.
char *returnParsed(int start, int end, char buffer[]){
	char *returnText[25];
	while(start < end){
		strncat(returnText, &buffer[start], 1);		
		start++;
	}
	return returnText;
}
*/

//Function for 60 second timer.
char checkAFK(){
	char station_num;
	time_t seconds;
	int startingSec = 0;
	startingSec = time(NULL);
	scanf(" %c", &station_num);
	seconds = time(NULL);
	if(startingSec+60 <= seconds){
		printf("Timer ran out...\n");
		exit(0);
	}
	return station_num;
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

do {

station_number = checkAFK();
//After a-n is entered, the corresponding weather URL is chosen.
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
message_fmt = "GET /KCBF.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
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
message_fmt = "GET /KSXK.xml HTTP/1.0\r\nHost: www.n0gud.net\r\n\r\n";
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
         (station_number != 'm')&&(station_number != 'n') && (sizeof(station_number) > 1));

int fd;
//Waits for the user's choice to be a valid input, then calls the socket function.
fd = socket_connect(host, port, message_fmt);

int byte_count;
byte_count = recv(fd,buffer,sizeof(buffer)-1,0); // <-- "-1" Leaves room for a null terminator.
	buffer[byte_count] = 0; // <-- This adds the null terminator
	//printf("recv()'d %d bytes of data in buf\n",byte_count); //Shows character count.
	//printf("%s",buffer); //Prints the XML from the buffer. 
	//printf("\n\n");
//After the information is extracted from the server, this creates a local file and stores the information.
FILE *fp;
fp = fopen ("serverinfo.txt", "w");
fputs(buffer,fp);
fclose (fp);

/* 
----- What we need to parse ------
Station – The 4 character station identifier <station_id></station_id>
Location – Description of the location ‘CR, The Eastern Iowa Airport’ <location></location>
Weather – Description of the conditions (i.e. Overcast) <weather></weather>
Wind – String with wind speed and direction held between the tags <wind_string></wind_string>
Temperature - Temp in F and C <temperature_string></temperature_string>
Humidity – Percent humidity <relative_humidity></relative_humidity>
You may include additional information held in other tags within the data  (like pressure_string, visibility_mi, etc)
*/
int index = 0;

int stationStart = 0;
int stationEnd = 0;
char stationText[10];

int locationStart = 0;
int locationEnd = 0;
char locationText[50];

int weatherStart = 0;
int weatherEnd = 0;
char weatherText[40];

int windStart = 0;
int windEnd = 0;
char windText[120];

int tempStart = 0;
int tempEnd = 0;
char tempText[40];

int humidStart = 0;
int humidEnd = 0;
char humidText[40];

while(index < byte_count-8){

	//Station Tags
	if(buffer[index] == '<' &&  buffer[index+1] == 's' && buffer[index+2] == 't' && buffer[index+3] == 'a'){
		stationStart = index+12;//12 spots after the starting point of <
	}
	if(buffer[index] == '<' &&  buffer[index+1] == '/' && buffer[index+2] == 's' && buffer[index+3] == 't' && buffer[index+4] == 'a'){
		stationEnd = index;
	}
	
	//Location Tags
	if(buffer[index] == '<' &&  buffer[index+1] == 'l' && buffer[index+2] == 'o' && buffer[index+3] == 'c'){
		locationStart = index+10;
	}
	if(buffer[index] == '<' &&  buffer[index+1] == '/' && buffer[index+2] == 'l' && buffer[index+3] == 'o' && buffer[index+4] == 'c'){
		locationEnd = index;
	}
	
	//Weather Tags
	if(buffer[index] == '<' &&  buffer[index+1] == 'w' && buffer[index+2] == 'e' && buffer[index+3] == 'a'){
		weatherStart = index+9;
		//printf("Received Start tag at %i\n", index);
	}
	if(buffer[index] == '<' &&  buffer[index+1] == '/' && buffer[index+2] == 'w' && buffer[index+3] == 'e' && buffer[index+4] == 'a'){
		weatherEnd = index;
		//printf("Received End tag at %i\n", index);
	}
	
	//Wind Tags
	if(buffer[index] == '<' &&  buffer[index+1] == 'w' && buffer[index+2] == 'i' && buffer[index+3] == 'n'  && buffer[index+4] == 'd'  && buffer[index+5] == '_'  && buffer[index+6] == 's'){
		windStart = index+13;
	}
	if(buffer[index] == '<' &&  buffer[index+1] == '/' && buffer[index+2] == 'w' && buffer[index+3] == 'i' && buffer[index+4] == 'n' && buffer[index+5] == 'd' && buffer[index+6] == '_' && buffer[index+7] == 's'){
		windEnd = index;
	}
	
	//Temperature Tags
	if(buffer[index] == '<' &&  buffer[index+1] == 't' && buffer[index+2] == 'e' && buffer[index+3] == 'm'  && buffer[index+4] == 'p'  && buffer[index+5] == 'e'  && buffer[index+6] == 'r'){
		tempStart = index+20;
	}
	if(buffer[index] == '<' &&  buffer[index+1] == '/' && buffer[index+2] == 't' && buffer[index+3] == 'e' && buffer[index+4] == 'm' && buffer[index+5] == 'p' && buffer[index+6] == 'e' && buffer[index+7] == 'r'){
		tempEnd = index;
	}
	
	//Humidity Tags
	if(buffer[index] == '<' &&  buffer[index+1] == 'r' && buffer[index+2] == 'e' && buffer[index+3] == 'l'  && buffer[index+4] == 'a'){
		humidStart = index+19;
	}
	if(buffer[index] == '<' &&  buffer[index+1] == '/' && buffer[index+2] == 'r' && buffer[index+3] == 'e' && buffer[index+4] == 'l' && buffer[index+5] == 'a'){
		humidEnd = index;
	}
	
index++;
}
//stationText = returnParsed(stationStart, stationEnd, buffer); //work-in-progress function call.
while(stationStart < stationEnd){
	//Concatenate string
	strncat(stationText, &buffer[stationStart], 1); 
	stationStart++;
}
while(locationStart < locationEnd){
	//Concatenate string
	strncat(locationText, &buffer[locationStart], 1); 
	locationStart++;
}
while(weatherStart < weatherEnd){
	//Concatenate string
	strncat(weatherText, &buffer[weatherStart], 1); 
	weatherStart++;
}
while(windStart < windEnd){
	//Concatenate string
	strncat(windText, &buffer[windStart], 1); 
	windStart++;
}
while(tempStart < tempEnd){
	//Concatenate string
	strncat(tempText, &buffer[tempStart], 1); 
	tempStart++;
}
while(humidStart < humidEnd){
	//Concatenate string
	strncat(humidText, &buffer[humidStart], 1); 
	humidStart++;
}
printf("Station: %s\n", stationText);
printf("Location: %s\n", locationText);
printf("Weather: %s\n", weatherText);
printf("Wind: %s\n", windText);
printf("Temperature: %s\n", tempText);
printf("Humidity: %s\n", humidText);

}//End of main
