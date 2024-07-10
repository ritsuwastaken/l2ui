#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        if (GetFileAttributes(L"libraries") != INVALID_FILE_ATTRIBUTES)
        {
            WIN32_FIND_DATA findFileData;
            HANDLE hFind = FindFirstFile(L"libraries\\*.dll", &findFileData);
            if (hFind != INVALID_HANDLE_VALUE)
            {
                do
                {
                    if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                        continue;

                    WCHAR dllPath[MAX_PATH];
                    wsprintf(dllPath, L"libraries\\%s", findFileData.cFileName);

                    LoadLibrary(dllPath);
                } while (FindNextFile(hFind, &findFileData));
                FindClose(hFind);
            }
        }
    }

    return TRUE;
}
