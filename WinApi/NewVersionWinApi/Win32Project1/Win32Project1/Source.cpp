#include<Windows.h>
#include <time.h>

LPCTSTR OpenFile();
int save_bmp(HDC hdc, BITMAP bm, int width, int height);
LRESULT CALLBACK DCDemoWndProc(HWND, UINT, WPARAM, LPARAM);
bool ScreenCapture(int x, int y, int width, int height, wchar_t *filename);
BOOL CreateBMPFile(LPTSTR pszFile, HWND hWndScreen, DWORD dwComp, WORD wBitCount);
bool SaveBMPFile(wchar_t *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height);
void setPixelDisplay(int width, int height, int offsetX, int offsetY, HDC hdc);
void setBlt(HWND hWnd);

//int execute(HWND hwnd);


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
HANDLE hBitmap, hOldBitmap;
BITMAP Bitmap;

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
	AppendMenu(MainMenu, MF_STRING, 1, TEXT("Загрузить"));
	AppendMenu(MainMenu, MF_STRING, 2, TEXT("Применить BitBlt"));
	AppendMenu(MainMenu, MF_STRING, 3, TEXT("Применить getPixel"));
	AppendMenu(MainMenu, MF_STRING, 4, TEXT("Начать тесты"));
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
		hDC = BeginPaint(hwnd, &PaintStruct);
		hCompatibleDC = CreateCompatibleDC(hDC);
		hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
		BitBlt(hDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);
		SelectObject(hCompatibleDC, hOldBitmap);
		DeleteDC(hCompatibleDC);
		EndPaint(hwnd, &PaintStruct);

		break;

	}

	case WM_COMMAND:{
	//	InvalidateRect(hwnd, 0, TRUE);
	//	UpdateWindow(hwnd);
		if (LOWORD(wParam) == 2) {}
			//execute(hwnd);
		if (LOWORD(wParam) == 1)
		{
			fileName = OpenFile();

			hBitmap = (HBITMAP)LoadImage(0, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			
			hDC = BeginPaint(hwnd, &PaintStruct);
			hCompatibleDC = CreateCompatibleDC(hDC);
			hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
			GetObject(hBitmap, sizeof(BITMAP), &Bitmap);

			SetDCBrushColor(hDC, RGB(255, 0, 0));
			SelectObject(hDC, GetStockObject(DC_BRUSH));
			BitBlt(hDC, 500, 0, 1000, 1000, hCompatibleDC, 0, 0, MERGECOPY);

			BitBlt(hDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);
			SelectObject(hCompatibleDC, hOldBitmap);
			DeleteDC(hCompatibleDC);
			EndPaint(hwnd, &PaintStruct);



			//save_bmp(source, hb, bm.bmWidth, bm.bmHeight);

		
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
	HDC hDC, hCompatibleDC;
	HANDLE hBitmap, hOldBitmap;
	RECT Rect;
	
	TCHAR str[100];
	//RECT rect;
	POINT point;
	POINT point_w;
	PAINTSTRUCT PaintStruct;
	BITMAP Bitmap;

	switch (Message) {
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}

	case WM_PAINT: {

		hDC = BeginPaint(hWnd, &PaintStruct);
		hCompatibleDC = CreateCompatibleDC(hDC);
		hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
		BitBlt(hDC, 0, 50, Bitmap.bmWidth, Bitmap.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);
		SelectObject(hCompatibleDC, hOldBitmap);
		DeleteDC(hCompatibleDC);
		EndPaint(hWnd, &PaintStruct);

		break;
	}

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
/*int execute(HWND hwnd){
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);
	int size = 0;
	ofstream result("result.csv");
	for (size_t i = 0; i < 10; i++)
	{
		char path[18];
		sprintf_s(path, "images/image_%d.bmp", i);
		HDC source = read_bmp(path);
		size += 100;

		InvalidateRect(hwnd, 0, TRUE);
		UpdateWindow(hwnd);

		long time1 = bitblt(hdc, source, size, size);
		long time2 = getsetpixel(hdc, size, size);

		result << time1 << ";" << time2 << ";\r\n";
	}
	result.close();
	EndPaint(hwnd, &ps);
	return 0;
}*/
void setBlt(HWND hWnd) {
	//BitBlt(hdc, 0, 50, Bitmap.bmWidth, Bitmap.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);
	HDC hDC;
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
	EndPaint(hWnd, &ps);

	//CreateBMPFile(L"result.bmp", hWnd, BI_RGB, 24);
	//MouseClick = FALSE;
}

void setPixelDisplay(int width, int height, int offsetX, int offsetY, HDC hdc) {
	for (int i = offsetX; i < width + offsetX; i++) {
		for (int j = offsetY; j < height + offsetY; j++) {
			COLORREF color = GetPixel(hdc, i, j);
			SetPixel(hdc, i, j, RGB(0, GetBValue(color), 0));
		}
	}
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
/*inline int GetFilePointer(HANDLE FileHandle){
	return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}*/
/*bool SaveBMPFile(wchar_t *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height){
	bool Success = 0;
	HDC SurfDC = NULL;
	HBITMAP OffscrBmp = NULL;
	HDC OffscrDC = NULL;
	LPBITMAPINFO lpbi = NULL;
	LPVOID lpvBits = NULL;
	HANDLE BmpFile = INVALID_HANDLE_VALUE;
	BITMAPFILEHEADER bmfh;
	if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
		return 0;
	if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == NULL)
		return 0;
	HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);
	BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
	if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
		return 0;
	ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
	lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	SelectObject(OffscrDC, OldBmp);
	if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS))
		return 0;
	if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
		return 0;
	if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
		return 0;
	if ((BmpFile = CreateFile(filename,
		GENERIC_WRITE,
		0, NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL)) == INVALID_HANDLE_VALUE)
		return 0;
	DWORD Written;
	bmfh.bfType = 19778;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
		return 0;
	if (Written < sizeof(bmfh))
		return 0;
	if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
		return 0;
	if (Written < sizeof(BITMAPINFOHEADER))
		return 0;
	int PalEntries;
	if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
		PalEntries = 3;
	else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
		(int)(1 << lpbi->bmiHeader.biBitCount) : 0;
	if (lpbi->bmiHeader.biClrUsed)
		PalEntries = lpbi->bmiHeader.biClrUsed;
	if (PalEntries){
		if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
			return 0;
		if (Written < PalEntries * sizeof(RGBQUAD))
			return 0;
	}
	bmfh.bfOffBits = GetFilePointer(BmpFile);
	if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL))
		return 0;
	if (Written < lpbi->bmiHeader.biSizeImage)
		return 0;
	bmfh.bfSize = GetFilePointer(BmpFile);
	SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
	if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
		return 0;
	if (Written < sizeof(bmfh))
		return 0;
	return 1;
}*/
/*bool ScreenCapture(int x, int y, int width, int height, wchar_t *filename){
	HDC hDc = CreateCompatibleDC(0);
	HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);
	SelectObject(hDc, hBmp);
	BitBlt(hDc, 0, 0, width, height, GetDC(0), x, y, SRCCOPY);
	bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);
	DeleteObject(hBmp);
	return ret;
}*/

/*PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp)
{
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD    cClrBits;
	// Retrieve the bitmap color format, width, and height. 
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
		return NULL;

	// Convert the color format to a count of bits. 
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;

	// Allocate memory for the BITMAPINFO structure. (This structure 
	// contains a BITMAPINFOHEADER structure and an array of RGBQUAD 
	// data structures.) 

	if (cClrBits != 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
		sizeof(BITMAPINFOHEADER) +
		sizeof(RGBQUAD) * (1 << cClrBits));

	// There is no RGBQUAD array for the 24-bit-per-pixel format. 

	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
		sizeof(BITMAPINFOHEADER));

	// Initialize the fields in the BITMAPINFO structure. 

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);

	// If the bitmap is not compressed, set the BI_RGB flag. 
	pbmi->bmiHeader.biCompression = BI_RGB;

	// Compute the number of bytes in the array of color 
	// indices and store the result in biSizeImage. 
	// For Windows NT, the width must be DWORD aligned unless 
	// the bitmap is RLE compressed. This example shows this. 
	// For Windows 95/98/Me, the width must be WORD aligned unless the 
	// bitmap is RLE compressed.
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
		* pbmi->bmiHeader.biHeight;
	// Set biClrImportant to 0, indicating that all of the 
	// device colors are important. 
	pbmi->bmiHeader.biClrImportant = 0;
	return pbmi;
}*/
/*void CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi,	HBITMAP hBMP, HDC hDC)
{
	HANDLE hf;                 // file handle 
	BITMAPFILEHEADER hdr;       // bitmap file-header 
	PBITMAPINFOHEADER pbih;     // bitmap info-header 
	LPBYTE lpBits;              // memory pointer 
	DWORD dwTotal;              // total count of bytes 
	DWORD cb;                   // incremental count of bytes 
	BYTE *hp;                   // byte pointer 
	DWORD dwTmp;

	pbih = (PBITMAPINFOHEADER)pbi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if (!lpBits)
		return;

	// Retrieve the color table (RGBQUAD array) and the bits 
	// (array of palette indices) from the DIB. 
	if (!GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi,
		DIB_RGB_COLORS))
	{
		return;
	}

	// Create the .BMP file. 
	hf = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	if (hf == INVALID_HANDLE_VALUE)
		return;
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
	// Compute the size of the entire file. 
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	// Compute the offset to the array of color indices. 
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD);

	// Copy the BITMAPFILEHEADER into the .BMP file. 
	if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL))
	{
		return;
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL)))
		return;

	// Copy the array of color indices into the .BMP file. 
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL))
		return;

	// Close the .BMP file. 
	if (!CloseHandle(hf))
		return;

	// Free memory. 
	GlobalFree((HGLOBAL)lpBits);
}*/
BOOL CreateBMPFile(LPTSTR pszFile, HWND hWndScreen, DWORD dwComp, WORD wBitCount)
{
	HANDLE hf;
	BITMAPFILEHEADER hdr;
	LPBYTE lpBits;
	DWORD dwTmp;

	BITMAP ddbinfo = { 0 };
	DIBINFO bInfo = { 0 };


	RECT rc = { 0 };

	if (!GetWindowRect(hWndScreen, &rc))             //если проблемы с окном -выход
		return FALSE;


	//Снимок экрана в диалоге
	HDC hDC = GetWindowDC(hWndScreen);
	HBITMAP hBmp = CreateCompatibleBitmap(hDC, rc.right - rc.left, rc.bottom - rc.top);

	if (!hBmp)
	{
		ReleaseDC(hWndScreen, hDC);
		return FALSE;
	}

	//Запись рисунка в память
	HDC  hMemDC = CreateCompatibleDC(hDC);
	HGDIOBJ hOld = SelectObject(hMemDC, hBmp);

	BitBlt(hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOld);
	DeleteDC(hMemDC);


	//Получение данных по изображению
	if (!GetObject(hBmp, sizeof(BITMAP), &ddbinfo))
	{
		DeleteObject(hBmp);
		ReleaseDC(hWndScreen, hDC);
		return FALSE;
	}


	bInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bInfo.bmiHeader.biWidth = ddbinfo.bmWidth;
	bInfo.bmiHeader.biHeight = ddbinfo.bmHeight;

	bInfo.bmiHeader.biPlanes = 1;
	bInfo.bmiHeader.biBitCount = wBitCount;
	bInfo.bmiHeader.biCompression = dwComp;

	//Получение размера для сжатого рисунка из исходного
	if (!GetDIBits(hDC, hBmp, 0, ddbinfo.bmHeight, NULL, (BITMAPINFO*)&bInfo, DIB_RGB_COLORS))
	{
		DeleteObject(hBmp);
		ReleaseDC(hWndScreen, hDC);
		return FALSE;
	}
	//Размер заголовка растра
	DWORD dwInfSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 259;
	//Весь растр
	DWORD dwTotalSize = dwInfSize + bInfo.bmiHeader.biSizeImage;

	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, dwTotalSize);

	if (!lpBits)
	{
		DeleteObject(hBmp);
		ReleaseDC(hWndScreen, hDC);
		return FALSE;
	}

	memset(lpBits, 0, dwTotalSize);
	memcpy(lpBits, &bInfo, dwInfSize);

	//Преобразование DDB в DIB
	if (!GetDIBits(hDC, hBmp, 0, ddbinfo.bmHeight, lpBits + dwInfSize, (BITMAPINFO*)lpBits, DIB_RGB_COLORS))
	{
		DeleteObject(hBmp);
		ReleaseDC(hWndScreen, hDC);
		GlobalFree((HGLOBAL)lpBits);

		return FALSE;
	}


	//Создание файла для рисунка
	hf = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);

	if (hf == INVALID_HANDLE_VALUE)
	{
		DeleteObject(hBmp);
		ReleaseDC(hWndScreen, hDC);
		GlobalFree((HGLOBAL)lpBits);
		return FALSE;
	}



	//Структура заголовка файла
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) + dwTotalSize);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER) + dwInfSize);

	//Запись заголовка
	if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL))
	{
		DeleteObject(hBmp);
		ReleaseDC(hWndScreen, hDC);
		GlobalFree((HGLOBAL)lpBits);
		CloseHandle(hf);
		return FALSE;
	}
	//Запись описания растра
	if (!WriteFile(hf, (BITMAPINFO*)& bInfo, dwInfSize, (LPDWORD)&dwTmp, NULL))
	{
		DeleteObject(hBmp);
		ReleaseDC(hWndScreen, hDC);
		GlobalFree((HGLOBAL)lpBits);
		CloseHandle(hf);
		return FALSE;
	}

	//Запись массива битов
	if (!WriteFile(hf, (BYTE*)lpBits + dwInfSize, dwTotalSize - dwInfSize, (LPDWORD)&dwTmp, NULL))
	{
		DeleteObject(hBmp);
		ReleaseDC(hWndScreen, hDC);
		GlobalFree((HGLOBAL)lpBits);
		CloseHandle(hf);
		return FALSE;
	}

	DeleteObject(hBmp);
	ReleaseDC(hWndScreen, hDC);
	GlobalFree((HGLOBAL)lpBits);
	CloseHandle(hf);

	return TRUE;
}

int save_bmp(HDC hdc, BITMAP bm, int width, int height)
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

	HANDLE hFile = CreateFile(L"res.bmp",
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
	WriteFile(hFile, bm.bmBits, dwBmpSize, &dwBytesWritten, NULL);

	//Close the handle for the file that was created
	CloseHandle(hFile);

	return 0;
}

