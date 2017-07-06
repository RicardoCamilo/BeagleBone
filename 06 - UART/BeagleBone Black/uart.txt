#include <iostream>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <sys/types.h>


using namespace std;


#define SYSFS_uart4_DIR "/dev/ttyO4"
#define MAX_BUF 64

int32_t i32_read_bytes = 0;
int32_t i32_written_bytes = 0;

int32_t i32_RW_bytes = 0;
int32_t configUART(int32_t);
int32_t openUART(const char*);


int32_t main (int argc, char *argv[])
{
	uint32_t count=0;
	char c_TX_buf[MAX_BUF];
	sprintf(c_TX_buf, "Era um vez, em uma aldeia bem distante..." );
 
	char c_RX_buf[MAX_BUF]="";
	int uart4 = openUART(SYSFS_uart4_DIR);

        if(uart4 == -1)
           cout << "Erro ao tentar abrir a uart4...\n";

	configUART(uart4);
   

	for(count=0; count <= 20; count++)
	{
	    i32_read_bytes = write(uart4, c_TX_buf, MAX_BUF);
            cout << "Bytes escritos - write(): " << i32_read_bytes << " = " << c_TX_buf << endl;  
	    usleep(1000000);

            i32_written_bytes = read(uart4, c_RX_buf, MAX_BUF);
	    cout << "Bytes lidos - read(): " << i32_written_bytes << " = " << c_RX_buf << endl;
	   
  	    usleep(1000000);
	
  	    close(uart4);
	    int uart4 = openUART(SYSFS_uart4_DIR);
    	    if(uart4 == -1)
        	cout << "Erro ao tentar abrir a uart4...\n";

	}
	
	close(uart4);
}



int32_t openUART(const char* serialPortName)
{
    // configuration options
    // O_RDWR - we need read
    //     and write access
    // O_CTTY - prevent other
    //     input (like keyboard)
    //     from affecting what we read
    // O_NDELAY - We don't care if
    //     the other side is
    //     connected (some devices
    //     don't explicitly connect)
    return open(serialPortName, O_RDWR | O_NOCTTY | O_NDELAY);
}



int32_t configUART(int32_t fd)
{
    // create the struct
    struct termios options;

    // get the current settings of the
    // serial port
    tcgetattr(fd, &options);

    // set the read and write speed to
    // 115200 BAUD
    // All speeds can be prefixed with B
    // as a settings.
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    // PARENB is enable parity bit
    // so this disables the parity bit
    options.c_cflag &= ~PARENB;

    // Only one stop bit
    options.c_cflag &= ~CSTOPB;

    // CSIZE is a mask for all the
    // data size bits, so anding
    // with the negation clears out
    // the current data size setting
    options.c_cflag &= ~CSIZE;

    // CS8 means 8-bits per work
    options.c_cflag |= CS8;

	options.c_lflag &= ~ECHO;

    // apply the settings to the serial port
    // TCSNOW means apply the changes now
    // other valid options include:
    //    TCSADRAIN - wait until every
    //        thing has been transmitted
    //    TCSAFLUSH - flush buffers
    //        and apply changes
    return tcsetattr(fd, TCSANOW, &options);
}



