#include "Student.h"
#include "Wykladowca.h"
#include "Wydzial.h"
#include "Wyklad.h"
#include "Materialy.h"
#include "testy.h"


#include <iostream>

//Wydzial
bool dodanieDoListyWykladowWydzial(){
    Wydzial* wydz = new Wydzial("Wydzial Matematyki");
    Wyklad* wyk = new Wyklad("wyklad1", wydz);

    bool result = wydz->getListaWykladow().size() == 1;

    delete wydz;

    return result;
}

bool usuwanieZListyWykladowWydzial(){
    Wydzial* wydz = new Wydzial("Wydzial");
    Wyklad* wyk = new Wyklad("wyklad1", wydz);

    wydz->usunWyklad(wyk);

    bool result = wydz->getListaWykladow().size() == 0;

    delete wydz;

    return result;
}

bool dodanieDoListyStudentowUczelnia(){
    Wydzial* wydz = new Wydzial("Wydzial Matematyki");
    vector<Wydzial*> wektor;
    wektor.push_back(wydz);
    Uczelnia* ucz = new Uczelnia("Uczelnia",wektor);

    Student* st1 = new Student("Imie", "Nazwisko", 1234, "haslo");

    ucz->dodajStudenta(st1);

    bool result = ucz->getListaStudentow().size() == 1;

    delete ucz;

    return result;
}

bool usuwanieZListyStudentowUczelnia(){
    Wydzial* wydz = new Wydzial("Wydzial Matematyki");
    vector<Wydzial*> wektor;
    wektor.push_back(wydz);
    Uczelnia* ucz = new Uczelnia("Uczelnia",wektor);

    Student* st1 = new Student("Imie", "Nazwisko", 1234, "haslo");

    ucz->dodajStudenta(st1);

    ucz->usunStudenta(st1);

    bool result = ucz->getListaStudentow().size() == 0;

    delete ucz;

    return result;
}

bool zmianaHasla(){
    Wydzial* wydz = new Wydzial("Wydzial Matematyki");
    vector<Wydzial*> wektor;
    wektor.push_back(wydz);
    Uczelnia* ucz = new Uczelnia("Uczelnia",wektor);

    Student* st1 = new Student("Imie", "Nazwisko", 1234, "haslo");

    ucz->dodajStudenta(st1);

    ucz->ZmianaHasla("1234", "haslo", "haslo1");

    bool result = st1->getHaslo() == "haslo1";

    delete ucz;

    return result;
}

bool dodawanieMateralowWykladowca(){
    Wykladowca* wyk = new Wykladowca("Imie", "Nazwisko", "login", "haslo");
    Wyklad* wyklad = new Wyklad("wyklad", nullptr);
    Materialy* mat = new Materialy("Plik", "PDF");

    wyklad->dodajWykladowce(wyk);
    wyk->dodajMaterialy(wyklad,mat);

    bool result = wyklad->getListaMaterialow().size() == 1;

    delete wyklad;
    delete wyk;

    return result;
}


bool usuwanieMateralowWykladowca(){
    Wykladowca* wyk = new Wykladowca("Imie", "Nazwisko", "login", "haslo");
    Wyklad* wyklad = new Wyklad("wyklad", nullptr);
    Materialy* mat = new Materialy("Plik", "PDF");

    wyklad->dodajWykladowce(wyk);
    wyk->dodajMaterialy(wyklad,mat);

    wyk->usunMaterialy(wyklad, mat);

    bool result = wyklad->getListaMaterialow().size() == 0;

    delete wyklad;
    delete wyk;

    return result;
}


bool przegladanieMateralowStudent(){
    Student* st1 = new Student("Imie", "Nazwisko", 1234, "haslo");
    Wyklad* wyklad = new Wyklad("wyklad", nullptr);
    Materialy* mat = new Materialy("Plik", "PDF");

    wyklad->dodajStudenta(st1);
    wyklad->dodajMaterialy(mat);

    bool result = wyklad->getListaMaterialow() == st1->przegladajMaterialy(wyklad);

    delete wyklad;
    delete st1;

    return result;
}

