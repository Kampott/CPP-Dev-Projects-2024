#pragma once
class Vector {

public:
    float x, y;

    Vector(float v_x, float v_y);

    //  оператор сложения двух векторов
    Vector operator+(Vector other_vector) {
        return Vector(x + other_vector.x, y + other_vector.y);
    }

};

Vector::Vector(float v_x, float v_y) {
    x = v_x;
    y = v_y;
}