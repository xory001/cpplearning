// vtkConsoleLearning.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "inc_examples.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);



void vtkMouseMove(vtkObject* caller, unsigned long eid,
    void* clientdata, void* calldata);

int main(int argc, char* argv[] )
{
    //RunPointPickExample();
    JPGShow();
    std::cout << "Hello World!\n";
}



void vtkMouseMove(vtkObject* caller, unsigned long eid,
    void* clientdata, void* calldata)
{
    TRACE_INFO("");
}
