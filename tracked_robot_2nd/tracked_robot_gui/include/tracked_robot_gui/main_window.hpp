/**
 * @file /include/tracked_robot_gui/main_window.hpp
 *
 * @brief Qt based gui for tracked_robot_gui.
 *
 * @date November 2010
 **/
#ifndef tracked_robot_gui_MAIN_WINDOW_H
#define tracked_robot_gui_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>
#include <QApplication>
//#include "ui_main_window.h"

#include <ros/package.h>

//***************************//
//     For rviz library      //
//***************************//
#include <rviz/tool.h>
#include <rviz/display.h>
#include <rviz/render_panel.h>
#include <rviz/tool_manager.h>
#include <rviz/frame_manager.h>
#include <rviz/visualization_frame.h>
#include <rviz/visualization_manager.h>
#include <rviz/yaml_config_reader.h>
#include <rviz/config.h>

#include "qnode.hpp"

#include <stdio.h>
/*****************************************************************************
** Namespace
*****************************************************************************/
namespace tracked_robot_gui
{
    using namespace Qt;
    class MainWindow;
}
/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow :
    public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(int argc, char** argv, QWidget *parent = 0);
        ~MainWindow();

//        void ReadSettings(); // Load up qt program settings at startup
//        void WriteSettings(); // Save qt program settings when closing

        void closeEvent(QCloseEvent *event); // Overloaded function
//        void showNoMasterMessage();

    public Q_SLOTS:
/******************************************
** Auto-connections (connectSlotsByName())
*******************************************/
        void on_actionAbout_triggered();
        void on_button_connect_clicked(bool check );
        void on_checkbox_use_environment_stateChanged(int state);
        void on_radio_button_camera_triggered();

/******************************************
** Manual connections
*******************************************/
//        void updateLoggingView(); // no idea why this can't connect automatically

    private:
        MainWindow *ui;

        void rviz_initial();

        rviz::VisualizationManager *rviz_manager;
        rviz::RenderPanel *render_panel;
        rviz::Display *camera_display;

        rviz::DisplayContext *display_context;
        rviz::FrameManager *frame_manager;
        rviz::ToolManager *tool_manager;

//        QNode qnode;
};

#endif // tracked_robot_gui_MAIN_WINDOW_H
