#include <windows.h>

void LoadDllsFromDirectory(const wchar_t *directory)
{
    WIN32_FIND_DATA findFileData;
    wchar_t searchPath[MAX_PATH];
    wsprintf(searchPath, L"%s\\*", directory);
    HANDLE hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        return;
    }

    do
    {
        if (wcscmp(findFileData.cFileName, L".") == 0 || wcscmp(findFileData.cFileName, L"..") == 0)
        {
            continue;
        }

        wchar_t fullPath[MAX_PATH];
        wsprintf(fullPath, L"%s\\%s", directory, findFileData.cFileName);

        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            LoadDllsFromDirectory(fullPath);
        }
        else if (wcsstr(findFileData.cFileName, L".dll") != nullptr)
        {
            LoadLibrary(fullPath);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);
    FindClose(hFind);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        if (GetFileAttributes(L"libraries") != INVALID_FILE_ATTRIBUTES)
        {
            LoadDllsFromDirectory(L"libraries");
        }
    }

    return TRUE;
}
