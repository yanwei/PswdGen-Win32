// PasswordGeneratorDlg.h : ͷ�ļ�
//

#pragma once

// CPasswordGeneratorDlg �Ի���
class CPasswordGeneratorDlg : public CDialog
{
// ����
public:
	CPasswordGeneratorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PASSWORDGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboPswdLength;
	CButton m_checkLetter;
	CButton m_checkLowerCase;
	CButton m_checkUpperCase;
	CButton m_checkDigital;
	CButton m_checkSpecial;
	CEdit m_editSpecialLetter;
	CEdit m_editPswdCount;

	CProgressCtrl m_progressGenerate;
	CButton m_btnSavePswd;
	CButton m_btnGeneratePswd;
	CListBox m_listPswd;

	afx_msg void OnBnClickedCheckLetter();
	afx_msg void OnBnClickedCheckSpecial();
	afx_msg void OnBnClickedBtnGeneratepswd();
	afx_msg void OnLbnDblclkListPswd();
	afx_msg void OnBnClickedBtnSavepswd();
};
