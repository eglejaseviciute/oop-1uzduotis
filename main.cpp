#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;

// Struktura, skirta studento duomenims saugoti
struct Studentas {
    string vardas;
    string pavarde;
    vector<int> namuDarbai;
    int egzaminas;
};

// Funkcija, kuri skaiciuoja vidurki is namu darbu rezultatu
double skaiciuotiVidurki(const vector<int>& namuDarbai) {
    double suma = 0;
    for (int nd : namuDarbai) {
        suma += nd;
    }
    return suma / namuDarbai.size();
}

// Funkcija, kuri skaiciuoja mediana is namu darbu rezultatu
double skaiciuotiMediana(vector<int> namuDarbai) {
    std::sort(namuDarbai.begin(), namuDarbai.end());
    int dydis = namuDarbai.size();
    if (dydis % 2 == 0) {
        return (namuDarbai[dydis / 2 - 1] + namuDarbai[dydis / 2]) / 2.0;
    } else {
        return namuDarbai[dydis / 2];
    }
}

// Funkcija, kuri generuoja atsitiktinius rezultatus
void generuotiRezultatus(Studentas &studentas, int namuDarbaiKiekis) {
    for (int i = 0; i < namuDarbaiKiekis; ++i) {
        studentas.namuDarbai.push_back(rand() % 11); // Generuojame atsitiktini rezultata nuo 0 iki 10
    }
    studentas.egzaminas = rand() % 11; // Generuojame atsitiktini egzamino rezultata nuo 0 iki 10
}

// Funkcija, kuri iveda studento duomenis
void ivestiStudenta(Studentas &studentas, bool atsitiktiniai, int namuDarbaiKiekis) {
    cout << "Iveskite studento varda: ";
    cin >> studentas.vardas;
    cout << "Iveskite studento pavarde: ";
    cin >> studentas.pavarde;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (atsitiktiniai) {
        generuotiRezultatus(studentas, namuDarbaiKiekis);
    } else {
        string input;
        int rezultatas;
        bool bentVienasRezultatas = false;

        cout << "Iveskite namu darbu rezultatus (du kartus paspauskite ENTER, kai noresite baigti):" << endl;

        while (true) {
            std::getline(cin, input);

            if (input.empty()) {
                if (bentVienasRezultatas) {
                    break;
                } else {
                    cout << "Turite ivesti bent viena namu darbu rezultata!" << endl;
                    continue;
                }
            }

            try {
                rezultatas = std::stoi(input);
                if (rezultatas < 0 || rezultatas > 10) {
                    cout << "Klaida! Namu darbu rezultatas turi buti tarp 0 ir 10. Iveskite teigiama skaiciu: ";
                } else {
                    studentas.namuDarbai.push_back(rezultatas);
                    bentVienasRezultatas = true;
                }
            } catch (const std::invalid_argument&) {
                cout << "Klaida! Prasome ivesti tinkama skaiciu: ";
            }
        }

        cout << "Iveskite egzamino rezultata: ";
        while (!(cin >> studentas.egzaminas) || studentas.egzaminas < 0 || studentas.egzaminas > 10) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Klaida! Prasome ivesti tinkama egzamino rezultata (0-10): ";
        }
        cout << endl;
    }
}

// Funkcija, kuri spausdina studento duomenis kartu su galutiniu balu
void spausdintiStudenta(const Studentas &studentas, bool naudotiVidurki) {
    double galutinis;
    if (naudotiVidurki) {
        double vidurkis = skaiciuotiVidurki(studentas.namuDarbai);
        galutinis = 0.4 * vidurkis + 0.6 * studentas.egzaminas;
    } else {
        double mediana = skaiciuotiMediana(studentas.namuDarbai);
        galutinis = 0.4 * mediana + 0.6 * studentas.egzaminas;
    }

    cout << std::left << std::setw(12) << studentas.vardas
         << std::setw(12) << studentas.pavarde
         << std::fixed << std::setprecision(2) << galutinis << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Atsitiktiniu skaičiu generatorius

    int studentuSkaicius;
    cout << "Kiek studentu norite ivesti? ";
    cin >> studentuSkaicius;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Studentas> studentai(studentuSkaicius);
    for (int i = 0; i < studentuSkaicius; ++i) {
        cout << endl;
        cout << "Iveskite " << i + 1 << "-ojo studento duomenis:" << endl;
        char pasirinkimas;
        cout << "Ar norite generuoti atsitiktinius balus (t - TAIP, n - NE)? ";
        cin >> pasirinkimas;
        bool atsitiktiniai = (pasirinkimas == 't');

        int namuDarbaiKiekis = 0;
        if (atsitiktiniai) {
            cout << "Kiek namu darbu rezultatu norite generuoti (nuo 1 iki 10)? ";
            cin >> namuDarbaiKiekis;
            while (namuDarbaiKiekis < 1 || namuDarbaiKiekis > 10) {
                cout << "Klaida! Iveskite skaiciu tarp 1 ir 10: ";
                cin >> namuDarbaiKiekis;
            }
        }

        ivestiStudenta(studentai[i], atsitiktiniai, namuDarbaiKiekis);
    }

    char pasirinkimas;
    cout << "Ar norite skaiciuoti galutini bala naudodami vidurki (v) ar mediana (m)? (iveskite v arba m): ";
    cin >> pasirinkimas;
    bool naudotiVidurki = (pasirinkimas == 'v');

    cout << std::left << std::setw(12) << "Vardas"
         << std::setw(12) << "Pavarde"
         << (naudotiVidurki ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
    cout << "------------------------------------------------------" << endl;

    for (const auto& studentas : studentai) {
        spausdintiStudenta(studentas, naudotiVidurki);
    }

    return 0;
}
