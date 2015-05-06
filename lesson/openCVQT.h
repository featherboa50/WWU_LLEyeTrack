#pragma once
#include <QImage>
#include <QPixmap>
#include <qdebug.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/types_c.h"

inline  cv::Mat QPixmapToCvMat(const QPixmap &inPixmap, bool inCloneImageData = true);
cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData = true);

