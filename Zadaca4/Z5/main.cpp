//TP 2018/2019: Zadaća 4, Zadatak 5
#include <iostream>
#include <string>
#include <vector>
#include <map>

//ZADATAK KOPIRAN I PASTEAN JER SE NIJE SPREMIO ZBOG GRESKE NA C9

std::string ukloniRazmake(std::string rijec)
{

    for(int i=0; i<rijec.length(); i++) { //brisanje razmaka sa pocetka
        while(rijec.at(i)==' ') rijec.erase(rijec.begin()+i);
        break;
    }
    //prvi sada sigurno nije razmak
    char prethodni=rijec.at(0);
    for(int i=1; i<rijec.length(); i++) {
        if(rijec.at(i)==' ' && prethodni==' ') { //visak razmaka
            rijec.erase(rijec.begin()+i);
            i--;
        }
        prethodni=rijec.at(i);
        if(rijec.at(rijec.length()-1)==' ') rijec.erase(rijec.begin()+rijec.length()-1);
    }


    return rijec;
}

class Student
{
    int brojIndeksa;
    std::string godinaStudija;
    std::string student;
    std::string adresa;
    std::string telefon;
public:
    Student(int indeks,std::string godina,std::string imeIPrezime,std::string adr,std::string tel)
    {
        if(indeks<10000 || indeks>99999) throw std::domain_error("Neispravni parametri");
        //provjera ispravnosti godine studija
        if(godina!="1" && godina!="2" && godina!="3" && godina!="1/B" && godina!="2/B"
                && godina!="3/B" && godina!="1/M" && godina!="2/M" && godina!="1/D" &&
                godina!="2/D" && godina!="3/D") throw std::domain_error("Neispravni parametri");

        //ukloniti suvisne razmake iz imena i prezimena i adrese

        //broj telefona u formatu cifre/cifre-cifre

        int i=0;
        while(i!=tel.length()-1 && tel.at(i)!='/') {
            if(tel.at(i)<'0' || tel.at(i)>'9') throw std::domain_error("Neispravni parametri");
            i++;
        }
        if(i!=tel.length()-1 && tel.at(i)=='/') {
            i++;//poslije slash
            while(i!=tel.length()-1 && tel.at(i)!='-') {
                if(tel.at(i)<'0' || tel.at(i)>'9' || i==tel.length()-1) throw std::domain_error("Neispravni parametri");
                i++;
            }
            if(i!=tel.length()-1 && tel.at(i)=='-') {
                i++;//poslije crtice
                while(i!=tel.length()-1) {
                    if(tel.at(i)<'0' || tel.at(i)>'9') throw std::domain_error("Neispravni parametri");
                    i++;
                }
            } else throw std::domain_error("Neispravni parametri");
        } else throw std::domain_error("Neispravni parametri");
        //ukloniti suvisne razmake iz imena i prezimena i adrese
        brojIndeksa=indeks;
        godinaStudija=godina;
        student=ukloniRazmake(imeIPrezime);
        telefon=tel;
        adresa=ukloniRazmake(adr);
    }

    int DajIndeks()
    {
        return brojIndeksa;
    }
    std::string DajGodinuStudija()
    {
        if(godinaStudija=="1") return "1/B";
        else if(godinaStudija=="2") return "2/B";
        else if(godinaStudija=="3") return "3/B";
        return godinaStudija;
    }
    std::string DajImePrezime()
    {
        return student;
    }
    std::string DajAdresu()
    {
        return adresa;
    }
    std::string DajTelefon()
    {
        return telefon;
    }
    void Ispisi()
    {
        std::cout<<"Broj indeksa: "<<DajIndeks()<<std::endl;
        std::cout<<"Godina studija: "<<DajGodinuStudija()<<std::endl;
        std::cout<<"Ime i prezime: "<<DajImePrezime()<<std::endl;
        std::cout<<"Adresa: "<<DajAdresu()<<std::endl;
        std::cout<<"Telefon: "<<DajTelefon()<<std::endl;
    }
};

class Laptop
{
    int ev_broj;
    std::string naziv;
    std::string karakteristike;
    Student *kod_koga_je;
public:
    Laptop(int broj,std::string n,std::string k)
    {
        if(broj<0) throw std::domain_error("Neispravni parametri");
        ev_broj=broj;
        naziv=n;
        karakteristike=k;
        kod_koga_je=nullptr;
    }
    int DajEvidencijskiBroj()
    {
        return ev_broj;
    }
    std::string DajNaziv()
    {
        return naziv;
    }
    std::string DajKarakteristike()
    {
        return karakteristike;
    }
    void Zaduzi(Student &s)
    {
        if(kod_koga_je!=nullptr) throw std::domain_error("Laptop vec zaduzen");
        kod_koga_je=&s;
    }
    void Razduzi()
    {
        kod_koga_je=nullptr;
    }
    bool DaLiJeZaduzen()
    {
        if(kod_koga_je==nullptr) return false;
        return true;
    }
    Student& DajKodKogaJe()
    {
        if(kod_koga_je==nullptr) throw std::domain_error("Laptop nije zaduzen");
        return *kod_koga_je;
    }
    Student* DajPokKodKogaJe()
    {
        return kod_koga_je;
    }
    void Ispisi()
    {
        std::cout<<"Evidencijski broj: "<<DajEvidencijskiBroj()<<std::endl;
        std::cout<<"Naziv: "<<DajNaziv()<<std::endl;
        std::cout<<"Karakteristike: "<<DajKarakteristike()<<std::endl;
    }

};

