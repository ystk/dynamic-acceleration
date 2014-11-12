#include <stdio.h>
#include <string.h>
#include <time.h>

#define	BUFFERSIZE 60

int get_timestr(char *buff, int size)
{
	time_t now;
	struct tm *now_time;

	if(time(&now) == (time_t)(-1)){
		printf("Unable to retrieve current time\n");
		return -1;
	}

	if ((now_time = localtime(&now)) == NULL) {
		printf("Unable to transform date and time to broken-down time or ASCII\n");
		return -1;
	}

	if ((strftime(buff, size, "%x %X", now_time)) == 0) {
		printf("Unable to format date and time\n");
		return -1;
	}

	return 0;
}

int main(){
	FILE *file;
	char before[BUFFERSIZE]="none\n", current[BUFFERSIZE];

	if ((file = fopen("testReadWrite.log", "a+")) == NULL) {
		printf("File could not be opened. \n");
		return -1;
	}
	  
	if (get_timestr(current, sizeof(current)) == -1 ) {
		printf("Can't get time str!!\n");
		return -1;
	}

	while (1) {
		fgets(before, sizeof(before), file);
		if (feof(file))
			break;
	}

	printf("The previous time update was %s", before);
	printf("The current time is %s\n", current);

	fprintf(file, "%s\n", current);
 
	fclose(file);

	return 0;
}
