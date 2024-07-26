#pragma once
#include <thread>

namespace cpp17
{
    void InitReference();

    std::thread Swap( std::thread&& t );


    class CReference
    {
    };


}