void petla(Uczelnia* uczelnia1){
    string login,haslo;
    char decyzja;
    Student* zalogowanyStudent = nullptr;
    Wykladowca* zalogowanyWykladowca = nullptr;

    cout << "\n=== EKRAN LOGOWANIA ===" << endl;
    cout << "Witaj na uczelni!" << endl;
    cout << "Zaloguj się:" << endl;

    while(1){
        cin >> login >> haslo;

        switch (uczelnia1->Zaloguj(login, haslo)){
        case 's':{
            zalogowanyStudent = uczelnia1->znajdzStudenta(login);
            while(1){
                cout << "\n--- MENU STUDENTA ---" << endl;
                cout << "Wybierz numer:" << endl;
                cout << "1.Przegladaj materialy" << endl;
                cout << "2.Zmien haslo" << endl;
                cout << "3.Dolacz do wykladu" << endl;
                cout << "4.Wyloguj" << endl;
                cin >> decyzja;

                switch (decyzja) {
                    case '1':{
                        cout << "Wybierz wyklad: " << endl;

                        for(Wyklad* w :zalogowanyStudent->getListaWykladow()){
                            cout << w->getNazwa() << endl;
                        }

                        string nazwaWykladu;
                        bool znaleziono = false;
                        std::cin.ignore();
                        getline(cin ,nazwaWykladu);

                        for(Wyklad* w :zalogowanyStudent->getListaWykladow()){
                            if(nazwaWykladu == w->getNazwa()){
                                znaleziono = true;
                                for(Materialy* mat: zalogowanyStudent->przegladajMaterialy(w)){
                                    cout << mat->getNazwa() << endl;
                                }
                            }
                        }
                        if (!znaleziono){
                            cout << "Nie znaleziono danego wykładu." << endl;
                        }
                        break;
                    }

                    case '2':{
                        string starehaslo, nowehaslo;

                        cout << "Wpisz stare haslo: " << endl;
                        cin >> starehaslo;
                        cout << "Wpisz nowe haslo: " << endl;
                        cin >> nowehaslo;

                        uczelnia1->ZmianaHasla(login, starehaslo ,nowehaslo);

                        break;
                    }

                    case '3':{
                        cout << "Dostepne wyklady:" << endl;
                        bool saDostepneWyklady = false;

                        for (Wydzial* wydz : uczelnia1->getListaWydzialow()) {
                            for (Wyklad* w : wydz->getListaWykladow()) {
                                if (!w->getHaslo().empty()) {
                                    auto mojeWyklady = zalogowanyStudent->getListaWykladow();
                                    if (find(mojeWyklady.begin(), mojeWyklady.end(), w) == mojeWyklady.end()) {
                                        cout << "- " << w->getNazwa() << " (Wydzial: " << wydz->getNazwa() << ")" << endl;
                                        saDostepneWyklady = true;
                                    }
                                }
                            }
                        }

                        if (!saDostepneWyklady) {
                            cout << "Brak nowych wykladow, do ktorych mozesz dolaczyc." << endl;
                            break;
                        }

                        cout << "Wpisz nazwe wykladu, do ktorego chcesz dolaczyc: " << endl;

                        string nazwaWyk;
                        cin.ignore();
                        getline(cin, nazwaWyk);

                        Wyklad* wybranyWyklad = nullptr;
                        for (Wydzial* wydz : uczelnia1->getListaWydzialow()) {
                            for (Wyklad* w : wydz->getListaWykladow()) {
                                if (w->getNazwa() == nazwaWyk && !w->getHaslo().empty()) {
                                    wybranyWyklad = w;
                                    break;
                                }
                            }
                            if (wybranyWyklad) break;
                        }

                        if (wybranyWyklad != nullptr) {
                            cout << "Wpisz haslo do wykladu: " << endl;
                            string podaneHasloWykladu;
                            getline(cin, podaneHasloWykladu);

                            zalogowanyStudent->dolaczDoWykladu(wybranyWyklad, podaneHasloWykladu);
                        } else {
                            cout << "Wyklad nie istnieje lub jest niewidoczny (brak hasla)." << endl;
                        }
                        break;
                    }

                    case '4':{
                        cout << "Wylogowano" << endl;
                        return;
                    }
                }
            }
            break;
        }

        case 'w':{
            zalogowanyWykladowca = uczelnia1->znajdzWykladowce(login);
            while(1){
                cout << "\n--- MENU WYKLADOWCY ---" << endl;
                cout << "Wybierz numer:" << endl;
                cout << "1.Przegladaj materialy" << endl;
                cout << "2.Dodaj materialy" << endl;
                cout << "3.Usun materialy" << endl;
                cout << "4.Zmien haslo" << endl;
                cout << "5.Utworz nowy wyklad" << endl;
                cout << "6.Zmien haslo wykladu" << endl;
                cout << "7.Wyloguj" << endl;
                cin >> decyzja;

                switch (decyzja) {
                    case '1':{
                        cout << "Wybierz wyklad: " << endl;

                        for(Wyklad* w :zalogowanyWykladowca->getListaWykladow()){
                            cout << w->getNazwa() << endl;
                        }

                        string nazwaWykladu;
                        bool znaleziono = false;
                        std::cin.ignore();
                        getline(cin ,nazwaWykladu);

                        for(Wyklad* w :zalogowanyWykladowca->getListaWykladow()){
                            if(nazwaWykladu == w->getNazwa()){
                                znaleziono = true;
                                for(Materialy* mat: zalogowanyWykladowca->przegladajMaterialy(w)){
                                    cout << mat->getNazwa() << ", Rodzaj: " << mat->getRodzaj() << endl;
                                }
                            }
                        }
                        if (!znaleziono){
                            cout << "Nie znaleziono danego wykładu." << endl;
                        }

                        break;
                    }

                    case '2':{
                        cout << "Wybierz wyklad: " << endl;

                        for(Wyklad* w :zalogowanyWykladowca->getListaWykladow()){
                            cout << w->getNazwa() << endl;
                            cout.flush();
                        }

                        string nazwaWykladu;
                        bool znaleziono = false;
                        std::cin.ignore();
                        getline(cin ,nazwaWykladu);

                        for(Wyklad* w :zalogowanyWykladowca->getListaWykladow()){
                            if(nazwaWykladu == w->getNazwa()){
                                znaleziono = true;
                                string nazwa,typ;

                                cout << "Wpisz nazwe zadania: " << endl;
                                getline(cin ,nazwa);

                                cout << "Wpisz typ zadania: " << endl;
                                // cin.ignore() usunięte!
                                getline(cin ,typ);

                                zalogowanyWykladowca->dodajMaterialy(w, new Materialy{nazwa,typ});
                            }
                        }
                        if (!znaleziono){
                            cout << "Nie znaleziono danego wykładu." << endl;
                        }

                        break;
                    }

                    case '3':{
                        cout << "Wybierz wyklad: " << endl;

                        for(Wyklad* w :zalogowanyWykladowca->getListaWykladow()){
                            cout << w->getNazwa() << endl;
                        }

                        string nazwaWykladu;
                        bool znaleziono = false;
                        std::cin.ignore();
                        getline(cin ,nazwaWykladu);

                        for(Wyklad* w :zalogowanyWykladowca->getListaWykladow()){
                            if(nazwaWykladu == w->getNazwa()){
                                znaleziono = true;
                                cout << "Wybierz zadanie do usuniecia: " << endl;
                                for(Materialy* mat: zalogowanyWykladowca->przegladajMaterialy(w)){
                                    cout << mat->getNazwa() << endl;
                                }

                                string nazwa;
                                getline(cin ,nazwa);

                                for(Materialy* mat: zalogowanyWykladowca->przegladajMaterialy(w)){
                                    if (mat->getNazwa() == nazwa){
                                        zalogowanyWykladowca->usunMaterialy(w, mat);
                                    }
                                }
                            }
                        }
                        if (!znaleziono){
                            cout << "Nie znaleziono danego wykładu." << endl;
                        }

                        break;
                    }

                    case '4':{
                        string starehaslo, nowehaslo;

                        cout << "Wpisz stare haslo: " << endl;
                        cin >> starehaslo;
                        cout << "Wpisz nowe haslo: " << endl;
                        cin >> nowehaslo;

                        uczelnia1->ZmianaHasla(login, starehaslo ,nowehaslo);

                        break;
                    }

                    case '5':{
                        cout << "Dostepne wydzialy na uczelni:" << endl;
                        for (Wydzial* wydz : uczelnia1->getListaWydzialow()) {
                            cout << "- " << wydz->getNazwa() << endl;
                        }

                        cout << "Wpisz nazwe wydzialu, do ktorego przypisac wyklad: " << endl;
                        string nazwaWydzialu;
                        cin.ignore();
                        getline(cin, nazwaWydzialu);

                        Wydzial* wybranyWydzial = nullptr;
                        for (Wydzial* wydz : uczelnia1->getListaWydzialow()) {
                            if (wydz->getNazwa() == nazwaWydzialu) {
                                wybranyWydzial = wydz;
                                break;
                            }
                        }

                        if (wybranyWydzial == nullptr) {
                            cout << "Blad: Nie znaleziono takiego wydzialu!" << endl;
                            break;
                        }

                        cout << "Wpisz nazwe nowego wykladu: " << endl;
                        string nazwaNowegoWykladu;
                        getline(cin, nazwaNowegoWykladu);

                        Wyklad* nowyWyklad = zalogowanyWykladowca->utworzWyklad(wybranyWydzial, nazwaNowegoWykladu);

                        cout << "Czy chcesz dodać hasło do wykładu? [T\\N]";
                        string wybor;
                        getline(cin, wybor);

                        if (wybor == "T") {
                            cout << "Wpisz haslo do wykladu: " << endl;
                            string hasloNowegoWykladu;
                            getline(cin, hasloNowegoWykladu);

                            nowyWyklad->setHaslo(hasloNowegoWykladu);
                            cout << "Pomyslnie utworzono wyklad z haslem." << endl;
                        } else {
                            cout << "Pomyslnie utworzono wyklad bez hasla." << endl;
                        }
                        break;
                    }

                    case '6':{
                        if (zalogowanyWykladowca->getListaWykladow().empty()) {
                            cout << "Nie prowadzisz obecnie zadnych wykladow." << endl;
                            break;
                        }

                        cout << "Wykłady: " << endl;
                        for (Wyklad* w : zalogowanyWykladowca->getListaWykladow()) {
                            cout << "- " << w->getNazwa() << " [Obecne haslo: " <<
                                (w->getHaslo().empty() ? "BRAK" : w->getHaslo()) << "]" << endl;
                        }

                        cout << "Wpisz nazwe wykladu, ktorego haslo chcesz zmienic: " << endl;
                        string nazwaWyk;
                        cin.ignore();
                        getline(cin, nazwaWyk);

                        Wyklad* wybranyWyk = nullptr;
                        for (Wyklad* w : zalogowanyWykladowca->getListaWykladow()) {
                            if (w->getNazwa() == nazwaWyk) {
                                wybranyWyk = w;
                                break;
                            }
                        }

                        if (wybranyWyk != nullptr) {
                            cout << "Wpisz nowe haslo dla wykladu: " << endl;
                            string noweHasloWyk;
                            getline(cin, noweHasloWyk);

                            wybranyWyk->setHaslo(noweHasloWyk);
                            cout << "Haslo wykladu zostalo zmienione pomyslnie." << endl;
                        } else {
                            cout << "Nie jestes prowadzacym tego wykladu lub podano zla nazwe." << endl;
                        }
                        break;
                    }

                    case '7':{
                        cout << "Wylogowano" << endl;
                        return;
                    }
                }
            }
            break;
        }
            case 'f':{
                cout << "Zaloguj się ponownie:" << endl;
                break;
            }
        }


    }
}

int testy(){
    cout << dodanieDoListyWykladowWydzial() << endl; //true
    cout << usuwanieZListyWykladowWydzial() << endl; //true
    cout << dodanieDoListyStudentowUczelnia() << endl; //true
    cout << usuwanieZListyStudentowUczelnia() << endl; //true
    cout << zmianaHasla() << endl; //true
    cout << dodawanieMateralowWykladowca() << endl;; //true
    cout << usuwanieMateralowWykladowca() << endl;; //true
    cout << przegladanieMateralowStudent() << endl;; //true

    return 0;
}
