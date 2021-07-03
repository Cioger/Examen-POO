/*
(3p) Se consideră o aplicație pentru gestionarea activității unei magazin care vinde baterii externe de tipul powerBank. 
Se vor urmări atribute specifice, precum: capacitate, greutate, numar intrari/iesiri, culoare etc. 
Datele membre sunt private și sunt puse la dispoziție metode de acces. 
Clasa conține cel puțin patru câmpuri, dintre care unul este alocat dinamic, constructori, metodele specifice claselor cu membri alocați 
dinamic și operatorul de afișare. Folosiți un membru static sau const.

 (1p) Se vor defini operator+=  și operator-= care permit încărcarea powerbank-ului respectiv descărcarea acestuia.

 (1p) Definiți operator== care compară două obiecte de tip PowerBank și returnează true dacă toate valorile atributelor corespunzătoare sunt 
 egale între ele.

 (2p) Exemplificați conceptul de relație de tip „is a” prin specializarea clasei PowerBank. Testați soluția prin instanțierea noii clase.

 (2p) Explicați conceptele de early binding și late binding.

 (1p) Exemplificați conceptul de funcție template în C++.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

//aici m-a pus sa ii exemplific polimorfism pt late binding si am facut eu o clasa interfata (credeam ca e abstracta)
// si am facut polimorfism la functia de afisare
class X {
    virtual void Afisare() = 0;
};

class PowerBank:public X{
private:
    int capacitate;
    int nrIntrari;
    float greutate;
    char* culoare;
    const int id;
public:
    friend X;
    static int contor;
    PowerBank():id(contor++) {
        this->capacitate = 0;
        this->greutate = 0;
        this->nrIntrari = 0;
        this->culoare = new char[strlen("") + 1];
        strcpy(this->culoare, "");
    }
    //nu iti trb validari, eu le-am facut pt ca aveam timp
    //mi-a zis profu ca nu e nev de ele si am si uitat sa scriu try catch in main
    PowerBank(int capacitate, float greutate, const char* culoare, int nrIntrari) :id(contor++) {
        if (capacitate <= 0) {
            throw new exception("capacitate prea mica");
        }
        else if (greutate <= 0) {
            throw new exception("greutate prea mica");
        }
        else {
            this->capacitate = capacitate;
            this->greutate = greutate;
            this->nrIntrari = nrIntrari;
            this->culoare = new char[strlen(culoare) + 1];
            strcpy(this->culoare, culoare);
        }
    }
    PowerBank(const PowerBank& p) :id(p.contor) {
            this->capacitate = p.capacitate;
            this->greutate = p.greutate;
            this->nrIntrari = p.nrIntrari;
            this->culoare = new char[strlen(p.culoare) + 1];
            strcpy(this->culoare, p.culoare);
        
    }
    //am facut toti getterii, cred ca era ok si doar cu unul
    //nu a fost nev de setteri
    int getCapacitate() {
        return this->capacitate;
    }
    float getGreutate() {
        return this->greutate;
    }
    int getNrIntrari() {
        return this->nrIntrari;
    }
    char* getCuloare() {
        return this->culoare;
    }

 //   void setCapacitate(int x) {}

    //asta e aici pentru polimorfism m-a pus el sa o fac dupa
    void Afisare() {
        cout << this->getCapacitate() << endl;
    }

    PowerBank& operator+=(int x) {
        this->capacitate += x;
        return *this;
    }
    PowerBank& operator-=(int x) {
        this->capacitate -= x;
        return *this;
    }

    //nu era nev de exceptie poti sa pui un cout
    PowerBank& operator=(const PowerBank& p){
        if (this != &p) {
        this->capacitate = p.capacitate;
        this->greutate = p.greutate;
        this->nrIntrari = p.nrIntrari;
        this->culoare = new char[strlen(p.culoare) + 1];
        strcpy(this->culoare, p.culoare);
        }
        else {
            throw new exception("nu s-a putut face autoasignarea");
        }
    }
    
    friend ostream& operator<<(ostream& out, PowerBank& p);

    ~PowerBank(){
        if (this->culoare != NULL) delete[] this->culoare;
    }

};
int PowerBank::contor = 1;

//asta e pentru cerinta cu "is a"
class PowerBankStricat :public PowerBank {
    bool estricat;
public:
    PowerBankStricat() :PowerBank() {
        this->estricat = false;
    }
    PowerBankStricat(int capacitate, float greutate, const char* culoare, int nrIntrari, bool estricat) :PowerBank(capacitate, greutate, culoare, nrIntrari) {
        this->estricat = estricat;
    }
    //bool getStricat()

    //afisarea e aici pentru polimorfism
    void Afisare() {
        cout << "daaaaaaaaa" << endl;
    }
    ~PowerBankStricat() {

    }
};

bool operator==(PowerBank b,PowerBank a) {
    if (a.getCapacitate() != b.getCapacitate()) {
        return false;
    }
    else if (a.getGreutate() != b.getGreutate()) {
        return false;
    }
    else if (a.getNrIntrari() != b.getNrIntrari()) {
        return false;
    }
    else if (strcmp(a.getCuloare(),b.getCuloare())!=0) {
        return false;
    }
    else return true;
}

ostream& operator<<(ostream& out, PowerBank& p) {
    out << "capacitate: " << p.capacitate << endl;
    out << "greutate: " << p.greutate << endl;
    out << "nrIntrari: " << p.nrIntrari << endl;
    out << "culoare: " << p.culoare << endl;
    return out;
}

//functia template am stiut doar sa o declar adica chestia asta de aici
//m-a ajutat profu sa o apelez
//T reprezinta un tip de date pe care i-l dai tu cand apelezi (int, float, double etc)
template<typename T>
T suma(T a, T b) {
    return a + b;
}

int main() {

    PowerBank p1;
    PowerBank p2(4, 20, "albastru", 3);
    PowerBank p3(p2);

    cout << p1 << endl << endl;
    cout << p2 << endl << endl;
    cout << p3 << endl << endl;
    //aici am apelat getterii sa fiu sigur ca merg
    cout << p2.getCapacitate() << " " << p2.getGreutate() << " " << p2.getNrIntrari() << " " << p2.getCuloare() << endl;
    p2 += 2;
    p2 -= 5;
    cout << p2 << endl;;
    if (p2 == p3)cout << "da" << endl;
    else cout << "nu" << endl;

    //astea sunt "instantierea" (adica faci obiecte) clasei copil pentru cerinta cu "is a"
    PowerBankStricat ps1;
    PowerBankStricat ps2(4, 20, "albastru", 3, true);

    //asta e apelarea la functia template careia i-am dat ca tip de date int
    cout << suma<int>(15, 40) << endl << endl;

    //aici demonstram early-binding (adica de la compilare se stie ca functia este a unei clase)
    p2.Afisare();
    ps2.Afisare();

    //aici m-a pus profu sa fac niste pointeri de obiect, carora le-am dat adresa unor obiecte existente
    PowerBank* pp = &p2;
    PowerBankStricat* pps = &ps2;

    //asta e un stl vector prin care sa parcurg pointerii de obiect de mai sus (m-a pus profu sa apelez polimorfismul prin stl)
    vector<PowerBank*> vectorPB;
    vectorPB.push_back(pp);
    vectorPB.push_back(pps);


    //aici demonstram late-binding pentru ca de-abea la runtime (adica dupa compilare) se decide a cui este functia afisare
    //asta m-a pus profu sa fac in plus pentru 10, dar m-a ghidat el prin tot codul asa ca mi-a dat 0.75 in loc de 2p pe subiect
    cout << endl << "aici" << endl;
    for (int i=0; i < vectorPB.size(); i++) {
        vectorPB[i]->Afisare();
    }
    
}

