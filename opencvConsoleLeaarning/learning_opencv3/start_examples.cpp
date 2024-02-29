#include "../inc.h"
#include "chapter_2.h"
#include "chapter_3.h"
#include "chapter_4.h"

namespace locv3 {
    void StartExamples()
    {
        std::string strExePath;
        std::string strImageBg19s;
        std::string strVidoeAiNews;
        char szBuf[MAX_PATH] = { 0 };
        GetModuleFileNameA(NULL, szBuf, MAX_PATH);
        char* pFind = strrchr(szBuf, '\\');
        if ( NULL != pFind )
        {
            *pFind = 0;
            strExePath = szBuf;
            strImageBg19s = strExePath + ("\\res\\bg19-s.jpg");
            strVidoeAiNews = strExePath + ("\\res\\ai-news.mp4");
        }

        Start_Exercise_2(strImageBg19s, strVidoeAiNews);

        Start_Exercise_3();
        Start_Exercise_4();
    }
}