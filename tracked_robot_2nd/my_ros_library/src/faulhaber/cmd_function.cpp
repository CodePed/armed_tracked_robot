#include <stdlib.h>
#include <stdio.h>
#include "faulhaber/faulhaber.h"

int Faulhaber::Position(int motor_number)
{
    memset(command, '\0', sizeof(command));
    sprintf(command , "%dPOS\r\n",motor_number);  //write in "iPOS\r\n" , i : encoder number
    Writter(command);
    Reader();
    if(reader_response == "OK")
    {
        Writter(command);
        Reader();
    }
    return  atoi(reader_response);
}

void Faulhaber::Speed(int motor_number, int motor_speed)
{
    memset(command, '\0', sizeof(command));                     //Set command to null
    sprintf(command, "%dSP%d\r\n", motor_number, motor_speed);	//Editting command :Max speed
    Writter(command);                                          //Writting command
    Reader();
}

void Faulhaber::Vel(int motor_number, int motor_speed)
{
    memset(command, '\0', sizeof(command));						//Set command to null
    sprintf(command, "%dV%d\r\n", motor_number, motor_speed);	//Editting command :Velocity
    Writter(command);				//Writting command
    Reader();
}

void Faulhaber::Acc(int motor_number, int motor_acc)
{
    memset(command, '\0', sizeof(command));						//Set command to null
    sprintf(command, "%dAC%d\r\n", motor_number, motor_acc);	//Editting command :Acceleration
    Writter(command);                       //Writting command
    Reader();
}
void Faulhaber::Dec(int motor_number, int motor_dec)
{
    memset(command, '\0', sizeof(command));						//Set command to null
    sprintf(command, "%dDEC%d\r\n", motor_number, motor_dec);	//Editting command :Deceleration
    Writter(command);						//Writting command
    Reader();
}

void Faulhaber::LA(int motor_number, int motor_LA)
{
    memset(command, '\0', sizeof(command));						//Set command to null
    sprintf(command, "%dLA%d\r\n", motor_number, motor_LA);		//Editting command :Load Absolute Position
    Writter(command);                       //Writting command
    Reader();
}

void Faulhaber::LR(int motor_number, int motor_LR)
{
    memset(command, '\0', sizeof(command));						//Set command to null
    sprintf(command, "%dLR%d\r\n", motor_number, motor_LR);		//Editting command :Load Relative Position
    Writter(command);						//Writting command
    Reader();
}
void Faulhaber::M(int motor_number)
{
    memset(command, '\0', sizeof(command));						//Set command to null
    sprintf(command, "%dM\r\n", motor_number);					//Editting command :Activate Position
    Writter(command);						//Writting command
    Reader();
}
void Faulhaber::HO(int motor_number, int motor_HO)
{
    memset(command, '\0', sizeof(command));						//Set command to null
    sprintf(command, "%dHO%d\r\n", motor_number, motor_HO);		//Editting command :Define Home Position
    Writter(command);						//Writting command
    Reader();
}
void Faulhaber::EN(int motor_number)
{
    memset(command, '\0', sizeof(command));						//Set command to null
    sprintf(command, "%dEN\r\n", motor_number);					//Editting command :Enable Motor
    Writter(command);						//Writting command
    Reader();
}
void Faulhaber::DI(int motor_number)
{
    memset(command, '\0', sizeof(command));						//Set command to null
    sprintf(command, "%dDI\r\n", motor_number);					//Editting command :Disable Motor
    Writter(command);                       //Writting command
    Reader();
}
int Faulhaber::GRC(int motor_number)
{
    memset(command, '\0', sizeof(command));					//Set command to null
    sprintf(command, "%dGRC\r\n", motor_number);			//Editting command :Get Actual Current
    Writter(command);
    Reader();
    return atoi(reader_response);
}
