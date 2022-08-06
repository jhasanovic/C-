//TP 2018/2019: Zadaća 5, Zadatak 1
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

bool smislenDatum(int dan,int mjesec,int godina)
{
    if(godina<1800) return false;
    if(mjesec>=1 && mjesec<=12 && dan>=1) {
        if(mjesec==1 && dan<=31) return true;
        else if(mjesec==2 && ((godina%4==0 && godina%100!=0) || godina%400==0) && dan<=29) return true;
        else if(mjesec==2 && dan<=28) return true;
        else if(mjesec==3 && dan<=31) return true;
        else if(mjesec==4 && dan<=30) return true;
        else if(mjesec==5 && dan<=31) return true;
        else if(mjesec==6 && dan<=30) return true;
        else if(mjesec==7 && dan<=31) return true;
        else if(mjesec==8 && dan<=31) return true;
        else if(mjesec==9 && dan<=30) return true;
        else if(mjesec==10 && dan<=31) return true;
        else if(mjesec==11 && dan<=30) return true;
        else if(mjesec==12 && dan<=31) return true;
    }
    return false;
}

int dajMaxDan(int m,int g)
{
    if(m==1) return 31;
    else if(m==2 && ((g%4==0 && g%100!=0) || g%400==0)) return 29;
    else if(m==2) return 28;
    else if(m==3) return 31;
    else if(m==4) return 30;
    else if(m==5) return 31;
    else if(m==6) return 30;
    else if(m==7) return 31;
    else if(m==8) return 31;
    else if(m==9) return 30;
    else if(m==10) return 31;
    else if(m==11) return 30;
    else if(m==12) return 31;
    return 0;
}

void dajSljedeciDan(int &d,int &m,int &g)
{
    int temp1=d,temp2=m;

    if(++temp1<=dajMaxDan(m,g)) { //ne treba uvecavati mjesec
        d=d+1;
    } else { //treba uvecati mjesec
        d=1;
        if(++temp2>12) { //treba uvecati godinu
            m=1;
            g=g+1;
        } else {
            m++;
        }
    }
}
void dajProsliDan(int &d,int &m,int &g)
{
    int temp1=d,temp2=m;
    if(--temp1>=1) { //ako je smanjeni datum legalan
        d=d-1;
    } else { //treba smanjiti mjesec
        if(--temp2<1) { //mjesec prebaciti na 12, a godinu smanjiti
            m=12;
            g--;
            d=dajMaxDan(m,g);
        } else { //samo smanjiti mjesec i postaviti max dan
            m--;
            d=dajMaxDan(m,g);
        }
    }
}

class Datum
{
    int dan;
    int mjesec;
    int godina;

public:
    enum Mjeseci {Januar=1,Februar,Mart,April,Maj,Juni,Juli,August,Septembar,Oktobar,Novembar,Decembar};
    enum Dani {Ponedjeljak=1,Utorak,Srijeda,Cetvrtak,Petak,Subota,Nedjelja};

    Datum(int d,int m,int g)
    {
        if(smislenDatum(d,m,g)==false) throw std::domain_error("Nelegalan datum");
        dan=d;
        mjesec=m;
        godina=g;
    }

    Datum(int d,Mjeseci m, int g)
    {
        if(smislenDatum(d,m,g)==false) throw std::domain_error("Nelegalan datum");
        dan=d;
        mjesec=m;
        godina=g;
    }

    void Postavi(int d,int m,int g)
    {
        if(smislenDatum(d,m,g)==false) throw std::domain_error("Nelegalan datum");
        dan=d;
        mjesec=m;
        godina=g;
    }

    void Postavi(int d,Mjeseci m,int g)
    {
        if(smislenDatum(d,m,g)==false) throw std::domain_error("Nelegalan datum");
        dan=d;
        mjesec=m;
        godina=g;
    }

