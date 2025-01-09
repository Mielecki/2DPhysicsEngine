#pragma once

struct Vector2D 
{
    float x, y;

    Vector2D(float x = 0, float y = 0) : x(x), y(y) {};

    Vector2D operator+(const Vector2D& other) const
    {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator-(const Vector2D& other) const
    {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D operator*(float mul) const
    {
        return Vector2D(x * mul, y * mul);
    }

    Vector2D operator/(float div) const
    {
        return Vector2D(x / div, y / div);
    }

    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2D& operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};