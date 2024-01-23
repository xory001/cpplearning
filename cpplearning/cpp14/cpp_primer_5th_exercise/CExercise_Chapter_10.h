#pragma once
#include "../../inc.h"

namespace cpp_primer_5th_exercise
{
    class CExercise_Chapter_10
    {
        using CVecStr = std::vector< std::string >;
        using CVecInt = std::vector< int >;

    public:
        void Start( const std::string& strResPath );

    protected:
        void StartExcercise_10_1__10_1();
        void StartExcercise_10_1__10_2();
        void StartExcercise_10_3_1__10_13();
        void StartExcercise_10_3_2(); //lambda

        void StartExcercise_10_3_3__10_20();
        void StartExcercise_10_3_3__10_21();
        void StartExcercise_10_3_4__10_22();

    protected:
        void GenerateData();
        void LoadData();
        CVecStr GetText() { return m_vecStr; }
        CVecInt GetInt() { return m_vecInt; }

    protected:
        std::string m_strResPath;
        std::string m_strResTextFile;
        std::string m_strResNumberFile;

        CVecStr m_vecStr;
        CVecInt m_vecInt;
    };
}


