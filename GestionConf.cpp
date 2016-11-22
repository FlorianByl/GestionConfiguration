//------------------------------------------------------------------
//GestionConf.cpp  – florian.bayle – 30/01/2015
//------------------------------------------------------------------
// Function Class : GestionConf
//------------------------------------------------------------------


#include "GestionConf.h"

using namespace std;



/*____________________________________________METHODE FONCTIONNEMENT DE LA CLASS_________________________________*/

/*!
   \brief Constructeur
   \param fichier : Chemin vers fichier de configuration
   \pre Avoir un fichier de configuration
*/
GestionConf::GestionConf(string fichier)
{
	fileName = fichier;
	this->loopFilling();
	this->supSpace();
	this->remplissageMap();
}

/*!
   \brief Analyse du fichier et recuperation ligne par ligne
   \return 0
*/
int GestionConf::loopFilling()
{
	string lecteur;		// Permet la lecture de tous le fichier (par ligne)

	readStream.open(fileName.c_str());	// Ouverture du fichier
	for(;getline(readStream, lecteur);)		//Tant qu'il lit des lignes
	{

			lines.push_back(lecteur);

	}
	readStream.close();
	return 0;
}

/*!
   \brief SUPPRESSION DES ESPACES (AVANT =)
*/
void GestionConf::supSpace()
{
	/* SUPPRIME LES ESPACE DE TOUS LES VECTEUR (AVANT LE =) */
	for(int j = 0; j<lines.size(); j++)
	{
		int pos = lines[j].find_first_of('=');
		int pos2 = lines[j].find_first_of('#');


		for(int i = 0; i<lines[j].size(); i++)
		{
			/* SUPRESSION SI (ESPACE OU TAB) ET AVANT = OU # */
			while((lines[j][i] == ' ' || lines[j][i] == '	') && (i <= pos || i < pos2))
			{
				lines[j].erase(i,1);
			}
		}
	}
}

/*!
   \brief Rempli le tableau associatif avec les cled et valeurs
*/
void GestionConf::remplissageMap()
{
	/* REMPLIT LA MAP */

	string clef, valeur;
	int tempPos, fin;
	for(int i = 0; i < lines.size(); i++)
	{
		if(!isVide(lines[i]) && !isComment(i))
		{
			clef = getCle(lines[i]);	//Recuparation Clef ligne
			valeur = getValeur(lines[i]);	//Recuperation valeur ligne
			if(valeur == "{")
				i = rempBigArea(i);
			else
				mapFile[clef] = valeur ;		//Ajout dans la map
		}
	}
}


/*!
   \brief Detecte si une ligne est commentée
   \param nLigne : Ligne
   \return True si commenté
*/
bool GestionConf::isComment(unsigned int nLigne)
{
	/* METHODE QUI RENVOI TRUE SI LIGNE COMMENTEE */

	if(nLigne >= 0)
	{
		if(lines[nLigne].at(0) == '#' )
			return true;
		if(lines[nLigne].at(0) == ';' )
			return true;
		else
			return false;
	}
	else
	{
		return true;
	}
}


/*!
   \brief ranvoi la valeur
   \param chaine : Chaine de caractere a anlyser
   \return Valeur
*/
string GestionConf::getValeur(string chaine)
{
	/* RENVOI LA VALEUR D'UNE CLEF */

	// chaine = supSpaceForReturn(chaine);
	string bufferVerif = "";
	int bonVecteur = 0;
	bool confir = false;


		int pos = chaine.find_first_of('=');	//Recherche de l'emplacement du signe "="
		for(int i = pos+1; i<chaine.size(); i++)		// boucle du signe = +1 jusqu'a la fin
		{
			bufferVerif+=chaine[i];	// Recuperation des valeurs
		}
		return bufferVerif;	//Retour
}

/*!
   \brief Renvoi la clef
   \param chaine : Chaine de caractere a anlyser
   \return clef
*/
string GestionConf::getCle(string chaine)
{
	/* RENVOI LA CLEF D'UNE VALEUR */

	string bufferVerif = "";
	int bonVecteur = 0;
	bool confir = false;

		int pos = chaine.find_first_of('=');	//Recherche de l'emplacement du signe "="
		for(int i = 0; i<pos ; i++)		// boucle du signe +1 jusqu'a la fin
			bufferVerif+=chaine[i];	// Recuperation des valeurs
		return bufferVerif;	//Retour
}

/*!
   \brief Remplissage d'une zone etendu
   \param i = iteration
   \return Retourne nouvelle iteration
*/
int GestionConf::rempBigArea(int i)
{
	string valeur, clef;
	int j = i;
	clef = getCle(lines[j]);	//Recuparation Clef ligne
	valeur = getValeur(lines[j]);	//Recupoeration valeur clef
	while(lines[j] != "}")
	{
		j++;
		valeur += getValeur(lines[j]);
	}

	mapFile[clef] = valeur;
	mapFile[clef].erase(mapFile[clef].begin());
	mapFile[clef].erase(mapFile[clef].end()-1); //Suppresison "}". -1 sinon erreure de segmentation
	mapFile[clef].erase(mapFile[clef].end()-1); 	//Suppression du "0"
	return j;
}



