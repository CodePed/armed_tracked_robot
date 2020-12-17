#include "../include/tracked_robot_gui/mainwindow.h"

//#include <cv_bridge/cv_bridge.h>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>

void MainWindow::displayMat(cv::Mat image)
{
  cv::Mat rgb;
      QImage img;
      if(image.channels()==3)
      {
          //cvt Mat BGR 2 QImage RGB
          cv::cvtColor(image,rgb,CV_BGR2RGB);
          img =QImage((const unsigned char*)(rgb.data),
                      rgb.cols,rgb.rows,
                      rgb.cols*rgb.channels(),
                      QImage::Format_RGB888);
      }
      else
      {
          img =QImage((const unsigned char*)(image.data),
                      image.cols,image.rows,
                      image.cols*image.channels(),
                      QImage::Format_RGB888);
      }
      QImage img2=img.scaled(ui->scrollArea->width()-15,ui->scrollArea->height()/2-5,Qt::KeepAspectRatio);
      ui->ImageLabel->setPixmap(QPixmap::fromImage(img2));
//      ui.ImageLabel->resize(ui.ImageLabel->pixmap()->size());
}
