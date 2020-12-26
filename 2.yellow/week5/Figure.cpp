#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <memory>
#define PI 3.14

using namespace std;

class Figure {
 public:
    Figure() = default;

    virtual string  Name()      const = 0;
    virtual double  Perimeter() const = 0;
    virtual double  Area()      const = 0;

 protected:
    const string _type;
};


class Triangle : public Figure {
 public:
    Triangle(int ab, int bc, int ca)
        : AB(ab)
        , BC(bc)
        , CA(ca) {}

    string Name()      const override { return "TRIANGLE"; }
    double Perimeter() const override { return AB + BC + CA; }
    double HalfP()     const          { return Perimeter()/2; }
    double Area()      const override { return sqrt(HalfP()*(HalfP() - AB) * (HalfP() - BC) * (HalfP() - CA)); }

 private:
    double AB;
    double BC;
    double CA;
};

class Rect : public Figure {
 public:
    Rect(int wi, int hi)
        : _width(wi)
        , _height(hi) {}

    string Name()      const override { return "RECT"; }
    double Perimeter() const override { return 2 * (_width + _height); }
    double Area()      const override { return _width * _height; }

 private:
    double _width;
    double _height;
};

class Circle : public Figure {
 public:
    Circle(int r)
        : _radius(r){}
 
    string Name()      const override { return "CIRCLE"; }
    double Perimeter() const override { return 2 * PI * _radius; }
    double Area()      const override { return PI * pow(_radius, 2); }

 private:
    double _radius;
};


shared_ptr<Figure> CreateFigure(istream& is) {
    string name;
    is >> name;

    if (name == "RECT") {
        int w, h;
        is >> w >> h;
        return make_shared<Rect>(w, h);
    }
    else if (name == "TRIANGLE") {
        int a, b,c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a,b,c);
    }
    else if (name == "CIRCLE") {
        int r;
        is >> r;
        return make_shared<Circle>(r);
    }

    return {};

}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}

//ADD RECT 2 3 ADD TRIANGLE 3 4 5 ADD RECT 10 20 ADD CIRCLE 5 PRINT