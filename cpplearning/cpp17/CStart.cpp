#include "CStart.h"
#include "../inc.h"
#include "CInitType.h"
#include "CThread.h"
#include <thread>
#include "CSyntax.h"
#include "CSTL.h"
#include "CPointer.h"
#include "CReference.h"
#include "CFunctionExample.h"
#include "cpp_primer_5th_exercise/CStartExecise.h"

namespace cpp17
{
    void Start()
    {
        //cpp_primer_5th_exercise::StartExecise();
        CSTL stl;
        stl.Start();
        
        TRACE_INFO( "--------CSyntax--------" );
        CSyntax syntax;
        syntax.Start();
        return;

        InitFunctionExample();
        //return;
        InitReference();
        //return;
        InitThread();
        InitType(); //value init & default init
        InitPointer();
        
        
    }
}

