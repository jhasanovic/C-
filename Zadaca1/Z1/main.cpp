//TP 2018/2019: Zadaća 1, Zadatak 1
#include <iostream>
#include <vector>

enum Kriterij {Veca,Manja,Jednaka};

int produktCifara(int n)
{
    if(n<0) n=-n;
    int produkt=1;
    while(n!=0) {
        int cifra=n%10;
        produkt*=cifra;
        n=n/10;
    }
    return produkt;
}

std::vector<int> IBSZMU(std::vector<int> v,int prag,Kriterij k)
{
    std::vector<int> vrati;
    for(int i=0; i<v.size(); i++) { 
        bool flag=false;
        int element=v.at(i);
        int mult=0;
        
        if(element<0) element=-element;
        while(element>=10){//sve dok produkt cifara nije jednocifren broj
            if(element<10) break;
            mult++;
            element=produktCifara(element);
        }
        
        if(vrati.size()>0) {
            for(int j=0; j<vrati.size(); j++) {
                if(vrati.at(j)==v.at(i)) {
                    flag=true;//broj se vec nalazi u vektoru
                    break;
                }
            }
        }
        if(flag==false) {
            if(k==Kriterij::Jednaka && mult==prag)
                vrati.push_back(v.at(i));
            else if(k==Kriterij::Manja && mult<prag)
                vrati.push_back(v.at(i));
            else if(k==Kriterij::Veca && mult>prag)
                vrati.push_back(v.at(i));
        }

    }
    return vrati;
}

int main ()
{
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    std::vector<int> ulaz;
    int element;
    do {
        std::cin>>element;
        if(element==0) break;
        ulaz.push_back(element);
    } while(element!=0);

    std::cout<<"Unesite zeljeni prag za multiplikativnu otpornost: "<<std::endl;
    int prag=0;
    std::cin>>prag;

    std::cout<<"Brojevi cija je multiplikativna otpornost manja od zadane: ";
    std::vector<int> v1=IBSZMU(ulaz,prag,Kriterij::Manja);
    if(v1.size()==0) std::cout<<"Nema takvih brojeva"<<std::endl;
    else {
        for(int i=0; i<v1.size(); i++) {
            std::cout<<v1.at(i)<<" ";
        }
         std::cout<<std::endl;
    }
    std::cout<<"Brojevi cija je multiplikativna otpornost veca od zadane: ";
    std::vector<int> v2=IBSZMU(ulaz,prag,Kriterij::Veca);
    if(v2.size()==0) std::cout<<"Nema takvih brojeva"<<std::endl;
    else {
        for(int i=0; i<v2.size(); i++) {
            std::cout<<v2.at(i)<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"Brojevi cija je multiplikativna otpornost jednaka zadanoj: ";
    std::vector<int> v3=IBSZMU(ulaz,prag,Kriterij::Jednaka);
    if(v3.size()==0) std::cout<<"Nema takvih brojeva"<<std::endl;
    else {
        for(int i=0; i<v3.size(); i++) {
            std::cout<<v3.at(i)<<" ";
        }
         std::cout<<std::endl;
    }

    return 0;
}