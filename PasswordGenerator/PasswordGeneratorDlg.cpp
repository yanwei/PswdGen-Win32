// PasswordGeneratorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PasswordGenerator.h"
#include "PasswordGeneratorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const CString c_strSpecial = _T("`~!@#$%^&*()-_=+[{]}\\|;:\'\",<.>/?");

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPasswordGeneratorDlg �Ի���




CPasswordGeneratorDlg::CPasswordGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordGeneratorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPasswordGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PSWDLENGTH, m_comboPswdLength);
	DDX_Control(pDX, IDC_CHECK_LETTER, m_checkLetter);
	DDX_Control(pDX, IDC_CHECK_LOWERCASE, m_checkLowerCase);
	DDX_Control(pDX, IDC_CHECK_UPPERCASE, m_checkUpperCase);
	DDX_Control(pDX, IDC_CHECK_DIGITAL, m_checkDigital);
	DDX_Control(pDX, IDC_CHECK_SPECIAL, m_checkSpecial);
	DDX_Control(pDX, IDC_EDIT_SPECIAL, m_editSpecialLetter);
	DDX_Control(pDX, IDC_EDIT_PSWD_COUNT, m_editPswdCount);
	DDX_Control(pDX, IDC_PROGRESS_GENERATE, m_progressGenerate);
	DDX_Control(pDX, IDC_LIST_PSWD, m_listPswd);
	DDX_Control(pDX, IDC_BTN_SAVEPSWD, m_btnSavePswd);
	DDX_Control(pDX, IDC_BTN_GENERATEPSWD, m_btnGeneratePswd);
}

BEGIN_MESSAGE_MAP(CPasswordGeneratorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_LETTER, &CPasswordGeneratorDlg::OnBnClickedCheckLetter)
	ON_BN_CLICKED(IDC_CHECK_SPECIAL, &CPasswordGeneratorDlg::OnBnClickedCheckSpecial)
	ON_BN_CLICKED(IDC_BTN_GENERATEPSWD, &CPasswordGeneratorDlg::OnBnClickedBtnGeneratepswd)
	ON_LBN_DBLCLK(IDC_LIST_PSWD, &CPasswordGeneratorDlg::OnLbnDblclkListPswd)
	ON_BN_CLICKED(IDC_BTN_SAVEPSWD, &CPasswordGeneratorDlg::OnBnClickedBtnSavepswd)
END_MESSAGE_MAP()


// CPasswordGeneratorDlg ��Ϣ�������

BOOL CPasswordGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	for (int i = 8; i <= 16; i ++)
	{
		CString strPswdLength;
		strPswdLength.Format(_T("%d"), i);
		m_comboPswdLength.AddString(strPswdLength);
	}
	m_comboPswdLength.SetCurSel(0);

	m_checkLetter.SetCheck(BST_CHECKED);
	m_checkLowerCase.SetCheck(BST_CHECKED);
	m_checkUpperCase.SetCheck(BST_CHECKED);
	m_checkDigital.SetCheck(BST_CHECKED);
	m_checkSpecial.SetCheck(BST_CHECKED);
	m_editSpecialLetter.SetWindowText(c_strSpecial);
	m_editPswdCount.SetWindowText(_T("10"));
	m_btnSavePswd.EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPasswordGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPasswordGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPasswordGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPasswordGeneratorDlg::OnBnClickedCheckLetter()
{
	// TODO: Add your control notification handler code here
	if (m_checkLetter.GetCheck() == BST_CHECKED)
	{
		m_checkLowerCase.EnableWindow(TRUE);
		m_checkUpperCase.EnableWindow(TRUE);
	}
	else
	{
		m_checkLowerCase.EnableWindow(FALSE);
		m_checkUpperCase.EnableWindow(FALSE);
	}
}

void CPasswordGeneratorDlg::OnBnClickedCheckSpecial()
{
	// TODO: Add your control notification handler code here
	if (m_checkSpecial.GetCheck() == BST_CHECKED)
	{
		m_editSpecialLetter.EnableWindow(TRUE);
	}
	else
	{
		m_editSpecialLetter.EnableWindow(FALSE);
	}
}

