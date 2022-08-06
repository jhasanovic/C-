//TP 2018/2019: Zadaća 2, Zadatak 4
#include <iostream>
#include <algorithm>
#include <cmath>

int BrojDjelilaca(int x)
{
    int brojac=0;
    for(int i=1; i*i<=x; i++) {
        if(x%i==0) {
            if(x/i==i) brojac++;
            else brojac+=2;
        }
    }
    return brojac;
}

bool KriterijSortiranja(int x, int y)
{
    if(BrojDjelilaca(x)>BrojDjelilaca(y)) return true;
    else if (BrojDjelilaca(x)<BrojDjelilaca(y)) return false;
    else if (x<y) return true;
    else return false;
}

void SortirajPoBrojuDjelilaca(int* niz, int br_el)
{
    std::sort(niz,niz+br_el,KriterijSortiranja);
}

bool PretraziBinarno(int* niz, int br_el, int trazeni)
{
    return std::binary_search(niz,niz+br_el,trazeni);
}

int main ()
{
    int br_el=0,element=0;
    std::cout<<"Unesite broj elemenata niza: "<<std::endl;
    std::cin>>br_el;
    int *niz=nullptr;
    niz=new int[br_el];

    std::cout<<"Unesite elemente niza: "<<std::endl;
    for(int i=0; i<br_el; i++) {
        std::cin>>element;
        niz[i]=element;
    }


    SortirajPoBrojuDjelilaca(niz,br_el);
    std::cout<<"Sortiran niz glasi: ";
    for(int i=0; i<br_el; i++) {
        std::cout<<niz[i]<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"Unesite element koji treba binarno pretraziti: "<<std::endl;
    int trazeni_el=0;
    std::cin>>trazeni_el;
    if(PretraziBinarno(niz,br_el,trazeni_el))
        std::cout<<"Trazeni element se nalazi u nizu."<<std::endl;
    else
        std::cout<<"Trazeni element se ne nalazi u nizu."<<std::endl;

    delete[] niz;

    return 0;
}
