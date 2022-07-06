// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "mem.h"
#include "proc.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
    //Create console
    AllocConsole();
    FILE * f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTitleW(L"Femboyware : AssaultCube Edition");
    SetConsoleTextAttribute(h, 3);
    std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    SetConsoleTextAttribute(h, 13);
    std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    SetConsoleTextAttribute(h, 15);
    std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    SetConsoleTextAttribute(h, 13);
    std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    SetConsoleTextAttribute(h, 3);
    std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n";
    std::cout << "\n";
    std::cout << "\n";

    SetConsoleTextAttribute(h, 3);
    std::cout << "FE";
    SetConsoleTextAttribute(h, 13);
    std::cout << "MB";
    SetConsoleTextAttribute(h, 15);
    std::cout << "OY";
    SetConsoleTextAttribute(h, 13);
    std::cout << "WA";
    SetConsoleTextAttribute(h, 3);
    std::cout << "RE\n";

    SetConsoleTextAttribute(h, 13);
    std::cout << "Infinite Health : NUMPAD 1\n";
    std::cout << "Infinite Ammo : NUMPAD 2\n";
    std::cout << "No Recoil : NUMPAD 3\n";
    std::cout << "NoClip : NUMPAD 4\n";
    std::cout << "Uninject : END\n";

    




    //get module base
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe"), recoilAddr1 = 0x56bf8e, recoilAddr2 = 0x56bf90;

    bool bHealth = false, bAmmo = false, bInvis = false, bNoClip = false, bRecoil = false, bClip = false;
    
    const int recoilValue = 0;
    const int oldRecoil1 = 25;
    const int oldRecoil2 = 50;
    
    //hack loop
    while(true)
    {
        //key input

       
        if (GetAsyncKeyState(VK_END) & 1)
        {
            fclose(f);
            FreeConsole();
            FreeLibraryAndExitThread(hModule, 0);
            return 0;
        }


        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            bHealth = !bHealth;
        }

        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            bAmmo = !bAmmo;
        }

        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            bRecoil = !bRecoil;
        }

        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            bNoClip = !bNoClip;
        }

        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            bClip = !bClip;
        }


       

      //  if (GetAsyncKeyState(VK_NUMPAD4) & 1)
      //  {
       //     bNoClip = !bNoClip;
       // }

       
        //freeze
        uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + 0x17E0A8);

        if (localPlayerPtr)
        {
            if (bHealth)
            {
                *(int*)(*localPlayerPtr + 0xEC) = 696969;

            }
            else
            {
                *(int*)(*localPlayerPtr + 0xEC) = 100;

            }

            if (bNoClip)
            {
                *(int*)(*localPlayerPtr + 0x76) = 4;

            }
            if(bClip)
                *(int*)(*localPlayerPtr + 0x76) = 0;



            if (bAmmo)
            {
                mem::Patch((BYTE*)(moduleBase + 0xC73EF), (BYTE*)"\xFF\x00", 2);

            }
            else
            {
                mem::Patch((BYTE*)(moduleBase + 0xC73EF), (BYTE*)"\xFF\x08", 2);

            }


            
           
            

            if (bRecoil)
            {
                *(int*)(0x056BF8E) = 0;
                *(int*)(0x056BF90) = 0;

            }
            else
            {
                *(int*)(0x056BF8E) = 25;
                *(int*)(0x056BF90) = 50;


            }
            Sleep(5);
        }

        
        
    }






    //cleanup & eject
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

