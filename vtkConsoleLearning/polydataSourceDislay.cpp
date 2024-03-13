#include "inc_examples.h"

int PolyDataSourceDisplay()
{
    vtkNew<vtkTextSource> textRed;
    textRed->SetText("red");
    textRed->SetBacking(false);

    vtkNew<vtkTextSource> textRed1;
    textRed1->SetText("red_1");
    textRed1->SetBacking(false);

    vtkNew<vtkPolyDataMapper> textMapperRed;
    //textMapperRed->AddInputConnection(0, textRed->GetOutputPort());
    textMapperRed->AddInputConnection(0, textRed1->GetOutputPort());

    vtkNew<vtkActor> textActorRed;
    textActorRed->SetMapper(textMapperRed);


    vtkSmartPointer<vtkRenderer> renderRed = vtkSmartPointer<vtkRenderer>::New();
    //render->AddActor(imageActor);
    renderRed->SetBackground(127, 0, 0);
    renderRed->SetViewport( 0, 0, 0.5, 0.5 );
    renderRed->AddActor(textActorRed);


    vtkNew<vtkTextSource> textGreen;
    textGreen->SetText("green");
    textGreen->SetBacking(false);
    //text->SetForegroundColor()

    vtkNew<vtkPolyDataMapper> textMapperGreen;
    textMapperGreen->SetInputConnection(textGreen->GetOutputPort());

    vtkNew<vtkActor> textActorGreen;
    //textActorGreen->SetMapper(textMapperGreen);

    vtkSmartPointer<vtkRenderer> renderGreen = vtkSmartPointer<vtkRenderer>::New();
    //render->AddActor(imageActor);
    renderGreen->SetBackground(0, 127, 0);
    renderGreen->SetViewport( 0.5, 0.5, 1, 1);
    renderGreen->AddActor(textActorGreen);
    //renderRed->SetLayer(1);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
  
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
        vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    renderWindowInteractor->SetInteractorStyle(style);
   
    vtkSmartPointer<vtkRenderWindow> rendWin = vtkSmartPointer<vtkRenderWindow>::New();
    rendWin->SetNumberOfLayers(2);
    rendWin->AddRenderer(renderRed);
    rendWin->AddRenderer(renderGreen);
    rendWin->SetInteractor(renderWindowInteractor);
    rendWin->Render();
    rendWin->SetSize(640, 480);

  
    renderWindowInteractor->Start();
    return 0;
}