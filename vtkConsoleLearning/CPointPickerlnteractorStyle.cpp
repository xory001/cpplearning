#include "vtkObjectFactory.h"
#include "CPointPickerlnteractorStyle.h"
#include "vtkSphereSource.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkAbstractPicker.h"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "vtkPointPicker.h"

vtkStandardNewMacro(CPointPickerlnteractorStyle);

CPointPickerlnteractorStyle::CPointPickerlnteractorStyle()
{

}

CPointPickerlnteractorStyle::~CPointPickerlnteractorStyle()
{

}

void CPointPickerlnteractorStyle::OnLeftButtonDown()
{
    std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
    this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
        this->Interactor->GetEventPosition()[1],
        0,  // always zero.
        this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
    double picked[3];
    this->Interactor->GetPicker()->GetPickPosition(picked);
    std::cout << "Picked value: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;

    vtkSmartPointer<vtkSphereSource> sphereSource =
        vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->SetPosition(picked);
    actor->SetScale(0.05);
    actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
    this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor);

    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void CPointPickerlnteractorStyle::PrintSelf(ostream& os, vtkIndent indent)
{
    os << "CPointPickerlnteractorStyle, ";
}



void RunPointPickExample()
{
    vtkSmartPointer<vtkSphereSource> sphereSource =
        vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkSmartPointer<vtkActor> actor =
        vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // Create a renderer, render window, and interactor
    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->Render();
    renderWindow->SetWindowName("PointPicker");
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkPointPicker> pointPicker =
        vtkSmartPointer<vtkPointPicker>::New();

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetPicker(pointPicker);
    renderWindowInteractor->SetRenderWindow(renderWindow);

    vtkSmartPointer<CPointPickerlnteractorStyle> style =
        vtkSmartPointer<CPointPickerlnteractorStyle>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    // Add the actor to the scene
    renderer->AddActor(actor);
    renderer->SetBackground(1, 1, 1);

    // Render and interact
    renderWindow->Render();
    renderWindowInteractor->Start();
}


