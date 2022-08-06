//TP 2018/2019: Zadaća 3, Zadatak 1
#include <iostream>
#include <vector>
#include <functional>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <exception>

bool Kriterij(std::pair<double,double> x1,std::pair<double,double> x2)
{
    return x1.first<x2.first;
}

std::function<double(double)> LinearnaInterpolacija(std::vector<std::pair<double,double>> cvorovi)
{
    for(int i=0; i<cvorovi.size(); i++) {
        for(int j=i+1; j<cvorovi.size(); j++) {
            if(std::fabs(cvorovi.at(i).first-cvorovi.at(j).first)<=0.01)
                throw std::domain_error("Neispravni cvorovi");    //ako ima cvorova sa istom x koordinatom
        }
    }

    //sortirati vektor po x koordinati
    std::sort(cvorovi.begin(),cvorovi.end(),Kriterij);

    return[cvorovi](double x) {
        if(x<cvorovi.at(0).first || x>cvorovi.at(cvorovi.size()-1).first) throw std::range_error("Argument izvan opsega");
        if(std::fabs(x-cvorovi.at(cvorovi.size()-1).first)<0.00001) return cvorovi.at(cvorovi.size()-1).second;
        double f=0;
        double x1=0,x2=0,y1=0,y2=0;

        std::vector<double> pomocni_x,pomocni_y;
        for(int i=0; i<cvorovi.size(); i++) {
            pomocni_x.push_back(cvorovi.at(i).first);//vektor x koordinata
            pomocni_y.push_back(cvorovi.at(i).second);//vektor y koordinata
        }


        auto donja_granica=std::lower_bound(pomocni_x.begin(),pomocni_x.end(),x);
        auto gornja_granica=std::upper_bound(pomocni_x.begin(),pomocni_x.end(),x);

        //  x1=*(donja_granica);
        x2=*gornja_granica;

        int indeks_y1=donja_granica-pomocni_x.begin();
        int indeks_y2=gornja_granica-pomocni_x.begin();

        // y1=cvorovi.at(indeks_y1).second;
        y2=cvorovi.at(indeks_y2).second;

        for(int i=cvorovi.size()-1; i>=0; i--) {
            if(x>=cvorovi.at(i).first) {
                x1=cvorovi.at(i).first;
                y1=cvorovi.at(i).second;
                break;
            }
        }

        // for(int i=0; i<cvorovi.size(); i++) {
        //     if(x<cvorovi.at(i).first) {
        //         x2=cvorovi.at(i).first;
        //         y2=cvorovi.at(i).second;
        //         break;
        //     }
        // }

        f=y1+((y2-y1)/(x2-x1))*(x-x1);

        return f;
    };
}


