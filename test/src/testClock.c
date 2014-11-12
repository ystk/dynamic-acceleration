#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

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

	clock_t before, after;
	struct tms tms;

	long clktck = 0;
	double diff;
	FILE *fPtr;

	int first = 1;
	
	clktck = sysconf(_SC_CLK_TCK);

	if ((fPtr = fopen("testClock.log", "w")) == NULL){
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

	printf("wait 10 sec ...\r");
	fflush(stdout);

	while(1){
retry:
		sleep(5);
		
		if ((after = times(&tms)) == -1){
			now_buf[0] = 0;
			if (get_timestr(now_buf, sizeof(now_buf)) == -1 ) {
				printf("Can't get time str!!\n");
			}

			printf("%s: Error getting times()!!\n", now_buf);
			fprintf(fPtr, "%s: Error getting times()!!\n", now_buf);
			fflush(fPtr);

			goto retry;
		}

		if (first) {
			first = 0;
		} else {
			printf("times(): past(%d) current(%d)\r", before, after);
			fflush(stdout);

			diff = (double)(after - before)/(double)clktck;

			if (diff < 4) {
				now_buf[0] = 0;
				if (get_timestr(now_buf, sizeof(now_buf)) == -1 ) {
					printf("Can't get time str!!\n");
				}

				printf("%s: Time is decreased "
					"[times(): past(%d) current(%d) diff(%d)]\n", 
					now_buf, before, after, diff);
				fprintf(fPtr, "%s: Time is decreased "
					"[times(): past(%d) current(%d) diff(%d)]\n", 
					now_buf, before, after, diff);
				fflush(fPtr);
			}
		}

		before = after;
	}

	fclose(fPtr);

	return 0;
}
