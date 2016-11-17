//cflags=-std=gnu++0x -Wl,-subsystem,windows -mwindows
//showcompile=1
#include<windows.h>
#include <time.h>
#include <stdio.h>
#include <iostream> 
#include <fstream>

#define LOAD	1
#define APPLY	2
#define APPLY_GETPIXEL	3
#define START_TESTS	4
#define DOUBLE_BLUE_CHANEL 5


LPCTSTR OpenFile();
int save_bmp(HDC hdc, HBITMAP bm, int width, int height);
LRESULT CALLBACK DCDemoWndProc(HWND, UINT, WPARAM, LPARAM);
void setPixelDisplay(HWND hwnd, HBITMAP hBitmap);
void setBlt(HWND hWnd, HBITMAP hBitmap);
void doubleBlueChanel(HWND hwnd, HBITMAP hBitmap);

void execute(HWND hwnd);


PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);

static bool MouseClick = FALSE; //переменная состояния клавиши мыши, изначально - "не нажата" 

typedef struct
{
	BITMAPINFOHEADER bmiHeader;
	RGBQUAD bmiColors[259];
} DIBINFO;

bool isLoaded = false;
LPCTSTR fileName;
HDC hDC;
PAINTSTRUCT PaintStruct;
HDC hCompatibleDC;
HANDLE hOldBitmap;
BITMAP Bitmap;
HBITMAP hBitmap;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;  
	WNDCLASS WndClass;
	MSG Msg;
	char szClassName[] = "DCDemo";

	// Set window attributes
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = DCDemoWndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = "MyMenu";
	WndClass.lpszClassName = szClassName;

	// Trying to register window
	if (!RegisterClass(&WndClass)) {
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}

	// Creating window
	hWnd = CreateWindow(szClassName, "Image",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);
	if (!hWnd) {
		MessageBox(NULL, "Cannot create window", "Error", MB_OK);
		return 0;
	}

	// Showing window and handling his messages
	ShowWindow(hWnd, SW_SHOWDEFAULT);

	HMENU MainMenu;
	MainMenu = CreateMenu();
	AppendMenu(MainMenu, MF_STRING, LOAD, TEXT("Загрузить"));
	AppendMenu(MainMenu, MF_STRING, APPLY, TEXT("Применить BitBlt"));
	AppendMenu(MainMenu, MF_STRING, START_TESTS, TEXT("Начать тесты"));
	AppendMenu(MainMenu, MF_STRING, APPLY_GETPIXEL, TEXT("GetPixel"));
	AppendMenu(MainMenu, MF_STRING, DOUBLE_BLUE_CHANEL, TEXT("Увеличить синий канал"));
	SetMenu(hWnd, MainMenu);



	UpdateWindow(hWnd);
	while (GetMessage(&Msg, NULL, 0, 0)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	} 
	return Msg.wParam;
}

LRESULT CALLBACK DCDemoWndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {

		/* Upon destruction, tell the main thread to stop */
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	case WM_PAINT: {
		BITMAP bm;
		PAINTSTRUCT ps;

		hDC = BeginPaint(hwnd, &ps);

		HDC hCompatibleDC = CreateCompatibleDC(hDC);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);

		GetObject(hBitmap, sizeof(bm), &bm);

		BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, SRCCOPY); //0, 50

		SelectObject(hCompatibleDC, hOldBitmap);
		DeleteDC(hCompatibleDC);

		EndPaint(hwnd, &ps);
		break;
	}

	case WM_COMMAND:{

		if (LOWORD(wParam) == LOAD)
		{
			fileName = OpenFile();

			hBitmap = (HBITMAP)LoadImage(0, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			InvalidateRect(hwnd, NULL, TRUE);
			isLoaded = true;
		}

		if (LOWORD(wParam) == START_TESTS)
		{
			execute(hwnd);
			break;
		}

		if (LOWORD(wParam) == APPLY){
			if (!isLoaded)
				break;
			setBlt(hwnd, hBitmap);
		}

		if (LOWORD(wParam) == APPLY_GETPIXEL)
		{
			if (!isLoaded)
				break;

			setPixelDisplay(hwnd, hBitmap);
		}
		if ( LOWORD(wParam) == DOUBLE_BLUE_CHANEL)
		{
			if(!isLoaded)
				break;
			doubleBlueChanel(hwnd, hBitmap);
		}
		break;
	}
					/* All other messages (a lot of them) are processed using default procedures */
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


void execute(HWND hwnd){
	HBITMAP cpy;
	time_t stats[20];
	clock_t starttime;
	long t;

	for (int type = 0; type<2; type++){
		printf(type ? "pixel:  " : "bitblt: ");
		for (int i = 1; i <= 10; i++){
			cpy = (HBITMAP)CopyImage(hBitmap, IMAGE_BITMAP, i * 100, i * 100, 0);
				t = GetTickCount();
			switch (type){
			case 0:
				setBlt(hwnd, cpy);
				break;
			case 1:
				setPixelDisplay(hwnd, cpy);
				break;
			}
			stats[type * 10 + (i - 1)] =  GetTickCount() - t;


			printf("%02d\t", stats[type * 10 + (i - 1)]);
			DeleteObject(cpy);
		}
		printf("\n");
	}
}

void setBlt(HWND hwnd, HBITMAP hBitmap) {
	BITMAP bm;

	HDC hCompatibleDC = CreateCompatibleDC(NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);

	GetObject(hBitmap, sizeof(bm), &bm);

	SelectObject(hCompatibleDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hCompatibleDC, RGB(255, 0, 0));

	BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, MERGECOPY);

	save_bmp(hCompatibleDC, hBitmap, bm.bmWidth, bm.bmHeight);

	InvalidateRect(hwnd, NULL, TRUE);

	SelectObject(hCompatibleDC, hOldBitmap);
	DeleteDC(hCompatibleDC);
}

