#include "menu.h"

Menu::path_name Menu::OpenFile(std::string id, Menu::path_name cur)
{
    Menu::path_name temp = cur;
    // ImGuiFileDialog::Instance()->OpenModal("ChooseFile", "Choose File", filters.c_str(), filePathName.c_str());

    if (ImGuiFileDialog::Instance()->Display(id))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            temp.path = ImGuiFileDialog::Instance()->GetFilePathName();
            temp.name = ImGuiFileDialog::Instance()->GetCurrentFileName();
        }
        ImGuiFileDialog::Instance()->Close();
    }
    return temp;
}