void CPasswordGeneratorDlg::OnBnClickedBtnGeneratepswd()
{
	//////////////////////////////////////////////////////////////////////////
	// ����û���������
	CString strPswdLength;
	m_comboPswdLength.GetWindowText(strPswdLength);
	int iPswdLength = _tstoi(strPswdLength);
	CString strPswdCount;
	m_editPswdCount.GetWindowText(strPswdCount);
	int iPswdCount = _tstoi(strPswdCount);
	CString strSpecial;
	m_editSpecialLetter.GetWindowText(strSpecial);

	// ����û���ѡ���Ƿ���ȷ���Ƿ�������������Ҫ��
	if (iPswdLength < 6 || iPswdLength > 64)
	{
		AfxMessageBox(_T("�����볤�ȡ��������6-64λ֮�䣬������ѡ��"));
		return;
	}
	if (m_checkLetter.GetCheck() != BST_CHECKED &&
		m_checkDigital.GetCheck() != BST_CHECKED &&
		m_checkSpecial.GetCheck() != BST_CHECKED)
	{
		AfxMessageBox(_T("������ѡ����ĸ���������֡��������ַ����е�һ�֡�"));
		return;
	}
	if (m_checkLetter.GetCheck() == BST_CHECKED)
	{
		if (m_checkLowerCase.GetCheck() != BST_CHECKED &&
			m_checkUpperCase.GetCheck() != BST_CHECKED)
		{
			AfxMessageBox(_T("������ѡ��Сд���򡾴�д���е�һ����"));
			return;
		}
	}
	if (m_checkSpecial.GetCheck() == BST_CHECKED)
	{
		if (strSpecial.IsEmpty())
		{
			AfxMessageBox(_T("��������š��б�Ϊ�ա�"));
			return;
		}
		for (int i = 0; i < strSpecial.GetLength(); i ++)
		{
			if (c_strSpecial.Find(strSpecial.GetAt(i)) < 0)
			{
				AfxMessageBox(_T("��������š��б��а�����ĸ�����顢�ո��������֧�ֵķ��š�"));
				return;
			}
		}
	}
	if (iPswdCount < 1 || iPswdCount > 1000)
	{
		AfxMessageBox(_T("�����ɸ������������1-1000֮�䣬���������롣"));
		return;
	}

	m_btnGeneratePswd.EnableWindow(FALSE);
	m_btnSavePswd.EnableWindow(FALSE);
	// ���ɿ�������������ĺϷ��ַ��б�
	CString strValidChar;
	if (m_checkLetter.GetCheck() == BST_CHECKED)
	{
		if (m_checkLowerCase.GetCheck() == BST_CHECKED)
		{
			for (TCHAR c = _T('a'); c <= _T('z'); c ++)
			{
				strValidChar.AppendChar(c);
			}
		}
		if (m_checkUpperCase.GetCheck() == BST_CHECKED)
		{
			for (TCHAR c = _T('A'); c <= _T('Z'); c ++)
			{
				strValidChar.AppendChar(c);
			}
		}
	}
	if (m_checkDigital.GetCheck() == BST_CHECKED)
	{
		for (TCHAR c = _T('0'); c <= _T('9'); c ++)
		{
			strValidChar.AppendChar(c);
		}
	}
	if (m_checkSpecial.GetCheck() == BST_CHECKED)
	{
		strValidChar.Append(strSpecial);
	}

	// ��ʼ��������
	m_listPswd.ResetContent();
	m_progressGenerate.SetRange32(0, iPswdCount);
	int iCurPswd = 0;
	while (iCurPswd < iPswdCount)
	{
		// ����һ������
		CString strCurPswd = _T("");
		unsigned int uRandNum;
		for (int i = 0; i < iPswdLength; i ++)
		{
			rand_s(&uRandNum);
			strCurPswd.AppendChar(strValidChar.GetAt(uRandNum % strValidChar.GetLength()));
		}

		// ���������ɵ������Ƿ�����Ҫ��
		if (m_checkLetter.GetCheck() == BST_CHECKED)
		{
			if (m_checkLowerCase.GetCheck() == BST_CHECKED)
			{
				BOOL bHaveLowerCaseLetter = FALSE;
				for (int i = 0; i < strCurPswd.GetLength(); i ++)
				{
					if (strCurPswd.GetAt(i) >= _T('a') &&
						strCurPswd.GetAt(i) <= _T('z'))
					{
						bHaveLowerCaseLetter =TRUE;
						break;
					}
				}
				if (!bHaveLowerCaseLetter)
					continue;
			}

			if (m_checkUpperCase.GetCheck() == BST_CHECKED)
			{
				BOOL bHaveUpperCaseLetter = FALSE;
				for (int i = 0; i < strCurPswd.GetLength(); i ++)
				{
					if (strCurPswd.GetAt(i) >= _T('A') &&
						strCurPswd.GetAt(i) <= _T('Z'))
					{
						bHaveUpperCaseLetter = TRUE;
						break;
					}
				}
				if (!bHaveUpperCaseLetter)
					continue;
			}
		}
		if (m_checkDigital.GetCheck() == BST_CHECKED)
		{
			BOOL bHaveDigital = FALSE;
			for (int i = 0; i < strCurPswd.GetLength(); i ++)
			{
				if (strCurPswd.GetAt(i) >= _T('0') &&
					strCurPswd.GetAt(i) <= _T('9'))
				{
					bHaveDigital = TRUE;
					break;
				}
			}
			if (!bHaveDigital)
				continue;
		}
		if (m_checkSpecial.GetCheck() == BST_CHECKED)
		{
			BOOL bHaveSpecial = FALSE;
			for (int i = 0; i < strCurPswd.GetLength(); i ++)
			{
				if (strSpecial.Find(strCurPswd.GetAt(i)) >= 0)
				{
					bHaveSpecial = TRUE;
					break;
				}
			}
			if (!bHaveSpecial)
				continue;
		}

		// �����ɵ���������б�
		m_listPswd.AddString(strCurPswd);
		iCurPswd ++;
		m_progressGenerate.SetPos(iCurPswd);
	}
	m_btnGeneratePswd.EnableWindow(TRUE);
	m_btnSavePswd.EnableWindow(TRUE);
}

