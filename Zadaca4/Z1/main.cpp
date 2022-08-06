//TP 2018/2019: Zadaća 4, Zadatak 1
#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
#include <memory>
#include <algorithm>

typedef std::pair<double,double> Tacka;

class Trougao
{
    Tacka t1;
    Tacka t2;
    Tacka t3;

public:

    Trougao (Tacka a,Tacka b,Tacka c)
    {
        if(Orijentacija(a,b,c)==0) throw std::domain_error("Nekorektne pozicije tjemena");
        t1.first=a.first;
        t2.first=b.first;
        t3.first=c.first;
        t1.second=a.second;
        t2.second=b.second;
        t3.second=c.second;
    }

    static int Orijentacija(Tacka t1,Tacka t2, Tacka t3);

    void Postavi(Tacka a,Tacka b,Tacka c)
    {
        if(Orijentacija(a,b,c)==0) throw std::domain_error("Nekorektne pozicije tjemena");
        t1.first=a.first;
        t2.first=b.first;
        t3.first=c.first;
        t1.second=a.second;
        t2.second=b.second;
        t3.second=c.second;
    }

    void Postavi(int t,Tacka tacka)
    {
        if(t!=1 && t!=2 && t!=3) throw std::range_error("Nekorektan indeks");
        if(t==1) {
            t1.first=tacka.first;
            t1.second=tacka.second;
        } else if(t==2) {
            t2.first=tacka.first;
            t2.second=tacka.second;
        } else if(t==3) {
            t3.first=tacka.first;
            t3.second=tacka.second;
        }
    }

    Tacka DajTjeme(int t)const
    {
        if(t!=1 && t!=2 && t!=3) throw std::range_error("Nekorektan indeks");
        if(t==1) return t1;
        else if(t==2) return t2;
        else return t3;
    }

    double DajStranicu(int t)const
    {
        //vraca duzinu stranice koja se nalazi naspram tjemena t
        if(t!=1 && t!=2 && t!=3) throw std::range_error("Nekorektan indeks");
        double stranica=0;
        if(t==1) return std::sqrt((t2.first-t3.first)*(t2.first-t3.first)+(t2.second-t3.second)*(t2.second-t3.second));
        else if(t==2) return std::sqrt((t1.first-t3.first)*(t1.first-t3.first)+(t1.second-t3.second)*(t1.second-t3.second));
        else if(t==3) return std::sqrt((t1.first-t2.first)*(t1.first-t2.first)+(t1.second-t2.second)*(t1.second-t2.second));
        return stranica;
    }

    double DajUgao(int t)const
    {
        //vraca ugao u radijanima
        if(t!=1 && t!=2 && t!=3) throw std::range_error("Nekorektan indeks");
        //nadjemo duzine stranica
        double t1t2=DajStranicu(3);
        double t1t3=DajStranicu(2);
        double t2t3=DajStranicu(1);
        double a=0,b=0,c=0;
        if(t==1) {
            a=t1t2;
            b=t1t3;
            c=t2t3;
        } else if(t==2) {
            a=t1t2;
            b=t2t3;
            c=t1t3;
        } else if(t==3) {
            a=t2t3;
            b=t1t3;
            c=t1t2;
        }
        return std::acos((a*a+b*b-c*c)/(2*a*b));
    }

    Tacka DajCentar()const
    {
        Tacka t;
        t.first=(t1.first+t2.first+t3.first)/3;
        t.second=(t1.second+t2.second+t3.second)/3;
        return t;
    }

    double DajObim()const
    {
        return DajStranicu(1)+DajStranicu(2)+DajStranicu(3);
    }

    double DajPovrsinu()const
    {
        return std::fabs(t1.first*(t2.second-t3.second)-t2.first*(t1.second-t3.second)+t3.first*(t1.second-t2.second))/2;
    }

    bool DaLiJePozitivnoOrijentiran()const
    {
        if(Orijentacija(t1,t2,t3)==1) return true;
        else return false;
    }

