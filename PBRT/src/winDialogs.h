#pragma once
//#include <windows.h>
//#include <GLFW/glfw3.h>
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>
#include "renderer.h"
#include <string>


std::string OpenFile(Renderer& UI, const char* filter) {
	//OPENFILENAMEA ofn;
	//CHAR szFile[260] = { 0 };
	//ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	//ofn.lStructSize = sizeof(OPENFILENAMEA);
	//ofn.hwndOwner = glfwGetWin32Window(UI.window);
	//ofn.lpstrFile = szFile;
	//ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrFilter = filter;
	//ofn.nFilterIndex = 1;
	//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	//if (GetOpenFileNameA(&ofn) == true) {
	//	return ofn.lpstrFile;
	//}
	return std::string();
}
