//TP 2018/2019: Zadaća 4, Zadatak 3
#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <initializer_list>
#include <utility>

class Let
{
//vodi evidenciju o jednom letu
    char naziv_odredista[30],oznaka_let[10];
    static const int max_odrediste=30,max_let=10;
    int izlazna_kapija,sat_polijetanja,minute_polijetanja,trajanje_leta,kasnjenje;

public:
    Let(const char odrediste[], const char oznaka_leta[],int kapija, int sat_polaska, int minute_polaska, int trajanje_leta);
    void PostaviKasnjenje(int kasnjenje);
    bool DaLiKasni() const;
    int DajTrajanjeLeta() const;
    std::pair<int,int> DajOcekivanoVrijemePolijetanja() const;
    std::pair<int,int> DajOcekivanoVrijemeSlijetanja() const;
    void Ispisi() const;
};
//konstruktor inicijalizira atribute na zadane vr, kasnjenje na 0
//konst baca domain_error uz odg pratece tekstove(po volji) ako parametar ima besmislene vrijednosti(naziv odredista ili oznaka leta predugacki)
Let::Let(const char odrediste[], const char oznaka_leta[],int kapija, int sat_polaska, int minute_polaska, int trajanje_leta)
{
    if(std::strlen(odrediste)>max_odrediste) throw std::domain_error("Predugacak naziv odredista!");
    if(std::strlen(oznaka_leta)>max_let) throw std::domain_error("Predugacka oznaka leta!");
    if(sat_polaska<0 || sat_polaska>23 || minute_polaska<0 || minute_polaska>59) throw std::domain_error("Pogresno vrijeme polaska!");
    std::strcpy(naziv_odredista,odrediste);
    std::strcpy(oznaka_let,oznaka_leta);
    sat_polijetanja=sat_polaska;
    minute_polijetanja=minute_polaska;
    Let::trajanje_leta=trajanje_leta;
    izlazna_kapija=kapija;
    kasnjenje=0;
}

void Let::PostaviKasnjenje(int kasnjenje)
{
    Let::kasnjenje=kasnjenje;
}
bool Let::DaLiKasni() const
{
    if(Let::kasnjenje>0) return true;
    else return false;
}
int Let::DajTrajanjeLeta() const
{
    return Let::trajanje_leta;
}
std::pair<int,int> Let::DajOcekivanoVrijemePolijetanja()const
{
    //uracunati kasnjenje
    std::pair<int,int> vrijeme;
    int kasni=Let::kasnjenje,minute=Let::minute_polijetanja,sati=Let::sat_polijetanja;
    while(kasni>=60) {
        kasni-=60;
        sati++;
    }
    vrijeme.first=sati;
    vrijeme.second=minute+kasni;
    while(vrijeme.second>=60) {
        vrijeme.second-=60;
        vrijeme.first++;
    }
    while(vrijeme.first>=24) {
        vrijeme.first-=24;
    }
    return vrijeme;
}
std::pair<int,int> Let::DajOcekivanoVrijemeSlijetanja()const
{
    std::pair<int,int> vrijeme;
    int kasni=Let::kasnjenje,minute=Let::minute_polijetanja,sati=Let::sat_polijetanja;
    while(kasni>=60) {
        kasni-=60;
        sati++;
    }
    vrijeme.first=sati;
    vrijeme.second=minute+kasni+Let::trajanje_leta;
    while(vrijeme.second>=60) {
        vrijeme.second-=60;
        vrijeme.first++;
    }
    while(vrijeme.first>=24) {
        vrijeme.first-=24;
    }
    return vrijeme;
}

