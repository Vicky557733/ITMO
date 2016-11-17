#include<windows.h>
#include <time.h>
#include <stdio.h>
#include <iostream> 
#include <fstream>

#define LOAD	1
#define APPLY	2
#define APPLY_GETPIXEL	3
#define START_TESTS	4


LPCTSTR OpenFile();
int save_bmp(HDC hdc, HBITMAP bm, int width, int height);
LRESULT CALLBACK DCDemoWndProc(HWND, UINT, WPARAM, LPARAM);
void setPixelDisplay(HWND hwnd, HBITMAP hBitmap);
void setBlt(HWND hWnd, HBITMAP hBitmap);
void execute(HWND hwnd);

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
	wchar_t szClassName[] = L"DCDemo";

	// Set window attributes
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = DCDemoWndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = L"MyMenu";
	WndClass.lpszClassName = szClassName;

	// Trying to register window
	if (!RegisterClass(&WndClass)) {
		MessageBox(NULL, L"Cannot register class", L"Error", MB_OK);
		return 0;
	}

	// Creating window
	hWnd = CreateWindow(szClassName, L"Image",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);
	if (!hWnd) {
		MessageBox(NULL, L"Cannot create window", L"Error", MB_OK);
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
	//1	hBitmap = (HBITMAP)LoadImage(0, L"C:/1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		HDC hCompatibleDC = CreateCompatibleDC(hDC);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);

		GetObject(hBitmap, sizeof(bm), &bm);

		BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, SRCCOPY); //0, 50

	/* 2	SetDCBrushColor(hDC, RGB(255, 0, 0));
		SelectObject(hDC, GetStockObject(DC_BRUSH));

		BitBlt(hDC, 0, 50, 1000, 1000, hCompatibleDC, 0, 0, MERGECOPY);

		HBITMAP hbitmap;
		hbitmap = (HBITMAP)LoadImage(0, L"C:/1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		BITMAP bm2;
		GetObject(hbitmap, sizeof(BITMAP), &bm2);

		BitBlt(hCompatibleDC, 0, 0, bm2.bmWidth, bm2.bmHeight, hDC, 0, 0, SRCCOPY);

		save_bmp(hCompatibleDC, hBitmap, bm.bmWidth, bm.bmHeight); */
		//int save_bmp(HDC hdc, HBITMAP bm, int width, int height);

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
			//	SelectObject(source, hb);
			//	BitBlt(hdc, 0, 50, 1500, 1000, source, 0, 0, SRCCOPY);
			InvalidateRect(hwnd, NULL, TRUE);
			//UpdateWindow(hwnd);
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
		/*	BITMAP bm;

			HDC hCompatibleDC = CreateCompatibleDC(NULL);
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);

			GetObject(hBitmap, sizeof(bm), &bm);

			SelectObject(hCompatibleDC, GetStockObject(DC_BRUSH));
			SetDCBrushColor(hCompatibleDC, RGB(255, 0, 0));

			BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, MERGECOPY);

			save_bmp(hCompatibleDC, hBitmap, bm.bmWidth, bm.bmHeight);
			//int save_bmp(HDC hdc, HBITMAP bm, int width, int height);

			InvalidateRect(hwnd, NULL, TRUE);

			SelectObject(hCompatibleDC, hOldBitmap);
			DeleteDC(hCompatibleDC);*/
		}
	//	break;

		if (LOWORD(wParam) == APPLY_GETPIXEL)
		{
			if (!isLoaded)
				break;

			setPixelDisplay(hwnd, hBitmap);

		/*	BITMAP bm;
			GetObject(hBitmap, sizeof(bm), &bm); //извлекает размеры заданного графического объекта

			HDC hCompatibleDC = CreateCompatibleDC(NULL); //создать контекст памяти, совместимый с контекстом отображения реального устройства вывода
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);  // Выбираем изображение bitmap в контекст памяти

			//BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);

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
			//int save_bmp(HDC hdc, HBITMAP bm, int width, int height);

			InvalidateRect(hwnd, NULL, TRUE);

			DeleteDC(hCompatibleDC); // Удаляем контекст памяти
			DeleteObject(hOldBitmap);*/

		}
		break;
	}
					/* All other messages (a lot of them) are processed using default procedures */
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
// Window messages handler
/*LRESULT CALLBACK DCDemoWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	case WM_COMMAND:
		if (LOWORD(wParam) == 1)
		{
			fileName = OpenFile();
			hBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			InvalidateRect(hWnd, NULL, TRUE);
			//UpdateWindow(hWnd);
			isLoaded = true;
		}
		if (LOWORD(wParam) == 4){
			//execute(hWnd);
		}
		if (LOWORD(wParam) == 3){
			//setPixelDisplay(Bitmap.bmWidth, Bitmap.bmHeight, 0, 0, hDC);
		}
		if (LOWORD(wParam) == 2){
			if (!isLoaded)
				break;

			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);


			HDC source;
			HBITMAP hb;
			source = CreateCompatibleDC(NULL);
			hb = (HBITMAP)LoadImage(0, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			SelectObject(source, hb);

			BitBlt(hdc, 0, 50, 1000, 1000, source, 0, 0, SRCCOPY);

			SetDCBrushColor(hdc, RGB(255, 0, 0));
			SelectObject(hdc, GetStockObject(DC_BRUSH));
			BitBlt(hdc, 500, 50, 1000, 1000, source, 0, 0, MERGECOPY);

			HBITMAP hbitmap;
			hbitmap = (HBITMAP)LoadImage(0, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			BITMAP bm;
			CHAR szBuffer[255];
			GetObject(hbitmap, sizeof(BITMAP), &bm);

			BitBlt(source, 0, 0, bm.bmWidth, bm.bmHeight, hdc, 500, 50, SRCCOPY);
			//save_bmp(source, hb, bm.bmWidth, bm.bmHeight);

			EndPaint(hWnd, &ps);

			//setBlt(hWnd);
			//hBitmap = (HBITMAP)LoadImage(0, L"res.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			InvalidateRect(hWnd, NULL, TRUE);			
		}
		break;*/
	
				   // Printing left picture
				   /*hDC = BeginPaint(hWnd, &PaintStruct);
				   hBitmap = LoadImage(NULL, L"C:\\1.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);   !!!
				   GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
				   hCompatibleDC = CreateCompatibleDC(hDC);
				   hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
				   GetClientRect(hWnd, &Rect);
				   StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
				   SelectObject(hCompatibleDC, hOldBitmap);
				   DeleteObject(hBitmap);
				   DeleteDC(hCompatibleDC);*/

				   // Printing right picture
				   /*hBitmap = LoadImage(NULL, L"C:\\1.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				   GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
				   hCompatibleDC = CreateCompatibleDC(hDC);
				   hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
				   GetClientRect(hWnd, &Rect);
				   StretchBlt(hDC, Rect.right / 2, 0, Rect.right / 2, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
				   SelectObject(hCompatibleDC, hOldBitmap);
				   DeleteObject(hBitmap);
				   DeleteDC(hCompatibleDC);*/

				   // AND
				   /*if (MouseClick){
					   hBitmap = LoadImage(NULL, L"C:\\green.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
					   GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
					   hCompatibleDC = CreateCompatibleDC(hDC);
					   hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
					   GetClientRect(hWnd, &Rect);
					   BitBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, SRCAND);
					   SelectObject(hCompatibleDC, hOldBitmap);
					   DeleteObject(hBitmap);
					   DeleteDC(hCompatibleDC);
					   EndPaint(hWnd, &PaintStruct);
					   CreateBMPFile(L"result.bmp", hWnd, BI_RGB, 24);
					   MouseClick = FALSE;
					   }*/

				   //if (MouseClick){!!!
				   //void setBlt(HWND hWnd, HANDLE hBitmap, HANDLE hOldBitmap, HDC hDC, HDC hCompatibleDC, PAINTSTRUCT PaintStruct, RECT Rect, BITMAP Bitmap)

				   //int c = clock();
				   //setBlt(hWnd, hBitmap, hOldBitmap, hDC, hCompatibleDC, PaintStruct, Rect, Bitmap);!!!
				   //cout << clock() - c << endl;

				   //(int width, int height, int offsetX, int offsetY, HDC hdc)
				   //setPixelDisplay(Rect.right, Rect.bottom, 0, 0, hDC);
				   //}!!!


				   // Save picture
				   //ScreenCapture(0, 0, 100, 100, L"result.bmp");
				   //PBITMAPINFO pBitmapInfo = CreateBitmapInfoStruct(hBitmap2);
				   //CreateBMPFile(L"result.bmp", pBitmapInfo, hBitmap2, hDC);
				   //	CreateBMPFile(L"result.bmp", hWnd, BI_RGB, 24);

				   // Exit



				   //return 0;!!!


				   /*case WM_LBUTTONDOWN:

					   GetWindowRect(hWnd, &Rect); //ф-ция подсчета размера прямоугольника
					   point_w.x = LOWORD(lParam);
					   point_w.y = HIWORD(lParam);

					   GetClientRect(hWnd, &Rect);
					   point.x = (Rect.right - Rect.left) / 2;
					   point.y = (Rect.bottom - Rect.top) / 2;

					   if (PtInRect(&Rect, point))
					   {
					   wsprintf(str, TEXT("Point in rect"));
					   SetWindowText(hWnd, str);
					   MouseClick = TRUE;
					   InvalidateRect(hWnd, NULL, 0);
					   //MouseClick = 0;
					   }
					   if (!PtInRect(&Rect, point_w))
					   {
					   wsprintf(str, TEXT("Point not in Rect"));
					   SetWindowText(hWnd, str);
					   }
					   return 0;

					   case WM_DESTROY:
					   PostQuitMessage(0);
					   return 0;
					   }*/
	//default:
		//return DefWindowProc(hWnd, Message, wParam, lParam);
	//}
	//return 0;
