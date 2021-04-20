#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

//fonction permettant de tester l'existance d'un fichier.
//file: chaine de caract�re qui est le path du fichier
bool is_readable( const std::string &);

// permet d'affichier avec un cadre au début et à la fin tout se permettant de remplir un espace vide
void aff(std::string strd, std::string strm, std::string strf, std::string ch="-", int taille=100);//*2.3);

int menu_championnat();

// affiche les grands titre en les mettant en majuscule et en les encadrants.
void grand_titre(std::string title);

// fonction retournant l'index d'un elt qu'on cherche dans un vecteur
int good_choix_score(int id, std::vector<int> liste_id_renc);
#endif // FONCTIONS_H_INCLUDED
