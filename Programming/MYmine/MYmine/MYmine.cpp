// MYmine.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MYmine.h"
#include<Windows.h>
#include<time.h>
#include"MineMap.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������
CMinemap minemap;//ɨ��������
BOOL f1 = FALSE;//ָʾ��1(��סδ�򿪸��ӣ�
BOOL f2 = FALSE;//ָʾ��2��Ц����
BOOL f3 = FALSE;//ָʾ��3������Ц����)
// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˷��ô��롣

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYMINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYMINE));

    MSG msg;

    // ����Ϣѭ��: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYMINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYMINE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
   int l;
  l = minemap.mx * 16+16;
  int h = minemap.my * 16 + 90;
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, l, h, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc,hdcMem,hdcFac,hdcTim;
	static HBITMAP mine_map,tim_map,fac_map;
	int m, n,px,py;
	CPoint m_mouse;
	GetCursorPos(&m_mouse);
	ScreenToClient(hWnd, &m_mouse);
	px = m_mouse.x;
	py = m_mouse.y;
	m = m_mouse.x/16;
	n = m_mouse.y/16-2;
	static int M = m;
	static int N = n;
	CRect rc(16 * m, 16 * n + 32, 16 * m + 16, 16 * n + 48);//�������ĸ���
	static clock_t time;
    switch (message)
    {
	case WM_CREATE:
		minemap.Create();
		mine_map = (HBITMAP)LoadImage((HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), TEXT("BITMAP10.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		tim_map = (HBITMAP)LoadImage((HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), TEXT("BITMAP20.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		fac_map= (HBITMAP)LoadImage((HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), TEXT("BITMAP30.BMP"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SetTimer(hWnd, 1, 1000, NULL);//����ÿ���ʱ��
	case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
			hdcMem = CreateCompatibleDC(hdc);
			hdcFac = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, mine_map);
			SelectObject(hdcFac, fac_map);
			if (minemap.isfail == TRUE)
				 {
					 for (int i = 0; i < minemap.mx; i++)
						 for (int j = 0; j < minemap.my; j++)
						 {

							 if (minemap.Map[i][j].isMine == FALSE)
								 if (minemap.Map[i][j].state != flaged)//������,û���죬��ʾ����
									 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 239 - 16 * minemap.Map[i][j].Num, SRCCOPY);
								 else//�����ף������
									 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 64, SRCCOPY);
							 else if (minemap.Map[i][j].state == flaged)//���ף��Ҳ���
								 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 16, SRCCOPY);
							 else if (minemap.Map[i][j].state == question)//�ʺ�
								 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 32, SRCCOPY);
							 else if (minemap.Map[i][j].state == boom)//��������
								 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 48, SRCCOPY);
							 else//�ޱ�ע����
								 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 80, SRCCOPY);
						 }
					 {//����
						 BitBlt(hdc, 8 * minemap.mx - 8, 8, 24, 24, hdcFac, 0, 48, SRCCOPY);
						 DeleteDC(hdcFac);
					 }

				 }
			else if (minemap.iswin == TRUE)
				 {
					 for (int i = 0; i < minemap.mx; i++)
						 for (int j = 0; j < minemap.my; j++)
						 {
							 if (minemap.Map[i][j].isMine == FALSE)
								 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 239 - 16 * minemap.Map[i][j].Num, SRCCOPY);
							 else 
								 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 16, SRCCOPY);

			
						 }
					 {//����
						 BitBlt(hdc, 8 * minemap.mx - 8, 8, 24, 24, hdcFac, 0, 24, SRCCOPY);
						 //InvalidateRect(hWnd, CRect(minemap.mx * 8 - 8, 8, minemap.mx * 8 + 16, 32), 1);
						 DeleteDC(hdcFac);
					 }

				 }
			else//��Ϸ��
			{
				for (int i = 0; i < minemap.mx; i++)
					for (int j = 0; j < minemap.my; j++)
					{
						if (minemap.Map[i][j].state == back)
								 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 0, SRCCOPY);
						else if (minemap.Map[i][j].state == lclicked)
								 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 239 - 16 * minemap.Map[i][j].Num, SRCCOPY);
						else if (minemap.Map[i][j].state == flaged)
								 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 16, SRCCOPY);
						else if (minemap.Map[i][j].state == question)
								 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 32, SRCCOPY);
						else if (minemap.Map[i][j].state == boom)
								 BitBlt(hdc, 16 * i, 16 * j + 32, 16, 16, hdcMem, 0, 48, SRCCOPY);
					}
				{//����
					BitBlt(hdc, 8 * minemap.mx - 8, 8, 24, 24, hdcFac, 0, 96, SRCCOPY);
					DeleteDC(hdcFac);
				}
			}
			DeleteDC(hdcMem);
			{//��ʱ��
				hdcTim = CreateCompatibleDC(hdc);
				SelectObject(hdcTim, tim_map);
				int a, b, c;
				a = minemap.ctime / 100;
				b = minemap.ctime / 10 - 10 * a;
				c = minemap.ctime - 100 * a - 10 * b;
				BitBlt(hdc, 0, 0, 12, 23, hdcTim, 0, 253 - a * 23, SRCCOPY);
				BitBlt(hdc, 12, 0, 12, 23, hdcTim, 0, 253 - b * 23, SRCCOPY);
				BitBlt(hdc, 24, 0, 12, 23, hdcTim, 0, 253 - c * 23, SRCCOPY);//��ʱ��
				a = (minemap.nMine - minemap.nflag) / 100;
				b = (minemap.nMine - minemap.nflag) / 10 - 10 * a;
				c = (minemap.nMine - minemap.nflag) - 100 * a - 10 * b;
				BitBlt(hdc, minemap.mx*16-36, 0, 12, 23, hdcTim, 0, 253 - a * 23, SRCCOPY);
				BitBlt(hdc, minemap.mx * 16 - 24, 0, 12, 23, hdcTim, 0, 253 - b * 23, SRCCOPY);
				BitBlt(hdc, minemap.mx * 16 - 12, 0, 12, 23, hdcTim, 0, 253 - c * 23, SRCCOPY);//������
				DeleteDC(hdcTim);
			}

            EndPaint(hWnd, &ps);
        break;
		}
	case WM_LBUTTONDOWN:
	{
		SetCapture(hWnd);
		if (m >= 0 && m < minemap.mx&&n >= 0 && n < minemap.my)//��������
		{
			M = m;//��¼��ǰ����
			N = n;
			if (minemap.Map[m][n].state == back)
			{
				hdc = GetDC(hWnd);
				SelectObject(hdc, GetStockObject(DC_BRUSH));
				SelectObject(hdc, GetStockObject(DC_PEN));
				SetDCBrushColor(hdc, RGB(230, 230, 230));
				SetDCPenColor(hdc, RGB(230, 230, 230));
				Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

				//InvalidateRect(hWnd, CRect(rc.left, rc.top, rc.right, rc.bottom), 0);
				f1 = TRUE;//��סָʾ��1
				HDC hdcfac = CreateCompatibleDC(hdc);
				SelectObject(hdcfac, fac_map);
				BitBlt(hdc, 8 * minemap.mx - 8, 8, 24, 24, hdcfac, 0, 72, SRCCOPY);
				DeleteDC(hdcfac);
				ReleaseDC(hWnd, hdc);
			}
			break;
		}
		else if (px >= (8 * minemap.mx - 8) && px <= (8 * minemap.mx + 16) && py >= 8 && py <= 32)
		{
			f2 = TRUE;
			hdc = GetDC(hWnd);
			HDC hdcfac = CreateCompatibleDC(hdc);
			SelectObject(hdcfac, fac_map);
			BitBlt(hdc, 8 * minemap.mx - 8, 8, 24, 24, hdcfac, 0, 0, SRCCOPY);
			DeleteDC(hdcfac);
		}
		break;
	}
	case WM_LBUTTONUP://�������
	{
		ReleaseCapture();
		if (m > minemap.mx || m<0 || n>minemap.my || n < 0)//��������
		{
			f1 = FALSE;
			if (px >= (8 * minemap.mx - 8) && px <= (8 * minemap.mx + 16) && py >= 8 && py <= 32)//��Ц����
			{
				minemap.Set();
				InvalidateRect(hWnd, CRect(0, 0, minemap.mx * 16 + 16, minemap.my * 16 + 48), 1);
				
				break;
			}
			break;
		}
		else//������
		{
			if (f1 == FALSE)//��Ч������
				break;
			else//��Ч������
			{
				f1 = FALSE;
				minemap.LClick(m, n, &rc);
				InvalidateRect(hWnd, &rc, 0);
				hdc = GetDC(hWnd);
				HDC hdcfac = CreateCompatibleDC(hdc);
				SelectObject(hdcfac, fac_map);
				BitBlt(hdc, 8 * minemap.mx - 8, 8, 24, 24, hdcfac, 0, 96, SRCCOPY);
				DeleteDC(hdcfac);
				if (minemap.iswin == TRUE)
				{
					hdc = GetDC(hWnd);
					HDC hdcfac = CreateCompatibleDC(hdc);
					SelectObject(hdcfac, fac_map);
					BitBlt(hdc, 8 * minemap.mx - 8, 8, 24, 24, hdcfac, 0, 24, SRCCOPY);
					DeleteDC(hdcfac);
				}
				break;
			}
		}
		break;
	}
	case WM_RBUTTONUP://�Ҽ�����
	{
		if (m > minemap.mx || m<0 || n>minemap.my || n < 0)
			break;
		else
		{
			minemap.RClick(m, n);
			InvalidateRect(hWnd, CRect(16 * m, 16 * n + 32, 16 * m + 16, 16 * n + 48), 0);
			InvalidateRect(hWnd, CRect(16 * minemap.mx-40, 0, 16 * minemap.mx, 25), 1);
			if (minemap.iswin == TRUE)
			{
				InvalidateRect(hWnd, CRect(minemap.mx * 8 - 8, 8, minemap.mx * 8 + 16, 32), 1);
				InvalidateRect(hWnd, CRect(0, 0, minemap.mx * 16, minemap.my * 16 + 48), 0);
			}
		}
	}
	case WM_MOUSEMOVE:
	{
		if (f1 == TRUE)//�������ס���ӵ�״̬��
		{
			if (m >= minemap.mx || m<0 || n>minemap.my || n < 0)//�Ƴ���������ˢ����ǰ����
			{
				InvalidateRect(hWnd, CRect(M * 16, N * 16 + 32, M * 16 + 16, N * 16 + 48), 0);
				break;
			}
			else if (m<M || m>M || n<N || n>N)
			{
				InvalidateRect(hWnd, CRect(M * 16, N * 16 + 32, M * 16 + 16, N * 16 + 48), 0);
				M = m;
				N = n;
				hdc = GetDC(hWnd);
				SelectObject(hdc, GetStockObject(DC_BRUSH));
				SelectObject(hdc, GetStockObject(DC_PEN));
				SetDCBrushColor(hdc, RGB(230, 230, 230));
				SetDCPenColor(hdc, RGB(230, 230, 230));
				Rectangle(hdc,m * 16, n * 16 + 32, m * 16 + 16, n * 16 + 48);
				ReleaseDC(hWnd, hdc);
				break;
			}
		}

		if (px >= (8 * minemap.mx - 8) && px <= (8 * minemap.mx + 16) && py >= 8 && py <= 32)//��Ц����
		{
			f3 = TRUE;
			hdc = GetDC(hWnd);
			HDC hdcfac = CreateCompatibleDC(hdc);
			SelectObject(hdcfac, fac_map);
			BitBlt(hdc, 8 * minemap.mx - 8, 8, 24, 24, hdcfac, 0, 72, SRCCOPY);
			DeleteDC(hdcfac);
		}
		else if (f3 == TRUE)
		{
			InvalidateRect(hWnd, CRect(minemap.mx * 8 - 8, 8, minemap.mx * 8 + 16, 32), 1);
			f3 = FALSE;
		}

		break;
	}
	case WM_TIMER:
		if (minemap.iswin != TRUE&&minemap.isfail != TRUE)
		{
			minemap.ctime++;

			InvalidateRect(hWnd, CRect(0, 0, 36, 23), 0);
		}
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
