#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // Kép méretei és a fraktál paraméterei
    const int szelesseg = 600;
    const int magassag = 600;
    const int iteraciosHatar = 255;

    // A vizsgált komplex sík tartománya
    const double a = -2.0, b = 0.7, c = -1.35, d = 1.35;

    // Létrehozunk egy képfájlt PPM formátumban
    ofstream kep("mandelbrot.ppm");
    if (!kep.is_open()) {
        cerr << "Hiba a fajl letrehozasakor!" << endl;
        return 1;
    }

    // A PPM fájl fejléce
    kep << "P3\n" << szelesseg << " " << magassag << "\n255\n";

    double dx = (b - a) / szelesseg;
    double dy = (d - c) / magassag;

    cout << "Fraktal generalasa folyamatban..." << endl;

    // Képpontok kiszámítása
    for (int i = 0; i < magassag; ++i) {
        for (int j = 0; j < szelesseg; ++j) {

            double reC = a + j * dx;
            double imC = d - i * dy;
            double reZ = 0, imZ = 0, ujReZ;
            int iteracio = 0;

            // Mandelbrot egyenlet
            while (reZ * reZ + imZ * imZ < 4 && iteracio < iteraciosHatar) {
                ujReZ = reZ * reZ - imZ * imZ + reC;
                imZ = 2 * reZ * imZ + imC;
                reZ = ujReZ;
                ++iteracio;
            }

            // RGB Színképzés az iterációszám alapján
            if (iteracio == iteraciosHatar) {
                // Halmazon belüli pontok
                kep << "0 0 0 ";
            } else {
                // Halmazon kívüli pontok
                int red = (iteracio * 9) % 256;
                int green = (iteracio * 3) % 256;
                int blue = (iteracio * 15) % 256;

                kep << red << " " << green << " " << blue << " ";
            }
        }
        kep << "\n";
    }

    kep.close();
    cout << "Kesz! A kep elmentve 'mandelbrot.ppm' neven a projekt mappajaba." << endl;

    return 0;
}
