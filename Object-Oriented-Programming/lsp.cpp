#include <iostream>
#include <chrono>

#include <thread>


/* * @file: lsp.cpp
* @brief: Liskov Substitution Principle, LSP С++

* @developer: @ynwqmv
* @license: GNU General Public License 2.0
*/

class Shape {
public:
    virtual double area() const = 0;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height)
        : width_(width), height_(height) {}

    double area() const override {
        return width_ * height_;
    }

private:
    double width_;
    double height_;
};

class Square : public Shape {
public:
    Square(double side)
        : side_(side) {}

    double area() const override {
        return side_ * side_;
    }

private:
    double side_;
};

void printArea(const Shape& shape) {
    std::cout << "Area: " << shape.area() << std::endl;
}

int main() {
    Rectangle r(3, 4);
    Square s(3);
    printArea(r);
    printArea(s); // компилятор не выдаст ошибки, так как Square является подтипом Shape
    return 0;
}
