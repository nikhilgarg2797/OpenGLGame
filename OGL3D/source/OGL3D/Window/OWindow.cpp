#include <OGL3D/Window/OWindow.h>
#include <Windows.h>
/*	Assert function allows to end the program if 
	the expression passed as paramter is false,
	Simple way to end all errors */
#include <assert.h>

// Window procedure and events 
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			OWindow* window = (OWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->onDestroy();
			break;
		}
		default: 
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return NULL;
}

OWindow::OWindow()
{
	// List initialisation of Windows. We are cleaning all the attributes of this object with Null
	WNDCLASSEX wc = {};
	// We have to pass the size of WNDClass Object
	wc.cbSize = sizeof(WNDCLASSEX);
	// Class Name to identify this class of Window
	wc.lpszClassName = L"OGL3DWindow";
	// 
	wc.lpfnWndProc = &WndProc;

	// To let know OS about the class we have to reduce the rate
	assert(RegisterClassEx(&wc));

	//To get the real window size
	RECT rc = { 0, 0, 1024, 768};
	AdjustWindowRect(&rc, WS_SYSMENU, false);

	// Function to create Window
	m_handle = CreateWindowEx(NULL, L"OGL3DWindow", L"PardCode | OpenGL 3D Game", WS_SYSMENU
				, CW_USEDEFAULT, CW_USEDEFAULT, rc.right, rc.bottom, NULL, NULL, NULL, NULL);

	assert(m_handle);

/*	To Retrieve Window Instance in our Window Procedure.
	This function allows us to store the OWindow instance pointer
	in a special data structure identified by the handle of the window */
	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);
}

OWindow::~OWindow()
{
	DestroyWindow((HWND)m_handle);
}

void OWindow::onDestroy()
{
	m_handle = nullptr;
}

bool OWindow::isClosed()
{
	return !m_handle;
}