void CPasswordGeneratorDlg::OnLbnDblclkListPswd()
{
	int iCurSel = m_listPswd.GetCurSel();
	if (iCurSel >=0 && iCurSel < m_listPswd.GetCount())
	{
		CString strPswd;
		m_listPswd.GetText(iCurSel, strPswd);
		if (OpenClipboard())
		{
			EmptyClipboard();

			HGLOBAL clipbuffer;
			TCHAR *szBuffer;
			clipbuffer = GlobalAlloc(GMEM_DDESHARE, (strPswd.GetLength() + 1) * sizeof(TCHAR));
			szBuffer = (TCHAR *)GlobalLock(clipbuffer);
			_tcscpy_s(szBuffer, strPswd.GetLength() + 1, strPswd);
			GlobalUnlock(clipbuffer);
#ifdef _UNICODE
			SetClipboardData(CF_UNICODETEXT, clipbuffer);
#else
			SetClipboardData(CF_TEXT, clipbuffer);
#endif
			CloseClipboard();

			AfxMessageBox(_T("��") + strPswd + _T("���Ѿ������������塣"));
		}
	}
}

void CPasswordGeneratorDlg::OnBnClickedBtnSavepswd()
{
	CString strFileName;
	CTime timeCur = CTime::GetCurrentTime();
	strFileName.Format(_T("�������%s.txt"), timeCur.Format(_T("%Y%m%d-%H%M%S")));
	CFileDialog dlgFile(FALSE,
						_T("txt"),
						strFileName,
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						_T("�ı��ļ� (*.txt)|*.txt||"),
						NULL,
						0);
	if (dlgFile.DoModal() == IDOK)
	{
		CString strNewFilePath = dlgFile.GetPathName();
		if (strNewFilePath.Right(4).CompareNoCase(_T(".txt")) != 0)
		{
			strNewFilePath += _T(".txt");
		}

		CStdioFile fileRslt;
		if (fileRslt.Open(strNewFilePath, CFile::modeCreate | CFile::modeWrite))
		{
			for (int i = 0; i < m_listPswd.GetCount(); i ++)
			{
				CString strCurLine;
				m_listPswd.GetText(i, strCurLine);

				fileRslt.WriteString(strCurLine);
				fileRslt.WriteString(_T("\n"));
			}

			fileRslt.Close();
			AfxMessageBox(_T("�����ѱ��档"), MB_ICONINFORMATION);
		}
	}
}
