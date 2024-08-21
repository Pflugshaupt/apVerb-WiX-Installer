// CustomAction.cpp : Defines the entry point for the custom action.
#include "pch.h"
#include <windows.h>
#include <intrin.h>
#include <Msi.h>
#include <MsiQuery.h>

UINT __stdcall AVXDetect(__in MSIHANDLE hInstall) {
    int CPUInfo[4] = {0};
    bool hasAVX = false;

    auto hr = WcaInitialize(hInstall, "AVXDetect");
    ExitOnFailure(hr, "Failed to initialize");

    WcaLog(LOGMSG_STANDARD, "Initialized.");

    __cpuid(CPUInfo, 1);
    hasAVX = (CPUInfo[2] & 0x18000000) == 0x18000000;

    if (hasAVX) {
        // WcaSetProperty(L"AVX_SUPPORTED", L"1");
        MsiSetProperty(hInstall, L"AVXSUPPORTED", L"1");
    } else {
        // WcaSetProperty(L"AVX_SUPPORTED", L"0");
        MsiSetProperty(hInstall, L"AVXSUPPORTED", L"0");
    }
    WcaLog(LOGMSG_STANDARD, "Done.");

LExit:
    return WcaFinalize(ERROR_SUCCESS);
}