void Let::Ispisi() const
{

    if(DaLiKasni()==false) {
        std::pair<int,int> odlazak=DajOcekivanoVrijemePolijetanja();
        std::pair<int,int> dolazak=DajOcekivanoVrijemeSlijetanja();
        std::cout<<std::left<<std::setw(10)<<oznaka_let;
        if(std::strlen(naziv_odredista)>20) {
            for(int i=0; i<20; i++) {
                std::cout<<naziv_odredista[i];
            }
        } else
            std::cout<<std::setw(20)<<naziv_odredista;
//ako je naziv odredista duzi od 20 znakova ispisati samo prvih 20
        std::cout<<"   "<<std::right<<std::setfill('0')<<std::setw(2)<<odlazak.first<<":"<<std::setfill('0')<<std::setw(2)<<odlazak.second<<"   ";
        std::cout<<std::setfill(' ');

        std::cout<<std::right<<std::setfill('0')<<std::setw(2)<<dolazak.first<<":"<<std::right<<std::setfill('0')<<std::setw(2)<<dolazak.second;
        std::cout<<std::setfill(' ');
        std::cout<<std::setw(6)<<izlazna_kapija<<std::endl;
    } else if(DaLiKasni()==true) {
        std::pair<int,int> odlazak=DajOcekivanoVrijemePolijetanja();

        std::cout<<std::left<<std::setw(10)<<oznaka_let;
        if(std::strlen(naziv_odredista)>20) {
            for(int i=0; i<20; i++) {
                std::cout<<naziv_odredista[i];
            }
        } else
            std::cout<<std::setw(20)<<naziv_odredista;

        std::cout<<"   "<<std::right<<std::setfill('0')<<std::setw(2)<<odlazak.first<<":"<<std::right<<std::setfill('0')<<std::setw(2)<<odlazak.second;
        std::cout<<std::setfill(' ');
        
        std::cout<<" (Planirano ";
        std::cout<<std::setw(2)<<std::setfill('0')<<sat_polijetanja<<":"<<std::setw(2)<<std::setfill('0')<<minute_polijetanja;
        std::cout<<std::setfill(' ');
        std::cout<<", Kasni "<<kasnjenje<<" min)"<<std::endl;

    }
}
class Letovi
{
    //svi letovi u toku dana
    int kapacitet;
    int broj_evidentiranih;
    Let **spisak;
public:
    explicit Letovi(int max_broj_letova);//konstruktor
    Letovi(std::initializer_list<Let> lista_letova);//sekvencijski konstruktor
    ~Letovi();
    Letovi(const Letovi &letovi);
    Letovi(Letovi &&letovi);
    Letovi &operator=(const Letovi &letovi);//kopirajuci operator dodjele
    Letovi &operator=(Letovi &&letovi);//pomjerajuci operator dodjele
    void RegistrirajLet(const char odrediste[], const char oznaka_leta[],int kapija, int sat_polaska, int minute_polaska, int trajanje_leta);
    void RegistrirajLet(Let *let);
    int DajBrojLetova() const
    {
        return broj_evidentiranih;
    }
    int DajBrojLetovaKojiKasne() const;
    int DajProsjecnoTrajanjeLetova() const;
    Let &DajPrviLet() const;
    Let &DajPosljednjiLet() const;
    void IsprazniKolekciju();
    void Ispisi(int sati, int minute) const;
};
Letovi::Letovi(int max_broj_letova):kapacitet(max_broj_letova),broj_evidentiranih(0),spisak(new Let*[max_broj_letova] {}) {}

Letovi::Letovi(std::initializer_list<Let> lista_letova)
{
    kapacitet=lista_letova.size();
    broj_evidentiranih=0;
    spisak=new Let*[kapacitet] {};
    try {
        for(auto i=lista_letova.begin(); i!=lista_letova.end(); i++)
            spisak[broj_evidentiranih++]=new Let(*i);
    } catch(...) {
        IsprazniKolekciju();
        throw;
    }
}
Letovi::~Letovi()
{
    for(int i=0; i<broj_evidentiranih; i++) delete spisak[i];
    delete[] spisak;
}
Letovi::Letovi(const Letovi &letovi): spisak(new Let *[kapacitet] {}), kapacitet(letovi.kapacitet), broj_evidentiranih(letovi.broj_evidentiranih)
{
    try {
        for(int i=0; i<letovi.broj_evidentiranih; i++)
            spisak[i]=new Let(*letovi.spisak[i]);
    } catch(...) {
        for(int i=0; i<letovi.broj_evidentiranih; i++) delete spisak[i];
        delete[] spisak;
        throw;
        //ili pozvati IsprazniKolekciju ovdje?
    }
}

Letovi::Letovi(Letovi &&letovi):spisak(letovi.spisak),kapacitet(letovi.kapacitet),broj_evidentiranih(letovi.broj_evidentiranih)
{
    letovi.spisak=nullptr;//mozda promijeniti ime niza letovi
    letovi.broj_evidentiranih=0;
}
Letovi &Letovi::operator=(const Letovi &letovi)
{
    if(letovi.broj_evidentiranih>broj_evidentiranih) {
        try {
            for(int i=broj_evidentiranih; i<letovi.broj_evidentiranih; i++)
                spisak[i]=new Let(*letovi.spisak[i]);
        } catch(...) {
            for(int i=broj_evidentiranih; i<letovi.broj_evidentiranih; i++) {
                delete spisak[i];
                spisak[i]=nullptr;
            }
            throw;
        }
    } else {
        for(int i=letovi.broj_evidentiranih; i<broj_evidentiranih; i++) {
            delete spisak[i];
            spisak[i]=nullptr;
        }
    }
    broj_evidentiranih=letovi.broj_evidentiranih;
    for(int i=0; i<broj_evidentiranih; i++) *spisak[i]=*letovi.spisak[i];
    return *this;
}
Letovi &Letovi::operator=(Letovi &&letovi)
{
    std::swap(broj_evidentiranih,letovi.broj_evidentiranih);
    std::swap(spisak,letovi.spisak);
    return *this;
}
void Letovi::RegistrirajLet(const char odrediste[], const char oznaka_leta[],int kapija, int sat_polaska, int minute_polaska, int trajanje_leta)
{
    if(broj_evidentiranih>=kapacitet) throw std::range_error("Dostignut maksimalni broj letova");
    spisak[broj_evidentiranih++]=new Let(odrediste,oznaka_leta,kapija,sat_polaska,minute_polaska,trajanje_leta);
}

