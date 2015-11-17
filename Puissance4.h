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


class Puissance4 {

public:

    Puissance4();

Puissance4(std::string g);
    ~Puissance4();

    const std::string& get_grille() const ;

    size_t get_grille_size() const ;

    void afficher_grille();

    int placer_pion(int xPos);

    //friend void test(int yPos, int xPos);
    char get_pion(int i);

    bool winner(int xPos);

    size_t grille_size()const;

    void test(int k);;

private:
    bool check(int xPos, int yDir, int xDir);
    int get_yPos(int xPos);
    bool isOnBoard(int x);
    std::string m_grille;
    const int LIGNE = 6;
    const int COLONNE = 7;
    const char m_rond = 'O';
    const char m_croix = 'X';
    const char m_vide = ' ';
    void init();
};

#endif // PUISSANCE4_H_
