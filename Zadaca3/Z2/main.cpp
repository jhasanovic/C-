//TP 2018/2019: Zadaća 3, Zadatak 2
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iterator>


typedef std::map<std::string,std::vector<std::string>> Knjiga;
typedef std::map<std::string,std::set<std::tuple<std::string,int,int>>> Mapa;
typedef std::set<std::tuple<std::string,int,int>> Skup;

std::string SveUMalaSlova(std::string rijec)
{
    std::string nova;
    for(auto slovo:rijec) {
        nova.push_back(std::tolower(slovo));
    }
    return nova;
}

Mapa KreirajIndeksPojmova(Knjiga k)
{
//knjiga je mapa sa kljucem koji je oznaka poglavlja i vektorom stringova koji su stranice sa tekstom
//treba vratiti mapu ciji su kljucevi rijeci, a pridruzene vrijednosti skup uredjenih trojki (poglavlje, stranica od 1, pozicija rijeci u str od 0)


//prolazimo kroz mapu knjiga, za svako poglavlje predjemo svaku stranicu, iz svake stranice za svaku rijec zapisemo njeno poglavlje,stranicu
//i njenu poziciju i stavimo u povratnu mapu
//svaki clan mape je jedna distinct rijec, a pridruzene vrijednosti su sve pozicije te rijeci u knjizi
    Mapa mapa{};
    for(auto it=k.begin(); it!=k.end(); it++) { //prolazimo kroz knjigu
        Skup skup;
        std::string rijec;
        for(int i=0; i<it->second.size(); i++) { //prolazimo kroz vektor stranica
            //sad smo u odredjenoj stranici, treba proci kroz string znak po znak
            std::tuple<std::string,int,int> t;
            for(int j=0; j<it->second.at(i).length();) {
                int pocetak_rijeci=0;
                bool zapoceta_rijec=false;
                rijec.clear();
                //sve dok nije kraj stringa i dok je znak slovo
                while(j!=it->second.at(i).length() && ((it->second.at(i).at(j)>='A' && it->second.at(i).at(j)<='z') || std::isdigit(it->second.at(i).at(j)))) {
                    if(zapoceta_rijec==false) {
                        pocetak_rijeci=j;
                        zapoceta_rijec=true;
                    }
                    rijec.push_back(it->second.at(i).at(j));//upisemo rijec u pomocni string
                    j++;
                }
                if(j!=it->second.at(i).length() && (!(it->second.at(i).at(j)>='A' && it->second.at(i).at(j)<='z') && !std::isdigit(it->second.at(i).at(j))))
                    j++;

                if(rijec.length()>0) {
                    //u skup koji vracamo dodamo poglavlje, stranicu+1 i pocetak rijeci
                    rijec=SveUMalaSlova(rijec);
                    t=std::make_tuple(it->first,i+1,pocetak_rijeci);
                    skup.insert(t);
                    //prije dodavanja rijeci u mapu, provjerimo da li smo je vec dodali
                    if(mapa.find(rijec)==mapa.end()) {
                        //znaci da rijec nije nadjena, dodamo je u mapu posebno
                        skup.insert(t);
                        mapa.insert({rijec,skup});
                    } else {
                        for(auto it=mapa.begin(); it!=mapa.end(); it++) {
                            if(it->first==rijec) it->second.insert(t);
                        }
                    }
                }
                skup.clear();
            }
        }
    }
    return mapa;
}

Skup PretraziIndeksPojmova(std::string rijec, Mapa indeks_pojmova)
{
    if(indeks_pojmova.find(SveUMalaSlova(rijec))==indeks_pojmova.end()) throw std::logic_error("Pojam nije nadjen.");
    return indeks_pojmova.find(SveUMalaSlova(rijec))->second;
}

void IspisiIndeksPojmova(Mapa indeks_pojmova)
{
    //prolazimo kroz mapu i ispisujemo kljuc i sve njegove tuples
    for(auto it=indeks_pojmova.begin(); it!=indeks_pojmova.end(); it++) {
        std::cout<<it->first<<": ";
        int trenutni=0;
        int kraj=std::distance(it->second.begin(),it->second.end());
        for(auto i:it->second) {
            if(trenutni!=kraj-1)
                std::cout<<std::get<0>(i)<<"/"<<std::get<1>(i)<<"/"<<std::get<2>(i)<<", ";
            else std::cout<<std::get<0>(i)<<"/"<<std::get<1>(i)<<"/"<<std::get<2>(i)<<std::endl;
            trenutni++;
        }
    }
}

int main ()
{
    std::string poglavlje;
    Knjiga knjiga;

    do {
        std::cout<<"Unesite naziv poglavlja: "<<std::endl;
        std::getline(std::cin,poglavlje);
        if(poglavlje==".") break;
        std::string sadrzaj_stranice;
        int i=1;
        std::vector<std::string> stranice;
        do {
            std::cout<<"Unesite sadrzaj stranice "<<i<<": "<<std::endl;
            std::getline(std::cin,sadrzaj_stranice);
            if(sadrzaj_stranice==".") break;
            stranice.push_back(sadrzaj_stranice);
            i++;
        } while(sadrzaj_stranice!=".");
        knjiga.insert(std::pair<std::string,std::vector<std::string>>(poglavlje,stranice));
    } while(poglavlje!=".");

    Mapa indeks_pojmova=KreirajIndeksPojmova(knjiga);
    std::cout<<"Kreirani indeks pojmova: "<<std::endl;
    IspisiIndeksPojmova(indeks_pojmova);

    std::string rijec;
    do {
        std::cout<<"Unesite rijec: "<<std::endl;
        std::getline(std::cin,rijec);
        if(rijec==".") break;
        try {
            Skup skup=PretraziIndeksPojmova(rijec,indeks_pojmova);
            int vel=skup.size();
            int i=0;
            for(auto x:skup) {
                if(i!=vel-1) std::cout<<std::get<0>(x)<<"/"<<std::get<1>(x)<<"/"<<std::get<2>(x)<<", ";
                else std::cout<<std::get<0>(x)<<"/"<<std::get<1>(x)<<"/"<<std::get<2>(x)<<std::endl;
                i++;
            }
        } catch(std::logic_error izuzetak) {
            std::cout<<izuzetak.what()<<std::endl;
        }
    } while(rijec!=".");

    return 0;
}
