#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct Point {
    double x, y, z;
};

// Functie pentru calculul distantei euclidiene
double euclideanDistance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
        (p1.y - p2.y) * (p1.y - p2.y) +
        (p1.z - p2.z) * (p1.z - p2.z));
}

int main() {
    const char* inputFile = "inputTest.txt";
    const int MAX_POINTS = 100000;

    // 1. DATE
    vector<Point> points;
    points.reserve(MAX_POINTS);

    ifstream inFile(inputFile);
    if (!inFile) {
        cerr << "EROARE: Nu s-a putut deschide fisierul de intrare!" << endl;
        return 1;
    }

    Point temp;
    while (points.size() < MAX_POINTS && inFile >> temp.x >> temp.y >> temp.z) {
        points.push_back(temp);
    }
    inFile.close();

    int n = points.size();
    if (n == 0) {
        cout << "Eroare: Nu s-au putut citi datele." << endl;
        return 1;
    }
    cout << "Am citit " << n << " puncte." << endl;

    // 2. Calculul performantei fara stocare in matrice
    // Calculam toate perechile pentru a simula efortul procesorului
    cout << "Calculare in curs pentru " << n << " puncte " << endl;

    auto start_calc = high_resolution_clock::now();

    double sumaControl = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = euclideanDistance(points[i], points[j]);

            sumaControl += d;
        }
    }

    auto end_calc = high_resolution_clock::now();
    duration<double> elapsed_calc = end_calc - start_calc;

    // 3. Afisare statistici
    cout << "\n------------------------------------------" << endl;
    cout << fixed << setprecision(6);
    cout << "Puncte procesate:   " << n << endl;
    cout << "Timp de CALCUL:     " << elapsed_calc.count() << " secunde" << endl;
    cout << "------------------------------------------" << endl;

    cout << "Suma de control:    " << (long long)sumaControl << " (doar pt verificare)" << endl;

    return 0;
}