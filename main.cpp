#include <windows.h>
#include <time.h>
#include "..\Glass.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";
MGlass glass, glass2, glass3;
MCircle circle;

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Three glasses",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           600,       /* Windows decides the position */
           400,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    CreateWindow("button",
                "Go",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10, 10, 80, 30,
                hwnd,
                (HMENU)1001,
                hThisInstance,
                NULL);

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    static int level=1;

    switch (message)                  /* handle the messages */
    {
        case WM_CONTEXTMENU :
            {
                HMENU hMenu = CreatePopupMenu();

                AppendMenu( hMenu, MFT_STRING, 10, "&Легко" );
                AppendMenu( hMenu, MFT_STRING, 20, "&Средне" );
                AppendMenu( hMenu, MFT_STRING, 30, "&Трудно" );

                TrackPopupMenu( hMenu, TPM_RIGHTBUTTON |
                                       TPM_TOPALIGN |
                                       TPM_LEFTALIGN,
                                       LOWORD( lParam ),
                                       HIWORD( lParam ), 0, hwnd, NULL );
                DestroyMenu( hMenu );
            }
            break;
        case WM_SIZE:
            //Запоминаем текущие размеры окна.
            glass.Size(LOWORD(lParam),HIWORD(lParam), 1);
            circle.Size(LOWORD(lParam),HIWORD(lParam), 1);
            glass2.Size(LOWORD(lParam),HIWORD(lParam), 2);
            glass3.Size(LOWORD(lParam),HIWORD(lParam), 3);

            break;

        case WM_TIMER:
            
            glass.Timer(hwnd, glass2, glass3);
            glass.Level(level);

            break;

        case WM_PAINT:

            hdc = BeginPaint(hwnd, &ps);

                glass.MPaint(hwnd,hdc);
                glass2.MPaint(hwnd,hdc);
                glass3.MPaint(hwnd,hdc);
                if(glass.circ)
                    circle.MPaint(hwnd,hdc);

            EndPaint(hwnd, &ps);

            break;

        case WM_LBUTTONDOWN:

            glass.Check(LOWORD(lParam),HIWORD(lParam), hwnd);

            break;

        case WM_COMMAND:

            if(LOWORD(wParam)==1001)
            {
                    glass.count=0;
                    glass.circ=true;
                    Sleep(1000);
            }
            if(LOWORD(wParam)==10)
                level=1;
            if(LOWORD(wParam)==20)
                level=6;
            if(LOWORD(wParam)==30)
                level=10;


            break;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
