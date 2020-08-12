// Algoritmi vizualno.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Algoritmi vizualno.h"
#include "Algoritam.h"


#define MAX_LOADSTRING 100
#define BUTTON_ID1 10
#define BUTTON_ID2 11
#define BUTTON_ID3 15
#define BUTTON_ID4 16
#define BUTTON_RADIO_START 12
#define BUTTON_RADIO_END 13
#define BUTTON_RADIO_WALLS 14

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
Algoritam alg;
RECT rectangles[32][32];




// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.
   

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ALGORITMIVIZUALNO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ALGORITMIVIZUALNO));

    MSG msg;


    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ALGORITMIVIZUALNO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ALGORITMIVIZUALNO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   HDC hDC = ::GetWindowDC(NULL);
   ::SetWindowPos(hWnd, NULL, 0, 0, ::GetDeviceCaps(hDC, HORZRES), ::GetDeviceCaps(hDC, VERTRES), SWP_FRAMECHANGED);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
        CreateWindowEx(0, L"BUTTON", L"SEARCH", 
            WS_CHILD | WS_VISIBLE, 
            500, 750, 100, 100, 
            hWnd, (HMENU)BUTTON_ID1, 
            GetModuleHandle(NULL), NULL);

        CreateWindowEx(0, L"BUTTON", L"RAND WALLS",
            WS_CHILD | WS_VISIBLE,
            600, 750, 100, 100, 
            hWnd, (HMENU)BUTTON_ID2, 
            GetModuleHandle(NULL), NULL);

        CreateWindowEx(0, L"BUTTON", L"CLEAR VISITED",
            WS_CHILD | WS_VISIBLE,
            700, 750, 100, 100,
            hWnd, (HMENU)BUTTON_ID3, 
            GetModuleHandle(NULL), NULL);

        CreateWindowEx(0, L"BUTTON", L"RESET WALLS",
            WS_CHILD | WS_VISIBLE,
            800, 750, 100, 100,
            hWnd, (HMENU)BUTTON_ID4,
            GetModuleHandle(NULL), NULL);

        CreateWindowExW(WS_EX_TRANSPARENT, L"BUTTON", L"START POSITION",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            50, 750, 200, 50,
            hWnd, (HMENU)BUTTON_RADIO_START,
            GetModuleHandle(NULL), 0);

        CreateWindowExW(WS_EX_TRANSPARENT, L"BUTTON", L"TARGET POSITION",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            50, 800, 200, 50,
            hWnd, (HMENU)BUTTON_RADIO_END,
            GetModuleHandle(NULL), 0);

        CreateWindowExW(WS_EX_TRANSPARENT, L"BUTTON", L"WALL POSITIONS",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            50, 850, 200, 50,
            hWnd, (HMENU)BUTTON_RADIO_WALLS,
            GetModuleHandle(NULL), 0);


        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case BUTTON_ID1:
                alg.BFS(hWnd);
                break;
            case BUTTON_ID2:               
                alg.generateRandomWalls();
                InvalidateRect(hWnd, NULL, 0);
                UpdateWindow(hWnd);
                break;
            case BUTTON_ID3:
                alg.resetMap();
                InvalidateRect(hWnd, NULL, 0);
                UpdateWindow(hWnd);
                break;
            case BUTTON_ID4:
                alg.resetMapALL();
                InvalidateRect(hWnd, NULL, 0);
                UpdateWindow(hWnd);
                break;
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


    case WM_LBUTTONDOWN:
    {
        RECT ClientRect;
        POINT p;
        if (GetCursorPos(&p))
        {
            ScreenToClient(hWnd, &p);
            for (int i = 0; i < 32; i++) {
                for (int j = 0; j < 32; j++) {
                    //check what rect is clicked
                    if (PtInRect(&rectangles[i][j], p)) {
                        //check what radio button is ON 
                        if (IsDlgButtonChecked(hWnd, BUTTON_RADIO_START) && alg.grid[i][j] == NOTVISITED) {
                            //remove current start pos
                            alg.removeStartPos();
                            //add new start pos
                            alg.grid[i][j] = START;
                            alg.start.x = i;
                            alg.start.y = j;
                            InvalidateRect(hWnd, NULL, 0);
                            UpdateWindow(hWnd);
                        }
                        else if (IsDlgButtonChecked(hWnd, BUTTON_RADIO_END) && alg.grid[i][j] == NOTVISITED) {
                            //remove current end pos
                            alg.removeEndPos();
                            //add new end pos
                            alg.grid[i][j] = END;
                            alg.end.x = i;
                            alg.end.y = j;
                            InvalidateRect(hWnd, NULL, 0);
                            UpdateWindow(hWnd);
                        }
                        else if  (IsDlgButtonChecked(hWnd, BUTTON_RADIO_WALLS) ) {
                            //if rect is not wall, start or end, make it a WALL
                             if (alg.grid[i][j] == NOTVISITED || alg.grid[i][j] == VISITED || alg.grid[i][j] == PATH || alg.grid[i][j] == QUEUE) {
                                 alg.grid[i][j] = WALL;
                                InvalidateRect(hWnd, NULL, 0);
                                UpdateWindow(hWnd);
                             }
                             //if rect is already wall, delete it
                             else if (alg.grid[i][j] == WALL) {
                                alg.grid[i][j] = NOTVISITED;
                                InvalidateRect(hWnd, NULL, 0);
                                UpdateWindow(hWnd);
                             }
                        }
                    };
                }
            }
        }
    }
    break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            int leftStart = 20;
            int topStart = 20;

            for (int i = 0; i < 32; i++) {
                for (int j = 0; j < 32; j++) {
                    int k = j * 22;
                    int n = i * 22;
                    rectangles[i][j].left = k + leftStart;
                    rectangles[i][j].right = k + leftStart + 20;
                    rectangles[i][j].top = topStart + n;
                    rectangles[i][j].bottom = topStart + n + 20;

                    if(alg.grid[i][j]== VISITED){
                        FillRect(hdc, &rectangles[i][j], (HBRUSH)GetStockObject(BLACK_BRUSH));
                    }
                    else if(alg.grid[i][j] == QUEUE){
                        FillRect(hdc, &rectangles[i][j], (HBRUSH)GetStockObject(GRAY_BRUSH));
                    }
                    else if(alg.grid[i][j] == START){                     
                        HBRUSH brush = ::CreateSolidBrush(RGB(50, 255, 255));
                        ::FillRect(hdc, &rectangles[i][j],brush);
                        DeleteObject(brush);
                    }
                    else if(alg.grid[i][j] == END) {
                        HBRUSH brush = CreateSolidBrush(RGB(0, 151, 151));
                        FillRect(hdc, &rectangles[i][j], brush);
                        DeleteObject(brush);
                    }
                    else if (alg.grid[i][j] == PATH) {
                        HBRUSH brush = CreateSolidBrush(RGB(34, 139, 34));
                        FillRect(hdc, &rectangles[i][j], brush);
                        DeleteObject(brush);
                    }
                    else if (alg.grid[i][j] == WALL) {
                        HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
                        FillRect(hdc, &rectangles[i][j], brush);
                        DeleteObject(brush);
                    }
                    else {   
                       FillRect(hdc, &rectangles[i][j], (HBRUSH)GetStockObject(LTGRAY_BRUSH));
                    }
                }
            }
           
           
            ReleaseDC(hWnd, hdc);
            EndPaint(hWnd, &ps);
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

// Message handler for about box.
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
