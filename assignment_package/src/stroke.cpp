#include "stroke.h"

Stroke::Stroke() : radius(0.), color(), points()
{}

Stroke::Stroke(int radius, QColor color, std::pair<int, int> start)
    : radius(radius), color(color), randomKey(std::rand()), points(), angles() {
    points.push_back(start);
}

void Stroke::addPoint(int x, int y) {
    points.push_back(std::pair<int, int>(x, y));
}

void Stroke::addAngle(float theta) {
    angles.push_back(theta);
}
