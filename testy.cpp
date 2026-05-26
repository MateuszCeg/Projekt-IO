#include "Student.h"
#include "Wykladowca.h"
#include "Uczelnia.h"
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
    delete wyk;

    return result;
}

bool usuwanieZListyWykladowWydzial(){
    Wydzial* wydz = new Wydzial("Wydzial Matematyki");
    Wyklad* wyk = new Wyklad("wyklad1", wydz);

    wydz->usunWyklad(wyk);

    bool result = wydz->getListaWykladow().size() == 0;

    delete wydz;
    delete wyk;

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

    return result;
}


bool przegladanieMateralowStudent(){
    Student* st1 = new Student("Imie", "Nazwisko", 1234, "haslo");
    Wyklad* wyklad = new Wyklad("wyklad", nullptr);
    Materialy* mat = new Materialy("Plik", "PDF");

    wyklad->dodajStudenta(st1);
    wyklad->dodajMaterial(mat);

    bool result = wyklad->getListaMaterialow() == st1->przegladajMaterialy(wyklad);

    delete wyklad;

    return result;
}

void petla(){
    // Wydziały
    Wydzial* wydzInformatyki = new Wydzial("Wydzial Informatyki");
    Wydzial* wydzMatematyki = new Wydzial("Wydzial Matematyki");

    vector<Wydzial*> wszystkieWydzialy;
    wszystkieWydzialy.push_back(wydzInformatyki);
    wszystkieWydzialy.push_back(wydzMatematyki);

    // Uczelnia
    Uczelnia* uczelnia = new Uczelnia("UMCS", wszystkieWydzialy);

    // Wyklady
    Wyklad* wykInf1 = new Wyklad("Programowanie C++", wydzInformatyki);
    Wyklad* wykInf2 = new Wyklad("Bazy Danych", wydzInformatyki);
    Wyklad* wykInf3 = new Wyklad("Sieci Komputerowe", wydzInformatyki);


    Wyklad* wykMat1 = new Wyklad("Analiza Matematyczna", wydzMatematyki);
    Wyklad* wykMat2 = new Wyklad("Algebra Liniowa", wydzMatematyki);
    Wyklad* wykMat3 = new Wyklad("Rachunek Prawdopodobienstwa", wydzMatematyki);

    // Studenci
    Student* s1 = new Student("Jan", "Kowalski", 100111, "haslo1");
    Student* s2 = new Student("Anna", "Nowak", 100222, "haslo2");
    Student* s3 = new Student("Piotr", "Wisniewski", 100333, "haslo3");
    Student* s4 = new Student("Katarzyna", "Zielinska", 100444, "haslo4");

    uczelnia->dodajStudenta(s1);
    uczelnia->dodajStudenta(s2);
    uczelnia->dodajStudenta(s3);
    uczelnia->dodajStudenta(s4);

    // Wykładowcy
    Wykladowca* w1 = new Wykladowca("Alan", "Turing", "aturing", "tajne123");
    Wykladowca* w2 = new Wykladowca("Ada", "Lovelace", "alovelace", "tajne456");

    uczelnia->dodajWykladowce(w1);
    uczelnia->dodajWykladowce(w2);

    // Przypisanie Wykładowców
    wykInf1->dodajWykladowce(w1);
    wykInf2->dodajWykladowce(w1);
    wykMat1->dodajWykladowce(w2);

    // Przypisanie Studentów
    wykInf1->dodajStudenta(s1);
    wykInf1->dodajStudenta(s2);

    wykInf2->dodajStudenta(s2);
    wykInf2->dodajStudenta(s3);

    wykMat1->dodajStudenta(s1);
    wykMat1->dodajStudenta(s4);

    string login,haslo;
    char decyzja;

    cout << "Witaj na uczelni!" << endl;
    cout << "Zaloguj się:" << endl;

    while(1){


        cin >> login >> haslo;

        switch (uczelnia->Zaloguj(login, haslo)){
        case 's':{
            while(1){
                cout << "Wybierz numer:" << endl;
                cout << "1.Przegladaj materialy" << endl;
                cout << "2.Zmien haslo" << endl;
                cout << "3.Wyloguj" << endl;
                cin >> decyzja;

                switch (decyzja) {
                case '1':{
                }
                case '3':{
                    //return 0;
                }
                }
            }
            break;
        }

        case 'w':{
            while(1){
                cout << "Wybierz numer:" << endl;
                cout << "1.Przegladaj materialy" << endl;
                cout << "2.Zmien haslo" << endl;
                cout << "3.Dodaj materialy" << endl;
                cout << "4.Usun materialy" << endl;
                cout << "5.Wyloguj" << endl;
                cin >> decyzja;

                switch (decyzja) {
                case '5':{
                    //return 0;
                }
                }
            }
            break;
        }
            case 'f':{
                cout << "Zaloguj się ponownie:" << endl;
            }
        }


    }
}

int testy(){
    cout << dodanieDoListyWykladowWydzial(); //true

    return 0;
}
