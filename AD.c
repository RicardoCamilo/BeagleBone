#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SYSFS_ADC_DIR "/sys/bus/iio/devices/iio:device0"
#define MAX_BUF 64


int main()
{

    int fd;
    char buf[MAX_BUF];
    char ch0[5];


    while(1)
    {
        snprintf(buf, sizeof(buf), SYSFS_ADC_DIR "/in_voltage%d_raw", 0);
        fd = open(buf, O_RDONLY);
        read(fd, ch0, 4);
	printf("Valor do AD é: %d\n", atoi(ch0));
        close(fd);
        usleep(1000000);
    }

    return 0;
}
