#include "myLib.h"
#include "studentas.h"
#include "funkcijos.h"

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<Studentas> studentai;
    char pasirinkimas;

    // Pagrindiniu pasirinkimu logika
    while (true) {
        cout << "Ar norite generuoti failus (g) ar nuskaityti duomenis is failo (f) ar juos ivesti patys (i)? (iveskite g arba f, arba i): ";
        cin >> pasirinkimas;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pasirinkimas == 'g') {
            // Failu generavimo logika
            int namuDarbaiKiekis;
            cout << "Kiek namu darbu rezultatu norite generuoti? ";
            cin >> namuDarbaiKiekis;

            cout << "Kiek studentu norite generuoti? (ivesti 1000, 10000, 100000, 1000000, 10000000, 'visi'): ";
            string input;
            cin >> input;

            if (input == "visi") {
                int sizes[] = {1000, 10000, 100000, 1000000, 10000000};
                for (int size : sizes) {
                    generuotiFailus(size, namuDarbaiKiekis, "studentai_");
                }
            } else {
                int studentuKiekis = std::stoi(input);
                generuotiFailus(studentuKiekis, namuDarbaiKiekis, "studentai_");
            }
            continue;
        } else if (pasirinkimas == 'f' || pasirinkimas == 'i') {
            break;
        } else {
            cout << "Klaida! Prasome ivesti 'g', 'f' arba 'i'!" << endl;
        }
    }

    try {
        if (pasirinkimas == 'f') {
            // Skaitymo is failo logika
            string failoPavadinimas;
            cout << "Iveskite failo pavadinima (pvz., studentai.txt): ";
            getline(cin, failoPavadinimas);
            nuskaitytiDuomenisIsFailo(failoPavadinimas, studentai);
        } else if (pasirinkimas == 'i') {
            // Rankinio ivedimo logika
            int studentuSkaicius;
            while (true) {
                cout << "Kiek studentu norite ivesti? ";
                cin >> studentuSkaicius;
                if (cin.fail() || studentuSkaicius <= 0) {
                    cout << "Klaida! Prasome ivesti teigiama skaiciu." << endl;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                } else {
                    break; 
                }
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

            for (int i = 0; i < studentuSkaicius; ++i) {
                cout << endl;
                cout << "Iveskite " << i + 1 << "-ojo studento duomenis:" << endl;

                // Generate random results?
                char atsitiktiniuPasirinkimas;
                while (true) {
                    cout << "Ar norite generuoti atsitiktinius balus (t - TAIP, n - NE)? ";
                    string ivestis; 
                    cin >> ivestis;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                    if (ivestis.length() == 1 && (ivestis[0] == 't' || ivestis[0] == 'n')) {
                        atsitiktiniuPasirinkimas = ivestis[0]; 
                        break; 
                    } else {
                        cout << "Klaida! Prasome ivesti tik viena simboli: 't' arba 'n'!" << endl;
                    }
                }

                bool atsitiktiniai = (atsitiktiniuPasirinkimas == 't');
                int namuDarbaiKiekis = 0;
                if (atsitiktiniai) {
                    cout << "Kiek namu darbu rezultatu norite generuoti? ";
                    while (true) {
                        cin >> namuDarbaiKiekis;
                        if (cin.fail() || namuDarbaiKiekis < 1) {
                            cout << "Klaida! Iveskite teigiama skaiciu: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                }

                Studentas studentas;
                ivestiStudenta(studentas, atsitiktiniai, namuDarbaiKiekis);
                studentai.push_back(studentas);
            }
        }
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    // Galutinio balo skaiciavimo metodo pasirinkimas
    char metodoPasirinkimas;
    while (true) {
        cout << "Ar norite skaiciuoti galutini bala pagal vidurki (v) ar mediana (m)? (iveskite v arba m): ";
        cin >> metodoPasirinkimas;

        if (metodoPasirinkimas == 'v' || metodoPasirinkimas == 'm') {
            break;
        } else {
            cout << "Klaida! Prasome ivesti 'v' arba 'm'!" << endl;
        }
    }

    bool naudotiVidurki = (metodoPasirinkimas == 'v');

    // Studentu rusiavimas ir spausdinimas
    std::sort(studentai.begin(), studentai.end(), lygintiPagalVarda);

    cout << endl;
    cout << left << setw(18) << "Vardas"
         << setw(18) << "Pavarde"
         << (naudotiVidurki ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (const auto &studentas : studentai) {
        spausdintiStudenta(studentas, naudotiVidurki);
    }

    return 0;
}