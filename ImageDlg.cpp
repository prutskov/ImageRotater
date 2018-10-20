// ImageDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "ImageRotater.h"
#include "ImageDlg.h"
#include "afxdialogex.h"


// Диалоговое окно ImageDlg

IMPLEMENT_DYNAMIC(ImageDlg, CDialogEx)

ImageDlg::ImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGE_DLG, pParent)
{

}

ImageDlg::~ImageDlg()
{
}

void ImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ImageDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений ImageDlg
