#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<locale>
#include<sstream>
#include "Vector.h"
#include "SFML\Graphics.hpp"


using namespace std;
using namespace sf;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGTH 480
#define MOVE_SPEED 0.5f
#define RADIUS 3

class Point
{
private:
    Vector position;
    vector<Vector> trail;
public:

    const float trail_length = 100;

    Point(float x, float y) : position(x, y) {}


    void PointMovement(Vector move_vector);

    auto Draw(RenderWindow& window, Vector move_vector, CircleShape trail_share);
};

auto Point::Draw(RenderWindow& window, Vector move_vector, CircleShape trail_share) {
    trail.push_back(position);
    if (trail.size() > trail_length) {
        trail.erase(trail.begin());
    }
    if (position.x < WINDOW_WIDTH + MOVE_SPEED && position.x > WINDOW_WIDTH - MOVE_SPEED) {
        position.x = 0;
    }
    else if (position.x < MOVE_SPEED) {
        position.x = WINDOW_WIDTH;
    }
    if (position.y < WINDOW_HEIGTH + MOVE_SPEED && position.y > WINDOW_HEIGTH - MOVE_SPEED) {
        position.y = 0;
    }
    else if (position.y < MOVE_SPEED) {
        position.y = WINDOW_HEIGTH;
    }
    position = position + move_vector;
    window.clear(Color::White);
    for (int i = 0; i < trail.size(); i++) {
        trail_share.setRadius(i * RADIUS / trail.size());
        trail_share.setFillColor(Color(255, 0, 255, i * 255 / trail.size()));
        trail_share.setPosition(trail[i].x, trail[i].y);
        window.draw(trail_share);
    }
}


void Point::PointMovement(Vector move_vector)
{

}

class Union
{
    Point point;
    CircleShape point_share;
    CircleShape trail_share;

public:
    Union(float x, float y, float R) : point(x, y), point_share(R), trail_share(R) {
        point_share.setFillColor(Color::Green);
    }

    void SetTrail(int i);

    void PointMovement(Vector change_movement) {
        
    }
    auto TrailShare() {
        return trail_share;
    }

    auto PointShare() {
        return point_share;
    }
    void DoDraw() {
        RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Draw");
        while (window.isOpen()) {

            Event event;
            window.pollEvent(event);
            if (event.type == Event::Closed) window.close();


            Vector change_movement(0, 0);
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                change_movement.x -= MOVE_SPEED;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                change_movement.x += MOVE_SPEED;
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                change_movement.y -= MOVE_SPEED;
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                change_movement.y += MOVE_SPEED;
            }


            point.Draw(window, change_movement, trail_share);

            window.draw(PointShare());

            window.display();
        }
    }
};


