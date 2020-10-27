#include "dynamixel_library_function.h"

int DXL::getch()
{
    struct termios oldt, newt;
    int ch;
    
    tcgetattr(STDIN_FILENO , &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO , TCSANOW , &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO , TCSANOW , &oldt);
    return ch
}

int DXL::keyboard_hit()
{
    struct termios oldt , newt;
    int ch;
    int oldf;

    cgetattr(STDIN_FILENO , &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO , TCSANOW , &newt);
    oldf = fcntl(STDIN_FILENO , F_GETFL , 0);
    fcntl(STDIN_FILENO , F_SETFL ,  oldf | O_NONBLOCK);

    CH = getchar();
    
    tcsetattr(STDIN_FILENO , TCSANOW , &oldt);
    fcntl(STDIN_FILENO , F_SETFL , oldf);

    if(ch ! EOF)
    {
        ungetc(ch , stdin);
        return 1;
    }

    return 0;
}