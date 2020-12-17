#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>     //Used for usleep

#include "ros/ros.h"
#include "faulhaber/faulhaber.h"

//using namespace std;

void Faulhaber::Writter(char *Command)
{
    pthread_mutex_lock(&mutex);
    tcflush(faulhaber, TCIOFLUSH); //Flush Buffer data need some delay
    memset(WrittenBuff, '\0', sizeof(WrittenBuff));
    for (int i = 0; i < sizeof(WrittenBuff); i++)
    {
        WrittenBuff[i] = Command[i];
    }
    write(faulhaber, WrittenBuff, sizeof(WrittenBuff));
    tcdrain(faulhaber);
    usleep(100);
    pthread_mutex_unlock(&mutex);
}

void Faulhaber::Reader()
{
    pthread_mutex_lock(&mutex);
    cout << "Reader start ...\t";
    memset(reader_response, '\0', sizeof(reader_response));//set response to null
    scanner = '\0';
    for(int i = 0 ;true; i++)
    {

        reader_status = read(faulhaber,&scanner,1);
        if(scanner == 10)   //Break reading when read '\n' or LF(Line Feed, ASCII decimal code 10)
        {
            reader_response[i-1] = '\0';
            reader_response[i] = '\0';
            cout<<"Recieved data length : "<<i+1<<"\t";
            break;
        }
        reader_response[i] = scanner;
    }
    switch(reader_status)
    {
        case -1:
            cout<<"*** Error ! ***"<<endl;
            cout<<"Error reading: "<<strerror(errno)<<endl;
            break;
        case  0:            //
            cout<<"Empty !"<<endl;
            break;
        case  1:
            cout<<"Recieved data : "<<reader_response<<endl; //Print the System message
            break;
    }
    tcflush(faulhaber, TCIOFLUSH);
    usleep(100);
    pthread_mutex_unlock(&mutex);
}
