#include "CStart.h"
#include "../inc.h"
#include "CInitType.h"
#include "CThread.h"
#include <thread>
#include "CGramma.h"
#include "CSTL.h"
#include "CPointer.h"
#include "CReference.h"
#include "CFunctionExample.h"
#include "cpp_primer_5th_exercise/CStartExecise.h"

namespace cpp14
{
    void Start()
    {
        cpp_primer_5th_exercise::StartExecise();
        InitFunctionExample();
        return;
        InitReference();
        return;
        InitThread();
        InitType(); //value init & default init
        InitPointer();
        CGramma_Test();
        CSTL_Init();
    }
}

