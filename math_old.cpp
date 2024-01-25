#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Curve {
public:
    virtual ~Curve() {}
    virtual double getRadius() const = 0;
    virtual double getStep() const = 0;
    virtual double getX(double t) const = 0;
    virtual double getY(double t) const = 0;
    virtual double getZ(double t) const = 0;
    virtual double getDerivativeX(double t) const = 0;
    virtual double getDerivativeY(double t) const = 0;
    virtual double getDerivativeZ(double t) const = 0;
};

class Circle : public Curve {
private:
    double radius;
public:
    Circle(double radius) : radius(radius) {}
    ~Circle() {}
    double getRadius() const { return radius; }
    double getStep() const { return 0.0; }
    double getX(double t) const { return radius * cos(t); }
    double getY(double t) const { return radius * sin(t); }
    double getZ(double t) const { return 0.0; }
    double getDerivativeX(double t) const { return -radius * sin(t); }
    double getDerivativeY(double t) const { return radius * cos(t); }
    double getDerivativeZ(double t) const { return 0.0; }
};

class Ellipse : public Curve {
private:
    double radiusX;
    double radiusY;
public:
    Ellipse(double radiusX, double radiusY) : radiusX(radiusX), radiusY(radiusY) {}
    ~Ellipse() {}
    double getRadius() const { return (radiusX + radiusY) / 2; }
    double getStep() const { return 0.0; }
    double getX(double t) const { return radiusX * cos(t); }
    double getY(double t) const { return radiusY * sin(t); }
    double getZ(double t) const { return 0.0; }
    double getDerivativeX(double t) const { return -radiusX * sin(t); }
    double getDerivativeY(double t) const { return radiusY * cos(t); }
    double getDerivativeZ(double t) const { return 0.0; }
};

class Helix : public Curve {
private:
    double radius;
    double step;
public:
    Helix(double radius, double step) : radius(radius), step(step) {}
    ~Helix() {}
    double getRadius() const { return radius; }
    double getStep() const { return step; }
    double getX(double t) const { return radius * cos(t); }
    double getY(double t) const { return radius * sin(t); }
    double getZ(double t) const { return step * t / (2 * M_PI); }
    double getDerivativeX(double t) const { return -radius * sin(t); }
    double getDerivativeY(double t) const { return radius * cos(t); }
    double getDerivativeZ(double t) const { return step / (2 * M_PI); }
};

int main() {
    std::vector<Curve*> curves;

    // Populate container with random curves
    curves.push_back(new Circle(5.0));
    curves.push_back(new Ellipse(3.0, 4.0));
    curves.push_back(new Helix(2.0, 1.5));

    // Print coordinates of points and derivatives at t=PI/4
    double t = M_PI / 4;
    for (Curve* curve : curves) {
        std::cout << "Point: (" << curve->getX(t) << ", " << curve->getY(t) << ", " << curve->getZ(t) << ")" << std::endl;
        std::cout << "Derivative: (" << curve->getDerivativeX(t) << ", " << curve->getDerivativeY(t) << ", " << curve->getDerivativeZ(t) << ")" << std::endl;
        std::cout << std::endl;
    }

    // Create a container for circles
    std::vector<Circle*> circles;

    // Populate the container with circles from the first container
    for (Curve* curve : curves) {
        Circle* circle = dynamic_cast<Circle*>(curve);
        if (circle != nullptr) {
            circles.push_back(circle);
        }
    }

    // Sort the second container in ascending order of radii
    std::sort(circles.begin(), circles.end(), [](Circle* a, Circle* b) { return a->getRadius() < b->getRadius(); });

    // Compute the total sum of radii of all circles
    double sum = 0.0;
    for (Circle* circle : circles) {
        sum += circle->getRadius();
    }
}

