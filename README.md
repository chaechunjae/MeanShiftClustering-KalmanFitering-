# MeanShiftClustering-KalmanFitering-
Tracking the object by MeanshiftCluster. Increase the precision by Kalman Filtering


================================================================================
    MFC 라이브러리 : Mean shift clustering 프로젝트 개요
===============================================================================

응용 프로그램 마법사에서 이 Mean shift clustering 응용 프로그램을 만들었습니다. 이 응용 프로그램은 MFC의 기본 사용법을 보여 줄 뿐만 아니라 응용 프로그램을 작성하기 위한 기본 구조를 제공합니다.

Mean shift clustering 응용 프로그램을 구성하는 각 파일에 대한
요약 설명이 포함되어 있습니다.

Mean shift clustering.vcxproj
    응용 프로그램 마법사를 사용하여 생성한 VC++ 프로젝트의 기본 프로젝트 파일입니다. 파일을 생성한 Visual C++ 버전에 대한 정보와 응용 프로그램 마법사를 사용하여 선택한 플랫폼, 구성 및 프로젝트 기능에 대한 정보가 포함되어 있습니다.

Mean shift clustering.vcxproj.filters
    응용 프로그램 마법사를 사용하여 생성된 VC++ 프로젝트의 필터 파일입니다. 이 파일에는 프로젝트의 파일과 필터 간의 연결 정보가 들어 있습니다. 이러한 연결은 특정 노드에서 유사한 확장명으로 그룹화된 파일을 표시하기 위해 IDE에서 사용됩니다. 예를 들어 ".cpp" 파일은 "소스 파일" 필터와 연결되어 있습니다.

Mean shift clustering.h
    해당 응용 프로그램의 기본 헤더 파일입니다.
    여기에는 resource.h를 비롯한 다른 프로젝트별 헤더가 포함되어 있으며 CMeanshiftclusteringApp 응용 프로그램 클래스가 선언되어 있습니다.

Mean shift clustering.cpp
    이는 응용 프로그램 클래스 CMeanshiftclusteringApp가 포함된 기본 응용 프로그램 소스 파일입니다.

Mean shift clustering.rc
    프로그램에서 사용하는 모든 Microsoft Windows 리소스의 목록입니다. 여기에는 RES 하위 디렉터리에 저장된 아이콘, 비트맵 및 커서가 포함됩니다. 이 파일은 Microsoft Visual C++에서 직접 편집할 수 있습니다. 프로젝트 리소스는 1042에 있습니다.

res\Mean shift clustering.ico
    아이콘 파일이며, 응용 프로그램의 아이콘으로 사용됩니다. 이 아이콘은 기본 리소스 파일인 Mean shift clustering.rc에 의해 포함됩니다.

res\Meanshiftclustering.rc2
    이 파일에는 Microsoft Visual C++ 이외의 다른 도구에서 편집한 리소스가 포함되어 있습니다. 리소스 편집기로 편집할 수 없는 모든 리소스는 이 파일에 넣어야 합니다.


/////////////////////////////////////////////////////////////////////////////

응용 프로그램 마법사에서 대화 상자 클래스 하나를 만듭니다.

Mean shift clusteringDlg.h, Mean shift clusteringDlg.cpp - 대화 상자
    이 파일에는 CMeanshiftclusteringDlg 클래스가 포함됩니다. 이 클래스는 응용 프로그램의 주 대화 상자에 대한 동작을 정의합니다. 이 대화 상자 템플릿은 Mean shift clustering.rc에 있으며, Microsoft Visual C++에서 직접 편집할 수 있습니다.

/////////////////////////////////////////////////////////////////////////////

기타 기능:

ActiveX 컨트롤
    응용 프로그램이 Active X 컨트롤을 지원합니다.

Windows 소켓
    응용 프로그램에서 TCP/IP 네트워크를 통한 통신을 구축할 수 있습니다.

/////////////////////////////////////////////////////////////////////////////

기타 표준 파일:

StdAfx.h, StdAfx.cpp
    이 파일은 미리 컴파일된 헤더(PCH) 파일 Mean shift clustering.pch와 미리 컴파일된 형식(PCT) 파일 StdAfx.obj를 빌드하는 데 사용됩니다.

Resource.h
    새 리소스 ID를 정의하는 표준 헤더 파일입니다. Microsoft Visual C++에서 이 파일을 읽고 업데이트합니다.

Mean shift clustering.manifest
	응용 프로그램 매니페스트 파일은 Windows XP에서 특정 버전의 Side-by-Side 어셈블리에 대한 응용 프로그램 종속성을 설명하는 데 사용됩니다. 로더는 이 정보를 통해 어셈블리 캐시 또는 응용 프로그램의 private에서 적절한 어셈블리를 로드합니다. 응용 프로그램 매니페스트는 응용 프로그램 실행 파일과 같은 폴더에 설치된 외부 .manifest 파일 형태로서 재배포용으로 포함되거나, 리소스 형태로 된 실행 파일에 포함될 수 있습니다.
/////////////////////////////////////////////////////////////////////////////

기타 참고:

응용 프로그램 마법사에서 사용하는 "TODO:"는 사용자가 추가하거나 사용자 지정해야 하는 소스 코드 부분을 나타냅니다.

공유된 DLL에서 MFC를 사용하는 응용 프로그램의 경우 MFC DLL을 재배포할 필요가 없습니다. 응용 프로그램에서 운영 체제의 로캘과 다른 언어를 사용하는 경우 이에 해당하는 지역화된 리소스인 mfc110XXX.DLL도 재배포해야 합니다.
이러한 두 항목에 대한 자세한 내용은 MSDN 설명서에 있는 Visual C++ 응용 프로그램 재배포 섹션을 참조하십시오.

/////////////////////////////////////////////////////////////////////////////
