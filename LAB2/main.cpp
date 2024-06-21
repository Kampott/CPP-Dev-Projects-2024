#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<locale>
#include<sstream>
#include<iterator>
#include "Vector.h"
#include "SFML\Graphics.hpp"
#include "Point.h"




using namespace std;

using namespace sf;

int main() {
    //  создаем окно указанного размера

    Union result(WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2, RADIUS);
    result.DoDraw();
    return 0;
}
