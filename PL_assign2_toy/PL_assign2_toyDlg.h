
// PL_assign2_toyDlg.h : 헤더 파일
//

#pragma once

namespace toy
{
	class CAdapter;
}

// CPL_assign2_toyDlg 대화 상자
class CPL_assign2_toyDlg : public CDialogEx
{
// 생성입니다.
public:
	CPL_assign2_toyDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PL_ASSIGN2_TOY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	toy::CAdapter * m_pToyAdapter;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	CString m_strInfix;
	CString m_strPost;
	CString m_strResult;

	afx_msg void OnBnClickedButton2();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnEnChangeEdit2();
	CString m_CommandLine;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
};