    bool DaLiJeUnutra(Tacka t)const
    {
        //ako lezi na stranici false
        if(Orijentacija(t1,t2,t)==0 || Orijentacija(t1,t3,t)==0 || Orijentacija(t2,t3,t)==0) return false;
        else if(Orijentacija(t1,t2,t3)<0 && Orijentacija(t1,t2,t)<0 && Orijentacija(t2,t3,t)<0 && Orijentacija(t3,t1,t)<0)
            return true;
        return false;
    }

    void Ispisi()const
    {
        std::cout<<"(("<<t1.first<<","<<t1.second<<"),("<<t2.first<<","<<t2.second<<"),("<<t3.first<<","<<t3.second<<"))";
    }

    void Transliraj(double x,double y)
    {
        //translira za x jedinica horizontalno i y jedinica vertikalno
        t1.first+=x;
        t2.first+=x;
        t3.first+=x;
        t1.second+=y;
        t2.second+=y;
        t3.second+=y;

    }
    void Centriraj(Tacka t)
    {
        //translira tako da se centar nadje u tacki t
        Tacka centar=DajCentar();
        t1.first+=t.first-centar.first;
        t1.second+=t.second-centar.second;
        t2.first+=t.first-centar.first;
        t2.second+=t.second-centar.second;
        t3.first+=t.first-centar.first;
        t3.second+=t.second-centar.second;


    }
    void Rotiraj(Tacka tc,double radijani)
    {
        //rotira oko tacke t za navedeni ugao
        double a1=tc.first+((t1.first-tc.first)*std::cos(radijani))-((t1.second-tc.second)*std::sin(radijani));
        double a2=tc.second+((t1.first-tc.first)*std::sin(radijani))+((t1.second-tc.second)*std::cos(radijani));
        Postavi(1,std::make_pair(a1,a2));
        double b1=tc.first+((t2.first-tc.first)*std::cos(radijani))-((t2.second-tc.second)*std::sin(radijani));
        double b2=tc.second+((t2.first-tc.first)*std::sin(radijani))+((t2.second-tc.second)*std::cos(radijani));
        Postavi(2,std::make_pair(b1,b2));
        double c1=tc.first+((t3.first-tc.first)*std::cos(radijani))-((t3.second-tc.second)*std::sin(radijani));
        double c2=tc.second+((t3.first-tc.first)*std::sin(radijani))+((t3.second-tc.second)*std::cos(radijani));
        Postavi(3,std::make_pair(c1,c2));
    }

    void Rotiraj(double radijani)
    {
        Rotiraj(DajCentar(),radijani);
    }

    void Skaliraj(Tacka centar,double k)
    {
        //tacka centar ce ostati nepromijenjena
        if(k==0) throw std::domain_error("Nekorektan faktor skaliranja");
        int indeks=0;
        if(std::fabs(centar.first-t1.first)<0.00001 && std::fabs(centar.second-t1.second)<0.00001) indeks=1;
        else if(std::fabs(centar.first-t2.first)<0.00001 && std::fabs(centar.second-t2.second)<0.00001) indeks=2;
        else if(std::fabs(centar.first-t3.first)<0.00001 && std::fabs(centar.second-t3.second)<0.00001) indeks=3;

        if(indeks==1) {
            Postavi(2,std::make_pair(centar.first+k*(t2.first-centar.first),centar.second+k*(t2.second-centar.second)));
            Postavi(3,std::make_pair(centar.first+k*(t3.first-centar.first),centar.second+k*(t3.second-centar.second)));
        } else if(indeks==2) {
            Postavi(1,std::make_pair(centar.first+k*(t1.first-centar.first),centar.second+k*(t1.second-centar.second)));
            Postavi(3,std::make_pair(centar.first+k*(t3.first-centar.first),centar.second+k*(t3.second-centar.second)));
        } else if(indeks==3) {
            Postavi(1,std::make_pair(centar.first+k*(t1.first-centar.first),centar.second+k*(t1.second-centar.second)));
            Postavi(2,std::make_pair(centar.first+k*(t2.first-centar.first),centar.second+k*(t2.second-centar.second)));
        } else {
            Postavi(1,std::make_pair(centar.first+k*(t1.first-centar.first),centar.second+k*(t1.second-centar.second)));
            Postavi(2,std::make_pair(centar.first+k*(t2.first-centar.first),centar.second+k*(t2.second-centar.second)));
            Postavi(3,std::make_pair(centar.first+k*(t3.first-centar.first),centar.second+k*(t3.second-centar.second)));
        }

    }

