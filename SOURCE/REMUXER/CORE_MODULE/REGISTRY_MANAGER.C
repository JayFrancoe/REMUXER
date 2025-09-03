#include <Windows.h>
#include <ShlObj.h>

#include "CORE_PRIVATE.H"
#include "CORE_PUBLIC.H"


void register_guid(void);

#define APP_GUID  "{F669792D-19D8-4952-ADA9-A3D1A1C03CB6}"
#define APP_NAME  "REMUXER"
#define MENU_TEXT "Open with Remux"

#define KEY_PATH  "CLSID\\"APP_GUID
#define KEY_PROC  KEY_PATH"\\InProcServer32"


void register_for_ext(core_module *core, const char *extension)
{
        
}

void unregister_for_ext(core_module *core, const char *extension)
{

}


void register_guid(void)
{
    HKEY h_key = NULL;
    LONG result = 0;

    puts(KEY_PATH);

    result = RegCreateKeyA(HKEY_CLASSES_ROOT, KEY_PATH, &h_key);

    if (result != ERROR_SUCCESS) {
        return;
    }

    result = RegSetValueExA(h_key, NULL, 0, 
                            REG_SZ, MENU_TEXT, sizeof(MENU_TEXT));
    
    RegCloseKey(h_key);

    if (result != ERROR_SUCCESS) {
        return;
    }

    result = RegCreateKeyExA(HKEY_CLASSES_ROOT, 
                             KEY_PROC, 0, 
                             NULL,
                             REG_OPTION_NON_VOLATILE, 
                             KEY_WRITE, NULL, &h_key, NULL);

    if (result != ERROR_SUCCESS) {
        return;
    }

    char exe_path[MAX_PATH];
    GetModuleFileNameA(NULL, exe_path, MAX_PATH);

    result = RegSetValueExA(h_key, NULL, NULL, 
                            REG_SZ, exe_path, strlen(exe_path));

    result = RegSetKeyValueA(h_key, "ThreadingModel", NULL, 
                             REG_SZ, "Apartment", sizeof("Apartment"));
    
    RegCloseKey(h_key);
}