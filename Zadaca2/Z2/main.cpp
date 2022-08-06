//TP 2018/2019: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>

void SumaCetiriKvadrata(int n, int &a, int &b, int &c, int &d)
{
    if(n<0) throw std::domain_error("Broj koji se rastavlja mora biti nenegativan");

    int korijen=std::sqrt(n);
    bool nadjen=false;
    int ostatak=0;

    for(int i=korijen; i>=0; i--) {
        int korijen2=std::sqrt(n-i*i);
        for(int j=korijen2; j>=0; j--) {
            int korijen3=std::sqrt(n-i*i-j*j);
            for(int k=korijen3; k>=0; k--) {
                nadjen=false;
                ostatak=n-i*i-j*j-k*k;
                double korijen4=std::sqrt(ostatak);
                if(std::fabs(korijen4-(int)korijen4)<0.00001) {
                    nadjen=true;
                    a=i;
                    b=j;
                    c=k;
                    d=std::sqrt(ostatak);
                    break;
                }
            }
            if(nadjen==true) break;
        }
        if(nadjen==true) break;
    }


}


int main ()
{
    int n=0;
    std::cout<<"Unesite broj: ";
    std::cin>>n;
    int a=0,b=0,c=0,d=0;
    try {
        SumaCetiriKvadrata(n,a,b,c,d);
        std::cout<<"Broj "<<n<<" se moze zapisati kao zbir kvadrata brojeva: "<<a<<", "<<b<<", "<<c<<", "<<d<<".";
    } catch(std::domain_error e) {
        std::cout<<e.what();
    }

    return 0;
}
