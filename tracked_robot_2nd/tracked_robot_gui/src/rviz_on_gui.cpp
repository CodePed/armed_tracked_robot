//#include "../include/tracked_robot_gui/main_window.hpp"

#include "../include/tracked_robot_gui/mainwindow.h"
//#include "rviz_on_gui.h"
//********************
//Include for rviz
//********************
#include "rviz/visualization_manager.h"
#include "rviz/render_panel.h"
#include "rviz/display.h"
#include "rviz/displays_panel.h"
//********************
//Include for Qt GUI Element
//********************
#include <QColor>
#include <QSlider>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>

#include <iostream>


//using namespace tracked_robot_gui;

MainWindow::MainWindow(QWidget *parent ):
    QWidget( parent )
{
    //Construct and lay out labels and slider controls.
    QLabel *thickness_label = new QLabel("Line Thickness");
    QSlider *thickness_slider = new QSlider( Qt::Horizontal );
    //Configure QSlider
    thickness_slider->setMinimum(1);
    thickness_slider->setMaximum(100);

    QLabel *cell_size_label = new QLabel("Cell Size");
    QSlider *cell_size_slider = new QSlider( Qt::Horizontal );
    //Configure QSlider
    cell_size_slider->setMinimum(1);
    cell_size_slider->setMaximum(100);

    QGridLayout *controls_layout = new QGridLayout();
    //Configure QGridLayout with elements above
    controls_layout->addWidget( thickness_label , 0 , 0 );
    controls_layout->addWidget( thickness_slider, 0 , 1 );
    controls_layout->addWidget( cell_size_label , 1 , 0 );
    controls_layout->addWidget( cell_size_slider, 1 , 1 );

    //Construct and lay out render panel.
    render_panel = new rviz::RenderPanel();
    QVBoxLayout *main_layout = new QVBoxLayout;

    //Configure QVBoxLayout with elements above
    main_layout->addLayout( controls_layout );
    main_layout->addWidget( render_panel );
//    main_layout->setGeometry(0,0,1280,1080);

    //Set the top-level layout for this Myviz widget
    setLayout( main_layout );

    //Make Signal/Slot connection
    //Just ignore the warning sign about valueChanged(int) with the description("expected token ";" got 'int'")
    connect( thickness_slider , SIGNAL( valueChanged(int) ),this,SLOT( setThickness( int ) ) );
    connect( cell_size_slider , SIGNAL( valueChanged(int) ),this,SLOT( setCellSize( int ) ) );

    //Next we initialize the main RViz class

    //The VisualizationManager is the container for Display objects
    //holds the main Ogre scene, holds the ViewController, etc.
    //It is very central and we will probably need one in every usage of librviz.
    viz_manager = new rviz::VisualizationManager( render_panel );
    render_panel->initialize( viz_manager->getSceneManager() ,viz_manager);
    viz_manager->initialize();
    viz_manager->startUpdate();

    //Create a grid Display
    grid = viz_manager->createDisplay("rviz/Image","Camera",true);

    ROS_ASSERT( grid != NULL );

    //Configure the GridDisplay the way we like it.
    grid->subProp( "Image Topic" )->setValue( "/zed/rgb/image_rect_color" );
    grid->subProp( "Color" )->setValue( QColor( Qt::yellow ) );

    //Initializethe slider values
    thickness_slider->setValue(25);
    cell_size_slider->setValue(10);

}

//Destructor
MainWindow::~MainWindow()
{
    delete viz_manager;
}

//This function is a Qt slot connected to a QSlider's valueChange() signal.
//It sets the line thickness of the grid by changing the grid's "Line Width" property
void MainWindow::setThickness( int thickness_percent )
{
    if( grid !=NULL )
    {
        grid->subProp( "Line Style" )->subProp( "Line Width" )->setValue( thickness_percent / 100.0f );
    }
}

//This function is a Qt slot connected to a QSlider's valueChange() signal.
//It sets the cell size of the grid by changing the grid's "Cell Size" property
void MainWindow::setCellSize( int cell_size_percent )
{
    if( grid != NULL )
    {
        grid->subProp("Cell Size")->setValue( cell_size_percent / 10.0f );
    }
}