    void Skaliraj(double k)
    {
        Skaliraj(DajCentar(),k);
    }

    friend bool DaLiSuPodudarni(Trougao t1,Trougao t2);
    friend bool DaLiSuSlicni(Trougao t1,Trougao t2);
    friend bool DaLiSuIdenticni(Trougao t1,Trougao t2);

};

bool DaLiSuIdenticni(Trougao t1,Trougao t2)
{
    //tjemena u istim tackama
    Tacka a1=t1.DajTjeme(1);
    Tacka a2=t1.DajTjeme(2);
    Tacka a3=t1.DajTjeme(3);
    Tacka b1=t2.DajTjeme(1);
    Tacka b2=t2.DajTjeme(2);
    Tacka b3=t2.DajTjeme(3);

    if(std::fabs(a1.first-b1.first)<0.0001 && std::fabs(a1.second-b1.second)<0.0001) {
        if(std::fabs(a2.first-b2.first)<0.0001 && std::fabs(a2.second-b2.second)<0.0001) {
            if(std::fabs(a3.first-b3.first)<0.0001 && std::fabs(a3.second-b3.second)<0.0001) return true;
        } else if(std::fabs(a2.first-b3.first)<0.0001 && std::fabs(a2.second-b3.second)<0.0001) {
            if(std::fabs(a3.first-b2.first)<0.0001 && std::fabs(a3.second-b2.second)<0.0001) return true;
        }
    } else if(std::fabs(a1.first-b2.first)<0.0001 && std::fabs(a1.second-b2.second)<0.0001) {
        if(std::fabs(a2.first-b2.first) && std::fabs(a2.second-b2.second)<0.0001) {
            if(std::fabs(a3.first-b3.first)<0.0001 && std::fabs(a3.second-b3.second)<0.0001) return true;
        } else if(std::fabs(a2.first-b3.first)<0.0001 && std::fabs(a2.second-b3.second)<0.0001) {
            if(std::fabs(a3.first-b2.first)<0.0001 && std::fabs(a3.second-b2.second)<0.0001) return true;
        }
    } else if(std::fabs(a1.first-b3.first)<0.0001 && std::fabs(a1.second-b3.second)<0.0001) {
        if(std::fabs(a2.first-b1.first)<0.0001 && std::fabs(a2.second-b1.second)<0.0001) {
            if(std::fabs(a3.first-b2.first)<0.0001 && std::fabs(a3.second-b2.second)<0.0001) return true;
        } else if(std::fabs(a2.first-b2.first)<0.0001 && std::fabs(a2.second-b2.second)<0.0001) {
            if(std::fabs(a3.first-b1.first)<0.0001 && std::fabs(a3.second-b1.second)<0.0001) return true;
        }
    }

    return false;
}

bool DaLiSuPodudarni(Trougao t1,Trougao t2)
{
    //duzine stranica iste i odgovarajuci uglovi jednaki
    double a1=t1.DajStranicu(1);
    double a2=t1.DajStranicu(2);
    double a3=t1.DajStranicu(3);
    double b1=t2.DajStranicu(1);
    double b2=t2.DajStranicu(2);
    double b3=t2.DajStranicu(3);

    double u1=t1.DajUgao(1);
    double u2=t1.DajUgao(2);
    double u3=t1.DajUgao(3);
    double v1=t2.DajUgao(1);
    double v2=t2.DajUgao(2);
    double v3=t2.DajUgao(3);


    std::vector<double> prvi,drugi;
    prvi.push_back(a1);
    prvi.push_back(a2);
    prvi.push_back(a3);
    drugi.push_back(b1);
    drugi.push_back(b2);
    drugi.push_back(b3);

    std::sort(prvi.begin(),prvi.end());
    std::sort(drugi.begin(),drugi.end());

    for(int i=0; i<3; i++) {
        if(std::fabs(prvi.at(i)-drugi.at(i))>0.0001) return false;
    }

    return true;
}

