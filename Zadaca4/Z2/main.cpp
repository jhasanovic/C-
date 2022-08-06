//TP 2018/2019: Zadaća 4, Zadatak 2
#include <iostream>
#include <string>


void dajCifreJMBG(long long int jmbg,int &c1,int&c2,int&c3,int&c4,int &c5,int&c6,int&c7,int&c8,int &c9,int&c10,int&c11,int&c12,int &c13)
{

    c13=jmbg%10;
    jmbg/=10;
    c12=jmbg%10;
    jmbg/=10;
    c11=jmbg%10;
    jmbg/=10;
    c10=jmbg%10;
    jmbg/=10;
    c9=jmbg%10;
    jmbg/=10;
    c8=jmbg%10;
    jmbg/=10;
    c7=jmbg%10;
    jmbg/=10;
    c6=jmbg%10;
    jmbg/=10;
    c5=jmbg%10;
    jmbg/=10;
    c4=jmbg%10;
    jmbg/=10;
    c3=jmbg%10;
    jmbg/=10;
    c2=jmbg%10;
    jmbg/=10;
    c1=jmbg%10;

}

bool testirajIspravnostDatuma(int dan,int mjesec,int godina)
{

    if(2000+godina>2021) godina=1000+godina;
    else godina=2000+godina;

    if(mjesec>=1 && mjesec<=12 && dan>=1) {
        if(mjesec==1 && dan<=31) return true;
        else if(mjesec==2 && godina%4==0 && dan<=29)return true;
        else if(mjesec==2 && godina%4!=0 && dan<=28)return true;
        else if(mjesec==3 && dan<=31)return true;
        else if(mjesec==4 && dan<=30)return true;
        else if(mjesec==5 && dan<=31)return true;
        else if(mjesec==6 && dan<=30)return true;
        else if(mjesec==7 && dan<=31)return true;
        else if(mjesec==8 && dan<=31)return true;
        else if(mjesec==9 && dan<=30)return true;
        else if(mjesec==10 && dan<=31)return true;
        else if(mjesec==11 && dan<=30)return true;
        else if(mjesec==12 && dan<=31)return true;
    }
    return false;
}

bool testirajZadnjuCifru(int c1,int c2,int c3,int c4,int c5,int c6,int c7,int c8,int c9,int c10,int c11,int c12,int c13)
{
    int zadnja=11-(7*(c1+c7)+6*(c2+c8)+5*(c3+c9)+4*(c4+c10)+3*(c5+c11)+2*(c6+c12))%11;
    if((zadnja==c13) || (zadnja==11 && c13==0)) return true;
    else if(zadnja==10) return false;
    else return false;
}

class GradjaninBiH
{
    std::string imeIPrezime;
    long long int JMBG;
    int danRodjenja;
    int mjesecRodjenja;
    int godinaRodjenja;
    int sifraRegije;
    
    GradjaninBiH *prethodni=nullptr;
    static GradjaninBiH *posljednjiKreirani;
    //ZABRANITI KOPIRANJE I DODJELU
public:
    enum Pol {Musko,Zensko};
    GradjaninBiH(const GradjaninBiH &g) = delete; // Zabrana kopiranja
    GradjaninBiH &operator =(const GradjaninBiH &g) = delete; // Zabrana dodjele

    ~GradjaninBiH()
    {
        //kad se objekat obrise preusmjeriti pokazivace
        //ako se brise prvi, prethodni onog iza njega postaje null
        //ako se brise zadnji, posljednji kreirani postaje njegov prethodni
        //ako se brise u sredini, prethodni onog poslije njega postaje prethodni onog kojeg brisemo

        //brisanje prvog
        if(this->prethodni==nullptr) {
            for(GradjaninBiH *p=posljednjiKreirani; p!=nullptr; p=posljednjiKreirani->prethodni) {
                if(p->prethodni==this) { //ako je instanca koju brisemo prethodnik trenutne
                    p->prethodni=nullptr;
                    break;
                }
            }
        }

        //brisanje u sredini i na kraju
        else {
            for(GradjaninBiH *p=posljednjiKreirani; p!=nullptr; p=posljednjiKreirani->prethodni) {
                if(p==this) {//brisanje posljednjeg
                    p=this->prethodni;
                    this->prethodni=nullptr;
                    break;
                }
                if(p->prethodni==this) { //onaj koji brisemo je prethodni trenutnog
                    p->prethodni=this->prethodni;
                    this->prethodni=nullptr;
                }
            }
        }
    }
    void PromijeniImeIPrezime(std::string novo)
    {
        imeIPrezime=novo;
    }
    std::string DajImeIPrezime()
    {
        return imeIPrezime;
    }

