//Edited by github.com/charmingjohn


// Mean shift clusteringDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Mean shift clustering.h"
#include "Mean shift clusteringDlg.h"
#include "afxdialogex.h"

#include <opencv2/core/utility.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMeanshiftclusteringDlg 대화 상자
TCHAR imagefolder[MAX_PATH];
TCHAR imagefiles[20000][MAX_PATH];
int   imagecount = 0;
int   imageindex = 0;
int   show_images = 0;

void load_unicode_image(TCHAR *imgfn, Mat& img);

CMeanshiftclusteringDlg::CMeanshiftclusteringDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMeanshiftclusteringDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMeanshiftclusteringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_folder);
}

BEGIN_MESSAGE_MAP(CMeanshiftclusteringDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMeanshiftclusteringDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMeanshiftclusteringDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMeanshiftclusteringDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK3, &CMeanshiftclusteringDlg::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK2, &CMeanshiftclusteringDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CMeanshiftclusteringDlg 메시지 처리기

BOOL CMeanshiftclusteringDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetTimer(1, 50, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMeanshiftclusteringDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMeanshiftclusteringDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int _main(int argc, const char** argv);

Mat image_t;

void InitTrace();
void Track(Mat& image);
void proc_init(Mat& frame);

int tracker_type = 1; // 디폴트 트랙커 1

void CMeanshiftclusteringDlg::OnBnClickedOk()
{
	namedWindow("test", 0);
	tracker_type = 1; // 디폴트 트랙커 1

	if (imagecount > 0) {
//		InitTrace();
		load_unicode_image(imagefiles[0], image_t);
		proc_init(image_t);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		show_images = 1;
//	_main(1, NULL);
	}

	//CDialogEx::OnOK();
}

void proc_loop(Mat& frame);
void kalman_loop(Mat& frame);

void load_unicode_image(TCHAR *imgfn, Mat& img)
{
	char imgname[MAX_PATH];
	// opencv는 unicode를 못 읽는다. 그래서 변환한다.
	WideCharToMultiByte(CP_ACP, 0, imagefiles[imageindex], lstrlen(imagefiles[imageindex]) + 1, imgname, MAX_PATH, NULL, NULL);
	img = imread(imgname);
}

void CMeanshiftclusteringDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!show_images)
		return;

	load_unicode_image(imagefiles[imageindex], image_t);
/*	if (!image_t.empty()) {
		imshow("test", image_t);
	}*/
//	Track(image_t);
	if (tracker_type == 1) // mean shift loop
		proc_loop(image_t);
	else {
		kalman_loop(image_t);
	}

	imageindex++;
	if(imageindex >= imagecount)
		imageindex = 0;

	CDialogEx::OnTimer(nIDEvent);
}

// 초기 셋팅 시 '경로'를 무조건 나오게 할려면
int CALLBACK BICallBackFunc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		if (lpData)
			::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);      // lpData 가 경로
		break;
	}
	return 0;
}
BOOL BrowseFolder(HWND hWnd, TCHAR *pszPathname, LPARAM lParam, DWORD flag)
{
	ITEMIDLIST*  pildBrowse;
	BROWSEINFO  bInfo;
	memset(&bInfo, 0, sizeof(bInfo));
	bInfo.hwndOwner = hWnd;
	bInfo.pidlRoot = NULL;
	bInfo.pszDisplayName = pszPathname;
	bInfo.lpszTitle = _T("디렉토리를 선택하세요");             // dialog title
	bInfo.ulFlags = flag;                 // 여러가지 옵션이 존재합니다.. msdn을 참고해보세요.
	bInfo.lpfn = BICallBackFunc;                        // 옵션? 입니다.. 초기 경로 설정등을 할때는 여기에 추가하세요.
	bInfo.lParam = (LPARAM)(LPCTSTR)lParam;
	pildBrowse = ::SHBrowseForFolder(&bInfo);
	if (!pildBrowse)
		return FALSE;
	SHGetPathFromIDList(pildBrowse, pszPathname);
	return TRUE;
}

int ShowFolderDialog(HWND hWnd, TCHAR* buf)
{
	TCHAR   pszPathname[MAX_PATH];
	if (BrowseFolder(hWnd, pszPathname, (LPARAM)buf, BIF_RETURNONLYFSDIRS | BIF_VALIDATE)) {
		lstrcpy(buf, (LPCTSTR)pszPathname);                                // => 실제 선택한 폴더가 전체 경로로 나옵니다.
		return TRUE;
	}
	return FALSE;
}

