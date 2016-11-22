/*!
   \file GestionConf.h
   \brief Permet de gerer un fichier de configuration Type
   \author BAYLE.F
   \date 30/01/2015


	 	FICHIERS TYPE :
	 	-------------------------------------------------
	 	#Mon fichier exemple
	 	#Les phrases commencants par un dièse sont commentées
	 	;Les phrase commencants par un point virgule sont commentées

	 	#Ci-dessous les assignations classiques
	 	clef = valeur

	 	#Ci-dessous les grosses assignations. Uniquement pour des int. (Ne pas oublier une espace en fin de ligne)
	 	clef ={
	 		X X X X X X X X X X X X X X X X X X X X X X X X X
	 		X X X X X X X X X X X X X X X X X X X X X X X X X
	 		X X X X X X X X X X X X X X X X X X X X X X X X X
	 		X X X X X X X X X X X X X X X X X X X X X X X X X
	 		X X X X X X X X X X X X X X X X X X X X X X X X X
	 	}

	 	#Les assignations classiques sont stockées dans un map de type clef valeur.
	 	#Les grosse assignation aussi met elles on une methode permettant de recuperer un tableau à deux dimensions (int**)(int** recup2DTab(int width, int height))

	 	-------------------------------------------------



*/

#include <iostream>
#include <stdlib.h>	/*atoi, atol, atoif*/
#include <string>
#include <fstream>
#include <vector>
#include <map>	/*Tableau associatif*/


using namespace std;

class GestionConf
{
	private :
		/*_____________ZONE DES ATTRIBUTS______________*/

		ifstream readStream;	//Buffer de lecture
		string fileName;		//Nom du fchier
		vector<string> lines;	//Capture des lignes avec espaces
		map<string, string> mapFile;	//Map qui contiendra le couple clef, valeur
		vector<char**> tableau2d;		//Contient les grosse zones de texte à deux dimensions


		/*______________ZONE DES METHODES________________*/

		/*_METHODES DE VERIFICATION_*/
		bool isComment(unsigned int nLigne);	//Renvoi vraie si la ligne est commentée
		bool isVide(string chaine);	//Verifie si une chaine est vide (vrai si elle est vide)

		/*_METHODE FONCTIONNEMENT DE LA CLASS_*/
		int loopFilling();	//Remplissage du vecteur
		void supSpace();	// Supression des espace avant le = ou #
		void remplissageMap();	//Rempli la Map
		string supSpaceForReturn(string ret);	//Suppression espace d'une seul chaine
		string getValeur(string recherche);		//Renvoi la valeur d'une clef
		string getCle(string chaine);			// Renvoi la clef d'une valeur
		int rempBigArea(int i);	//Remplit une clef assigné a une valeur étendue

	public :

		/* CONSTRUCTEUR */
		GestionConf(string fichier);

		/*_METHODES DE VERIFICATION_*/
		bool estValide();	//Renvoi 1 si le fichier a pu être chargé

		/* METHODES DE RENVOI */

		int getIntVal(string clef);		//Retourne la valeur en Int
		long getLongVal(string clef);	// Retourne la valeur en Long
		float getFloatVal(string clef);		// Retourne la valeur en Float
		string getStringVal(string clef);	// Retourne la valeur en String
		bool isPresent(string clef);	//Renvoi 1 si la valeur existe
		void recupAllKey(vector<string> &vecteurString);	//Retourne toutes les clef dans le vecteur
		int** recup2DTab(const char* key, int with, int height);	// Retourne un tableau à deux dimensions d'une zone de valeurs (fonctionne qu'avec des chiffres)
		void getIntLst(const char* key, vector<int> &vecteur);		//Remplit un vecteur de valeur int presente sur une clef dont les valeurs sont inline et espacées

};
