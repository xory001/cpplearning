// vtkConsoleLearning.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "vtkImageData.h"
#include "vtkImageViewer.h"
#include "vtkJPEGReader.h"
//#include "vtkRegressionTestImage.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"

#include "../include/vtk_8.2.0_lib.h"


int jpgShow();

int main(int argc, char* argv[] )
{
    for ( int i = 0; i < argc; i++ )
    {
        std::cout << argv[i] << "\n";
    }
    std::cout << "Hello World!\n";
}

int jpgShow()
{
    std::string filename = "res\\a.jpg";

    vtkSmartPointer<vtkJPEGReader> JPEGReader = vtkSmartPointer<vtkJPEGReader>::New();

    // Check the image can be read
    if (!JPEGReader->CanReadFile(filename.c_str()))
    {
        cerr << "CanReadFile failed for " << filename << "\n";
        return EXIT_FAILURE;
    }

    // Read the input image
    JPEGReader->SetFileName(filename.c_str());
    JPEGReader->Update();

    // Read and display the image properties
    const char* fileExtensions = JPEGReader->GetFileExtensions();
    cout << "File xtensions: " << fileExtensions << endl;

    const char* descriptiveName = JPEGReader->GetDescriptiveName();
    cout << "Descriptive name: " << descriptiveName << endl;

    // Visualize
    vtkSmartPointer<vtkImageViewer> imageViewer = vtkSmartPointer<vtkImageViewer>::New();
    imageViewer->SetInputConnection(JPEGReader->GetOutputPort());
    imageViewer->SetColorWindow(256);
    imageViewer->SetColorLevel(127.5);

    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
    imageViewer->SetupInteractor(renderWindowInteractor);
    imageViewer->Render();

    vtkRenderWindow* renWin = imageViewer->GetRenderWindow();
   // int retVal = vtkRegressionTestImage(renWin);
  //  if (retVal == vtkRegressionTester::DO_INTERACTOR)
    {
        renderWindowInteractor->Start();
    }

    //return !retVal;
    return 0;
}