// 파일 이름에 00이 안 붙어오니까 내 맘대로 소팅하자
void sort_image()
{
	for (int i = 0; i < imagecount - 1; i++) {
		for (int j = i + 1; j < imagecount; j++) {
			int ix0 = StrToInt(imagefiles[i]);
			int ix1 = StrToInt(imagefiles[j]);
			if(ix0 > ix1) {
				TCHAR ft[MAX_PATH];
				lstrcpy(ft, imagefiles[i]);
				lstrcpy(imagefiles[i], imagefiles[j]);
				lstrcpy(imagefiles[j], ft);
			}
		}
	}
}

void CMeanshiftclusteringDlg::OnBnClickedButton1()
{
// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowFolderDialog(this->m_hWnd, imagefolder);
	SetDlgItemText(IDC_EDIT1, imagefolder);

	// 선택한 폴더의 이미지 이름을 모두 가져온다
	WIN32_FIND_DATA wfd;
	TCHAR srchfolder[MAX_PATH];
	lstrcpy(srchfolder, imagefolder);
	lstrcat(srchfolder, L"\\*.jpg");
	imagecount = 0;
	imageindex = 0;
	HANDLE hfind = FindFirstFile(srchfolder, &wfd);
	while (hfind != INVALID_HANDLE_VALUE) {
		lstrcat(imagefiles[imagecount], wfd.cFileName);
		imagecount++; // 파일 갯수 증가
		if (!FindNextFile(hfind, &wfd)) {
			FindClose(hfind);
			break;
		}
	}
	sort_image();
	// 폴더 붙이기~ ^^
	TCHAR ft[MAX_PATH];
	for (int i = 0; i < imagecount; i++) {
		lstrcpy(ft, imagefolder);
		lstrcat(ft, L"\\");
		lstrcat(ft, imagefiles[i]);
		lstrcpy(imagefiles[i], ft);
	}

	if (imagecount == 0) {
		MessageBox(L"이미지 파일이 없습니다");
	} else {
		TCHAR msg[256];
		wsprintf(msg, L"이미지 파일이 %d개 입니다", imagecount);
		MessageBox(msg);
	}

}


void CMeanshiftclusteringDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowFolderDialog(this->m_hWnd, imagefolder);
	SetDlgItemText(IDC_EDIT2, imagefolder);

	// 선택한 폴더의 이미지 이름을 모두 가져온다
	WIN32_FIND_DATA wfd;
	TCHAR srchfolder[MAX_PATH];
	lstrcpy(srchfolder, imagefolder);
	lstrcat(srchfolder, L"\\*.jpg");
	imagecount = 0;
	imageindex = 0;
	HANDLE hfind = FindFirstFile(srchfolder, &wfd);
	while (hfind != INVALID_HANDLE_VALUE) {
		lstrcat(imagefiles[imagecount], wfd.cFileName);
		imagecount++; // 파일 갯수 증가
		if (!FindNextFile(hfind, &wfd)) {
			FindClose(hfind);
			break;
		}
	}
	sort_image();
	// 폴더 붙이기~ ^^
	TCHAR ft[MAX_PATH];
	for (int i = 0; i < imagecount; i++) {
		lstrcpy(ft, imagefolder);
		lstrcat(ft, L"\\");
		lstrcat(ft, imagefiles[i]);
		lstrcpy(imagefiles[i], ft);
	}

	if (imagecount == 0) {
		MessageBox(L"이미지 파일이 없습니다");
	}
	else {
		TCHAR msg[256];
		wsprintf(msg, L"이미지 파일이 %d개 입니다", imagecount);
		MessageBox(msg);
	}
}

void kalman_capture(TCHAR *folder);

void CMeanshiftclusteringDlg::OnBnClickedOk3()
{
	kalman_capture(imagefolder);
}

void kalman_init();
void kalman_loop(Mat& frame);

void CMeanshiftclusteringDlg::OnBnClickedOk2()
{
	if (imagecount > 0) {
		//		InitTrace();
		load_unicode_image(imagefiles[0], image_t);
		kalman_init();

		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		show_images = 1;
		//	_main(1, NULL);
		tracker_type = 2; // 디폴트 트랙커 1
	}
}
