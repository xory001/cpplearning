#include "../inc.h"
#include "chapter_3.h"
#include <opencv2/opencv.hpp>

namespace locv3
{

    bool Start_Exercise_3()
    {
        Exercise_3_1();
        Exercise_3_2();
        Exercise_3_3();
        return true;
    }

    bool Exercise_3_1()
    {
        cv::Point2f pt2f{ 1.49f, 2.5f };
        TRACE_INFO("pt2f.x = " << pt2f.x << ", pt2f.y = " << pt2f.y);
        cv::Point pt = (cv::Point)pt2f;  //convert by rounding
        TRACE_INFO("pt.x = " << pt.x << ", pt.y = " << pt.y);

        return false;
    }

    bool Exercise_3_2()
    {
        cv::Matx33f mat33f( 1.1f, 2.1f, 3.1f, 4.1f, 5.1f, 6.1f, 7.1f, 8.1f, 9.1f);
        cv::Vec3f vec3f(1.1f, 2.1f, 3.1f);
        auto res = mat33f * vec3f;
        return false;
    }

    bool Exercise_3_3()
    {
        cv::Mat mat(3, 3, CV_8UC1);
        cv::Vec<int,3> vec;
        
        return false;
    }

}


