#**********************************************************************
#
#  Copyright (c) ������, �޻���. All rights reserved.
#  ������Ϣ�����: 
#    http://www.vtkchina.org (VTK�й�)
#	 http://blog.csdn.net/www_doling_net (���鹤����) 
#
#**********************************************************************

CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( vtkDialog )

#----------------------------------------------------------------------------------
# ���Ҳ�����VTK���߰�
FIND_PACKAGE( VTK )
IF (VTK_FOUND)
  INCLUDE (${VTK_USE_FILE})
ELSE (VTK_FOUND)
  MESSAGE (FATAL_ERROR "Cannot build without VTK. Please set VTK_DIR")
ENDIF( VTK_FOUND )

#----------------------------------------------------------------------------------
# �������ӱ����̵��ļ�
# ��Ҫ��Ϊ������:
# һ���½��ĵ��ĵ������еķǹ����ļ�
# �����û��������ӵ����ļ�
SET( PROJECT_SRCS
    stdafx.h
    stdafx.cpp
    vtkDialog.h
    vtkDialog.cpp
    vtkDialogDlg.h
    vtkDialogDlg.cpp
    vtkView.h
    vtkView.cpp
    vtkView3D.h
    vtkView3D.cpp
    targetver.h
    Resource.h
    vtkDialog.rc
    res/vtkDialog.rc2
    res/vtkDialog.ico
 )

#----------------------------------------------------------------------------------
# ���ù��̰�����vtkģ�飬���������Ҫ���ض�Ӧ��ģ��
INCLUDE("${VTK_DIR}/GUISupport/MFC/VTKMFCSettings.cmake")
SET( VTK_LIBS ${vtk_libraries} 
              vtkMFC
              vtkIO
              vtkRendering 
              vtkGraphics 
			  vtkHybrid 
              vtkFiltering 
	          vtkCommon 
	          vtkImaging
	          vtkWidgets
   )

VTK_MFC_ADD_DELAYLOAD_FLAGS(CMAKE_EXE_LINKER_FLAGS
    vtkMFC.dll
    vtkIO.dll
    vtkRendering.dll
    vtkGraphics.dll
    vtkHybrid.dll
    vtkFiltering.dll
    vtkCommon.dll
    vtkImaging.dll
    )
    
#----------------------------------------------------------------------------------
ADD_EXECUTABLE( vtkDialog WIN32  ${PROJECT_SRCS} )
TARGET_LINK_LIBRARIES ( vtkDialog ${VTK_LIBS} )

#----------------------------------------------------------------------------------
# Construct a list of paths containing runtime directories for project applications on Windows.
# Create two batch files which correctly set up the environment for the application and for Visual Studio.
IF(WIN32)
  SET(PROJECT_RUNTIME_PATH "${VTK_DIR}/bin/@VS_BUILD_TYPE@")
  INCLUDE(CreateWindowsBatchScript.cmake)
  SET(VS_SOLUTION_FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.sln")
  FOREACH(VS_BUILD_TYPE Debug Release)
    CreateWindowsBatchScript("${CMAKE_SOURCE_DIR}/StartVS.bat.in"
      ${PROJECT_BINARY_DIR}/StartVS_${VS_BUILD_TYPE}.bat
      ${VS_BUILD_TYPE})
  ENDFOREACH()
ENDIF(WIN32)