/*________________________________________________VERIFICATIONS_______________________________________________*/



/*!
   \brief Check si chaine vide
   \param chaine: chaine a analyser
   \return True si chaine vide
*/
bool GestionConf::isVide(string chaine)
{
	/* Verifie si chaine est vide */
	if(chaine.empty())
		return true;

	int pos = chaine.find_first_of('=');
	if(pos == string::npos)
		return true;
	else
	{
		string last = getValeur(chaine);
		if(last.empty())
			return true;
	}


	return false;
}

/*!
   \brief Si fichier est valide
   \return True si fichier valide
*/
bool GestionConf::estValide()
{
	if(!mapFile.empty())
		return 1;
	else
		return 0;
}
/*!
   \brief Si clef existe
   \param clef : Clef
   \return True si la clef existe
*/
bool GestionConf::isPresent(string clef)
{
	if(!mapFile[clef].empty())
		return 1;
	else
		return 0;
}

/*__________________________________________________________ZONE DES METHODES DE RETOUR_______________________________*/



/*!
   \brief Renvoi la valeur en INT
   \param clef : Clef
   \return Valeur int
*/
int GestionConf::getIntVal(string clef)
{
	return atoi(mapFile[clef].c_str());
}

/*!
   \brief Renvoi la valeur en string
   \param clef : Clef
   \return Valeur string
*/
string GestionConf::getStringVal(string clef)
{
	return mapFile[clef];
}


/*!
   \brief Renvoi la valeur en long
   \param clef : Clef
   \return Valeur long
*/
long GestionConf::getLongVal(string clef)
{
	return atol(mapFile[clef].c_str());
}

/*!
   \brief Renvoi la valeur en FLOAT
   \param clef : Clef
   \return Valeur float
*/
float GestionConf::getFloatVal(string clef)
{
	return atof(mapFile[clef].c_str());
}

/* PERMET DE RECUPERER TOUTES LES CLEFS DANS UN VECTEUR DE STRING */
/*!
   \brief Renvoi toute clef
   \param vecteurString : vecteur de retour
*/
void GestionConf::recupAllKey(vector<string> &vecteurString)
{
	for(map<string, string>::iterator i = mapFile.begin(); i != mapFile.end(); i++)
	{
		vecteurString.push_back(i->first);
	}
}

/* RENVOI UN TABLEAU DEUX DIMENSION D'UNE VALEUR DE CLEF INITIALEMENT A UNE DIMENSION */
/*!
   \brief Renvoi tableau deux dimension
   \param key : Clef
	 \param width : Largeur x
	 \param height : Hauteur y
   \return Tableau a deux dimension
*/
int** GestionConf::recup2DTab(const char* key, int width, int height)
{
	/* String qui contient les valeurs en une dimension */
	string map = getStringVal(key);
	vector<string> nombres(width*height);
	vector<int> stringConvertis(width*height);

	for (int i = 0; i < width*height; i++)
	{
		if(map[0] == ' ')
			map.erase(0, 1);
		while(map[0] != ' ')
		{
			nombres[i] += map[0];
			map.erase(0, 1);
			if(map.size() == 0)
				break;
		}

	}

	for (int i = 0; i < width*height; i++)
	{
		stringConvertis[i] = atoi(nombres[i].c_str());
	}

	/*Création dynamique du tableau à renvoyer */
	int** tab = new int *[height];	//On crée un tableau de height cases

	for (int i=0; i<height; i++)	//Pour i allant de 0 a height
	{
		tab[i] = new int [width];	//On crée pour chaque case width autres cases
	}

	for (int y = 0; y < height; y++)
	{

		for (int x = y*width, z = 0; x < width + y*width; x++, z++)
		{
			tab[y][z] = stringConvertis[x];
		}

	}

	return tab;
}

/*!
   \brief Renvoi list de int
   \param key : Clef
	 \param vecteur : Vecteur de sortie
*/
void GestionConf::getIntLst(const char* key, vector<int> &vecteur)
{
	string temp = mapFile[key];
	string tampon;

	for(int i = 0; i < mapFile[key].size(); i++)
	{
			if(temp[0] == ' ')
				temp.erase(0, 1);
			while(temp[0] != ' ')
			{
				tampon += temp[0];
				temp.erase(0, 1);
				if(temp.size() == 0)
				{
					break;
				}
			}
			vecteur.push_back(atoi(tampon.c_str()));
			tampon = "";
			if(temp.size() == 0)
			{
				break;
			}
	}
}

/*__________________________________________________________OUTILS___________________________________________________*/

/* SUPPRIME LES ESPACE D'UNE CHAINE PASSE EN PARAMETRE */
/*!
   \brief Supprime les espaces d'une chaine
   \param ret: chaine
   \return Chaine sans espace
*/
string GestionConf::supSpaceForReturn(string ret)
{

		for(int i = 0; i<ret.size(); i++)
		{
			/* SUPRESSION SI (ESPACE OU TAB) ET AVANT =*/
			while((ret[i] == ' ' || ret[i] == '	' ))
			{
				ret.erase(i,1);
			}
		}

		return ret;

}