    int DajDan()const
    {
        return dan;
    }
    Mjeseci DajMjesec()const
    {
        return static_cast<Mjeseci>(mjesec);
    }
    int DajGodinu()const
    {
        return godina;
    }
    const char* DajImeMjeseca()const //pokazivac na char
    {
        const char* mjeseci[]= {"Januar","Februar","Mart","April","Maj","Juni","Juli","August","Septembar","Oktobar","Novembar","Decembar"};
        return mjeseci[mjesec-1];
    }
    Dani DajDanUSedmici()const;
    const char* DajImeDanaUSedmici()const;

//preklopljeni operatori

//prefiksne verzije
    friend Datum &operator ++(Datum &d);
    friend Datum &operator --(Datum &d);
//postfiksne verzije
    friend Datum operator ++(Datum &d,int );
    friend Datum operator --(Datum &d,int );

    friend Datum operator+(const Datum &d,const int n);
    friend Datum operator-(const Datum &d,const int n);

    friend Datum &operator +=(Datum &d,const int n);
    friend Datum &operator -=(Datum &d,const int n);

    friend std::ostream &operator<<(std::ostream &cout,const Datum &d);
    friend std::istream &operator>>(std::istream &cin,const Datum &d);

    friend int operator-(const Datum &d1,const Datum &d2);

    friend bool operator ==(const Datum &d1,const Datum &d2);
    friend bool operator !=(const Datum &d1,const Datum &d2);
    friend bool operator <(const Datum &d1,const Datum &d2);
    friend bool operator <=(const Datum &d1,const Datum &d2);
    friend bool operator >(const Datum &d1,const Datum &d2);
    friend bool operator >=(const Datum &d1,const Datum &d2);

    operator std::string()const;
    explicit operator int()const;

};

Datum::operator int()const
{
    Datum referentni=Datum(1,1,1800);
    Datum trenutni=*this;
    return referentni-trenutni;
}

Datum::operator std::string()const
{
    return std::to_string(this->dan)+". "+std::string(this->DajImeMjeseca())+" "+std::to_string(this->godina)+". ("+std::string(this->DajImeDanaUSedmici())+")";
}

bool operator <(const Datum &d1,const Datum &d2)
{
    if(d1.godina<d2.godina) return true;
    else if(d1.godina==d2.godina) {
        if(d1.mjesec<d2.mjesec) return true;
        else if(d1.mjesec==d2.mjesec) {
            if(d1.dan<d2.dan) return true;
        }
    }
    return false;
}

bool operator >(const Datum &d1,const Datum &d2)
{
    if(d1.godina>d2.godina) return true;
    else if(d1.godina==d2.godina) {
        if(d1.mjesec>d2.mjesec) return true;
        else if(d1.mjesec==d2.mjesec) {
            if(d1.dan>d2.dan) return true;
        }
    }
    return false;
}

bool operator >=(const Datum &d1,const Datum &d2)
{
    if(d1.godina>=d2.godina) return true;
    else if(d1.godina==d2.godina) {
        if(d1.mjesec>=d2.mjesec) return true;
        else if(d1.mjesec==d2.mjesec) {
            if(d1.dan>=d2.dan) return true;
        }
    }
    return false;
}

bool operator <=(const Datum &d1,const Datum &d2)
{
    if(d1.godina<=d2.godina) return true;
    else if(d1.godina==d2.godina) {
        if(d1.mjesec<=d2.mjesec) return true;
        else if(d1.mjesec==d2.mjesec) {
            if(d1.dan<=d2.dan) return true;
        }
    }
    return false;
}

bool operator ==(const Datum &d1,const Datum &d2)
{
    if(d1.godina==d2.godina && d1.mjesec==d2.mjesec && d1.dan==d2.dan) return true;
    return false;
}

bool operator !=(const Datum &d1,const Datum &d2)
{
    return !(d1==d2);
}

bool DaLiJePrestupna(int godina)
{
    if ((godina%4==0 && godina%100!=0) || godina%400==0) return true;
    return false;
}