std::function<double(double)> LinearnaInterpolacija(std::function<double(double)> f,double xmin, double xmax, double korak)
{

    if(xmin>xmax || korak<=0) throw std::domain_error("Nekorektni parametri");
    //kreiramo cvorove na intervalu [xmin,xmax] sa korakom korak i za y uzimati vrijednosti y iz zadane funkcije
    //zatim uraditi isto sto i u prvoj verziji
    std::vector<std::pair<double,double>> cvorovi;
    double y=f(xmin);
    cvorovi.push_back(std::make_pair(xmin,y));
    xmin+=korak;
    while(xmin<xmax) {
        cvorovi.push_back(std::make_pair(xmin,f(xmin)));
        xmin+=korak;
    }

    for(int i=0; i<cvorovi.size(); i++) {
        for(int j=i+1; j<cvorovi.size(); j++) {
            if(std::fabs(cvorovi.at(i).first-cvorovi.at(j).first)<=0.01)
                throw std::domain_error("Neispravni cvorovi");    //ako ima cvorova sa istom x koordinatom
        }
    }

    return[cvorovi](double x) {
        if(x<cvorovi.at(0).first || x>cvorovi.at(cvorovi.size()-1).first) throw std::range_error("Argument izvan opsega");
        if(std::fabs(x-cvorovi.at(cvorovi.size()-1).first)<0.00001) return cvorovi.at(cvorovi.size()-1).second;
        double f=0;
        double x1=0,x2=0,y1=0,y2=0;

        std::vector<double> pomocni_x,pomocni_y;
        for(int i=0; i<cvorovi.size(); i++) {
            pomocni_x.push_back(cvorovi.at(i).first);//vektor x koordinata
            pomocni_y.push_back(cvorovi.at(i).second);//vektor y koordinata
        }


        auto donja_granica=std::lower_bound(pomocni_x.begin(),pomocni_x.end(),x);
        auto gornja_granica=std::upper_bound(pomocni_x.begin(),pomocni_x.end(),x);

        //  x1=*(donja_granica);
        x2=*gornja_granica;

        int indeks_y1=donja_granica-pomocni_x.begin();
        int indeks_y2=gornja_granica-pomocni_x.begin();

        // y1=cvorovi.at(indeks_y1).second;
        y2=cvorovi.at(indeks_y2).second;

        for(int i=cvorovi.size()-1; i>=0; i--) {
            if(x>=cvorovi.at(i).first) {
                x1=cvorovi.at(i).first;
                y1=cvorovi.at(i).second;
                break;
            }
        }

        f=y1+((y2-y1)/(x2-x1))*(x-x1);

        return f;
    };

}


int main ()
{
    std::string unos;
    int n=0,opcija=0;
    std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): "<<std::endl;
    std::cin>>opcija;
    if(opcija==1) {
        std::cout<<"Unesite broj cvorova: "<<std::endl;
        std::cin>>n;
        std::cout<<"Unesite cvorove kao parove x i y:"<<std::endl;
        std::vector<std::pair<double,double>> cvorovi;
        for(int i=0; i<n; i++) {
            double x=0,y=0;
            std::cin>>x>>y;
            cvorovi.push_back(std::make_pair(x,y));
        }

        do {
            std::function<double(double)> f;
             try {
                f=LinearnaInterpolacija(cvorovi);
            } catch(std::range_error izuzetak) {
                std::cout<<izuzetak.what()<<"."<<std::endl;
                return 0;
            } catch(std::domain_error izuzetak3) {
                std::cout<<izuzetak3.what()<<"."<<std::endl;
                return 0;
            }
            
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): "<<std::endl;
            std::cin>>unos;
           

            if(unos!="kraj") {
                try {
                    std::cout<<"f("<<unos<<") = "<<f(std::stod(unos))<<std::endl;
                } catch(std::range_error izuzetak2) {
                    std::cout<<izuzetak2.what()<<"."<<std::endl;
                }
            }



        } while(unos!="kraj");
    } else if(opcija==2) {
        std::cout<<"Unesite krajeve intervala i korak: "<<std::endl;
        double xmin=0,xmax=0,korak=0;
        std::cin>>xmin>>xmax>>korak;
        std::function<double(double)> f;
        do {
            try {
                f=LinearnaInterpolacija([](double x) {
                    return x*x+std::sin(x);
                },xmin,xmax,korak);
            } catch(std::range_error izuzetak) {
                std::cout<<izuzetak.what()<<"."<<std::endl;
                return 0;
            } catch(std::domain_error izuzetak3) {
                std::cout<<izuzetak3.what()<<"."<<std::endl;
                return 0;
            }

            std::cout<<"Unesite argument (ili \"kraj\" za kraj): "<<std::endl;
            std::cin>>unos;


            if(unos!="kraj") {
                try {
                    std::cout<<"f("<<unos<<") = "<<std::stod(unos)*std::stod(unos)+std::sin(std::stod(unos))<<" f_approx("<<unos<<") = "<<
                             f(std::stod(unos))<<std::endl;
                } catch(std::range_error izuzetak2) {
                    std::cout<<izuzetak2.what()<<"."<<std::endl;
                }
            }

        } while(unos!="kraj");

    }

    return 0;
}
