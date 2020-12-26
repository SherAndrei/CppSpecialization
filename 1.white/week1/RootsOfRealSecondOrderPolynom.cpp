#include <iostream>
#include <cmath>
using namespace std;

double D(const double& a, const double& b, const double& c) {
    return ((b*b)-(4*a*c));
}

int main() {
    double a, b, c;

    cin >> a >> b >> c;

    if (a == 0) {
        if (b != 0)
            cout << -c / b << endl;
    } else if (D(a, b, c) > 0) {
        cout << (-b - sqrt(D(a, b, c))) / (2 * a) << " " << (-b + sqrt(D(a, b, c))) / (2 * a) << endl;
    } else if (D(a, b, c) == 0) {
        cout << -b / (2 * a) << endl;
    }

    return 0;
}

