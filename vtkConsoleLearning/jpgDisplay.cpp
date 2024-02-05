#include "inc_examples.h"


int JPGShow()
{
    TCHAR szBuf[MAX_PATH] = { 0 };
    GetCurrentDirectoryW(MAX_PATH, szBuf);
    std::wcout << "work dir = " << szBuf;

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

    vtkSmartPointer<vtkOpenGLImageSliceMapper> imageMapper = vtkSmartPointer<vtkOpenGLImageSliceMapper>::New();
    imageMapper->SetInputConnection(JPEGReader->GetOutputPort());

    vtkSmartPointer<vtkImageActor> imageActor = vtkSmartPointer<vtkImageActor>::New();
    //imageActor->SetInputData(JPEGReader->GetOutput());
    imageActor->SetMapper(imageMapper);

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->AddActor(imageActor);
    render->SetBackground(1, 1, 1);
    

    // Read and display the image properties
    const char* fileExtensions = JPEGReader->GetFileExtensions();
    cout << "File xtensions: " << fileExtensions << endl;

    const char* descriptiveName = JPEGReader->GetDescriptiveName();
    cout << "Descriptive name: " << descriptiveName << endl;

    // Visualize
    //vtkSmartPointer<vtkImageViewer> imageViewer = vtkSmartPointer<vtkImageViewer>::New();
    //imageViewer->SetInputConnection(JPEGReader->GetOutputPort());
    //imageViewer->SetColorWindow(256);
    //imageViewer->SetColorLevel(127.5);
    //vtkRenderer *pRender = imageViewer->GetRenderer();
    //vtkRenderWindow* pRenerWin = imageViewer->GetRenderWindow();

    //vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
   // vtkSmartPointer<vtkCallbackCommand> vtkCmd = vtkSmartPointer<vtkCallbackCommand>::New();
    //vtkCmd->SetCallback(vtkMouseMove);
    //renderWindowInteractor->AddObserver(vtkCommand::MouseMoveEvent, vtkCmd);
    vtkSmartPointer<vtkPointPicker> pointPicker =
        vtkSmartPointer<vtkPointPicker>::New();

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetPicker(pointPicker);
    //renderWindowInteractor->SetRenderWindow(pRenerWin);

    vtkSmartPointer<CPointPickerlnteractorStyle> style =
        vtkSmartPointer<CPointPickerlnteractorStyle>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    vtkSmartPointer<vtkRenderWindow> rendWin = vtkSmartPointer<vtkRenderWindow>::New();
    rendWin->SetInteractor(renderWindowInteractor);
    rendWin->AddRenderer(render);
    rendWin->Render();

    //imageViewer->SetupInteractor(renderWindowInteractor);
    //imageViewer->Render();

    //vtkRenderWindow* renWin = imageViewer->GetRenderWindow();
    // int retVal = vtkRegressionTestImage(renWin);
   //  if (retVal == vtkRegressionTester::DO_INTERACTOR)
    {
        renderWindowInteractor->Start();
    }

    //return !retVal;
    return 0;
}