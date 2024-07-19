#pragma once

#include "../../inc.h"

namespace cpp_primer_5th_exercise
{ 
    void StartExecise();

    class CStartExecise
    {
    public:
        CStartExecise();

    public:
        const std::string& GetAppPath() const { return m_strAppPath; };
        const std::string& GetResPath() const { return m_strResPath; };

    protected:
        std::string m_strAppPath;
        std::string m_strResPath;
    };

}