    long long int DajJMBG()
    {
        return JMBG;
    }
    int DajDanRodjenja()
    {
        return danRodjenja;
    }
    int DajMjesecRodjenja()
    {
        return mjesecRodjenja;
    }
    int DajGodinuRodjenja()
    {
        return godinaRodjenja;
    }
    int DajSifruRegije()
    {
        return sifraRegije;
    }
    Pol DajPol()
    {
        long long int temp=JMBG/10;
        int c012=temp%10;
        temp/=10;
        int c011=temp%10;
        temp/=10;
        int c010=temp%10;

        int sifraPola=c010*100+c011*10+c012;
        if(sifraPola>=0 && sifraPola<=499) return GradjaninBiH::Pol::Musko;
        else return GradjaninBiH::Pol::Zensko;
    }

    GradjaninBiH(std::string ip,long long int jmbg)
    {
        //provjera ispravnosti podataka
        int c1=0,c2=0,c3=0,c4=0,c5=0,c6=0,c7=0,c8=0,c9=0,c10=0,c11=0,c12=0,c13=0;
        dajCifreJMBG(jmbg,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13);

        if(testirajIspravnostDatuma(c1*10+c2,c3*10+c4,c5*100+c6*10+c7)==false || testirajZadnjuCifru(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13)==false)
            throw std::logic_error("JMBG nije validan");

//provjera da li zadati jmbg vec postoji
        for(GradjaninBiH *prosli=posljednjiKreirani; prosli!=nullptr; prosli=prosli->prethodni) {
            if(prosli->DajJMBG()==jmbg) throw std::logic_error ("Vec postoji gradjanin sa istim JMBG");
        }

//ako JMBG ne postoji, postavljamo ga
        
        
        imeIPrezime=ip;
        JMBG=jmbg;
        danRodjenja=c1*10+c2;
        mjesecRodjenja=c3*10+c4;
        int godina=c5*100+c6*10+c7;
        if(2000+godina>2021) godinaRodjenja=1000+godina;
        else godinaRodjenja=2000+godina;
        sifraRegije=c8*10+c9;
        this->prethodni=posljednjiKreirani;
        posljednjiKreirani=this;

    }

    GradjaninBiH(std::string imeIPrezime,int dan,int mjesec,int godina,int regija,GradjaninBiH::Pol pol)
    {
        //provjera ispravnosti podataka
        if(testirajIspravnostDatuma(dan,mjesec,godina)==false || regija<0 || regija>99) throw std::logic_error("Neispravni podaci");
        GradjaninBiH::imeIPrezime=imeIPrezime;
        danRodjenja=dan;
        mjesecRodjenja=mjesec;
        godinaRodjenja=godina;
        sifraRegije=regija;
        //OVDJE TREBA KREIRATI JMBG
        //kod c10,11,12 treba uzeti za jedan uvecan od prethodnog kreiranog muskog/zenskog gradjanina
        int c2=0;
        c2=dan%10;
        int c1=0;
        c1=(dan/10)%10;
        int c4=0;
        c4=mjesec%10;
        int c3=0;
        c3=(mjesec/10)%10;
        int c7=0;
        c7=godina%10;
        int c6=0;
        c6=(godina/10)%10;
        int c5=0;
        c5=((godina/10)/10)%10;
        int c9=0;
        c9=regija%10;
        int c8=0;
        c8=(regija/10)%10;

        int c12=0,c11=0,c10=0;
        bool nadjenProsli=false;
        //nadjemo tri cifre
        for(GradjaninBiH *prosli=posljednjiKreirani; prosli!=nullptr; prosli=prosli->prethodni) {
            if(prosli->DajPol()==pol) {
                long long int temp=prosli->DajJMBG();
                temp/=10;//c13
                c12=temp%10;
                temp/=10;
                c11=temp%10;
                temp/=10;
                c10=temp%10;
                nadjenProsli=true;
                break;
            }
        }
        int trenutniKod=c10*100+c11*10+c12;
        int sljedeci=0;
        if(nadjenProsli==false) {
            if(pol==GradjaninBiH::Pol::Musko) sljedeci=0;
            else if(pol==GradjaninBiH::Pol::Zensko) sljedeci=500;
        } else sljedeci=trenutniKod+1;

        int temp2=sljedeci;
        int c12novi=temp2%10;
        c12=c12novi;
        temp2/=10;
        int c11novi=temp2%10;
        c11=c11novi;
        temp2/=10;
        int c10novi=temp2%10;
        c10=c10novi;

        //ako ispadne c13 pogresan, ponoviti izbor koda
        int zadnja=11-(7*(c1+c7)+6*(c2+c8)+5*(c3+c9)+4*(c4+c10novi)+3*(c5+c11novi)+2*(c6+c12novi))%11;
        while(zadnja==10) {
            sljedeci++;
            int temp3=sljedeci;
            c12novi=temp3%10;
            c12=c12novi;
            temp3/=10;
            c11novi=temp3%10;
            c11=c11novi;
            temp3/=10;
            c10novi=temp3%10;
            c10=c10novi;
            zadnja=11-(7*(c1+c7)+6*(c2+c8)+5*(c3+c9)+4*(c4+c10novi)+3*(c5+c11novi)+2*(c6+c12novi))%11;//nova zadnja cifra
        }

        if(nadjenProsli==false && pol==GradjaninBiH::Pol::Zensko) {
            c10=5;
            c11=0;
            c12=0;
        }



        int c13=zadnja;
        if(c13==11) c13=0;
        std::string tempJMBG=std::to_string(c1)+std::to_string(c2)+std::to_string(c3)+std::to_string(c4)+std::to_string(c5)+std::to_string(c6)
                             +std::to_string(c7) +std::to_string(c8) +std::to_string(c9)+std::to_string(c10)+std::to_string(c11)+std::to_string(c12)
                             +std::to_string(c13);
        JMBG=std::stoll(tempJMBG);
        this->prethodni=posljednjiKreirani;
        posljednjiKreirani=this;
    }

};


