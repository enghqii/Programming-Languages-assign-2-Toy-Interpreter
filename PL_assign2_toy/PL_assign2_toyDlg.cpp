
// PL_assign2_toyDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "PL_assign2_toy.h"
#include "PL_assign2_toyDlg.h"
#include "afxdialogex.h"

#include "Adapter.h"
#include "Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPL_assign2_toyDlg 대화 상자



CPL_assign2_toyDlg::CPL_assign2_toyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPL_assign2_toyDlg::IDD, pParent)
	, m_strInfix(_T(""))
	, m_strResult(_T(""))
	, m_strPost(_T(""))
	, m_CommandLine(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPL_assign2_toyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strInfix);
	DDX_Text(pDX, IDC_EDIT4, m_strResult);
	DDX_Text(pDX, IDC_EDIT3, m_strPost);
	DDX_Text(pDX, IDC_EDIT2, m_CommandLine);
}

BEGIN_MESSAGE_MAP(CPL_assign2_toyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPL_assign2_toyDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPL_assign2_toyDlg::OnBnClickedButton2)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON3, &CPL_assign2_toyDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPL_assign2_toyDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CPL_assign2_toyDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CPL_assign2_toyDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CPL_assign2_toyDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CPL_assign2_toyDlg::OnBnClickedButton8)
	ON_EN_CHANGE(IDC_EDIT2, &CPL_assign2_toyDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON9, &CPL_assign2_toyDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CPL_assign2_toyDlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// CPL_assign2_toyDlg 메시지 처리기

BOOL CPL_assign2_toyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	{
		this->m_pToyAdapter = new toy::CAdapter();
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPL_assign2_toyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPL_assign2_toyDlg::OnPaint()
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
HCURSOR CPL_assign2_toyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/* on DESTORY */
void CPL_assign2_toyDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// dtor here
	{
		delete m_pToyAdapter;
	}
}

/* on EXIT */
void CPL_assign2_toyDlg::OnBnClickedButton1()
{
	CDialog::OnCancel();
}

/* on CLEAR*/
void CPL_assign2_toyDlg::OnBnClickedButton2()
{
	UpdateData(true);
	
	m_strInfix	= L"";
	m_strPost	= L"";
	m_strResult = L"";

	UpdateData(false);
}

/* on LOAD SOURCE*/
void CPL_assign2_toyDlg::OnBnClickedButton3()
{
	// Obtain current dir path
	TCHAR szDirectory[512] = L"";
	::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);

	// File selecting dir
	CFileDialog dlg(true, NULL,NULL, OFN_HIDEREADONLY);
	dlg.m_ofn.lpstrInitialDir = szDirectory;

	if(IDOK == dlg.DoModal()){
		CString strPathName = dlg.GetPathName();

		if(m_pToyAdapter->LoadSource(strPathName)){

			UpdateData(true);
			m_strInfix = m_pToyAdapter->GetSourceString();
			UpdateData(false);
			MessageBox(L"Load done.");
		}
		else
		{
			MessageBox(L"Load failed.");
		}
	}
}

// Save Source
void CPL_assign2_toyDlg::OnBnClickedButton10()
{
	UpdateData(true);
	// Obtain current dir path
	TCHAR szDirectory[512] = L"";
	::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);

	// File selecting dir
	CFileDialog dlg(false, NULL, NULL, OFN_OVERWRITEPROMPT, NULL);
	dlg.m_ofn.lpstrInitialDir = szDirectory;

	if(IDOK == dlg.DoModal()){
		CString strPathName = dlg.GetPathName();
		if(m_pToyAdapter->SaveSource(strPathName, m_strInfix))
		{
			MessageBox(L"Save done.");
		}
		else{
			MessageBox(L"Save failed.");
		}
	}
	UpdateData(false);
}

/* on Parse */
void CPL_assign2_toyDlg::OnBnClickedButton4()
{
	UpdateData(true);

	std::list<std::wstring> sources;
	sources.clear();

	/* Separate strings line by line */
	{
		// Tokenize has side-effect on 'curpos'
		int		curpos = 0;
		CString resToken = m_strInfix.Tokenize(L"\r\n", curpos);

		while (resToken != _T(""))
		{
			std::wstring wstr = resToken;
			sources.push_back(wstr);
			resToken = m_strInfix.Tokenize(L"\r\n", curpos);
		}
	}

	if( m_pToyAdapter->Parse(sources) )
	{
		// generate interms
		m_pToyAdapter->GenerateIntermediateString();

		// get and append strings
		m_strPost = m_pToyAdapter->GetPostFixString();
		m_strPost.Append(L"\r\n\r\n");
		m_strPost.Append(m_pToyAdapter->GetIntermediateString());
	}
	else
	{
	}
	
	m_strResult += m_pToyAdapter->GetResultString();
	m_strResult += L"\r\n";

	UpdateData(false);
}


