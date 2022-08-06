//TP 2018/2019: Zadaća 5, Zadatak 4
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

class ApstraktnoVozilo
{
    int tezinaVozila;
public:
    ApstraktnoVozilo(int t):tezinaVozila(t) {}
    virtual ~ApstraktnoVozilo() {}
    int DajTezinu()const
    {
        return tezinaVozila;
    }
    virtual int DajUkupnuTezinu()const {}
    virtual ApstraktnoVozilo *DajKopiju()const {}
    virtual void IspisiPodatke()const {}

};

class Automobil:public ApstraktnoVozilo
{
    std::vector<int> tezinePutnika;
public:
    Automobil(int t,std::vector<int> putnici):ApstraktnoVozilo(t),tezinePutnika(putnici) {}
    int DajUkupnuTezinu()const override;
    Automobil *DajKopiju()const override
    {
        return new Automobil(*this);
    }
    void IspisiPodatke()const override;
};

int Automobil::DajUkupnuTezinu()const
{
    int ukupna=DajTezinu();
    for(int t:tezinePutnika) ukupna+=t;
    return ukupna;
}

void Automobil::IspisiPodatke()const
{
    std::cout<<"Vrsta vozila: Automobil"<<std::endl;
    std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
    std::cout<<"Tezine putnika: ";
    for(int i=0; i<tezinePutnika.size(); i++) {
        if(i!=tezinePutnika.size()-1) std::cout<<tezinePutnika.at(i)<<" kg, ";
        else std::cout<<tezinePutnika.at(i)<<" kg";
    }
    std::cout<<std::endl;
    std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
}


class Kamion:public ApstraktnoVozilo
{
    int tezinaTereta;
public:
    Kamion(int t,int teret):ApstraktnoVozilo(t),tezinaTereta(teret) {};
    int DajUkupnuTezinu()const override;
    Kamion *DajKopiju()const override
    {
        return new Kamion(*this);
    }
    void IspisiPodatke()const override;
};

int Kamion::DajUkupnuTezinu()const
{
    return DajTezinu()+tezinaTereta;
}

void Kamion::IspisiPodatke()const
{
    std::cout<<"Vrsta vozila: Kamion"<<std::endl;
    std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
    std::cout<<"Tezine tereta: "<<tezinaTereta<<" kg"<<std::endl;
    std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
}

class Autobus:public ApstraktnoVozilo
{
    int brojPutnika;
    int prosjecnaTezina;
public:
    Autobus(int t,int brp,int pt):ApstraktnoVozilo(t),brojPutnika(brp),prosjecnaTezina(pt) {};
    int DajUkupnuTezinu()const override;
    Autobus *DajKopiju()const override
    {
        return new Autobus(*this);
    }
    void IspisiPodatke()const override;
};

int Autobus::DajUkupnuTezinu()const
{
    return DajTezinu()+brojPutnika*prosjecnaTezina;
}

void Autobus::IspisiPodatke()const
{
    std::cout<<"Vrsta vozila: Autobus"<<std::endl;
    std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
    std::cout<<"Broj putnika: "<<brojPutnika<<std::endl;
    std::cout<<"Prosjecna tezina putnika: "<<prosjecnaTezina<<std::endl;
    std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
}


class Vozilo
{
    ApstraktnoVozilo *v=nullptr;
public:
    ~Vozilo()
    {
        delete v;
    }
    int DajTezinu()const
    {
        return v->DajTezinu();
    }
    int DajUkupnuTezinu()const
    {
        return v->DajUkupnuTezinu();
    }
    Vozilo* DajKopiju()const
    {
        return new Vozilo(*this);
    }
    int IspisiPodatke()const
    {
        v->IspisiPodatke();
    }
    //bezbjedno dodjeljivanje i kopiranje
    Vozilo(const ApstraktnoVozilo &av)
    {
        v=av.DajKopiju();
    }
    Vozilo &operator=(const ApstraktnoVozilo &av);
    Vozilo (const Vozilo &vozilo);
    Vozilo(Vozilo &&vozilo);
    Vozilo &operator=(Vozilo &&vozilo);
};

Vozilo& Vozilo::operator=(const ApstraktnoVozilo &av)
{
    delete v;
    v=av.DajKopiju();
    return *this;
}

Vozilo::Vozilo(const Vozilo &vozilo)
{
    if(!vozilo.v) v=nullptr;
    else v=vozilo.v->DajKopiju();
}

Vozilo::Vozilo(Vozilo &&vozilo)
{
    v=vozilo.v;
    vozilo.v=nullptr;
}

Vozilo& Vozilo::operator=(Vozilo &&vozilo)
{
    if(&vozilo!=this) {
        delete v;
        v=vozilo.v;
        vozilo.v=nullptr;
    }
    return *this;
}

int main ()
{
    //VOZILA.TXT
    //citati iz datoteke u vektor ciji su elementi vozila tipa Vozilo
    //sortirati po ukupnoj tezini
    //ispisati ukupne tezine zasebno u svakom redu
    std::vector<Vozilo> vozila;
    bool neispravni_podaci=false;

    std::ifstream ulazni_tok("VOZILA.TXT");
    if(!ulazni_tok) std::cout << "Otvaranje datoteke nije uspjelo!\n";
    else {
        char znak;//oznaka tipa vozila
        for(;;) {
            ulazni_tok>>znak;
            if(znak!='A' && znak!='K' && znak!='B') {
                neispravni_podaci=true;
                break;
            } else if(znak=='A') {
                //tezina automobila, broj putnika i tezina svakog od putnika
                int t=0,n=0,tezina=0;
                ulazni_tok>>t>>n;
                std::vector<int> putnici;
                for(int i=0; i<n; i++) {
                    ulazni_tok>>tezina;
                    putnici.push_back(tezina);
                }
                if(!ulazni_tok) {
                    neispravni_podaci=true;
                    break;
                }
                Vozilo v=Automobil(t,putnici);
                vozila.push_back(v);
            } else if(znak=='K') {
                int t=0,teret=0;
                ulazni_tok>>t>>teret;
                if(!ulazni_tok) {
                    neispravni_podaci=true;
                    break;
                }
                Vozilo v=Kamion(t,teret);
                vozila.push_back(v);
            } else if(znak=='B') {
                int t=0,br=0,pt=0;
                ulazni_tok>>t>>br>>pt;
                if(!ulazni_tok) {
                    neispravni_podaci=true;
                    break;
                }
                Vozilo v=Autobus(t,br,pt);
                vozila.push_back(v);
            }
        }

    }

    if(ulazni_tok.bad()) std::cout << "Datoteka je vjerovatno oštećena!\n";
    else if(neispravni_podaci==true && !ulazni_tok.eof()) std::cout << "Datoteka sadrži neočekivane podatke!\n";

//sortirati vektor
    std::sort(vozila.begin(),vozila.end(),[](Vozilo &v1,Vozilo &v2){return v1.DajUkupnuTezinu()<v2.DajUkupnuTezinu();});
    for(int i=0;i<vozila.size();i++){
        vozila.at(i).IspisiPodatke();
        std::cout<<std::endl;
    }

    return 0;
}