bool DaLiSuSlicni(Trougao t1,Trougao t2)
{
    double a1=t1.DajStranicu(1);
    double a2=t1.DajStranicu(2);
    double a3=t1.DajStranicu(3);
    double b1=t2.DajStranicu(1);
    double b2=t2.DajStranicu(2);
    double b3=t2.DajStranicu(3);

    std::vector<double> prvi,drugi;
    prvi.push_back(a1);
    prvi.push_back(a2);
    prvi.push_back(a3);
    drugi.push_back(b1);
    drugi.push_back(b2);
    drugi.push_back(b3);

    std::sort(prvi.begin(),prvi.end());
    std::sort(drugi.begin(),drugi.end());

    double odnos1=prvi.at(0)/drugi.at(0);
    double odnos2=prvi.at(1)/drugi.at(1);
    double odnos3=prvi.at(2)/drugi.at(2);

    if(std::fabs(odnos1-odnos2)>0.0001 || std::fabs(odnos1-odnos3)>0.0001 || std::fabs(odnos2-odnos3)>0.0001) return false;

    return true;
}

int Trougao::Orijentacija(Tacka t1,Tacka t2,Tacka t3)
{
    double vr=t1.first*(t2.second-t3.second)-t2.first*(t1.second-t3.second)+t3.first*(t1.second-t2.second);
    if(std::fabs(vr)<0.000000001) return 0;
    if(vr<0) return -1;
    else return 1;
}

