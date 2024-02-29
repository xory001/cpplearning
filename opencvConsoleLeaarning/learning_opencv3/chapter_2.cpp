#include "../inc.h"
#include "chapter_2.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace locv3 {


    bool Start_Exercise_2(const std::string& strImageFile, const std::string& strVidoeFile)
    {
        chapter2_1(strImageFile);
        chapter2_3(strVidoeFile);
        chapter2_4(strVidoeFile);

        return true;
    }

    int chapter2_1(const std::string& strImageFile)
    {
        std::string strWindowName = "Example2_1";
        cv::Mat img = cv::imread(strImageFile, -1);
        if (img.empty()) return -1;
        cv::namedWindow(strWindowName, cv::WINDOW_NORMAL );
        //cv::resizeWindow(strWindowName, 1024, 768);
        //cv::Mat imgResize;
        //cv::resize(img, imgResize, cv::Size(640, 480));
        cv::imshow(strWindowName, img);
        cv::waitKey(0);
        cv::destroyWindow(strWindowName);
        return 0;
    }

    int chapter2_3(const std::string& strVidoeFile)
    {
        cv::namedWindow("Example3", cv::WINDOW_AUTOSIZE);
        cv::VideoCapture cap;
        cap.open(strVidoeFile);
        cv::Mat frame;
        for (; ;)
        {
            cap >> frame;
            if (frame.empty()) break;
            cv::imshow("Example3", frame);
            if (cv::waitKey(33) >= 0) break;
        }
        return 0;
    }

    //2_4
    int g_slider_position = 0;
    int g_run = 1, g_dontset = 0; //start out in single step mode
    cv::VideoCapture g_cap;
    void onTrackbarSlide(int pos, void*)
    {
        g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
        if (!g_dontset)
        {
            g_run = 1;
        }
        g_dontset = 0;
    }

    int chapter2_4(const std::string& strVidoeFile)
    {
        cv::namedWindow("Example2_4", cv::WINDOW_AUTOSIZE);
        g_cap.open(strVidoeFile);
        int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
        int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
        int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
        std::cout << "Video has " << frames << "frames of dimensions(" << tmpw << ", " << tmph << ")." << std::endl;
        cv::createTrackbar("Position", "Example2_4", &g_slider_position, frames, onTrackbarSlide);
        cv::Mat frame;
        for (;;)
        {
            if (g_run != 0)
            {
                g_cap >> frame;
                if ( frame.empty() )
                {
                    break;
                }
                int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
                g_dontset = 1;
                cv::setTrackbarPos("Position", "Example2_4", current_pos);
                cv::imshow("Example2_4", frame);
                g_run -= 1;
            }

            char c = (char)cv::waitKey(10);
            if ( c == 's' )
            {
                g_run = 1;
            }
            if ( c == 'r' )
            {
                g_run = -1;
            }

            if ( c == 27 ) //'ESC' key
            {
                break;
            }
        }

        return 0;
    }
}


