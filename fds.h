#pragma once
#include <windows.h>
#include <shlobj.h>
#include <string>
#include <fstream>

std::string get_documents_path() {
    char documents_path[MAX_PATH];
    if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, documents_path) == S_OK) {
        return std::string(documents_path);
    }
    return "";
}

std::string get_config_file_path() {
    return get_documents_path() + "\\config.json";
}