#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

 /*
 * ./ledtest /dev/100ask_led0 on
 * ./ledtest /dev/100ask_led0 off
 */


int main(int argc, char **argv)
{
	int fd;
	char status = 0;
	
	if(argc != 3)
	{
		printf("Usage:%s <dev> <on/off>\n", argv[0]);
		return -1;
	}
	else
	{
		fd = open("argv[1]", O_RDWR);
		if (fd < 0)
		{
			printf("open false!!\n");
			return -1;
		}
		if(strcmp(argv[2], "on") == 0)
		{
			status = 1;
		}
		write(fd, &status, 1);	
	}
	
	return 0;
}

