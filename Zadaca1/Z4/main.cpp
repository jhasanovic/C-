//TP 2018/2019: Zadaća 1, Zadatak 4
#include <iostream>
#include <string>
#include <vector>

std::string ZamjenaRijeci(std::string recenica, std::vector<std::string> original, std::vector<std::string> zamjena)
{
    if(original.size()!=zamjena.size()) throw std::domain_error("Nekorektni parametri");

    std::vector<std::string> rijeci;

    for(int i=0; i<recenica.length();) {
        if(recenica.at(i)==' ') {
            std::string razmak;
            while(i<recenica.length() && recenica.at(i)==' ') {
                razmak.push_back(' ');
                i++;
            }
            if(razmak.size()>0)
                rijeci.push_back(razmak);
        }

        else {
            std::string pomocni;
            while(i<recenica.length()) {
                if(recenica.at(i)==' ') break;
                pomocni.push_back(recenica.at(i));
                i++;
            }
            if(pomocni.length()!=0) rijeci.push_back(pomocni);
        }
    }

    for(int i=0; i<rijeci.size(); i++) {
        for(int j=0; j<original.size(); j++) {
            if(rijeci.at(i).compare(original.at(j))==0) {
                rijeci.at(i)=zamjena.at(j);
                break;
            }
        }
    }
    std::string krajnji;
    for (const auto &rijec : rijeci) krajnji += rijec;
    return krajnji;
}



int main ()
{
    int br_rijeci=0;
    std::cout<<"Unesite koliko riječi sadrži rječnik."<<std::endl;
    std::cin>>br_rijeci;
    std::cin.ignore(10000,'\n');
    std::vector<std::string> v_original, v_zamjena;
    for(int i=1; i<=br_rijeci; i++) {
        std::cout<<"Unesite "<<i<<". original rječnika."<<std::endl;
        std::string original, zamjena;
        std::getline(std::cin,original);
        v_original.push_back(original);
        std::cout<<"Unesite "<<i<<". zamjenu rječnika."<<std::endl;
        std::getline(std::cin,zamjena);
        v_zamjena.push_back(zamjena);
    }

    std::string recenica;
    do {
        std::cout<<"Unesite rečenicu koju želite transformisati: "<<std::endl;
        std::getline(std::cin,recenica);
        if(recenica.empty()) break;
        std::cout<<"Transformisana rečenica glasi: "<<std::endl;

        try {
            std::cout<<ZamjenaRijeci(recenica,v_original,v_zamjena);
        } catch(std::domain_error izuzetak) {
            std::cout<<izuzetak.what();
        }
        std::cout<<std::endl;

    } while(!recenica.empty());
    return 0;
}