/* on save intermediate code */
void CPL_assign2_toyDlg::OnBnClickedButton6()
{
	// Obtain current dir path
	TCHAR szDirectory[512] = L"";
	::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);

	// File selecting dir
	CFileDialog dlg(false, NULL, NULL, OFN_OVERWRITEPROMPT, NULL);
	dlg.m_ofn.lpstrInitialDir = szDirectory;

	if(IDOK == dlg.DoModal()){
		CString strPathName = dlg.GetPathName();
		if(m_pToyAdapter->SaveIntermediateCode(strPathName))
		{
			MessageBox(L"Save done.");
		}
		else{
			MessageBox(L"Save failed.");
		}
	}
}


/* on load intermediate code */
void CPL_assign2_toyDlg::OnBnClickedButton7()
{
	// Obtain current dir path
	TCHAR szDirectory[512] = L"";
	::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);

	// File selecting dir
	CFileDialog dlg(true, NULL,NULL, OFN_HIDEREADONLY);
	dlg.m_ofn.lpstrInitialDir = szDirectory;

	if(IDOK == dlg.DoModal()){
		CString strPathName = dlg.GetPathName();
		//m_Game.LoadGame(strPathName);

		if(m_pToyAdapter->LoadIntermediateCode(strPathName)){
			UpdateData(true);
			m_strPost= m_pToyAdapter->GetIntermediateString();
			UpdateData(false);
			MessageBox(L"Load done.");
		}
		else
		{
			MessageBox(L"Load failed.");
		}
	}
}

/* on execution */
void CPL_assign2_toyDlg::OnBnClickedButton8()
{
	UpdateData(true);

	m_pToyAdapter->Execute();

	m_strResult += m_pToyAdapter->GetResultString();
	m_strResult += L"\r\n";

	UpdateData(false);
}


void CPL_assign2_toyDlg::OnEnChangeEdit2()
{

}

/* Load defun */
void CPL_assign2_toyDlg::OnBnClickedButton5()
{
	m_pToyAdapter->LoadDefun();

	UpdateData(true);
	m_strInfix = m_pToyAdapter->GetSourceString();
	UpdateData(false);
}

void CPL_assign2_toyDlg::OnBnClickedButton9()
{
	UpdateData(true);
	m_pToyAdapter->SaveDefun(m_strInfix);
	UpdateData(false);
}



BOOL CPL_assign2_toyDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_RETURN &&
		GetFocus() == GetDlgItem(IDC_EDIT2))
	{
		UpdateData(true);

		int		curpos = 0;
		CString resToken = m_CommandLine.Tokenize(L"\r\n", curpos);

		while (true)
		{
			CString temp = m_CommandLine.Tokenize(L"\r\n", curpos);
			if( temp == _T("") )
				break;

			resToken = temp;
		}

		OutputDebugString( resToken + L"\n" );
		UpdateData(false);

		std::wstring command(resToken);

		if(command.substr(0,7) == L"compile")
		{
			std::wstring arg = command.substr(8,command.length());

			// clear, defun, prog
			m_pToyAdapter->ClearSource();
			m_pToyAdapter->LoadDefun();
			m_pToyAdapter->LoadSource(CString(arg.c_str()));

			// and parse
			{
				UpdateData(true);
				if( m_pToyAdapter->Parse(m_pToyAdapter->GetListCode()) )
				{
					// generate interms
					m_pToyAdapter->GenerateIntermediateString();

					// get and append strings
					m_strPost = m_pToyAdapter->GetPostFixString();
					m_strPost.Append(L"\r\n\r\n");
					m_strPost.Append(m_pToyAdapter->GetIntermediateString());
				}
				else
				{
				}

				m_strResult += m_pToyAdapter->GetResultString();
				m_strResult += L"\r\n";

				UpdateData(false);
			}
			
			// save obj
			std::wstring objName = arg.substr(0, arg.length() - 2) + L".o" ;
			m_pToyAdapter->SaveIntermediateCode(objName.c_str());

		}
		else if(command.substr(0,3) == L"run")
		{
			std::wstring arg = command.substr(4,command.length());

			// load obj
			m_pToyAdapter->LoadIntermediateCode(CString(arg.c_str()));
			
			// and run
			this->OnBnClickedButton8();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

