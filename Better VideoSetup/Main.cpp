#include "Main.h"
#include "BinaryFileWork.h"
#include "Additional Files.h"

#include <Windows.h>
#include <msclr\marshal_cppstd.h>
#include <stdio.h>
#include <filesystem>
#include <string>
#include <fstream>

#pragma comment(lib, "user32.lib")

using namespace BetterVideoSetup;

std::string currentPath = std::filesystem::current_path().string();
std::string configPath = currentPath + "\\config\\beetle.cfg";
std::vector<Resolution> resolutions;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew Main);

    return 1;
}

void Main::SaveSettings()
{
    if (std::filesystem::exists(configPath))
    {
        std::ofstream file;

        if (
            !std::filesystem::exists(currentPath + "\\dgVoodoo.conf") &&
            !std::filesystem::exists(currentPath + "\\DDraw.dll") &&
            !std::filesystem::exists(currentPath + "\\D3DImm.dll")
            )
        {
            if (improveCheckBox->Checked)
            {
                file.open(currentPath + "\\DDraw.dll", std::ios::binary);
                file.write(files::DDraw, files::ddraw_count);
                file.close();

                file.open(currentPath + "\\D3DImm.dll", std::ios::binary);
                file.write(files::D3DImm, files::d3dimm_count);
                file.close();

                file.open(currentPath + "\\dgVoodoo.conf", std::ios::binary);
                file.write(files::dgVoodoo, files::config_count);
                file.close();
            }
        }

        file.open(configPath, std::ios::binary);

        file << Binary::WriteLong(resolutions[resolutionComboBox->SelectedIndex].width);
        file << Binary::WriteLong(resolutions[resolutionComboBox->SelectedIndex].height);
        file << Binary::WriteLong(32);

        if (driverComboBox->SelectedIndex == driverComboBox->Items->Count - 1)
        {
            file << Binary::WriteLong(1000);
            file << Binary::WriteLong(0);
            file << Binary::WriteLong(0);
        }
        else
        {
            file << Binary::WriteLong(driverComboBox->SelectedIndex);
            file << Binary::WriteLong(0);
            file << Binary::WriteLong(1);
        }

        file << Binary::WriteString(24, "");

        file.close();

        this->Close();
    }
    else
        MessageBox::Show("File save failed!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
}

void Main::GetSettings()
{
    Resolution res(640, 480);
    int driverIndex = 0;

    if (std::filesystem::exists(configPath))
    {
        char* f = NULL;
        size_t fsize = 0;
        size_t ptr = 0;

        if (Binary::OpenFile(f, fsize, configPath))
        {
            res.width = Binary::ReadLong(f, ptr);
            res.height = Binary::ReadLong(f, ptr);

            ptr += 4;

            int index = Binary::ReadLong(f, ptr);

            if (index == 1000)
                driverIndex = driverComboBox->Items->Count - 1;
            else
                driverIndex = index;
        }

        if (f != NULL)
        {
            delete[] f;
            f = NULL;
        }
    }

    for (int i = 0; i < resolutions.size(); i++)
        if (resolutions[i] == res)
        {
            resolutionComboBox->SelectedIndex = i;
            break;
        }

    driverComboBox->SelectedIndex = driverIndex;
}

void Main::GetDrivers()
{
    if (!std::filesystem::exists(configPath))
        MessageBox::Show("Incorrect location of the program. To work correctly, place the program in the folder with the executable file of the original game.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);

	if (
		std::filesystem::exists(currentPath + "\\dgVoodoo.conf") &&
		std::filesystem::exists(currentPath + "\\DDraw.dll") &&
		std::filesystem::exists(currentPath + "\\D3DImm.dll")
		)
		driverComboBox->Items->Add("dgVoodoo DirectX Wrapper");
	else
		driverComboBox->Items->Add("Primary Video Driver");

	DISPLAY_DEVICE dd;
	dd.cb = sizeof(DISPLAY_DEVICE);
	EnumDisplayDevices(NULL, 0, &dd, 0);
	driverComboBox->Items->Add(msclr::interop::marshal_as<String^>(dd.DeviceString));

	driverComboBox->Items->Add("(Software rendering)");

    HMONITOR hMonitor = 0;
    DEVMODE monMode;

    monMode.dmSize = sizeof(monMode);
    monMode.dmDriverExtra = 0;
    monMode.dmFields = DM_DISPLAYFREQUENCY;

    EnumDisplayDevices(NULL, 0, &dd, 0);

    DWORD numMode = 0;
    while (EnumDisplaySettingsEx(NULL, numMode, &monMode, EDS_RAWMODE))
    {
        std::string temp = "";
        temp = std::to_string(monMode.dmPelsWidth) + " x " + std::to_string(monMode.dmPelsHeight) + " x " + std::to_string(monMode.dmBitsPerPel) + " bits";

        if (!resolutionComboBox->Items->Contains(msclr::interop::marshal_as<String^>(temp)))
        {
            resolutionComboBox->Items->Add(msclr::interop::marshal_as<String^>(temp));       
            Resolution res(monMode.dmPelsWidth, monMode.dmPelsHeight);
            resolutions.push_back(res);
        }
        numMode++;
    }
}