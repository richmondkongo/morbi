#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <limits>
#include <regex>
#include <unistd.h>

//fonction permettant de tester l'existance d'un fichier.
//file: chaine de caract�re qui est le path du fichier
bool is_readable( const std::string &);

// permet d'affichier avec un cadre au début et à la fin tout se permettant de remplir un espace vide
//void aff(std::string strd, std::string strm, std::string strf, std::string ch="-", int taille=100);//*2.3);
void aff(std::string strd, std::string strm, std::string strf, std::string ch="-", int taille=140);

// affiche les grands titre en les mettant en majuscule et en les encadrants.
void grand_titre(std::string title);

// fonction retournant l'index d'un elt qu'on cherche dans un vecteur
int good_choix_score(int id, std::vector<int> liste_id_renc);

// fonction permettant de se rassurer que le user a bien entré un entier
bool read_choice(int &N);

// fonction permettant de savoir si un string est un nombre ou pas
bool is_int(std::string str);

// fonction affichant le splashscreen: message de depart
void splashscreen(float tps=5.0);
void splashscreen_end(float tps=5.0);
#endif // FONCTIONS_H_INCLUDED
