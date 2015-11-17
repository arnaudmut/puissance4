//
// Created by kardudu on 07/07/15.
//

#include "Puissance4.h"
#include <iomanip>






Puissance4::Puissance4():m_grille(42,' '){
}
Puissance4::~Puissance4() {}
const std::string & Puissance4::get_grille() const {
    return m_grille;
}
size_t Puissance4::grille_size() const {
    return m_grille.size();
}

void Puissance4::afficher_grille() {
    std::cout << " -----------------------------" << std::endl;
    for (int i = 0; i < LIGNE; i++) {
        for (int j = 0; j < COLONNE; j++) {
            std::cout << " | " << m_grille.at((COLONNE*i)+j);
        }
        std::cout << " | " << std::endl;
        std::cout << " -----------------------------" << std::endl;
    }
    for (int k = 0; k <= 6; k++) {
        std::cout << std::setw(4) << k;
    }
    std::cout << std::endl;
}
char Puissance4::get_pion(int i) {
    return i == 0 ? this->m_croix : this->m_rond;
}

 int Puissance4::placer_pion(int xPos) {
     int yPos = xPos;
     std::cout<<((LIGNE*COLONNE)-(COLONNE-xPos))<<std::endl;
     if(m_grille.at((LIGNE*COLONNE)-(COLONNE-xPos))==' '){
         m_grille.at((LIGNE*COLONNE)-(COLONNE-xPos))=get_pion(1);
         return (LIGNE*COLONNE)-(COLONNE-xPos);
     } else {
         bool b;
         while (b) {

             if (m_grille.at(yPos) == ' ') {
                 yPos += COLONNE;
             }
             else {
                 b = false;
             }
         }
         //colonne pleine
         if (yPos-COLONNE < 0){

             return -1;
         } else{

         m_grille.at(yPos-COLONNE)=m_rond;
         }
         yPos -=COLONNE;
     }
     std::cout<< "yPos : "<<yPos<<std::endl;
     return  yPos;
}

void Puissance4::test(int xPos) {
    int k = placer_pion(xPos);
    std::cout<<"K : "<<k<<std::endl;
    bool b = winner(k);
}
bool Puissance4::isOnBoard(int x) {
    return x<42 && x >=0;
}
bool Puissance4::check(int yPos, int yDir, int xDir) {
    int c = 0;
    bool b = true;
    while (c < 4){
        std::cout<<" ypos check : "<<yPos<<std::endl;
        int x = yPos + (c*(xDir+yDir));
        bool v = isOnBoard(x);
        if (!v){ return 0;}
        bool b = m_grille.at(yPos) == m_grille.at(x);
        if (!b){ return 0;}
        c++;
    }
    return b;
}
/*
bool Puissance4::check(int xPos, int yDir, int xDir) {
    bool align4;
    for (int y = 0; y < this->LIGNE; y++) {
        for (int x = 0; x < this->COLONNE; x++) {
            //on verifie que trois pions voisins
            align4 = true;
            int c = 0;
            bool same;
            //tant que voisin les 3 pions voisins sont les memes
            while (align4 && c < 4) {
                int yPos = this->get_yPos(xPos);
                if (yPos == -1) {
                    return -1;   //checking for errors
                }
                int lign = yPos + c * yDir;
                int col = xPos + c * xDir;
                same = this->m_grille[yPos][xPos] == this->m_grille[lign][col];
                align4 = isOnBoard(lign, col) && same;
                c++;
            }
            return align4;
        }
    }
}
*/

bool Puissance4::winner(int xPos) {

    bool status;
    // gauche --> droite
    status = this->check(xPos, 0, 1);
    if (status) {
        return status;
    }
    //droite --> gauche
    status = this->check(xPos, 0, -1);
    if (status) {
        return status;
    }
    // bas --> haut
    status = this->check(xPos, -7, 0);
    if (status) {
        return status;
    }
    //haut -->bas
    status = check(xPos,7,0);
    if(status){ return status;};
    //top droite --> bas gauche
    status = this->check(xPos, 7, -1);
    if (status) {
        return status;
    }
    //bas gauche --> top droite
    status = this->check(xPos, -7, 1);
    if (status) {
        return status;
    }
    //top gauche --> bas droite
    status = this->check(xPos, 7, 1);
    if (status) {
        return status;
    }
    //bas droite --> haut gauche
    status = this->check(xPos, -7, -1);
    if (status) {
        return status;
    }else {
        return false;
    }
}