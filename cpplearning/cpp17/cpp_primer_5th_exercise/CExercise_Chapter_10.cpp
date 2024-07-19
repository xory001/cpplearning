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
        StartExcercise_10_3_4__10_24();
    }

    void CExercise_Chapter_10::StartExcercise_10_1__10_1()
    {
        std::ifstream file(m_strResNumberFile);
        if ( file.is_open() )
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

            for (int i = 0; i < 5; i++)
            {
                int nIndex = rand() % vecVal.size();
                int nCount = std::count(vecVal.begin(), vecVal.end(), vecVal.at(nIndex));
                TRACE_INFO_THIS(vecVal.at(nIndex) << " count is " << nCount);
            }
        }
    }

    void CExercise_Chapter_10::StartExcercise_10_1__10_2()
    {
        std::ifstream file(m_strResTextFile);
        if (file.is_open())
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
        //std::for_each(itStart, it, [](const std::string& strItem) { TRACE_INFO(strItem); });
        std::for_each(itStart, it, [](std::string& strItem) { strItem += "_*****"; });  //can change the vector's item value
        //std::for_each(itStart, it, [](const std::string& strItem) { TRACE_INFO(strItem); });
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
        //first answer
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

        //second answer
        nCount = 5;
        auto f1 = [nCount]()->auto
        {
            int nVal = nCount;  //nVal will release after f1 called; so if want to hold nCount, do that like 'third answer'
            return [&nVal]()->bool
            {
                TRACE_INFO("nVal = " << nVal); //nVal is unpredictable values
                if (nVal > 0)
                {
                    nVal--;
                }
                TRACE_INFO("nVal = " << nVal);
                return nVal > 0;
            };
        };

        auto f1Ret = f1();
        nCount = 0;
        while (f1Ret())
        {
            nCount++;
           if ( nCount >= 5 )
           {
               break;
           }
        }
        bool bRet = f1Ret();
        TRACE_INFO("bRet = " << bRet);

        //third answer
        nCount = 5;
        auto f2 = [nCount]()->auto{
            return [nCount]()mutable->bool //nCount is a copy, change the value, do not affect ::nCount 
            {
                if (nCount > 0)
                {
                    nCount--;
                }
                TRACE_INFO("nCount = " << nCount);
                return nCount > 0;
            };
        };
        auto f2Ret = f2();
        while ( f2Ret() )
        {

        }
        bRet = f2Ret();
        TRACE_INFO("nCount = " << nCount);

        //four answer
        auto f3 = [nCount]()->auto
        {
            int nLocalCount = nCount;
            return [nLocalCount]()mutable->bool {
                if (nLocalCount > 0)
                {
                    nLocalCount--;
                }
                TRACE_INFO("nLocalCount = " << nLocalCount);
                return nLocalCount > 0;
            };
        };
        auto f3Ret = f3();
        while ( f3Ret() )
        {

        }
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

    bool check_size( const std::string& strSrc, int nVal )
    {
        return (std::string::size_type)nVal > strSrc.length();
    }
    void CExercise_Chapter_10::StartExcercise_10_3_4__10_24()
    {
        CVecInt vecInt = GetInt();
        std::sort(vecInt.begin(), vecInt.end());
        //std::sort(vecInt.begin(), vecInt.end(), [](int a, int b) {return a > b; });
        auto it = std::unique(vecInt.begin(), vecInt.end());
        vecInt.erase(it, vecInt.end());
        std::string strOrg = "1323fafsafasfas24";
        auto f = std::bind(check_size, strOrg, std::placeholders::_1);
        CVecInt::iterator it1 = std::find_if(vecInt.begin(), vecInt.end(), f);
        if ( it1 != vecInt.end() )
        {
            TRACE_INFO_THIS("val is " << *it1);
        }
        else
        {
            TRACE_INFO_THIS("no val find");
        }
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