#include "../inc.h"
#include "CReference.h"


namespace cpp17
{ 
    void InitReference()
    {
        //c++ primer 5th cn, p46
        int i = 0, &r1 = i;
        double d = 0, &r2 = d;
        r2 = 3.14159;  //ok
        r2 = r1; //ok
        i = r2; //ok
        r1 = d; //ok

        int a1 = 10;
        int& a1r = a1;
        a1r = 20;
        TRACE_INFO("a1 = " << a1);
        int&& a2r = 100;
        a2r = 300;
        TRACE_INFO("a2r = " << a2r);
        a2r = a1;
        TRACE_INFO("a2r = " << a2r);

        std::string s1 = "a";
        std::string& s1r = s1;
        s1r = "b";
        TRACE_INFO("s1r = " << s1r);
        std::string&& s1rr = "s1rr";
        s1rr = s1r;
        TRACE_INFO("s1rr = " << s1rr);
        s1rr = "s1rr_1";
        TRACE_INFO("s1rr = " << s1rr);
    }

}
