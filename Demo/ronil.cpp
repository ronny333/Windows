#include <Windows.h>
#include <stdio.h>

/*********************************************************
 *   Main Function Entry
 *
 *********************************************************/
int _cdecl main(void)
{
    HANDLE hFile;
    DWORD dwReturn;
	printf("hello world...\n");
    hFile = CreateFile("\\\\.\\RonilD", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if(hFile)
    {
        WriteFile(hFile, "Hello from user mode!", sizeof("Hello from user mode!"), &dwReturn, NULL); 
        CloseHandle(hFile);
    }
    return 0;
    
}