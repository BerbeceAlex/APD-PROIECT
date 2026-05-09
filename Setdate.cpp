#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {

    const char* outputFile = "inputTest.txt";

    int numPoints;
    cout << "Cate puncte doresti sa generezi? ";
    cin >> numPoints;


    srand((unsigned int)time(0));

    ofstream file(outputFile);

    if (!file) {
        cerr << "EROARE: Nu s-a putut crea fisierul!" << endl;
        return 1;
    }

    cout << "Se genereaza datele..." << endl;

    for (int i = 0; i < numPoints; i++) {
  
        double x = (double)rand() / RAND_MAX * 1000.0;
        double y = (double)rand() / RAND_MAX * 1000.0;
        double z = (double)rand() / RAND_MAX * 1000.0;

        file << x << " " << y << " " << z << "\n";
    }

    file.close();

    cout << "Succes! S-au generat " << numPoints << " puncte in " << outputFile << endl;
    cout << "Acum poti rula programul principal (Secvential.cpp)." << endl;

    return 0;
}