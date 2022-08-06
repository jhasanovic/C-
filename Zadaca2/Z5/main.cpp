//TP 2018/2019: Zadaća 2, Zadatak 5
#include <iostream>
#include <vector>
#include <string>


int PotencijalniKrivci(char** &ref, std::vector<std::string> imena)
{
    //Funkcija treba dinamički alocirati niz pokazivača na dinamički alocirane nizove znakova u koje će
    //se smjestiti imena proslijeđena funkciji, te u prvi parametar funkcije smjestiti pokazivač na početak ovog niza.
    //Za svaki od nizova znakova treba alocirati tačno onoliko prostora koliko treba, uključujući i prostor za NUL graničnik.

    char **niz=nullptr;
    niz=new char*[imena.size()] {};
    try {
        for(int i=0; i<imena.size(); i++) niz[i]=new char[imena.at(i).size()+1];
    } catch(std::bad_alloc izuzetak) {
        for(int i=0; i<imena.size(); i++) delete[] niz[i];
        delete[] niz;
        niz=nullptr;
        throw "Nedovoljno memorije!";
    }

    //imena smjestamo u alocirani niz
    for(int i=0; i<imena.size(); i++) {
        for(int j=0; j<imena.at(i).size()+1; j++) {
            if(j==imena.at(i).size()) niz[i][j]='\0';
            else niz[i][j]=imena.at(i).at(j);

        }
    }

    ref=niz;
    for(int i=0; i<imena.size(); i++) delete[] niz[i];
    delete[] niz;
    niz=nullptr;
    return imena.size();
}

int OdbaciOptuzbu(char **&ref,int vel_niza_pok, std::string ime)
{

    bool nadjen=false;
    for(int i=0; i<vel_niza_pok; i++) {
        std::string osoba="";
        int j=0;
        while(ref[i][j]!='\0') {
            osoba.push_back(ref[i][j]);
            j++;
        }

        if(osoba==ime) {
            nadjen=true;
            delete[] ref[i];
            ref[i]=nullptr;
        }
    }

    //provjera da li ima vise od 10 nullptr-a
    int nul_pok=0;
    for(int i=0; i<vel_niza_pok; i++) {
        if(ref[i]==nullptr) nul_pok++;
    }

    bool alokacija=false;
    char **novi=nullptr;

    if(nul_pok>10) {
        alokacija=true;
        novi=new char*[vel_niza_pok-nul_pok] {};
        try {
            for(int i=0,j=0; i<vel_niza_pok-nul_pok && j<vel_niza_pok; ) {
                if(ref[j]!=nullptr) {
                    novi[i]=new char[5];
                    j++;
                    i++;
                } else j++;
            }
        } catch(std::bad_alloc izuzetak) {
            for(int i=0; i<vel_niza_pok-nul_pok; i++) delete[] novi[i];
            delete[] novi;
            novi=nullptr;
        }
    }


    std::string izuzetak="Osoba sa imenom "+ime+" nije bila optuzena";
    if(nadjen==false) throw std::domain_error(izuzetak);

    if(alokacija==false) return vel_niza_pok;
    ref=novi;
    for(int i=0; i<vel_niza_pok-nul_pok; i++) delete[] novi[i];
    delete[] novi;
    novi=nullptr;

    return vel_niza_pok-nul_pok;
}

int DodajOptuzbu(char **&ref,int vel_niza_pok, std::string ime)
{
    //alocirati novi niz velicine ime.size()+1
    //prvom null pokazivacu dodijeliti pok na novo ime
    //ako nema null pokazivaca dodati ime na kraj (u prethodno alocirani novi niz velicine vel_niz_pok+1)
    //ako neka alokacija ne uspije baciti bad_alloc
    return vel_niza_pok+1;
}

void IzlistajOptuzbu(char **ref,int vel_niza_pok)
{
    for(int i=0; i<vel_niza_pok; i++) {
        if(ref[i]!=nullptr) {
            std::string optuzeni=ref[i];
            std::cout<<optuzeni<<std::endl;
        }
    }
}

int main ()
{
    int broj=0;
    std::cout<<"Unesite broj ljudi koji su optuzeni za prepisivanje/prodavanje zadaca: ";
    std::cin>>broj;
    std::cin.ignore(1000,'\n');
    char** niz;
    std::vector<std::string> spisak;
    for(int i=0; i<broj; i++) {
        std::cout<<"Unesite ime optuzenog: ";
        std::string ime;
        std::getline(std::cin,ime);
        spisak.push_back(ime);
    }

    try {
        int vel=PotencijalniKrivci(niz,spisak);
        std::cout<<"Duzina spiska: "<<vel<<" "<<std::endl;
        std::cout<<"Spisak trenutno optuzenih: "<<std::endl;
        IzlistajOptuzbu(niz,vel);
        std::cout<<"Unesite ime osobe oslobodjene optuzbi: ";
        std::string osoba;
        std::getline(std::cin,osoba);
        vel=OdbaciOptuzbu(niz,spisak.size(),osoba);

        std::cout<<"Spisak trenutno optuzenih: "<<std::endl;
        IzlistajOptuzbu(niz,vel);
        std::cout<<"Unesite ime novog optuzenog: ";
        std::getline(std::cin,osoba);

        std::cout<<"Spisak trenutno optuzenih: ";
        IzlistajOptuzbu(niz,vel);
        vel=DodajOptuzbu(niz,vel,osoba);


    } catch(std::exception &izuzetak) {
        std::cout<<izuzetak.what()<<"!";
    }
    return 0;
}
