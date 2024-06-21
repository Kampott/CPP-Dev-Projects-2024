#pragma once
#include "C:\Users\nasty\3D Objects\C++\Lab3\include\glut.h"
#define WIDTH_WINDOW 800
#define HEIGHT_WINDOW 600
#define WIDTH_MARGIN 50
#define HEIGHT_MARGIN 20
#define HEIGHT_TEXT 50
#define WIDTH_MARGIN_SUB_MENU 70
#define HEIGHT_MARGIN_SUB_MENU 10
#define HEIGHT_TEXT_SUB_MENU 30

struct MenuItem {
    float x;
    float y;
    std::string name;
    std::vector <MenuItem> sub_menu;
    bool SubMenuOpen = 0;
};

class MainMenu {
    std::vector <MenuItem> main_menu;
public:
    void AddItem(MenuItem new_item);
    void ReadMenu(std::string& filename);
    void PrintMenu();
    void OpenSub(int i);
    void CloseSub(int i);

    void Display();
    bool LeftBotton(int x, int y);
};

