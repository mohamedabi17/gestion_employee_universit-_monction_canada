#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "gestion.h"

using namespace std;

/*
Fonction : liste des professions
*/
string listeprofessions()
{
	int choix;

	cout << setfill(' ');
	cout << "\n----------------------------------\n";
	cout << "      Liste des professions\n";
	cout << "----------------------------------\n";
	cout << "1) " << Vemplois[0] << "\n";
	cout << "2) " << Vemplois[1] << "\n";
	cout << "3) " << Vemplois[2] << "\n";
	cout << "4) " << Vemplois[3] << "\n";
	cout << "5) " << Vemplois[4] << "\n";
	cout << "----------------------------------\n";
	cout << "Profession -> ";

	// Lecture du choix
	cin >> choix;

	return (Vemplois[choix - 1]);
}

// Ajoute les informations saisies au fichier "personnel.dat"
// Ajoute les informations saisies au fichier "personnel.dat"
void ajoutersurlefichier()
{
	ofstream fichier("personnel.dat", ios::app); // Ouverture du fichier en mode ajout

	if (!fichier)
	{
		cerr << "Erreur : Impossible d'ouvrir le fichier personnel.dat" << endl;
		return;
	}

	string nom, prenom, profession;
	int annee, matricule;
	double salaire;

	// Saisie des informations
	cout << "-----------------------------------\n";
	cout << "Nouveau/nouvelle employe-e :\n";
	cout << "-----------------------------------\n";

	// Matricule
	cout << "matricule : ";
	cin >> matricule;

	// Nom
	cout << "Nom : ";
	cin >> nom;

	// Annee de recrutement
	cout << "Annee de recrutement : ";
	cin >> annee;

	// Salaire horaire (validation between 11.50 and 75.00)
	do
	{
		cout << "Salaire horaire (entre 11.50 et 75.00) : ";
		cin >> salaire;
		if (salaire < 11.50 || salaire > 75.00)
		{
			cout << "Salaire hors de la plage autorisee. Veuillez reessayer." << endl;
		}
	} while (salaire < 11.50 || salaire > 75.00);

	// Écriture des informations dans le fichier
	fichier << matricule << "\n"
			<< nom << "\n"
			<< annee << "\n"
			<< salaire << "\n";

	profession = listeprofessions(); // Utilisation de la fonction pour choisir la profession

	fichier << profession << "\n";
	// Fermeture du fichier
	fichier.close();
}

/*
Fonction : menu principal
*/
int menu()
{
	int choix;

	do
	{
		cout << "\n=================================================\n";
		cout << "Menu : Gestion du personnel\n";
		cout << "=================================================\n";
		cout << "1) Recruter un nouveau/une nouvelle employe-e\n";
		cout << "2) Consulter les informations d'un-e employe-e\n";
		cout << "-------------------\n";
		cout << "3) Imprimer les etats\n";
		cout << "-------------------\n";
		cout << "4) Quitter l'application\n";
		cout << "=================================================\n";
		cout << "Choix -> ";
		cin >> choix;

		switch (choix)
		{
		case 1:
			ajoutersurlefichier(); // Call the function to recruit a new employee
			break;
		case 2:
			consulter(); // Call the function to consult employee information
			break;
		case 3:
			sousmenu(); // Appeler le sous-menu
			break;
			// You need to implement the functionality for printing states
			// e.g., entete_listematricule(), corps_listematricule(), bas_listematricule(), etc.
			break;
		case 4:
			cout << "Quitter l'application. Au revoir !" << endl;
			break;
		default:
			cout << "Choix invalide. Veuillez réessayer." << endl;
		}

	} while (choix != 4);

	return 0;
}

/*
Fonction : sous menu imprimer
*/
int sousmenu()
{
	int choixSousMenu;

	do
	{
		cout << "\n==========================================\n";
		cout << "Sous menu : 3) Imprimer les etats\n";
		cout << "==========================================\n";
		cout << "1) Liste des employe-es par matricule\n";
		cout << "2) Liste des salaires par deux semaines\n";
		cout << "3) Liste des employe-es\n";
		cout << "-------------------\n";
		cout << "4) Quitter\n";
		cout << "------------------------------------------\n";
		cout << "Choisir un etat -> ";
		cin >> choixSousMenu;

		switch (choixSousMenu)
		{
		case 1:
			// Ajoutez l'appel de votre fonction pour imprimer la liste par matricule ici
			listematricule();
			break;
		case 2:
			// Ajoutez l'appel de votre fonction pour imprimer la liste des salaires ici
			liste2semaines();
			break;
		case 3:
			// Ajoutez l'appel de votre fonction pour imprimer la liste des employés ici
			listeemployees();
			break;
		case 4:
			cout << "Quitter le sous-menu d'impression." << endl;
			break;
		default:
			cout << "Choix invalide. Veuillez réessayer." << endl;
		}

	} while (choixSousMenu != 4);

	return 0;
}

/*
Fonction : verifie si le matricule existe deja dans le fichier personnel.dat
et s'il est assigne a un-e employe-e
*/
bool employeexiste(int matricule)
{
	ifstream fin;
	string ligne;
	int lemat;
	int i;
	bool cond;

	cond = false; // Au debut on suppose que l'employe-e n'existe pas
	fin.open("personnel.dat", std::ios::in);
	i = 1;
	if (fin.is_open())
	{
		while (getline(fin, ligne))
		{
			switch (i)
			{
			case 1: // matricule
				lemat = stoi(ligne);
				break;
			case 2:
				nom = ligne;
				break;
			case 3:
				annee = stoi(ligne);
				break;
			case 4:
				salaireh = stof(ligne);
				break;
			case 5:
				profession = ligne;
				if (lemat == matricule)
				{
					// Employe-e existe
					cond = true;
					return cond;
				}
				//
				i = 0;
				break;
			}
			i = i + 1;
		}
	}

	if (fin.is_open())
		fin.close();

	return cond;
}

/*
Fonction : ajoute un nouveau employe
*/
void nouveau()
{
}

/*
Fonction : Affiche les informations d'un-e employe-e existant
*/
void consulter()
{
}

/*
Fonction : imprime la liste des employe-es par matricule :
entete
*/
void entete_listematricule()
{
}

/*
Fonction : imprime la liste des employe-es par matricule :
corps
*/
void corps_listematricule()
{
}

/*
Fonction : imprime la liste des employe-es par matricule :
bas
*/
void bas_listematricule()
{
}

/*
Fonction : imprime la liste des employe-es par matricule
dans le fichier listematricule.dat
*/
void listematricule()
{

	entete_listematricule();
	corps_listematricule();
	bas_listematricule();
}

/*
Fonction : imprime la paye des employe-es au deux semaines
dans le fichier paie.dat
entete
*/
void entete_liste2semaines()
{
}

/*
Fonction : imprime la paye des employe-es au deux semaines
dans le fichier paie.dat
corps
*/
void corps_liste2semaines()
{
}

/*
Fonction : imprime la paye des employe-es au deux semaines
dans le fichier paie.dat
bas
*/
void bas_liste2semaines()
{
}

/*
Fonction : imprime la paye des employe-es au deux semaines
dans le fichier paie.dat
*/
void liste2semaines()
{

	entete_liste2semaines();
	corps_liste2semaines();
	bas_liste2semaines();
}

/*
Fonction : imprime la liste des employes dans le fichier employees.dat
*/
void listeemployees()
{
}

/*
Fonction main
*/
int main()
{
	cout << "Bienvenue dans le programme de gestion du personnel" << endl;

	// Call the menu function
	menu();

	cout << "Programme terminé." << endl;
	return 0;
}
