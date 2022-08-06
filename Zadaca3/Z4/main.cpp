//TP 2018/2019: Zadaća 3, Zadatak 4
#include <iostream>
#include <vector>
#include <list>



std::vector<int> Razbrajanje(int n,int korak)
{
    //napunimo listu brojevima od 1 do n
    std::list<int> lista;
    for(int i=1; i<=n; i++)
        lista.push_back(i);

    std::vector<int> vektor;
    auto it=lista.begin();
    int br_koraka=korak;

    vektor.push_back(*it);//ubacimo izbacenu vrijednost u vektor
    it=lista.erase(it);

    while(lista.size()>0) { //izbacujemo sve dok ne ostaje samo jedan broj u listi
        br_koraka=korak-1;
        while(br_koraka>0) {
            it++;
            br_koraka--;
            if(it==lista.end()) it=lista.begin(); //ako smo dosli do kraja liste vratimo na pocetak
        }
        vektor.push_back(*it);//ubacimo izbacenu vrijednost u vektor
        it=lista.erase(it);
        if(it==lista.end()) it=lista.begin();
    }

    return vektor;
}


int OdabirKoraka(int n,int odabrani_blok)
{
    if(n<=0 || odabrani_blok<=0 || odabrani_blok>n) throw std::domain_error("Broj blokova i redni broj bloka su pozitivni cijeli brojevi i redni broj bloka ne moze biti veci od broja blokova");
    //poziva razbrajanje za korake od 1 do n
    std::vector<int> redoslijed;
    int vrati=0;
    for(int korak=1; korak<=n; korak++) {
        redoslijed=Razbrajanje(n,korak);
        if(redoslijed.at(redoslijed.size()-1)==odabrani_blok) {
            vrati=korak;
            break;
        }
    }
    return vrati;
}


int main ()
{
    std::cout<<"Unesite broj blokova u gradu: ";
    int n=0;
    std::cin>>n;
    std::cout<<"Unesite redni broj bloka u kojem se nalazi sjediste stranke: ";
    int sjediste=0;
    std::cin>>sjediste;
    int korak=0;
    try {
        korak=OdabirKoraka(n,sjediste);
        std::cout<<"Trazeni korak: "<<korak;
    } catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what();
    }

    return 0;
}
