/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/
#include <QApplication>
#include "ros/ros.h"
#include "rviz_on_gui.h"

//#include "../include/tracked_robot_gui/main_window.hpp"

/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv)
{

    if( !ros::isInitialized() )
    {
        printf("Not Detected Node Name with \"tracked_robot_gui\".\nSet up a new one.\n\n");
        ros::init(argc,argv,"tracked_robot_gui",ros::init_options::AnonymousName);
    }
    else
    {
        printf("Detecting Node Name \"tracked_robot_gui\" existed already.\nShut it down and try again.\n\n");
        return 0;
    }

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
//    tracked_robot_gui::MainWindow w(ar    gc,argv);
//    w.show();
    MyViz *myviz = new MyViz();
    myviz->resize(1280,1080);
    myviz->show();

//    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    int result = app.exec();

//    delete myviz;
	return result;
}