int operator-(const Datum &d1,const Datum &d2)
{
    const int danaUMjesecu[]= {31,28,31,30,31,30,31,31,30,31,30,31};
    int br1=0,br2=0;

    for(int i=1800; i<d1.godina; i++) {
        if(DaLiJePrestupna(i)) br1+=366;
        else br1+=365;
    }
    for(int i=1800; i<d2.godina; i++) {
        if(DaLiJePrestupna(i)) br2+=366;
        else br2+=365;
    }

    for(int i=1; i<d1.mjesec; i++) {
        if(DaLiJePrestupna(d1.godina)==true && i==2) br1+=29;
        else br1+=danaUMjesecu[i-1];
    }
    for(int i=1; i<d2.mjesec; i++) {
        if(DaLiJePrestupna(d2.godina)==true && i==2) br2+=29;
        else br2+=danaUMjesecu[i-1];
    }


    br1+=d1.dan-2;
    br2+=d2.dan-2;
    int br_dana=std::abs(br2-br1);
    return br_dana;
}


Datum::Dani Datum::DajDanUSedmici()const
{
    const int t[]= {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int y=this->godina;
    y-= this->mjesec < 3;
    return Datum::Dani((y + y/4 - y/100 + y/400 + t[this->mjesec-1] + this->dan) % 7);
}

const char* Datum::DajImeDanaUSedmici()const
{
    const char* dani[]= {"Nedjelja","Ponedjeljak","Utorak","Srijeda","Cetvrtak","Petak","Subota"};
    const int t[]= {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int y=this->godina;
    y-= this->mjesec < 3;
    return dani[(y + y/4 - y/100 + y/400 + t[this->mjesec-1] + this->dan) % 7];
}

Datum &operator ++(Datum &d)
{
    if(d.dan<=27) d.dan++;
    else dajSljedeciDan(d.dan,d.mjesec,d.godina);
    return d;
}

Datum operator ++(Datum &d,int)
{
    Datum pomocni=d;
    if(pomocni.dan<=27) d.dan++;
    else dajSljedeciDan(d.dan,d.mjesec,d.godina);
    return pomocni;
}

Datum &operator --(Datum &d)
{
    int temp1=d.dan,temp2=d.mjesec,temp3=d.godina;
    dajProsliDan(temp1,temp2,temp3);
    if(temp3<1800) throw std::domain_error("Nelegalan datum");
    else dajProsliDan(d.dan,d.mjesec,d.godina);
    return d;
}

Datum operator --(Datum &d,int)
{
    Datum pomocni=d;
    int temp1=d.dan,temp2=d.mjesec,temp3=d.godina;
    dajProsliDan(temp1,temp2,temp3);
    if(temp3<1800) throw std::domain_error("Nelegalan datum");
    else dajProsliDan(d.dan,d.mjesec,d.godina);
    return pomocni;
}

Datum operator+(const Datum &d,const int n)
{

    Datum datum=d;
    if(n==0) return datum;
    else if(n>0) {
        //uvecati za n dana
        for(int i=0; i<n; i++) {
            dajSljedeciDan(datum.dan,datum.mjesec,datum.godina);
        }
    } else {
        int temp1=d.dan,temp2=d.mjesec,temp3=d.godina;
        int m=-n;
        for(int i=0; i<m; i++) {
            dajProsliDan(temp1,temp2,temp3);
        }
        if(temp3<1800) throw std::domain_error("Nelegalan datum");
        for(int i=0; i<m; i++) {
            dajProsliDan(datum.dan,datum.mjesec,datum.godina);
        }
    }
    return datum;
}

Datum operator-(const Datum &d,const int n)
{
    Datum datum=d;
    if(n==0) return datum;
    else if(n>0) {
        int temp1=d.dan,temp2=d.mjesec,temp3=d.godina;
        for(int i=0; i<n; i++) {
            dajProsliDan(temp1,temp2,temp3);
        }
        if(temp3<1800) throw std::domain_error("Nelegalan datum");
        for(int i=0; i<n; i++) {
            dajProsliDan(datum.dan,datum.mjesec,datum.godina);
        }
    } else if(n<0) {
        int m=-n;
        for(int i=0; i<m; i++) {
            dajSljedeciDan(datum.dan,datum.mjesec,datum.godina);
        }
    }
    return datum;
}

Datum &operator +=(Datum &d,const int n)
{
    return d=d+n;
}

Datum &operator -=(Datum &d,const int n)
{
    return d=d-n;
}

std::ostream& operator<<(std::ostream &cout,const Datum &d)
{
    cout<<d.dan<<". "<<d.DajImeMjeseca()<<" "<<d.godina<<". ("<<d.DajImeDanaUSedmici()<<")";
    return cout;
}
std::istream& operator>>(std::istream &cin, Datum &d)
{
    //ako unos nije u formatu int/int/int tok postaviti u neispravno stanje
    //ako datum nije smislen takodjer
    std::string s;
    std::getline(cin>>std::ws,s);
    std::string dan,mjesec,godina;
    int i=0;
    while(i!=s.length()-1 && s.at(i)!='/') {
        if(s.at(i)<'0' || s.at(i)>'9') {
            cin.setstate(std::ios::failbit);
            return cin;
        }
        dan.push_back(s.at(i));
        i++;
    }
    if(i!=s.length()-1 && s.at(i)=='/') {
        i++;
        while(i!=s.length()-1 && s.at(i)!='/') {
            if(i==s.length()-1 || s.at(i)<'0' || s.at(i)>'9') {
                cin.setstate(std::ios::failbit);
                return cin;
            }
            mjesec.push_back(s.at(i));
            i++;
        }
        if(i!=s.length()-1 && s.at(i)=='/') {
            i++;
            while(i!=s.length()-1) {
                if(s.at(i)<'0' || s.at(i)>'9') {
                    cin.setstate(std::ios::failbit);
                    return cin;
                }
                godina.push_back(s.at(i));
                i++;
            }
            if(i==s.length()-1) {
                godina.push_back(s.at(i));
            }
            if(smislenDatum(std::stoi(dan),std::stoi(mjesec),std::stoi(godina))==false) {
                cin.setstate(std::ios::failbit);
                return cin;
            }
            d.Postavi(std::stoi(dan),std::stoi(mjesec),std::stoi(godina));

        } else {
            cin.setstate(std::ios::failbit);
            return cin;
        }
    } else {
        cin.setstate(std::ios::failbit);
        return cin;
    }

    return cin;
}

int main ()
{

    Datum d1=Datum(18,6,2021);
    Datum d2=Datum(16,Datum::Mjeseci::Oktobar,2021);

    std::cout<<"Danasnji dan je: "<<d1++<<std::endl;
    std::cout<<"Prekosutra je: "<<++d1<<std::endl;
    std::cout<<"Sutra je: "<<--d1<<std::endl;
    std::cout<<"Sutra je: "<<d1--<<std::endl;

    d1.Postavi(1,2,2021);
    std::cout<<"Novi datum d1: "<<d1<<std::endl;
    d1.Postavi(1,Datum::Mjeseci::Januar,2021);
    std::cout<<"Novi datum d1: "<<d1<<std::endl;

    std::cout<<d1.DajDan() <<std::endl;
    std::cout<<d1.DajMjesec()<<std::endl;
    std::cout<<d1.DajGodinu()<<std::endl;
    std::cout<<d1.DajDanUSedmici()<<std::endl;
    std::cout<<d1.DajImeDanaUSedmici()<<std::endl;
    std::cout<<d1.DajImeMjeseca()<<std::endl;

    d1.Postavi(18,6,2021);
    std::cout<<"Datum za 4 dana: "<<d1+4<<std::endl;
    d1.Postavi(18,6,2021);
    d1+=4;
    std::cout<<"Datum za 4 dana: "<<d1<<std::endl;
    std::cout<<"Danasnji datum: "<<d1-4<<std::endl;
    d1-=4;
    std::cout<<"Datum prije 15 dana: "<<d1<<std::endl;
    d1.Postavi(18,6,2021);

    std::cout<<"Broj dana izmedju dva datuma: "<<d1-d2<<std::endl;
    if(d1==d2) std::cout<<"Jednaki"<<std::endl;
    else std::cout<<"Nisu jednaki"<<std::endl;
    if(d1<d2) std::cout<<"Datum d1 prije datuma d2"<<std::endl;
    else if(d1>d2) std::cout<<"Datum d2 prije datuma d1"<<std::endl;

    return 0;
}
