//TP 2018/2019: Zadaća 1, Zadatak 2
#include <iostream>
#include <vector>
#include <array>
#include <cmath>

typedef std::vector<std::vector<double>> Matrica;

Matrica KreirajMatricu(int redovi, int kolone)
{
    return Matrica(redovi,std::vector<double> (kolone));
}

bool SveNuleUKoloni(Matrica mat, int kolona)
{
    bool flag=true;
    for(int i=0; i<mat.size(); i++) {
        if(std::fabs(mat.at(i).at(kolona))>1e-10) {
            flag=false;
            break;
        }
    }
    return flag;
}

bool SveNuleURedu(Matrica mat, int red)
{
    bool flag=true;
    for(int j=0; j<mat.at(0).size(); j++) {
        if(std::fabs(mat.at(red).at(j))>1e-10) {
            flag=false;
            break;
        }
    }
    return flag;
}

std::array<int,4> RasponMatrice(std::vector<std::vector<double>> mat)
{
    //provjera validnosti matrice
    if(mat.size()==0) throw std::domain_error("Raspon nije definiran za nul-matricu ili praznu matricu");

    int br_kolona=mat.at(0).size();
    for(int i=0; i<mat.size(); i++) if(mat.at(i).size()!=br_kolona) throw std::domain_error("Nekorektna matrica");

    bool flag=true;
    for(int i=0; i<mat.size(); i++) {
        for(int j=0; j<br_kolona; j++) {
            if(std::fabs(mat.at(i).at(j))>1e-10) {
                flag=false;
                break;
            }
        }
        if(flag==false) break;
    }
    if(flag==true) throw std::domain_error("Raspon nije definiran za nul-matricu ili praznu matricu");

    std::array<int,4> niz;
    int i_min=0, j_min=0, i_max=mat.size()-1, j_max=br_kolona-1;

    bool i_min_nadjen=false;
    for(int i=0; i<mat.size(); i++) {
        if(SveNuleURedu(mat,i)==false) i_min_nadjen=true;
        if(SveNuleURedu(mat,i)==true && i_min_nadjen==false) {
            i_min++;
        }
    }

    bool i_max_nadjen=false;
    for(int i=mat.size()-1; i>0; i--) {
        if(SveNuleURedu(mat,i)==false) i_max_nadjen=true;
        if(SveNuleURedu(mat,i)==true && i_max_nadjen==false) {
            i_max--;
        }
    }

    bool j_min_nadjen=false;
    for(int j=0; j<br_kolona; j++) {
        if(SveNuleUKoloni(mat,j)==false) j_min_nadjen=true;
        if(SveNuleUKoloni(mat,j)==true && j_min_nadjen==false) {
            j_min++;
        }
    }

    bool j_max_nadjen=false;
    for(int j=br_kolona-1; j>0; j--) {
        if(SveNuleUKoloni(mat,j)==false) j_max_nadjen=true;
        if(SveNuleUKoloni(mat,j)==true && j_max_nadjen==false) {
            j_max--;
        }
    }
    niz.at(0)=i_min+1;
    niz.at(1)=j_min+1;
    niz.at(2)=i_max+1;
    niz.at(3)=j_max+1;

    return niz;
}


int main ()
{
    std::array<int,4> niz;
    std::cout<<"Unesite dimenziju matrice u formatu m x n: ";
    int m=0,n=0;
    char x='x';
    std::cin>>m>>x>>n;
    Matrica mat=KreirajMatricu(m,n);

    std::cout<<"Unesite elemente matrice: "<<std::endl;
    for(int i=0; i<m; i++) {
        std::cout<<"Elementi "<<i+1<<". reda: ";
        for(int j=0; j<n; j++) {
            double element=0;
            std::cin>>element;
            mat.at(i).at(j)=element;
        }
    }

    try {
        niz=RasponMatrice(mat);
        std::cout<<std::endl<<"Raspon matrice je od ("<<niz.at(0)<<","<<niz.at(1)<<") do ("<<niz.at(2)<<","<<niz.at(3)<<").";

    } catch(std::domain_error izuzetak) {
        std::cout<<"IZUZETAK: "<<izuzetak.what()<<"!";
    }

    return 0;
}
