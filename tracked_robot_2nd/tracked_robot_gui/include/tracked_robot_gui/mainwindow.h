#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "ros/ros.h"

namespace Ui {
    class MainWindow;
}

namespace rviz
{
    class Display;
    class RenderPanel;
    class VisualizationManager;
}

class MainWindow:
    public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow( QWidget *parent =0 );
        ~MainWindow();

        void displayMat(cv::Mat image);

    private Q_SLOTS:
        void setThickness(int thickness_percent);
        void setCellSize(int cell_size_percent);

    private:
        ros::NodeHandle n;
        MainWindow *ui;
        rviz::VisualizationManager *viz_manager;
        rviz::RenderPanel *render_panel;
        rviz::Display *grid;

};
#endif

