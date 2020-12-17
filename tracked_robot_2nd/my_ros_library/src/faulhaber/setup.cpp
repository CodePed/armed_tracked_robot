#include <stdlib.h>
#include <stdio.h>

#include "faulhaber/faulhaber.h"
#include "std_msgs/Int32MultiArray.h"
#include "actionlib/server/simple_action_server.h"
#include "my_ros_action/FaulhaberAction.h"


Faulhaber::Faulhaber()
{
    pub_encoder = nh.advertise<std_msgs::Int32MultiArray>("/faulhaber/encoder",1);
    sub_cmd = nh.subscribe("/cmd",1,&Faulhaber::Cmd_Listener,this);                 //Always subscribe and publish encoder
    pthread_mutex_init(&mutex, NULL);
    encoder.data.clear();
    action_server.start();
    cout<<endl;
    ROS_INFO("%s Action Server Start !",action_name.c_str());
}
Faulhaber::~Faulhaber()
{
    pthread_mutex_destroy(&mutex);
    ros::shutdown();
    printf("\n\nFaulhaber Control Shutdown ...\t*** Done ! ***\n\n");
}

void Faulhaber::ExecuteCB(const my_ros_action::FaulhaberGoalConstPtr &goal)
{
    bool cmd_status = true;

    // pushback the seeds
    if(action_server.isPreemptRequested())
    {
        action_server.setPreempted();
        cmd_status = false;
        printf("New Order Recieved !\n");
    }
    else
    {
        Cmd_Listener(goal);
    }
    if(cmd_status)
    {
        action_server.setSucceeded(result);
    }
//    ROS_INFO("%s: Executing,Status: %s\n", action_name.c_str(),cmd_status? "Completed" : "Failed");
}
int Faulhaber::Init(int fd_faulhaber_port,int baud_rate)
{
    printf("\nOpening Faulhaber port ...\t\t");
    //Use from USB-serial
    //Open in non blocking read/write mode

    //fd_Slim9 = open(Xtion_serialPortName,O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);

    //  ----EVENT-----
    fcntl(fd_faulhaber_port, F_SETFL, 0);      //fd = File Descriptor
    //  ----EVENT-----

    //This call will set opened file desciptor's file status flag to value 0.
    //The FNDELAY option causes the read function to return 0 if no characters are available on the port. To restore normal (blocking) behavior, call fcntl() without the FNDELAY option:

    //ERROR - CAN'T OPEN SERIAL PORT
    if(fd_faulhaber_port < 0)
    {
        printf("*** Open Faulhaber port error ***\n\n");
        printf("\t--> Please checkout your power status for your faulhaber motor\n");
        printf("\t--> Please checkout your serial port status\n");
        printf("\t--> File Permission: try chmod 777 /dev/YourSerialPortName\n");
        printf("\t--> Variable name not matched: checkout your port name in setup.cpp\n");
        printf("\t    and symlink name for faulhaber motor in\n");
        printf("\t    /etc/udev/rules.d/99-usb-serial.rules\n\n");
        return -1;
    }

//    memset(command, '\0', sizeof(command));	//Set command to null
//    sprintf(command, "Hello!\r\n");         //Testing  command call with "Hello"
//    Writter(command);                       //Writting command
//    Reader();                               //Read response

    faulhaber = fd_faulhaber_port;
    //CONFIGURE THE UART
    //The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
    //	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
    //	CSIZE:- CS5, CS6, CS7, CS8
    //	CLOCAL - Ignore modem status lines
    //	CREAD - Enable receiver
    //	IGNPAR = Ignore characters with parity errors
    //	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
    //	PARENB - Parity enable
    //	PARODD - Odd parity (else even)

    struct termios options;

    tcgetattr(fd_faulhaber_port, &options);

    if( (baud_rate != B9600) && (baud_rate != B19200) && (baud_rate != B38400) && (baud_rate != B57600) && (baud_rate != B115200) )
    {
        printf("Invalid Baud Rate !\n");
        printf("( Available Options: B9600 , B19200 , B38400 , B57600 , B115200 )\n");
        return 0;
    }

    cfsetispeed(&options,baud_rate);
    cfsetospeed(&options,baud_rate);

//    options.c_ispeed = B9600;
//    options.c_ospeed = B9600;
//
//    options.c_cflag &= ~PARENB;
//    options.c_cflag &= ~CSTOPB;
//    options.c_cflag &= ~CSIZE;
//    options.c_cflag |= CS8;
//    options.c_cflag |= (CREAD);
//    options.c_iflag |= (IXON | IXOFF);

    //options.c_cflag = B9600 | CS8 | CLOCAL | CREAD ;
    //options.c_iflag = IGNPAR;
    //options.c_oflag = 0;
    //options.c_lflag = ICANON;
    //------------------------------------------------------
    /* Setting other Port Stuff */
    options.c_cflag &= ~PARENB;            // Make 8n1
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;                //8 data bits
    options.c_cflag &= ~CRTSCTS;           // no flow control
    options.c_cc[VMIN] = 0;                // read doesn't block
    options.c_cc[VTIME] = 1;               // 0.5 seconds read timeout
    options.c_cflag |= CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
    /* Make raw */
    cfmakeraw(&options);
    //-------------------------------------------------------

    if(tcsetattr(fd_faulhaber_port, TCSANOW, &options) != 0)      //tcsetattr: 0 -> success ; -1 -> failure
    {
        printf("*** Error %d from tcsetattr ***\n\n", errno);
        printf("\t--> Please checkout your protocol spec for faulhaber\n");
        printf("\t--> Protocol setting can be changed in setup.cpp\n\n");

        close(fd_faulhaber_port);

        return -1;
    }


    /* Flush Port, then applies attributes */
    tcflush(fd_faulhaber_port, TCIOFLUSH);      //Flush port fd

    printf("*** Successful ! ***\n\n");
    return 1;
}

void Faulhaber::Close(int fd_faulhaber_port)
{


    printf("\nClosing Faulhaber port ... \t\t");
    close(fd_faulhaber_port);
    printf("*** Successful ! ***\n");
}

void Faulhaber::Buffer_Reset(int fd_faulhaber_port)
{
    memset(WrittenBuff, '\0', sizeof(WrittenBuff));
    sprintf(WrittenBuff,"RESET\r\n");
    write(fd_faulhaber_port,WrittenBuff,sizeof(WrittenBuff));
    tcflush(fd_faulhaber_port, TCIFLUSH); //Flush Buffer data
}
