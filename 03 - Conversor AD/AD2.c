#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


#define SYSFS_ADC_DIR "/sys/bus/iio/devices/iio:device0"
#define MAX_BUF 64


int adc_read(unsigned int pin)
{
	int fd;
  	char buf[MAX_BUF];
   	char ch[5];

	snprintf(buf, sizeof(buf), SYSFS_ADC_DIR "/in_voltage%d_raw", pin);
	fd = open(buf, O_RDONLY);
	if (fd < 0) 
        {
		perror("adc/get-value");
        }
	read(fd, ch, 5);
        close(fd);
        return atoi(ch);
}

//--------------------------------------------------------------------------
int main()
{
    int valorAD=0;
   
    while (1)
    {
        valorAD = adc_read(3);               
        printf("Valor do AD �: %d\n", valorAD);
        usleep(1000000);
    }

    return 0;

}
