//TP 2018/2019: Zadaća 1, Zadatak 3
#include <iostream>
#include <deque>
#include <iomanip>

typedef std::deque<std::deque<double>> Matrica;

Matrica KreirajMatricu(int redovi, int kolone)
{
    return Matrica(redovi,std::deque<double> (kolone));
}


Matrica EkspanzijaMatrice(Matrica a,int p,int q)
{

    if(p<=0 || q<=0) throw std::domain_error("Nelegalni parametri");
    if(a.size()==0) throw std::domain_error ("Nekorektna matrica");

    //ako a nema formu matrice
    int br_elemenata_reda=a.at(0).size();
    bool nekorektna=false;
    for(int i=0; i<a.size(); i++) {
        if(a.at(i).size()!=br_elemenata_reda) {
            nekorektna=true;
            break;
        }
    }
    if(nekorektna==true) throw std::domain_error ("Nekorektna matrica");

    Matrica mat=KreirajMatricu(a.size(),br_elemenata_reda);
    for(int i=0; i<a.size(); i++) {
        for(int j=0; j<br_elemenata_reda; j++) {
            mat.at(i).at(j)=a.at(i).at(j);
        }
    }


    for(int i=0; i<a.size(); i++) {
        for(int j=0; j<br_elemenata_reda; j++) {
            if(q>1)
                mat.at(i*p).insert(mat.at(i*p).begin()+(j*q)+1,q-1,a.at(i).at(j));
        }
        //kad se zavrsi upis jednog reda, insertujemo pomocni dek ispod p-1 puta (ako je p>1, u suprotnom nista)
        if(p>1) {
            std::deque<double> pomocni=mat.at(i*p);
            mat.insert(mat.begin()+(i*p)+1,p-1,pomocni);
        }
    }

    return mat;
}


int main ()
{
    int m=0,n=0;
    std::cout<<"Unesite broj redova matrice A (m): ";
    std::cin>>m;
    std::cout<<"Unesite broj kolona matrice A (n): ";
    std::cin>>n;

    Matrica a=KreirajMatricu(m,n);

    for(int i=0; i<m; i++) {
        std::cout<<"Unesite "<<i+1<<". red matrice: ";
        for(int j=0; j<n; j++) {
            double element=0;
            std::cin>>element;
            a.at(i).at(j)=element;
        }
    }
    int p=0,q=0;
    std::cout<<"Unesite dimenziju ekspanzije p: ";
    std::cin>>p;
    std::cout<<"Unesite dimenziju ekspanzije q: ";
    std::cin>>q;
    std::cout<<"Ekspanzija matrice A glasi: "<<std::endl;

    try {
        Matrica mat=EkspanzijaMatrice(a,p,q);

        for(int i=0; i<m*p; i++) {
            for(int j=0; j<n*q; j++) {
                std::cout<<std::fixed<<std::setprecision(2)<<mat.at(i).at(j)<<" ";
            }
            std::cout<<std::endl;
        }
    } catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what();
    }
    return 0;
}