class Administracija
{
    std::map<int,Student*> studenti;//broj indeksa je id
    std::map<int,Laptop*> laptopi;//ev_broj je id
public:
    Administracija() {}
//moraju se moci bezbjedno kopirati i dodjeljivati medjusobno
//koristiti strategiju dubokog kopiranja uz optimizirane verzije kad su u pitanju privremeni objekti
    ~Administracija()
    {
    for(auto it=studenti.begin();it!=studenti.end();it++){
        delete it->second;
    }
    for(auto it=laptopi.begin();it!=laptopi.end();it++){
        delete it->second;
    }
    }

    void RegistrirajNovogStudenta(int indeks,std::string godina,std::string imeIPrezime,std::string adr,std::string tel)
    {
        auto trazeni=studenti.find(indeks);
        if(trazeni!=studenti.end()) throw std::domain_error("Student s tim indeksom vec postoji");
        //dinamicki alocirati studenta i dodati ga u mapu
        Student *s=new Student(indeks,godina,imeIPrezime,adr,tel);
        studenti.insert({indeks,s});
    }
    void RegistrirajNoviLaptop(int broj,std::string n,std::string k)
    {
        auto trazeni=laptopi.find(broj);
        if(trazeni!=laptopi.end()) throw std::domain_error("Laptop s tim evidencijskim brojem vec postoji");
        Laptop *l=new Laptop(broj,n,k);
        laptopi.insert({broj,l});

    }
    Student& NadjiStudenta(int brojIndeksa)
    {
        auto trazeni=studenti.find(brojIndeksa);
        if(trazeni==studenti.end()) throw std::domain_error("Student nije nadjen");
        Student *s=trazeni->second;
        return *s;

    }
    Student NadjiStudenta(int brojIndeksa)const
    {
        auto trazeni=studenti.find(brojIndeksa);
        if(trazeni==studenti.end()) throw std::domain_error("Student nije nadjen");
        Student *s=trazeni->second;
        return *s;
    }
    Laptop& NadjiLaptop(int ev_broj)
    {
        auto trazeni=laptopi.find(ev_broj);
        if(trazeni==laptopi.end()) throw std::domain_error("Laptop nije nadjen");
        Laptop *l=trazeni->second;
        return *l;
    }
    Laptop NadjiLaptop(int ev_broj)const
    {
        auto trazeni=laptopi.find(ev_broj);
        if(trazeni==laptopi.end()) throw std::domain_error("Laptop nije nadjen");
        Laptop *l=trazeni->second;
        return *l;
    }
    void IzlistajStudente()
    {
        for(auto it=studenti.begin(); it!=studenti.end(); it++) {
            it->second->Ispisi();
            std::cout<<std::endl;
        }
    }

    void IzlistajLaptope()
    {
        for(auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            it->second->Ispisi();
            if(it->second->DajPokKodKogaJe()!=nullptr) std::cout<<"Zaduzio(la): "<<it->second->DajPokKodKogaJe()->DajImePrezime()<<
            " ("<<it->second->DajPokKodKogaJe()->DajIndeks()<<")"<<std::endl;
            std::cout<<std::endl;
        }
    }
    void ZaduziLaptop(int indeks,int ev_broj)
    {
        auto s=studenti.find(indeks);
        if(s==studenti.end()) throw std::domain_error("Student nije nadjen");
        auto l=laptopi.find(ev_broj);
        if(l==laptopi.end()) throw std::domain_error("Laptop nije nadjen");

        if(l->second->DaLiJeZaduzen()==true) throw std::domain_error("Laptop vec zaduzen");

        for(auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if(it->second->DajPokKodKogaJe()!=nullptr && it->second->DajPokKodKogaJe()->DajIndeks()==indeks) {
                throw std::domain_error("Student je vec zaduzio laptop");
            }
        }
        Student *st=s->second;
        for(auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if(it->second->DajEvidencijskiBroj()==ev_broj) {
                it->second->Zaduzi(*st);
                break;
            }
        }
    }
    int NadjiSlobodniLaptop()
    {
        bool nadjen=false;
        int br=0;
        for(auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if(it->second->DaLiJeZaduzen()==false) {
                br=it->second->DajEvidencijskiBroj();
                nadjen=true;
                break;
            }
        }
        if(nadjen==false) throw std::domain_error("Nema slobodnih laptopa");
        return br;
    }

