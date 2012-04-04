#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;
using std::string;

#define MESSAGENBCHAR 25

/* Affichage de message */
void Message(string cla, string func, string msg);
void ErrorMessage(string cla, string func, string msg);
void Message(string msg);
void ErrorMessage(string msg);


/* Fonction qui enleve le nom de fichier d'un chemin relatif et colle un autre nom de fichier */
void FileReplace(string & ficcomplet, string fic);
void FileReplace(string ficcomplet, string fic, string & ficout);

/* Fonction de test */
void FindStr2(istream & ptfic, const char* pattern, const char* commentaire="%");

/* fonction cpp qui recherche un pattern dans un fichier */
void FindStr(istream & ptfic, const char* pattern);

/* Fonction qui recherche un pattern dans un fichier et retourne le pointeur de fichier courant */
FILE * FindStr(FILE * fichier, const char* pattern);
/*
  Convertit une chaine de caractere passe en parametre en un indice correpondant
  a la position de la chaine dans un tableau passe aussi en parametre
*/
int StrToIndex(char strtab[][50], int nb, char *pattern);

/* Retourne une chaine de caractere contenant la chaine originale et les
   espace necessaires au remplissage pour avoir une size caracteres */
void FormatStr(string strIn, string & strOut, int size);


#endif