//}
/*int errhandler(char* s, HWND hwnd) {
	// Plug
	return 0;
}*/


void execute(HWND hwnd){
	HBITMAP cpy;
	time_t start_time;
	time_t stats[20];
	for (int type = 0; type<2; type++){
		printf(type ? "pixel:  " : "bitblt: ");
		for (int i = 1; i <= 10; i++){
			cpy = (HBITMAP)CopyImage(hBitmap, IMAGE_BITMAP, i * 100, i * 100, 0);
			start_time = time(NULL);
			switch (type){
			case 0:
				setBlt(hwnd, cpy);
				break;
			case 1:
				setPixelDisplay(hwnd, cpy);
				break;
			}
			stats[type * 10 + (i - 1)] = time(NULL) - start_time;


			printf("%02d\t", stats[type * 10 + (i - 1)]);
			DeleteObject(cpy);
		}
		printf("\n");
	}
}
void setBlt(HWND hwnd, HBITMAP hBitmap) {
	//BitBlt(hdc, 0, 50, Bitmap.bmWidth, Bitmap.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);
	BITMAP bm;

	HDC hCompatibleDC = CreateCompatibleDC(NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);

	GetObject(hBitmap, sizeof(bm), &bm);

	SelectObject(hCompatibleDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hCompatibleDC, RGB(255, 0, 0));

	BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, MERGECOPY);

	save_bmp(hCompatibleDC, hBitmap, bm.bmWidth, bm.bmHeight);
	//int save_bmp(HDC hdc, HBITMAP bm, int width, int height);

	InvalidateRect(hwnd, NULL, TRUE);

	SelectObject(hCompatibleDC, hOldBitmap);
	DeleteDC(hCompatibleDC);
	/*HDC hDC;
	PAINTSTRUCT ps;
	BITMAP Bitmap;
	HDC hCompatibleDC;
	HANDLE hBitmap, hOldBitmap;
	RECT Rect;

	hDC = BeginPaint(hWnd, &ps);
	hBitmap = LoadImage(NULL, L"C:\\green.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
	hCompatibleDC = CreateCompatibleDC(hDC);
	hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
	GetClientRect(hWnd, &Rect);
	BitBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, SRCAND);
	SelectObject(hCompatibleDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hCompatibleDC);
	save_bmp(hDC, Bitmap, Bitmap.bmWidth, Bitmap.bmHeight);
	EndPaint(hWnd, &ps);*/

}

