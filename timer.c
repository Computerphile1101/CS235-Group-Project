
#include <stdio.h>
#include <time.h>

time_t seconds;

int startingSec = 0;
char testInput[25];

void checkAFK();

int main(){ 

checkAFK(); //how to call it
return(0); 
}
void checkAFK(){
	startingSec = time(NULL);
	scanf(" %s", testInput);
	seconds = time(NULL);
	if(startingSec+60 <= seconds){
		printf("Timer ran out...\n");
	}
}





