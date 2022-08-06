//TP 2018/2019: Zadaća 2, Zadatak 1
#include <iostream>
#include <vector>
#include <string>

enum class Polje {
    Prazno,Posjeceno,Mina,BlokiranoPrazno,BlokiranoPosjeceno,BlokiranoMina
};

typedef std::vector<std::vector<Polje>> Tabla;

enum class Smjerovi {
    GoreLijevo, Gore, GoreDesno, Desno, DoljeDesno, Dolje, DoljeLijevo, Lijevo
};
enum class Status {
    NijeKraj, KrajPoraz, KrajPobjeda
};
enum class KodoviGresaka {
    PogresnaKomanda, NedostajeParmetar, SuvisanParametar, NeispravanParametar
};
enum class Komande {
    PomjeriJednoMjesto, PomjeriDalje, Blokiraj, Deblokiraj, PrikaziOkolinu, ZavrsiIgru,KreirajIgru
};

Tabla KreirajIgru(int n, const std::vector<std::vector<int>> &mine)
{
    for(int i=0; i<mine.size(); i++) //ako svaki vektor nema 2 elementa
        if(mine.at(i).size()!=2) throw std::domain_error("Ilegalan format zadavanja mina");


    for(int i=0; i<mine.size(); i++) {
        for(int j=0; j<mine.at(i).size(); j++) {
            if(mine.at(i).at(j)<0 || mine.at(i).at(j)>=n) throw std::domain_error("Ilegalne pozicije mina");
        }
    }

    if(n<=0) throw std::domain_error("Ilegalna veličina");

    Tabla tabla(n,std::vector<Polje>(n,Polje::Prazno));

    for(int i=0; i<mine.size(); i++) {
        int h=mine.at(i).at(0), v=mine.at(i).at(1);
        tabla.at(h).at(v)=Polje::Mina;
    }
    return tabla;
}

bool UOpsegu(int x,int y, int dimenzija)
{
    if(x<0 || x>=dimenzija || y<0 || y>=dimenzija) return false;
    return true;
}

int PrebrojMine(int x,int y,Tabla polja)
{
    int mine=0;
    if(UOpsegu(x-1,y-1,polja.size()) && polja.at(x-1).at(y-1)==Polje::Mina) mine++;
    if(UOpsegu(x-1,y,polja.size()) && polja.at(x-1).at(y)==Polje::Mina) mine++;
    if(UOpsegu(x-1,y+1,polja.size()) && polja.at(x-1).at(y+1)==Polje::Mina) mine++;
    if(UOpsegu(x,y-1,polja.size()) && polja.at(x).at(y-1)==Polje::Mina) mine++;
    if(UOpsegu(x,y+1,polja.size()) && polja.at(x).at(y+1)==Polje::Mina) mine++;
    if(UOpsegu(x+1,y-1,polja.size()) && polja.at(x+1).at(y-1)==Polje::Mina) mine++;
    if(UOpsegu(x+1,y,polja.size()) && polja.at(x+1).at(y)==Polje::Mina) mine++;
    if(UOpsegu(x+1,y+1,polja.size()) && polja.at(x+1).at(y+1)==Polje::Mina) mine++;

    return mine;
}

std::vector<std::vector<int>> PrikaziOkolinu(const Tabla &polja, int x, int y)
{
    std::vector<std::vector<int>> okolina{{0,0,0},{0,0,0},{0,0,0}};
    if(x<0 || x>=polja.size() || y<0 || y>=polja.size()) {
        std::string izuzetak= std::string("Polje (")+std::to_string(x)+std::string(",")+std::to_string(y)+std::string(") ne postoji");
        throw std::domain_error(izuzetak);
    }

    int gore_lijevo_x=x-1,gore_lijevo_y=y-1,gore_x=x-1,gore_y=y,gore_desno_x=x-1,gore_desno_y=y+1,lijevo_x=x,lijevo_y=y-1,desno_x=x,desno_y=y+1;
    int dole_lijevo_x=x+1,dole_lijevo_y=y-1,dole_x=x+1,dole_y=y,dole_desno_x=x+1,dole_desno_y=y+1;

    okolina.at(0).at(0)=PrebrojMine(gore_lijevo_x,gore_lijevo_y,polja);
    okolina.at(0).at(1)=PrebrojMine(gore_x,gore_y,polja);
    okolina.at(0).at(2)=PrebrojMine(gore_desno_x,gore_desno_y,polja);
    okolina.at(1).at(0)=PrebrojMine(lijevo_x,lijevo_y,polja);
    okolina.at(1).at(1)=PrebrojMine(x,y,polja);
    okolina.at(1).at(2)=PrebrojMine(desno_x,desno_y,polja);
    okolina.at(2).at(0)=PrebrojMine(dole_lijevo_x,dole_lijevo_y,polja);
    okolina.at(2).at(1)=PrebrojMine(dole_x,dole_y,polja);
    okolina.at(2).at(2)=PrebrojMine(dole_desno_x,dole_desno_y,polja);
    return okolina;
}

void BlokirajPolje(Tabla &polja, int x, int y)
{
    if(x<0 || x>=polja.size() || y<0 || y>=polja.size()) {
        std::string izuzetak= std::string("Polje (")+std::to_string(x)+std::string(",")+std::to_string(y)+std::string(") ne postoji");
        throw std::domain_error(izuzetak);
    }
    if(polja.at(x).at(y)==Polje::Prazno) polja.at(x).at(y)=Polje::BlokiranoPrazno;
    else if(polja.at(x).at(y)==Polje::Posjeceno) polja.at(x).at(y)=Polje::BlokiranoPosjeceno;
    else if(polja.at(x).at(y)==Polje::Mina) polja.at(x).at(y)=Polje::BlokiranoMina;
}