    void RazduziLaptop(int ev_broj)
    {
        //registrira u kolekciji da laptop vise nije zaduzen
        bool razduzen=false;
        for(auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if(it->second->DajEvidencijskiBroj()==ev_broj && it->second->DaLiJeZaduzen()==true) { //nadjen i bio zaduzen
                it->second->Razduzi();
                razduzen=true;
                break;
            } else if(it->second->DajEvidencijskiBroj()==ev_broj && it->second->DaLiJeZaduzen()==false) {
                throw std::domain_error("Laptop nije zaduzen");
            }
        }
        if(razduzen==false) throw std::domain_error("Laptop nije nadjen");
    }

    void PrikaziZaduzenja()
    {

        int zaduzenja=0;
        //"Student Huso Husic Car (35124) zaduzio/la laptop broj 724"
        //ili tekst Nema zaduzenja ako nema nijedno zaduzenje
        for(auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if(it->second->DajPokKodKogaJe()!=nullptr) {
                std::cout<<"Student "<<it->second->DajPokKodKogaJe()->DajImePrezime()<<" ("<<it->second->DajPokKodKogaJe()->DajIndeks()<<
                         ") zaduzio/la laptop broj "<<it->second->DajEvidencijskiBroj()<<std::endl;
                zaduzenja++;
            }
        }
        if(zaduzenja==0)  std::cout<<"Nema zaduzenja"<<std::endl;

    }

};

int main ()
{
    Administracija a=Administracija();
    char unos='A';
    do {

        std::cout<<"Odaberite jednu od  sljedecih opcija: "<<std::endl;
        std::cout<<"1 - RegistrirajNovogStudenta"<<std::endl;
        std::cout<<"2 - RegistrirajNoviLaptop"<<std::endl;
        std::cout<<"3 - IzlistajStudente"<<std::endl;
        std::cout<<"4 - IzlistajLaptope"<<std::endl;
        std::cout<<"5 - NadjiSlobodniLaptop"<<std::endl;
        std::cout<<"6 - ZaduziLaptop"<<std::endl;
        std::cout<<"7 - RazduziLaptop"<<std::endl;
        std::cout<<"8 - PrikaziZaduzenja"<<std::endl;
        std::cout<<"K - Kraj programa"<<std::endl;
        std::cin>>unos;
        if(unos=='K') break;

        if(unos=='1') {
            std::cout<<"Unesite broj indeksa: ";
            int indeks=0;
            std::cin>>indeks;
            std::cin.ignore(1000,'\n');
            std::cout<<"Unesite godinu studija (formata A/X, gdje je A godina studija, a X prima vrijednosti B,M,D, zavisno od studija): "<<std::endl;
            std::string godina,ime,adresa,telefon;
            std::getline(std::cin,godina);
            std::cout<<"Unesite ime i prezime studenta: "<<std::endl;
            std::getline(std::cin,ime);
            std::cout<<"Unesite adresu studenta: "<<std::endl;
            std::getline(std::cin,adresa);
            std::cout<<"Unesite broj telefona (formata x/x-x): "<<std::endl;
            std::getline(std::cin,telefon);
            try {
                a.RegistrirajNovogStudenta(indeks,godina,ime,adresa,telefon);
                std::cout<<"Korisnik uspjesno registrovan!"<<std::endl;
            } catch(std::domain_error izuzetak) {
                std::cout<<"Izuzetak: "<<izuzetak.what()<<"!"<<std::endl;
            }
        } else if(unos=='2') {
            std::cout<<"Unesite evidencijski broj laptopa "<<std::endl;
            int broj=0;
            std::cin>>broj;
            std::cin.ignore(1000,'\n');
            std::string n,k;
            std::cout<<"Unesite naziv laptopa "<<std::endl;
            std::getline(std::cin,n);
            std::cout<<"Unesite karakteristike laptopa: "<<std::endl;
            std::getline(std::cin,k);
            try {
                a.RegistrirajNoviLaptop(broj,n,k);
                std::cout<<"Laptop uspjesno registrovan!"<<std::endl;
            } catch(std::domain_error izuzetak) {
                std::cout<<"Izuzetak: "<<izuzetak.what()<<"!"<<std::endl;
            }

        } else if(unos=='3') {
            a.IzlistajStudente();

        } else if(unos=='4') {
            a.IzlistajLaptope();

        } else if(unos=='5') {
            std::cout<<"Evidencijski broj slobodnog laptopa: "<<a.NadjiSlobodniLaptop()<<std::endl;

        } else if(unos=='6') {
            std::cout<<"Unesite broj indeksa: "<<std::endl;
            int indeks=0;
            std::cin>>indeks;
            std::cout<<"Unesite evidencijski broj laptopa: "<<std::endl;
            int broj=0;
            std::cin>>broj;
            a.ZaduziLaptop(indeks,broj);

        } else if(unos=='7') {
            std::cout<<"Unesite evidencijski broj laptopa: "<<std::endl;
            int broj=0;
            std::cin>>broj;
            a.RazduziLaptop(broj);

        } else if(unos=='8') {
            a.PrikaziZaduzenja();
        }
        std::cout<<std::endl<<std::endl;
    } while(unos!='K');


    return 0;
}
