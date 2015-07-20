//
// Created by kardudu on 07/07/15.
//

#include "Puissance4.h"
#include <iomanip>



Puissance4::Puissance4(tab g) : m_grille(g) {}
Puissance4::Puissance4() : m_grille(LIGNE,std::vector<char>(COLONNE,m_vide)) {}
Puissance4::~Puissance4() {}
const tab & Puissance4::get_grille() const {
    return m_grille;
}
size_t Puissance4::get_grille_size() const {
    return grille_size();
}

size_t Puissance4::grille_size()const {
    size_t taille = 0 ;
    for (auto const& i : m_grille) {
        taille += i.size();
    }
    return taille;
}

void Puissance4::afficher_grille() {
    std::cout << " -----------------------------" << std::endl;
    for (int i = 0; i < LIGNE; i++) {
        for (int j = 0; j < COLONNE; j++) {
            std::cout << " | " << m_grille[i][j];
        }
        std::cout << " | " << std::endl;
        std::cout << " -----------------------------" << std::endl;
    }
    for (int k = 0; k <= 6; k++) {
        std::cout << std::setw(4) << k;
    }
    std::cout << std::endl;
}

int Puissance4::get_yPos(int xPos) {
    int yPos = 0  ; //ligne
    bool colPleine = (m_grille[yPos][xPos] == m_vide);
    if (colPleine) {
        //on cherche la case m_vide a y postion pour placer le pion
        while (this->m_grille[yPos][xPos] == m_vide && yPos < this->LIGNE) {
            //!< si la dernier case est m_vide aussi
            if (yPos == LIGNE) {
                yPos++;
                continue;
            }
            yPos++;
        }
        return yPos;
    } else {
        return -1;
    }
}

bool Puissance4::placer_pion(int xPos, char pion) {
    int yPos = this->get_yPos(xPos);
    if (yPos != -1) {
        this->m_grille[yPos-1][xPos] = pion;
        return true;
    } else {
        return false;
    }
}

//void Puissance4::test(int yPos, int xPos) {
//    m_grille[yPos][xPos] = get_pion(0);
//}
/**
 * @param :
 */
bool Puissance4::check(int xPos, int yDir, int xDir) {
    bool align4;
    for (int y = 0; y < this->LIGNE; y++) {
        for (int x = 0; x < this->COLONNE; x++) {
            //on verifie que trois pion voisins
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

char Puissance4::get_pion(int i) {
    if (i == 0) {
        return this->m_croix;
    } else {
        return this->m_rond;
    }
}

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
    status = this->check(xPos, -1, 0);
    if (status) {
        return status;
    }
    //top droite --> bas gauche
    status = this->check(xPos, 1, -1);
    if (status) {
        return status;
    }
    //bas gauche --> top droite
    status = this->check(xPos, -1, 1);
    if (status) {
        return status;
    }
    //top gauche --> bas droite
    status = this->check(xPos, 1, 1);
    if (status) {
        return status;
    }
    //bas droite --> haut gauche
    status = this->check(xPos, 1, -1);
    if (status) {
        return status;
    }else {
        return false;
    }
}

bool Puissance4::isOnBoard(int y, int x) {
    return ((0 <= y && y < this->LIGNE) && (0 <= x && x < this->COLONNE));
}

