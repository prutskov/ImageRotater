#pragma once


// Диалоговое окно ImageDlg

class ImageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ImageDlg)

public:
	ImageDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~ImageDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
