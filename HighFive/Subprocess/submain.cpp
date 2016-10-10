
#pragma comment (lib , "libcef64.lib")
#pragma comment (lib , "libcef.lib")
#pragma comment (lib, "cef_sandbox.lib")
#pragma comment (lib , "libcef_dll_wrapper.lib")

#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>
#include <include/wrapper/cef_helpers.h>
#include <include/cef_parser.h>
#include <include/cef_task.h>
#include <include/cef_app.h>
#include <include/cef_client.h>
#include <include/cef_render_handler.h>
#include <include/cef_life_span_handler.h>
#include <include/internal/cef_types_wrappers.h>
#include <include/internal/cef_win.h>
#include <include/internal/cef_types.h>
#include <include/cef_origin_whitelist.h>
#include <include/cef_browser.h>
#include <include/cef_command_line.h>

//register as winmain so no annoying console window shit
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR    lpCmdLine, int       cmdShow)
{
	//start proc
	CefMainArgs main_args;
	return CefExecuteProcess(main_args, nullptr, nullptr);
}