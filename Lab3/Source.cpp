/*
* 
*     ������� 3.
* 
*   �������� ������� ����. ������� ������ ������������:
*    � �������� ����
*    � ������� 
*    � ���������� ���� 
*   ������� ������ ����������� �� ������� ����� ��������
*   � ������ ���� ������, ����������:
*    � ��������� ������ ����� � ����������� ������ ��������� ����. ��� ����� ������������ 
*           ������ � �������� ������ �� ������, � ����� ��� ��� �������������� � ������ ������
*    � ����������� �������� ������� �������� ��� ������� �� ������� ��� ������ ������ ����
*   ������� ������ �� GLUT.
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
        std::cerr << "��� �������: " << argv[0] << ", ���������� ������: <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::cout << "��� �����: " << filename << std::endl;

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