void setPixelDisplay(HWND hwnd, HBITMAP hBitmap) {
	BITMAP bm;
	GetObject(hBitmap, sizeof(bm), &bm); //извлекает размеры заданного графического объекта

	HDC hCompatibleDC = CreateCompatibleDC(NULL); //создать контекст памяти, совместимый с контекстом отображения реального устройства вывода
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);  // Выбираем изображение bitmap в контекст памяти

	//BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);

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
	//int save_bmp(HDC hdc, HBITMAP bm, int width, int height);

	InvalidateRect(hwnd, NULL, TRUE);

	DeleteDC(hCompatibleDC); // Удаляем контекст памяти
	DeleteObject(hOldBitmap);
/*	for (int i = offsetX; i < width + offsetX; i++) {
		for (int j = offsetY; j < height + offsetY; j++) {
			COLORREF color = GetPixel(hdc, i, j);
			SetPixel(hdc, i, j, RGB(0, GetBValue(color), 0));
		}
	}*/
}
LPCTSTR OpenFile(){
	OPENFILENAME ofn;
	wchar_t szFile[100];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"BMP\0*.bmp\0";
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

	HANDLE hFile = CreateFile(L"C:/Users/Vika-PC/Desktop/Win32Project1/Win32Project1/res.bmp",
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


