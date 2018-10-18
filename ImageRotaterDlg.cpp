
// ImageRotaterDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "ImageRotater.h"
#include "ImageRotaterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CImageRotaterDlg



CImageRotaterDlg::CImageRotaterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGEROTATER_DIALOG, pParent)
	, _angle(45)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageRotaterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, _drawer2D);
	DDX_Text(pDX, IDC_ANGLE, _angle);
}

BEGIN_MESSAGE_MAP(CImageRotaterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD, &CImageRotaterDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BUTTON1, &CImageRotaterDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CImageRotaterDlg

BOOL CImageRotaterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	_drawer2D._image = &_imageOriginal;
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CImageRotaterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CImageRotaterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageRotaterDlg::OnBnClickedLoad()
{
	LoadPicture();
	_drawer2D._image = &_imageOriginal;
	_drawer2D.RedrawWindow();	
}

void CImageRotaterDlg::LoadPicture()
{
	CFileDialog fd(true, NULL, NULL, OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY |
		OFN_LONGNAMES | OFN_PATHMUSTEXIST, _T("Image Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL, 0, TRUE);

	if (fd.DoModal() != IDOK)
	{
		MessageBox(L"ERROR!!!", L"Error opening picture file.", MB_ICONERROR);
	};

	CString pathBMP = fd.GetPathName();
	Bitmap bmp(pathBMP);
	int width = bmp.GetWidth();
	int height = bmp.GetHeight();
	_imageOriginal.clear();

	for (size_t i = 0; i < height; i++)
	{
		std::vector<Pixel> bufPix;
		for (size_t j = 0; j < width; j++)
		{
			Pixel px;
			Color color;
			bmp.GetPixel(j, height - i - 1, &color);
			px.x = j;
			px.y = i;
			px.red = color.GetRed();
			px.green = color.GetGreen();
			px.blue = color.GetBlue();
			bufPix.push_back(px);
		}
		_imageOriginal.push_back(bufPix);
	}
}

void CImageRotaterDlg::RotateImage(double angle)
{
	_imageNew.clear();
	const int newSize = (int)sqrt(_imageOriginal.size()*_imageOriginal.size() + _imageOriginal[0].size()*_imageOriginal[0].size());
	const Point centerNew(newSize / 2, newSize / 2);
	std::vector<Pixel> row(newSize);
	_imageNew.resize(newSize, row);

	const int widthOld = _imageOriginal[0].size(),
		heightOld = _imageOriginal.size();
	Matrix matrix;
	Point pointNew;
	const Point center(widthOld / 2, heightOld / 2);
	matrix.Translate(center.X, center.Y);
	matrix.Rotate(angle);

	Rect rect(0, 0, widthOld, heightOld);
	for (int y = 0; y < newSize; y++)
	{
		for (int x = 0; x < newSize; x++)
		{
			pointNew.X = x - centerNew.X;
			pointNew.Y = y - centerNew.Y;
			matrix.TransformPoints(&pointNew);
			if (!rect.Contains(pointNew)) continue;
			_imageNew[y][x] = _imageOriginal[pointNew.Y][pointNew.X];
		}
	}

}


void CImageRotaterDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	RotateImage(_angle);
	_drawer2D._image = &_imageNew;
	_drawer2D.RedrawWindow();
}
