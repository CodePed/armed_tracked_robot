#ifndef RVIZ_ON_GUI_H
#define RVIZ_ON_GUI_H

#include <QWidget>

namespace rviz
{
    class Display;
    class RenderPanel;
    class VisualizationManager;
//    class ImageDisplay;
//    class DisplayWrapper;
}

class MyViz:
    public QWidget
{
    Q_OBJECT
    public:
        MyViz( QWidget *parent = 0 );
        virtual ~MyViz();

    private Q_SLOTS:
        void setThickness(int thickness_percent);
        void setCellSize(int cell_size_percent);

    private:
        rviz::VisualizationManager *viz_manager;
        rviz::RenderPanel *render_panel;
        rviz::Display *grid;
//        rviz::DisplayWrapper *image_wrapper;


};
#endif
