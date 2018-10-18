
// ImageRotaterDlg.h: файл заголовка
//

#pragma once
#include "Draw2D.h"

// Диалоговое окно CImageRotaterDlg
class CImageRotaterDlg : public CDialogEx
{
// Создание
public:
	CImageRotaterDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEROTATER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV

	std::vector<std::vector<Pixel>> _imageOriginal;
	std::vector<std::vector<Pixel>> _image;
	std::vector<std::vector<Pixel>> _imageNew;

// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Draw2D _drawer2D;
	afx_msg void OnBnClickedLoad();
	void LoadPicture();
	void RotateImage(double angle);

	double _angle;
	afx_msg void OnBnClickedButton1();
};
