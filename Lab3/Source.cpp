/*
* 
*     Задание 3.
* 
*   Написать систему меню. Система должна поддерживать:
*    • Основное меню
*    • Подменю 
*    • Диалоговые окна 
*   Система должна описываться во внешнем файле ресурсов
*   В рамках этой задачи, необходимо:
*    • Придумать формат файла и реализовать чтение элементов меню. Для этого использовать 
*           потоки и оператор чтения из потока, а также все что использовалось в первой задаче
*    • Разработать механизм задания действий при нажатии на клавишу или выборе пункта меню
*   Графику делаем на GLUT.
* 
*/

#include "C:\Users\nasty\3D Objects\C++\Lab3\include\glut.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<locale>
#include<sstream>
#include<iterator>
#include<Windows.h>
#include "Menu.h"
#include "resource.h"

MainMenu Menu;

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG:
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            EndDialog(hwndDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    }
    return FALSE;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    Menu.Display();
    glutSwapBuffers();
}

void MouseCallBack(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (Menu.LeftBotton(x, y)) {
            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
        }
        display();
    }
}

int main(int argc, char* argv[]) {
    std::locale::global(std::locale(""));

    if (argc != 2) {
        std::cerr << "Для запуска: " << argv[0] << ", необходимо ввести: <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::cout << "Имя файла: " << filename << std::endl;

    Menu.ReadMenu(filename);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH_WINDOW, HEIGHT_WINDOW);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Menu");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH_WINDOW, HEIGHT_WINDOW, 0.0);

    glutMouseFunc(MouseCallBack);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}