#pragma once
#include "vtkInteractorStyleTrackballCamera.h"

void RunPointPickExample();

class CPointPickerlnteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    static CPointPickerlnteractorStyle* New();
    vtkTypeMacro(CPointPickerlnteractorStyle, vtkInteractorStyleTrackballCamera);
    void PrintSelf(ostream& os, vtkIndent indent) override;

protected:
    CPointPickerlnteractorStyle();
    virtual ~CPointPickerlnteractorStyle() override;

public:
    virtual void OnLeftButtonDown() override;


private:
    CPointPickerlnteractorStyle(const CPointPickerlnteractorStyle&) = delete;
    CPointPickerlnteractorStyle& operator=(const CPointPickerlnteractorStyle&) = delete;

};

