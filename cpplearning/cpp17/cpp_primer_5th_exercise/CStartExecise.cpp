#include "CStartExecise.h"
#include "../../inc.h"
#include "CExercise_Chapter_10.h"

namespace cpp_primer_5th_exercise
{
    void StartExecise()
    {
        TRACE_INFO("cpp_primer_5th_exercise::StartExecise");
        CStartExecise se;
        CExercise_Chapter_10 ec10;
        ec10.Start( se.GetResPath() );
    }

    CStartExecise::CStartExecise()
    {
        char szBuf[MAX_PATH] = { 0 };
        GetModuleFileNameA(NULL, szBuf, MAX_PATH);
        m_strAppPath = szBuf;
        std::string::size_type pos = m_strAppPath.rfind( "\\" );
        if ( pos != std::string::npos )
        {
            m_strAppPath = m_strAppPath.substr( 0, pos );
        }
        m_strResPath = m_strAppPath + "\\res";
        TRACE_INFO_THIS("m_strResPath = " << m_strResPath );
    }

}