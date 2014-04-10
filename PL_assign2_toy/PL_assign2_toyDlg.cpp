
// PL_assign2_toyDlg.cpp : ���� ����
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


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CPL_assign2_toyDlg ��ȭ ����



CPL_assign2_toyDlg::CPL_assign2_toyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPL_assign2_toyDlg::IDD, pParent)
	, m_strInfix(_T(""))
	, m_strResult(_T(""))
	, m_strPost(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPL_assign2_toyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strInfix);
	DDX_Text(pDX, IDC_EDIT4, m_strResult);
	DDX_Text(pDX, IDC_EDIT3, m_strPost);
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
END_MESSAGE_MAP()


// CPL_assign2_toyDlg �޽��� ó����

BOOL CPL_assign2_toyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	{
		this->m_pToyAdapter = new toy::CAdapter();
	}

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CPL_assign2_toyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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

	}
}

/* on Parse */
void CPL_assign2_toyDlg::OnBnClickedButton4()
{
	UpdateData(true);
	//std::string infix = toy::CUtil::ConvertString(m_strInfix);
	std::wstring infix(m_strInfix);
	m_pToyAdapter->Parse(infix);
	UpdateData(false);
}
