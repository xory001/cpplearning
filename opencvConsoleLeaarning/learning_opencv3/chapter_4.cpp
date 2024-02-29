#include "../inc.h"
#include "chapter_4.h"

namespace locv3
{

    bool Start_Exercise_4()
    {
        Chatper_4_Mat();
        return true;
    }

    bool Chatper_4_Mat()
    {
        int m = 3;
        int n = 5;

        cv::Mat mat1(m, n, CV_8UC4);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cv::Vec4b& pt = mat1.at<cv::Vec4b>(i, j);
                pt[0] = 'a';
                pt[1] = 'b';
                pt[2] = 'c';
                pt[3] = 'd';
                cv::Vec4b* pData = mat1.ptr<cv::Vec4b>(i, j);
                TRACE_INFO("pData = " << *pData);
            }
        }
        mat1.data;
        mat1.step[0]; //20, 5 * sizeof CV_8UC4, per line size, bytes
        mat1.step[1]; //4, size of CV_8UC4, bytes
        uchar* pData = mat1.ptr(); //equal to mat1.data
        

        return true;
    }

}