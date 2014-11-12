#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define BUFFSIZE	256

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

int main()
{
	char now_buf[BUFFSIZE];
	struct timeval before, after;
	long diff;
	FILE *fPtr;

	int first = 1;
	
	if ((fPtr = fopen("testTime.log", "w")) == NULL){
		printf("Unable to open file\n");
		return -1;
	}

	now_buf[0] = 0;	
	if (get_timestr(now_buf, sizeof(now_buf)) == -1 ) {
		printf("Can't get time str!!\n");
		return -1;
	}

	printf("Test started...  %s\n", now_buf);
	fprintf(fPtr, "Test started...	%s\n", now_buf);
	fflush(fPtr);

	printf("wait 2 sec ...\r");
	fflush(stdout);

	while(1){
retry:
		sleep(1);
		
		if ((gettimeofday(&after, NULL)) == -1){
			now_buf[0] = 0;	
			if (get_timestr(now_buf, sizeof(now_buf)) == -1 ) {
				printf("Can't get time str!!\n");
			}

			printf("%s: Error getting gettimeofdsy()!!\n", now_buf);
			fprintf(fPtr, "%s: Error getting gettimeofday()!!\n", now_buf);
			fflush(fPtr);

			goto retry;
		}

		if (first) {
			first = 0;
		} else {
			printf("gettimeoftimes(): past(%d) current(%d)\r", before.tv_sec, after.tv_sec);
			fflush(stdout);

			diff = after.tv_sec - before.tv_sec;

			if (diff < 1) {
				now_buf[0] = 0;	
				if (get_timestr(now_buf, sizeof(now_buf)) == -1 ) {
					printf("Can't get time str!!\n");
				}

				printf("%s: Time is decreased "
					"[gettimeofday(): past(%d) current(%d) diff(%d)]\n", 
					now_buf, before.tv_sec, after.tv_sec, diff);
				fprintf(fPtr, "%s: Time is decreased "
					"[gettimeofday(): past(%d) current(%d) diff(%d)]\n", 
					now_buf, before.tv_sec, after.tv_sec, diff);
				fflush(fPtr);
			}
		}

		before = after;
	}

	fclose(fPtr);

	return 0;
}
