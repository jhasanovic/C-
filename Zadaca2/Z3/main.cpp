//TP 2018/2019: Zadaća 2, Zadatak 3
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <list>
#include <forward_list>
#include <cmath>

template <typename Tip3,typename Tip>
bool Duplikat(Tip3 p5,Tip3 kraj,Tip element) //provjera da li se element vec nalazi u krajnjem bloku
{
    while(p5!=kraj) {
        if(*p5==element) return true;
        p5++;
    }
    return false;
}

template <typename Tip1, typename Tip2, typename Tip3>
Tip3 ZajednickiElementiBlokova(Tip1 p1, Tip1 p2, Tip2 p3, Tip2 p4, Tip3 p5)
{

    Tip2 p=p3;//sacuvamo pocetak bloka 2
    Tip3 poc=p5;
    Tip3 kraj=p5;

    while(p1!=p2) {
        p3=p;
        while(p3!=p4) {
            if(*p1==*p3 && !Duplikat(poc,kraj,*p1)) {
                //upis u odredisni blok
                *p5=*p1;
                p5++;
                kraj++;
            }
            if(p3!=p4)
                p3++;
        }
        p1++;
    }

    return p5;
}

int main ()
{
    int br_el=0;
    int niz[100];
    std::cout<<"Unesi broj elemenata niza (ne vise od 100): "<<std::endl;
    std::cin>>br_el;


    std::cout<<"Unesi elemente niza: ";
    for(int i=0; i<br_el; i++) {
        std::cin>>niz[i];
    }

    std::cout<<"Unesi broj elemenata deka: "<<std::endl;
    int br_el_deka=0;
    std::cin>>br_el_deka;
    std::deque<int> dek(br_el_deka);

    std::cout<<"Unesi elemente deka: "<<std::endl;
    for(int i=0; i<br_el_deka; i++) {
        int element=0;
        std::cin>>element;
        dek.push_back(element);
    }
    std::vector<int> v(100);
    //velicinu zadati kao povratna vrijednost funkcije-v.begin()
    auto kraj=ZajednickiElementiBlokova(niz,niz+br_el,dek.begin(),dek.end(),v.begin());
    v.resize(kraj-v.begin());
    std::cout<<"Vektor zajednickih elemenata niza i deka ima "<<v.size()<<" elemenata"<<std::endl;
    std::cout<<"Zajednicki elementi glase: ";
    for(int i=0; i<kraj-v.begin(); i++) {
        std::cout<<v.at(i)<<" ";
    }

    return 0;
}