void Letovi::RegistrirajLet(Let *let)
{
    if(broj_evidentiranih>=kapacitet) throw std::range_error("Dostignut maksimalni broj letova");
    spisak[broj_evidentiranih++]=let;
}

int Letovi::DajBrojLetovaKojiKasne() const
{
    int kasne=0;
    kasne=std::count_if(spisak,spisak+broj_evidentiranih,[](Let *neki) {
        return neki->DaLiKasni();
    });
    return kasne;
}
int Letovi::DajProsjecnoTrajanjeLetova()const
{
    int ukupno=0;
    for(int i=0; i<broj_evidentiranih; i++) {
        ukupno+=spisak[i]->DajTrajanjeLeta();
    }
    double prosjek=0;
    prosjek=ukupno/broj_evidentiranih;
    return prosjek;
}
Let &Letovi::DajPrviLet() const
{
    if(broj_evidentiranih==0) throw std::domain_error("Nema registriranih letova");
    //preko funkcije min_element naci min ukupan broj minuta
    return **std::min_element(spisak,spisak+broj_evidentiranih,[](Let *let1,Let *let2)->bool{
        std::pair<int,int> vrijeme1=let1->DajOcekivanoVrijemePolijetanja();
        std::pair<int,int> vrijeme2=let2->DajOcekivanoVrijemePolijetanja();
        int ukupno1=vrijeme1.first*60+vrijeme1.second;
        int ukupno2=vrijeme2.first*60+vrijeme2.second;
        return ukupno1<ukupno2;
    });
}
Let &Letovi::DajPosljednjiLet() const
{
    if(broj_evidentiranih==0) throw std::domain_error("Nema registriranih letova");
    return **std::max_element(spisak,spisak+broj_evidentiranih,[](Let *let1, Let *let2)->bool{
        std::pair<int,int> vrijeme1=let1->DajOcekivanoVrijemePolijetanja();
        std::pair<int,int> vrijeme2=let2->DajOcekivanoVrijemePolijetanja();
        int ukupno1=vrijeme1.first*60+vrijeme1.second;
        int ukupno2=vrijeme2.first*60+vrijeme2.second;
        return ukupno1>ukupno2;
    });
}
void Letovi::IsprazniKolekciju()
{
    for(int i=0; i<broj_evidentiranih; i++) {
        delete spisak[i];
        spisak[i]=nullptr;
    }
    broj_evidentiranih=0;
}
void Letovi::Ispisi(int sati,int minute)const
{
    //ispisati sve letove od zadatog do kraja dana prema ocekivanom vremenu polijetanja, sortirati sa sort i lambda funkcijom kriterija
    std::sort(spisak,spisak+broj_evidentiranih,[](Let *let1,Let *let2)->bool{
        int ukupno1=0,ukupno2=0;
        std::pair<int,int> vrijeme1=let1->DajOcekivanoVrijemePolijetanja();
        std::pair<int,int> vrijeme2=let2->DajOcekivanoVrijemePolijetanja();
        ukupno1=vrijeme1.first*60+vrijeme1.second;
        ukupno2=vrijeme2.first*60+vrijeme2.second;
        return ukupno1<ukupno2;
    });

    for(int i=0; i<broj_evidentiranih; i++) {
        int ukupno=sati*60+minute;
        std::pair<int,int> vrijeme=spisak[i]->DajOcekivanoVrijemePolijetanja();
        int trenutni=vrijeme.first*60+vrijeme.second;
        if(trenutni>=ukupno)
            spisak[i]->Ispisi();
    }
}

int main ()
{
    try {
        Letovi l(1000);
        for (int i(1); i<=10; i++)
            l.RegistrirajLet("A","B",1,i,1,61);

        for (int i(1); i<=10; i++) {
            Let* let = new Let("C","D",1,i,1,1);
            let->PostaviKasnjenje(1);
            l.RegistrirajLet(let);
        }
        const Letovi& l2(l);
        std::cout << l2.DajBrojLetova() << " " << l2.DajBrojLetovaKojiKasne() << " ";
        std::cout << l2.DajProsjecnoTrajanjeLetova() << std::endl;
        Let let (l2.DajPrviLet());
        Let let2(l2.DajPosljednjiLet());
        l2.Ispisi(0,0);
    } catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what();
    }
    return 0;
}
