#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<locale>
#include<sstream>
#include<iterator>
#include<Windows.h>
#include "Menu.h"


void MainMenu::AddItem(MenuItem new_item) {
	main_menu.push_back(new_item);
}

void MainMenu::ReadMenu(std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Не удается открыть файл." << std::endl;
        return;
    }

    std::string line;
    MenuItem item;
    while (std::getline(file, line)) {
        if (line.empty()) {
            main_menu.push_back(item);
            MenuItem item;
        }
        else {
            item.sub_menu.clear();
            if (line.find("SUB_MENU") != std::string::npos) {
                std::getline(file, line);
                while (line.find("END_SUB_MENU") == std::string::npos) {
                    MenuItem item_sub_menu;
                    item_sub_menu.name = line;
                    item.sub_menu.push_back(item_sub_menu);
                    std::getline(file, line);
                }
            }
            else item.name = line;
        }
    }
    main_menu.push_back(item);

    file.close();

    for (int i = 0; i < (int)main_menu.size(); i++) {
        main_menu[i].x = WIDTH_MARGIN;
        main_menu[i].y = HEIGHT_MARGIN * (1 + i) + HEIGHT_TEXT * i;
        if (!main_menu[i].sub_menu.empty()) {
            for (int j = 0; j < (int)main_menu[i].sub_menu.size(); j++) {
                main_menu[i].sub_menu[j].x = WIDTH_MARGIN_SUB_MENU;
                main_menu[i].sub_menu[j].y = main_menu[i].y + HEIGHT_MARGIN_SUB_MENU * (1 + j) + HEIGHT_TEXT + j * HEIGHT_TEXT_SUB_MENU;
            }
        }
    }
}

void MainMenu::OpenSub(int i) {
    int count = main_menu[i].sub_menu.size();
    main_menu[i].SubMenuOpen = 1;
    int height = count * HEIGHT_TEXT_SUB_MENU + (count + 1) * HEIGHT_MARGIN_SUB_MENU - HEIGHT_MARGIN;
    for (int j = i + 1; j < (int)main_menu.size(); j++) {
        main_menu[j].y += height;
        if (!main_menu[j].sub_menu.empty()) for (auto& k : main_menu[j].sub_menu) k.y += height;
    }
}

void MainMenu::CloseSub(int i) {
    int count = main_menu[i].sub_menu.size();
    main_menu[i].SubMenuOpen = 0;
    int height = -count * HEIGHT_TEXT_SUB_MENU - (count + 1) * HEIGHT_MARGIN_SUB_MENU + HEIGHT_MARGIN;
    for (int j = i + 1; j < (int)main_menu.size(); j++) {
        main_menu[j].y += height;
        if (!main_menu[j].sub_menu.empty()) for (auto& k : main_menu[j].sub_menu) k.y += height;
    }
}

void PrintSubMenu(std::vector<MenuItem>& menu) {
    for (auto& item : menu) std::cout << " - " << item.name << std::endl;
}

void MainMenu::PrintMenu() {
    for (auto& item : main_menu) {
        std::cout << item.name << std::endl;
        if (!item.sub_menu.empty()) PrintSubMenu(item.sub_menu);
    }
}

void DrawArrowUpSubMenu(float x, float y) {
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 40, y + 10);
    glVertex2f(x + 40, y + 40);
    glVertex2f(x + 10, y + 40);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 25, y + 20);
    glVertex2f(x + 15, y + 30);
    glVertex2f(x + 35, y + 30);
    glEnd();
}

void DrawArrowDownSubMenu(float x, float y) {
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x + 40, y + 10);
    glVertex2f(x + 40, y + 40);
    glVertex2f(x + 10, y + 40);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 15, y + 20);
    glVertex2f(x + 35, y + 20);
    glVertex2f(x + 25, y + 30);
    glEnd();
}

void DrawFieldSubMenu(std::vector<MenuItem> menu) {
    for (auto& item_menu : menu) {
        glColor3f(1, 1, 1);
        glRasterPos2i(item_menu.x + 1.12 * WIDTH_MARGIN_SUB_MENU, item_menu.y + 0.6 * HEIGHT_TEXT_SUB_MENU);
        for (auto& i : item_menu.name) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, i);
        }
    }
}

void DrawFieldMenuItem(MenuItem item_menu, float width) {
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(item_menu.x, item_menu.y);
    glVertex2f(item_menu.x + width, item_menu.y);
    glVertex2f(item_menu.x + width, item_menu.y + HEIGHT_TEXT);
    glVertex2f(item_menu.x, item_menu.y + HEIGHT_TEXT);
    glEnd();
    if (!item_menu.sub_menu.empty()) {
        if (item_menu.SubMenuOpen == 0) DrawArrowDownSubMenu(item_menu.x, item_menu.y);
        else {
            DrawArrowUpSubMenu(item_menu.x, item_menu.y);
            DrawFieldSubMenu(item_menu.sub_menu);
        }
    }
    glColor3f(1, 1, 1);
    glRasterPos2i(item_menu.x + 1.12 * WIDTH_MARGIN, item_menu.y + 0.6 * HEIGHT_TEXT);
    for (auto& i : item_menu.name) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, i);
    }
}

void MainMenu::Display() {
    float width_text = 0;
    for (auto& i : main_menu) {
        int length = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)i.name.c_str());
        if (length > width_text) width_text = length;
    }
    width_text *= 3;

    for (auto& i : main_menu) DrawFieldMenuItem(i, width_text);
}

bool MainMenu::LeftBotton(int x, int y) {
    for (int i = 0; i < (int)main_menu.size(); i++) {
        if (x >= main_menu[i].x + 10 && x <= main_menu[i].x + 40 && y >= main_menu[i].y + 10 && y <= main_menu[i].y + 40 && !main_menu[i].sub_menu.empty()) {
            if (main_menu[i].SubMenuOpen == 0) {
                OpenSub(i);
                return 1;
            }
            else CloseSub(i);
        }
    }
    return 0;
}