int main ()
{ 
  
    int n=0;
    std::cout<<"Unesite broj trouglova: ";
    std::cin>>n;
    std::vector<std::shared_ptr<Trougao>> trouglovi;
    for(int i=1; i<=n; i++) {
        std::cout<<"Unesite vrhove "<<i<<". trougla [x1 y1 x2 y2 x3 y3]: ";
        double x1=0,y1=0,x2=0,y2=0,x3=0,y3=0;
        std::cin>>x1;
        std::cin>>y1;
        std::cin>>x2;
        std::cin>>y2;
        std::cin>>x3;
        std::cin>>y3;
        Tacka t1=std::make_pair(x1,y1);
        Tacka t2=std::make_pair(x2,y2);
        Tacka t3=std::make_pair(x3,y3);

        try {
            trouglovi.push_back(std::make_shared<Trougao>(t1,t2,t3));
        } catch(std::domain_error izuzetak) {
            std::cout<<izuzetak.what()<<", ponovite unos!"<<std::endl;
            i--;
        }
    }
    std::cout<<std::endl;
    std::cout<<"Trouglovi prije transformacija:"<<std::endl;
    for(int i=0; i<trouglovi.size(); i++) {
        trouglovi.at(i)->Ispisi();
        std::cout<<std::endl;
    }

std::cin.ignore(1000,'\n');
    std::cout<<std::endl;
    std::cout<<"Unesite vektor translacije [dx dy]: ";
    double x=0,y=0;
    std::cin>>x;
    std::cin>>y;
    std::cout<<"Unesite ugao rotacije: ";
    double ugao=0;
    std::cin>>ugao;
    std::cout<<"Unesite faktor skaliranja: "<<std::endl;
    double k=0;
    std::cin>>k;

    std::transform(trouglovi.begin(),trouglovi.end(),trouglovi.begin(),[x,y](std::shared_ptr<Trougao> t) {
        t->Transliraj(x,y);
        return t;
    });
    std::transform(trouglovi.begin(),trouglovi.end(),trouglovi.begin(),[ugao](std::shared_ptr<Trougao> t) {
        t->Rotiraj(ugao);
        return t;
    });

    std::transform(trouglovi.begin(),trouglovi.end(),trouglovi.begin(),[k](std::shared_ptr<Trougao> t) {
        t->Skaliraj(t->DajTjeme(1),k);
        return t;
    });


//sortiranje po povrsini u rastuci poredak
    std::sort(trouglovi.begin(),trouglovi.end(),[](std::shared_ptr<Trougao> t1, std::shared_ptr<Trougao> t2) {
        return t1->DajPovrsinu()<t2->DajPovrsinu();
    });
    std::cout<<"Trouglovi nakon transformacija i sortiranja:"<<std::endl;

//ispis sa foreach
    std::for_each(trouglovi.begin(),trouglovi.end(),[](std::shared_ptr<Trougao> t) {
        t->Ispisi();
        std::cout<<std::endl;
    });
    std::cout<<std::endl;

    std::cout<<"Vrhovi trougla sa najmanjim obimom: ";
    auto it=std::min_element(trouglovi.begin(),trouglovi.end(),[](std::shared_ptr<Trougao> t1,std::shared_ptr<Trougao> t2) {
        return t1->DajObim()<t2->DajObim();
    });
    (*it)->Ispisi();
    std::cout<<std::endl;
    std::cout<<std::endl;
    //NE UBACIVATI DUPLE PAROVE
    std::vector<std::pair<Trougao,Trougao>> paroviIdenticnih;
    std::vector<std::pair<Trougao,Trougao>> paroviPodudarnih;
    std::vector<std::pair<Trougao,Trougao>> paroviSlicnih;

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(DaLiSuIdenticni(*trouglovi.at(i),*trouglovi.at(j))==true) {
                paroviIdenticnih.push_back(std::make_pair(*trouglovi.at(i),*trouglovi.at(j)));
            }
        }
    }


    if(paroviIdenticnih.size()>0) {
        std::cout<<"Parovi identicnih trouglova:"<<std::endl;
        std::for_each(paroviIdenticnih.begin(),paroviIdenticnih.end(),[](std::pair<Trougao,Trougao> par) {
            par.first.Ispisi();
            std::cout<<" i ";
            par.second.Ispisi();
            std::cout<<std::endl;
        });
    } else std::cout<<"Nema identicnih trouglova!"<<std::endl;
    std::cout<<std::endl;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(DaLiSuPodudarni(*trouglovi.at(i),*trouglovi.at(j))==true)
                paroviPodudarnih.push_back(std::make_pair(*trouglovi.at(i),*trouglovi.at(j)));
        }
    }
    if(paroviPodudarnih.size()>0) {
        std::cout<<"Parovi podudarnih trouglova:"<<std::endl;
        std::for_each(paroviPodudarnih.begin(),paroviPodudarnih.end(),[](std::pair<Trougao,Trougao> par) {
            par.first.Ispisi();
            std::cout<<" i ";
            par.second.Ispisi();
            std::cout<<std::endl;
        });
    } else std::cout<<"Nema podudarnih trouglova!"<<std::endl;
    std::cout<<std::endl;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(DaLiSuSlicni(*trouglovi.at(i),*trouglovi.at(j))==true)
                paroviSlicnih.push_back(std::make_pair(*trouglovi.at(i),*trouglovi.at(j)));
        }
    }

    if(paroviSlicnih.size()>0) {
        std::cout<<"Parovi slicnih trouglova:"<<std::endl;
        std::for_each(paroviSlicnih.begin(),paroviSlicnih.end(),[](std::pair<Trougao,Trougao> par) {
            par.first.Ispisi();
            std::cout<<" i ";
            par.second.Ispisi();
            std::cout<<std::endl;
        });
    } else std::cout<<"Nema slicnih trouglova!"<<std::endl;
    std::cout<<std::endl;
    return 0;

    
}
