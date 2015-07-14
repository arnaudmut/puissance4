/*
 * puissance.h
 *
 *  Created on: 3 déc. 2014
 *      Author: arnaud.mutana
 */

#ifndef PUISSANCE4_H_
#define PUISSANCE4_H_


/**
* @class Puissance4
* @author arnaud
* @date 11/28/14
* @file Puissance4.h
* @brief
*/
#include <vector>
#include <cstdlib>
#include <iostream>

using tab = std::vector<std::vector<char> >;

class Puissance4 {

public:

    Puissance4();

    Puissance4(tab g);

    ~Puissance4();

    const tab &get_grille() const;

    size_t get_grille_size() const;

    void afficher_grille();

    bool placer_pion(int xPos, char pion);

    //friend void test(int yPos, int xPos);
    char get_pion(int i);

    bool winner(int xPos);

private:
    bool check(int xPos, int yDir, int xDir);

    int get_yPos(int xPos);

    bool isOnBoard(int y, int x);

    tab m_grille;

    size_t grille_size() const;

    const int LIGNE = 6;
    const int COLONNE = 7;
    const char m_rond = 'O';
    const char m_croix = 'X';
    const char m_vide = ' ';
};

#endif // PUISSANCE4_H_