void doubleBlueChanel(HWND hwnd, HBITMAP hBitmap)
{
	BITMAP bmp;
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	HDC hDCMem = CreateCompatibleDC(NULL);
	HGDIOBJ oldBitmap = SelectObject(hDCMem, hBitmap);
	
	//Преобразование цветового формата для подсчета битов; бит на пиксель
	WORD cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);

	DWORD biSizeImage = ((bmp.bmWidth * cClrBits + 31) & ~31) / 8 * bmp.bmHeight;

	BITMAPINFO bmi = { 0 }; //описывает размеры и цветовую информацию аппаратно-зависимого растра
	//bmiHeader - задает структуру BITMAPINFOHEADER, содержащую информацию о размерности и цветовом формате
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = bmp.bmWidth;
	bmi.bmiHeader.biHeight = bmp.bmHeight;
	bmi.bmiHeader.biPlanes = bmp.bmPlanes;
	bmi.bmiHeader.biBitCount = bmp.bmBitsPixel;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = biSizeImage;
	bmi.bmiHeader.biClrImportant = 0;

	LPBYTE lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, biSizeImage); // memory pointer 
	
	GetDIBits(hDCMem, hBitmap, 0, bmp.bmHeight, lpBits, &bmi, DIB_RGB_COLORS); // (3 на пиксель) Получаем таблицу цветов и биты
	//возвращает биты заданной аппаратно-зависимой картинки и копирует их в буфер DIB в заданном формате, независящем от устройства; 
	//из памяти получаем цвета
	
	WORD buf; //1 канал цвета
	
	for (long i = 0; i < bmp.bmWidth * bmp.bmHeight * 3; i += 3)
	{
		// 0xBB 0xGG 0xRR
		buf = lpBits[i];
		buf <<= 1;
		if (buf > 255)
			buf = 255;
		lpBits[i] = buf;
	}

	SetDIBits(hDCMem, hBitmap, 0, bmp.bmHeight, lpBits, &bmi, DIB_RGB_COLORS);
	save_bmp(hDCMem, hBitmap, bmp.bmWidth, bmp.bmHeight);

	SelectObject(hDCMem, oldBitmap);

	GlobalFree((HGLOBAL)lpBits);
	DeleteDC(hDCMem);
	DeleteObject(oldBitmap);
	
	InvalidateRect(hwnd, NULL, TRUE);
}

void setPixelDisplay(HWND hwnd, HBITMAP hBitmap) {
	BITMAP bm;
	GetObject(hBitmap, sizeof(bm), &bm); //извлекает размеры заданного графического объекта

	HDC hCompatibleDC = CreateCompatibleDC(NULL); //создать контекст памяти, совместимый с контекстом отображения реального устройства вывода
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);  // Выбираем изображение bitmap в контекст памяти

	for (int i = 0; i < bm.bmWidth; i++) {
		for (int j = 0; j < bm.bmHeight; j++) {
			//COLORREF clr = GetPixel(hCompatibleDC, i, j);
			//SetPixel(hCompatibleDC, i, j, RGB(GetRValue(clr), 0, 0));
			SetPixel(hCompatibleDC, i, j,
				GetPixel(hCompatibleDC, i, j) | 0x00FF00);
		}
	}

	SelectObject(hCompatibleDC, hOldBitmap);     // Восстанавливаем контекст памяти

	save_bmp(hCompatibleDC, hBitmap, bm.bmWidth, bm.bmHeight);

	InvalidateRect(hwnd, NULL, TRUE);

	DeleteDC(hCompatibleDC); // Удаляем контекст памяти
	DeleteObject(hOldBitmap);
}

LPCTSTR OpenFile(){
	OPENFILENAME ofn;
	char szFile[100];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "BMP\0*.bmp\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);
	return ofn.lpstrFile;
}

int save_bmp(HDC hdc, HBITMAP H, int width, int height)
{
	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmpSize = ((width * bi.biBitCount + 31) / 32) * 4 * height;

	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	char *lpbitmap = (char *)GlobalLock(hDIB);

	GetDIBits(hdc, H, 0,
		(UINT)height,
		lpbitmap,
		(BITMAPINFO *)&bi, DIB_RGB_COLORS);

	HANDLE hFile = CreateFile("C:/Users/Vika-PC/Desktop/res.bmp",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
	bmfHeader.bfSize = dwSizeofDIB;
	bmfHeader.bfType = 0x4D42; //BM   

	DWORD dwBytesWritten = 0;
	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

	//Unlock and Free the DIB from the heap
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	//Close the handle for the file that was created
	CloseHandle(hFile);

	return 0;
}