GradjaninBiH * GradjaninBiH::posljednjiKreirani=nullptr;

int main ()
{
 
    std::cout<<"Unesite broj gradjana koje zelite unijeti po JMBG: "<<std::endl;
    int n=0;
    std::cin>>n;

    for(int i=1; i<=n; i++) {
        std::cout<<"Unos podataka za "<<i<<". gradjanina"<<std::endl;
        std::cin.ignore(10000, '\n');
        std::cout<<"Unesite ime i prezime (u istom redu): ";
        std::string imeIPrezime;
        std::getline(std::cin,imeIPrezime);
        std::cout<<"Unesite JMBG: ";
        long long int jmbg;
        std::cin>>jmbg;
        try {
            GradjaninBiH(imeIPrezime,jmbg);
            std::cout<<"Ime i prezime: "<<imeIPrezime<<", JMBG: "<<jmbg<<std::endl;
        } catch(std::logic_error izuzetak) {
            std::cout<<izuzetak.what()<<std::endl;
            i--;
        }
        std::cout<<std::endl;
    }

    std::cin.ignore(10000, '\n');
    std::cout<<"Unesite broj gradjana koje zelite unijeti po datumu rodjenja, regiji i polu: "<<std::endl;
    int m=0;
    std::cin>>m;

    for(int i=n+1; i<=m+n; i++) {
        std::cout<<"Unos podataka za "<<i<<". gradjanina"<<std::endl;
        std::cin.ignore(10000, '\n');
        std::cout<<"Unesite ime i prezime (u istom redu): ";
        std::string imeIPrezime;
        std::getline(std::cin,imeIPrezime);
        std::cout<<"Unesite datum rodjenja(format dd/mm/gggg): ";
        int dan=0,mjesec=0,godina=0;
        char slash='/';
        std::cin>>dan>>slash>>mjesec>>slash>>godina;
        std::cout<<"Unesite sifru regije: ";
        int regija=0;
        std::cin>>regija;
        std::cout<<"Unesite M za musko, Z za zensko: ";
        char pol;
        std::cin>>pol;
        try {
            if(pol=='M'){
                GradjaninBiH g(imeIPrezime,dan,mjesec,godina,regija,GradjaninBiH::Pol::Musko); 
                std::cout<<"Ime i prezime: "<<imeIPrezime<<", JMBG: "<<g.DajJMBG()<<std::endl;
            }
                
            else if(pol=='Z'){
                GradjaninBiH g(imeIPrezime,dan,mjesec,godina,regija,GradjaninBiH::Pol::Zensko);
                 std::cout<<"Ime i prezime: "<<imeIPrezime<<", JMBG: "<<g.DajJMBG()<<std::endl;
            }
        } catch(std::logic_error izuzetak) {
            std::cout<<izuzetak.what()<<std::endl;
            i--;
        }
       
        std::cout<<std::endl;
    }


    return 0;
}
