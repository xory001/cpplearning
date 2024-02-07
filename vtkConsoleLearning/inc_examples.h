#pragma once

#include <windows.h>
#include <iostream>

#include "../include/xlog.h"
#include "../include/vtk_8.2.0_lib.h"

#include "vtkAutoInit.h"
#include "vtkImageData.h"
#include "vtkImageViewer.h"
#include "vtkJPEGReader.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"
#include "vtkCallbackCommand.h"
#include "vtkPointPicker.h"
#include "CPointPickerlnteractorStyle.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkImageActor.h"
#include "vtkOpenGLImageSliceMapper.h"
#include "vtkTextSource.h"

int JPGShow();
int PolyDataSourceDisplay();