void DeblokirajPolje(Tabla &polja, int x, int y)
{
    if(x<0 || x>=polja.size() || y<0 || y>=polja.size()) {
        std::string izuzetak= std::string("Polje (")+std::to_string(x)+std::string(",")+std::to_string(y)+std::string(") ne postoji");
        throw std::domain_error(izuzetak);
    }
    if(polja.at(x).at(y)==Polje::BlokiranoPrazno) polja.at(x).at(y)=Polje::Prazno;
    else if(polja.at(x).at(y)==Polje::BlokiranoPosjeceno) polja.at(x).at(y)=Polje::Posjeceno;
    else if(polja.at(x).at(y)==Polje::BlokiranoMina) polja.at(x).at(y)=Polje::Mina;
}

void OcistiMatricu(Tabla &polja)
{
    for(int i=0; i<polja.size(); i++) {
        for(int j=0; j<polja.size(); j++) {
            polja.at(i).at(j)=Polje::Prazno;
        }
    }
}
bool ImaJosPraznih(const Tabla polja,int x,int y)
{
    int brojac=0;
    for(int i=0; i<polja.size(); i++) {
        for(int j=0; j<polja.size(); j++) {
            if(i==x && j==y) continue;
            else if(polja.at(i).at(j)==Polje::Prazno) brojac++;
            
        }
    }
    if(brojac>0) return true;
    return false;
}

Status Idi(Tabla &polja, int &x, int &y, Smjerovi smjer)
{
    int nova_x=x,nova_y=y;

    if(smjer==Smjerovi::GoreLijevo) {
        nova_x=x-1;
        nova_y=y-1;
    }
    if(smjer==Smjerovi::Gore) {
        nova_x=x-1;
    }
    if(smjer==Smjerovi::GoreDesno) {
        nova_x=x-1;
        nova_y=y+1;
    }
    if(smjer==Smjerovi::Lijevo) {
        nova_y=y-1;
    }
    if(smjer==Smjerovi::Desno) {
        nova_y=y+1;
    }
    if(smjer==Smjerovi::DoljeLijevo) {
        nova_x=x+1;
        nova_y=y-1;
    }
    if(smjer==Smjerovi::Dolje) {
        nova_x=x+1;
    }
    if(smjer==Smjerovi::DoljeDesno) {
        nova_x=x+1;
        nova_y=y+1;
    }

    //provjera da li je novo polje van igrace table
    if(!UOpsegu(nova_x,nova_y,polja.size())) throw std::out_of_range("Izlazak van igrace table");
    //provjera da li je novo polje blokirano
    if(polja.at(nova_x).at(nova_y)==Polje::BlokiranoPosjeceno || polja.at(nova_x).at(nova_y)==Polje::BlokiranoMina ||
            polja.at(nova_x).at(nova_y)==Polje::BlokiranoPrazno) throw std::logic_error("Blokirano polje");

    //ako je sve ok, prelazimo na novo polje
    polja.at(x).at(y)=Polje::Posjeceno;
    x=nova_x;
    y=nova_y;

    if(polja.at(x).at(y)==Polje::Mina) {
        OcistiMatricu(polja);
        return Status::KrajPoraz;
    }
    
    
    if(!ImaJosPraznih(polja,x,y) && polja.at(x).at(y)!=Polje::Posjeceno && polja.at(x).at(y)!=Polje::Mina)
        return Status::KrajPobjeda;

    return Status::NijeKraj;

    

}

Status Idi(Tabla &polja, int &x, int &y, int novi_x, int novi_y)
{
    if(!UOpsegu(novi_x,novi_y,polja.size())) throw std::out_of_range("Izlazak van igrace table");
    if(polja.at(novi_x).at(novi_y)==Polje::BlokiranoPosjeceno || polja.at(novi_x).at(novi_y)==Polje::BlokiranoMina ||
            polja.at(novi_x).at(novi_y)==Polje::BlokiranoPrazno) throw std::logic_error("Blokirano polje");
    polja.at(x).at(y)=Polje::Posjeceno;
    x=novi_x;
    y=novi_y;
    if(polja.at(x).at(y)==Polje::Mina) {
        OcistiMatricu(polja);
        return Status::KrajPoraz;
    }
    if(!ImaJosPraznih(polja,x,y) && polja.at(x).at(y)!=Polje::Posjeceno && polja.at(x).at(y)!=Polje::Mina)
        return Status::KrajPobjeda;

    return Status::NijeKraj;
}

void PrijaviGresku(KodoviGresaka kod)
{
    if(kod==KodoviGresaka::PogresnaKomanda) std::cout<<"Nerazumljiva komanda!";
    else if(kod==KodoviGresaka::NedostajeParmetar) std::cout<<"Komanda trazi parametar koji nije naveden!";
    else if(kod==KodoviGresaka::NeispravanParametar) std::cout<<"Parametar komande nije ispravan!";
    else if(kod==KodoviGresaka::SuvisanParametar) std::cout<<"Zadan je suvisan parametar nakon komande!";

}
// bool UnosKomande(Komande &komanda, Smjerovi &smjer, int &x, int &y,KodoviGresaka &greska)
// {

// }

int main ()
 {
     return 0;
}
