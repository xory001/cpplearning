#include "../../inc.h"
#include <sys/stat.h>
#include "CExercise_Chapter_10.h"

namespace cpp_primer_5th_exercise
{


    void CExercise_Chapter_10::Start(const std::string& strResPath)
    {
        m_strResPath = strResPath;
        m_strResNumberFile = m_strResPath + "\\chapter_10_number.txt";
        m_strResTextFile = m_strResPath + "\\chapter_10_text.txt";
        GenerateData();
        LoadData();

        StartExcercise_10_1__10_1();
        StartExcercise_10_1__10_2();
        StartExcercise_10_3_1__10_13();
        StartExcercise_10_3_2();

        StartExcercise_10_3_3__10_20();
        StartExcercise_10_3_3__10_21();
        StartExcercise_10_3_4__10_22();
    }

    void CExercise_Chapter_10::StartExcercise_10_1__10_1()
    {
        std::ifstream file(m_strResNumberFile);
        if ( !file.bad() )
        {
            std::vector<int> vecVal;
            vecVal.reserve( 2048 );
            std::string strLine;
            while (std::getline( file, strLine ) )
            {
                std::istringstream issLine( strLine );
                int nVal;
                while ( issLine >> nVal )
                {
                    vecVal.push_back(nVal);
                }
            }
            file.close();

            TRACE_INFO_THIS("vecVal.size = " << vecVal.size());
            srand(clock());
            for ( int i = 0; i < 5; i++ )
            {
                int nIndex = rand() % vecVal.size();
                int nCount = std::count(vecVal.begin(), vecVal.end(), vecVal.at(nIndex));
                TRACE_INFO_THIS( vecVal.at(nIndex) << " count is " << nCount );
            }
        }
    }

    void CExercise_Chapter_10::StartExcercise_10_1__10_2()
    {
        std::ifstream file(m_strResTextFile);
        if (!file.bad())
        {
            std::vector<std::string> vecVal;
            std::string strLine;
            while (std::getline(file, strLine))
            {
                std::istringstream issLine(strLine);
                std::string strVal;
                while (issLine >> strVal)
                {
                    vecVal.push_back(strVal);
                }
            }
            file.close();

            TRACE_INFO_THIS("vecVal.size = " << vecVal.size());
            srand(clock());
            for (int i = 0; i < 5; i++)
            {
                int nIndex = rand() % vecVal.size();
                int nCount = std::count(vecVal.begin(), vecVal.end(), vecVal.at(nIndex));
                TRACE_INFO_THIS(vecVal.at(nCount) << " count is " << nCount);
            }
        }
    }

    void CExercise_Chapter_10::StartExcercise_10_3_1__10_13()
    {
        CVecStr vecStr = GetText();
        std::string::size_type nLength = 5;
        CVecStr::iterator it = std::partition(vecStr.begin(), vecStr.end(), [nLength](const std::string& strWord)->bool { return strWord.length() >= nLength; });
        CVecStr::iterator itStart = vecStr.begin();
        while (itStart != it)
        {
            TRACE_INFO_THIS(*itStart);
            itStart++;
        }
    }

    void CExercise_Chapter_10::StartExcercise_10_3_2()
    {
        int nVal = 10;
        auto f1 = [](int a, int b) { return a + b; };
        int nRet1 = f1(1, 2);
        TRACE_INFO_THIS("nRet1 = " << nRet1);
        
        auto f2 = [nVal](int a) { return nVal + a; };
        int nRet2 = f2(9);
        TRACE_INFO_THIS("nRet2 = " << nRet2);
    }

    void CExercise_Chapter_10::StartExcercise_10_3_3__10_20()
    {
        CVecStr vecStr = GetText();
        std::string::size_type nLength = 6;
        int nCount = std::count_if(vecStr.begin(), vecStr.end(), 
            [nLength](const std::string& strWord) { return strWord.length() >= nLength; });
        TRACE_INFO_THIS("nCount = " << nCount );
    }

    void CExercise_Chapter_10::StartExcercise_10_3_3__10_21()
    {
        int nCount = 10;
        auto f = [&nCount]()->bool
        {
            if ( nCount > 0 )
            {
                nCount--;
            }
            return nCount > 0;
        };

        while ( f() )
        {
            TRACE_INFO_THIS("nCount = " << nCount);
        }
        TRACE_INFO_THIS("nCount = " << nCount);
        f();
        TRACE_INFO_THIS("nCount = " << nCount);
    }


    bool IsWordLess(const std::string& strWord, std::string::size_type nLength)
    {
        return strWord.length() <= nLength;
    }
    void CExercise_Chapter_10::StartExcercise_10_3_4__10_22()
    {
        CVecStr vecStr = GetText();
        std::string::size_type nLength = 6;
        auto f = std::bind(IsWordLess, std::placeholders::_1, nLength);
        int nCount = std::count_if(vecStr.begin(), vecStr.end(), f);
        TRACE_INFO_THIS("nCount = " << nCount);
    }

    void CExercise_Chapter_10::GenerateData()
    {
        struct _stat buf;
        int nRes = _stat( m_strResNumberFile.c_str(), &buf);
        if ( 0 != nRes )
        {
            switch (errno)
            {
            case ENOENT:
                {
                    srand(clock());
                    std::vector< INT32 > vecVal;
                    vecVal.reserve(1000);
                    //for ( int i = 0; i < 1000; i++ )
                    //{
                    //    vecVal.push_back( rand() * i % 1000 );
                    //}

                    //from c++ 11
                    std::mt19937 mtRandGen{ std::random_device{}() };
                    std::uniform_int_distribution<> distr(1, 1000);
                    for ( int i = 0; i < 1000; i++ )
                    {
                        vecVal.push_back( distr(mtRandGen) );
                    }

                    std::ofstream outFile(m_strResNumberFile);
                    if ( !outFile.bad() )
                    {
                        for (int i : vecVal)
                        {
                            outFile << i;
                            if ( 0 == ( i % 3 ) )
                            {
                                outFile << "\n";
                            }
                            else
                            {
                                outFile << " ";
                            }
                        }
                        outFile.close();
                    }
                    
                }
                break;

            default:
                break;
            }
        }
     
    }

    void CExercise_Chapter_10::LoadData()
    {
        std::ifstream file(m_strResNumberFile);
        if (!file.bad())
        {
            m_vecInt.clear();
            std::string strLine;
            while (std::getline(file, strLine))
            {
                std::istringstream issLine(strLine);
                int nVal;
                while (issLine >> nVal)
                {
                    m_vecInt.push_back(nVal);
                }
            }
            file.close();

            TRACE_INFO_THIS("m_vecInt.size = " << m_vecInt.size());
        }

        std::ifstream fileText(m_strResTextFile);
        if (!fileText.bad())
        {
            m_vecStr.clear();
            std::string strLine;
            std::string strWord;
            while (std::getline(fileText, strLine))
            {
                std::istringstream issLine(strLine);
                while (issLine >> strWord)
                {
                    m_vecStr.push_back(strWord);
                }
            }
            fileText.close();

            TRACE_INFO_THIS("m_vecStr.size = " << m_vecStr.size());
        }
    }

}