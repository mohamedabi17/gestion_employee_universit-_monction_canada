#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "gestion.h"
using namespace std;

// Function to display the content of personnel.dat
void afficherPersonnel()
{
	// ifstream fichier("personnel.dat"); // Ouverture du fichier en mode lecture
	ifstream fichier;
	// Au debut on suppose que l'employe-e n'existe pas
	fichier.open("personnel.dat", std::ios::in);
	if (!fichier)
	{
		cerr << "Erreur : Impossible d'ouvrir le fichier personnel.dat" << endl;
		return;
	}

	string line;

	cout << "\n===================================\n";
	cout << "Contenu du fichier personnel.dat :\n";
	cout << "===================================\n";

	while (getline(fichier, line))
	{
		cout << line << endl;
	}

	// Fermeture du fichier
	fichier.close();
}
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

// Fonction pour ajouter un nouvel employé
void nouveau()
{
	int matricule;
	cout << "Matricule de l'employe-e : ";
	cin >> matricule;

	if (employeexiste(matricule))
	{
		cout << "ERREUR : Employe-e existant-e avec le matricule " << matricule << ".\n";
		return;
	}

	ofstream fichier("./personnel.dat", ios::app); // Ouverture du fichier en mode ajout

	if (!fichier)
	{
		cerr << "Erreur : Impossible d'ouvrir le fichier personnel.dat" << endl;
		return;
	}

	string nom, profession;
	int annee;
	double salaire;

	// Saisie des informations
	cout << "-----------------------------------\n";
	cout << "Nouveau/nouvelle employe-e :\n";
	cout << "-----------------------------------\n";

	// Nom
	cout << "Nom : ";
	cin >> nom;

	// Annee de recrutement
	cout << "Annee de recrutement : ";
	cin >> annee;

	// Salaire horaire (validation entre 11.50 et 75.00)
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

	cout << "Nouvel employe-e cree avec succes !" << endl;
	afficherPersonnel(); // Afficher le personnel mis à jour
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
			nouveau(); // Call the function to recruit a new employee
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
Fonction : Affiche les informations d'un-e employe-e existant
*/

void consulter()
{
	int matricule;
	cout << "Matricule de l'employe-e : ";
	cin >> matricule;

	if (!employeexiste(matricule))
	{
		cout << "Aucun employe-e avec le matricule " << matricule << " n'a été trouvé." << endl;
		return;
	}

	// Afficher les informations de l'employe-e (à compléter avec votre code)
	// ...

	// Exemple d'affichage :
	cout << "Informations pour l'employe-e avec le matricule " << matricule << " :\n";
	cout << "Nom : " << nom << "\n";
	cout << "Annee de recrutement : " << annee << "\n";
	cout << "Salaire horaire : " << salaireh << "\n";
	cout << "Profession : " << profession << "\n";
}
/*
Fonction : imprime la liste des employe-es par matricule :
entete
*/
void entete_listematricule(ofstream &fichier)
{
	fichier << "\n+------+---------+--------------------+------+\n";
	fichier << "|Numero|Matricule| Nom                |Annee |\n";
	fichier << "|------|---------|--------------------|------|\n";
}

void corps_listematricule(ofstream &fichier)
{
	ifstream inputFile("personnel.dat");

	if (!inputFile)
	{
		cerr << "Erreur : Impossible d'ouvrir le fichier personnel.dat" << endl;
		return;
	}

	int matricule;
	string nom, profession;
	int annee;

	int numero = 1;

	while (inputFile >> matricule >> nom >> annee >> salaireh >> profession)
	{
		fichier << "|" << setw(6) << numero << "|" << setw(9) << matricule << "|" << setw(20) << nom << "|" << setw(6) << annee << " |\n";
		numero++;
	}

	inputFile.close();
}

void bas_listematricule(ofstream &fichier)
{
	fichier << "+------+---------+--------------------+------+\n";
}

void listematricule()
{
	ofstream outputFile("listematricule.dat");

	if (!outputFile)
	{
		cerr << "Erreur : Impossible de créer le fichier listematricule.dat" << endl;
		return;
	}

	entete_listematricule(outputFile);
	corps_listematricule(outputFile);
	bas_listematricule(outputFile);

	outputFile.close();
}

/*
Fonction : imprime la paye des employe-es au deux semaines
dans le fichier paie.dat
entete
*/
void entete_liste2semaines(ofstream &fichierSortie)
{
	fichierSortie << "\n+------+---------+--------------------+---------------+------------------+\n";
	fichierSortie << "|Numero|Matricule| Nom                |Salaire horaire|Paie de 2 semaines|\n";
	fichierSortie << "|------|---------|--------------------|---------------|------------------|\n";
}

void corps_liste2semaines(ofstream &fichierSortie)
{
	ifstream fichier("personnel.dat");

	if (!fichier)
	{
		cerr << "Erreur : Impossible d'ouvrir le fichier personnel.dat" << endl;
		return;
	}

	int numero = 1;
	int matricule;

	entete_liste2semaines(fichierSortie);

	while (fichier >> matricule >> nom >> annee >> salaireh >> profession)
	{
		double paie2semaines = salaireh * 2 * 40; // Assuming 40 working hours per week

		fichierSortie << "|" << setw(6) << numero << "|" << setw(9) << matricule << "|" << setw(20) << nom
					  << "|" << setw(15) << fixed << setprecision(2) << salaireh << "|" << setw(18) << fixed << setprecision(2) << paie2semaines << " |\n";

		// Output to console (cmd)
		cout << "|" << setw(6) << numero << "|" << setw(9) << matricule << "|" << setw(20) << nom
			 << "|" << setw(15) << fixed << setprecision(2) << salaireh << "|" << setw(18) << fixed << setprecision(2) << paie2semaines << " |\n";

		numero++;
	}

	fichierSortie << "+------------------------------------------------------------------------+\n";

	fichier.close();
}

void bas_liste2semaines(ofstream &fichierSortie)
{
	double totalPaie = 0.0;

	ifstream fichier("personnel.dat");

	if (!fichier)
	{
		cerr << "Erreur : Impossible d'ouvrir le fichier personnel.dat" << endl;
		return;
	}

	int matricule;
	string nom, profession;
	double salaire;

	while (fichier >> matricule >> nom >> annee >> salaire >> profession)
	{
		totalPaie += salaire * 2 * 40; // Assuming 40 working hours per week
	}

	fichierSortie << "+------------------------------------------------------------------------+\n";
	fichierSortie << "|      |         |                    |       Total = |" << setw(14) << fixed << setprecision(2) << totalPaie << " |\n";
	fichierSortie << "+------------------------------------------------------------------------+\n";

	fichier.close();
}

void liste2semaines()
{
	ofstream fichierSortie("paie.dat");

	if (!fichierSortie)
	{
		cerr << "Erreur : Impossible de créer le fichier paie.dat" << endl;
		return;
	}

	corps_liste2semaines(fichierSortie);

	fichierSortie.close();
}

/*
Fonction : imprime la liste des employes dans le fichier employees.dat
*/
/*
Fonction : imprime la liste des employes dans le fichier employees.dat
*/
void listeemployees()
{
	ifstream fichier("personnel.dat");

	if (!fichier)
	{
		cerr << "Erreur : Impossible d'ouvrir le fichier personnel.dat" << endl;
		return;
	}

	ofstream fichierSortie("employees.dat");

	if (!fichierSortie)
	{
		cerr << "Erreur : Impossible de créer le fichier employees.dat" << endl;
		fichier.close();
		return;
	}

	int matricule;
	string nom, profession;

	int numero = 1;

	while (fichier >> matricule >> nom >> annee >> salaireh >> profession)
	{
		double salaireSemaine = salaireh * 40; // Assuming 40 working hours per week

		// Output to console
		cout << "+===============================================================+\n";
		cout << "| EMPLOYE-E" << setw(7) << numero << " : " << setw(45) << nom << " |\n";
		cout << "|===============================================================|\n";
		cout << "| Matricule             : " << setw(35) << matricule << " |\n";
		cout << "| ------------------------------------------------------------- |\n";
		cout << "| Profession            : " << setw(35) << profession << " |\n";
		cout << "| ------------------------------------------------------------- |\n";
		cout << "| Annee de recrutement  : " << setw(35) << annee << " |\n";
		cout << "| ------------------------------------------------------------- |\n";
		cout << "| Salaire horaire       : " << setw(35) << fixed << setprecision(2) << salaireh << " |\n";
		cout << "| ------------------------------------------------------------- |\n";
		cout << "| Salaire d'une semaine : " << setw(35) << fixed << setprecision(2) << salaireSemaine << " |\n";
		cout << "+===============================================================+\n";

		// Output to employees.dat file
		fichierSortie << "+===============================================================+\n";
		fichierSortie << "| EMPLOYE-E" << setw(7) << numero << " : " << setw(45) << nom << " |\n";
		fichierSortie << "|===============================================================|\n";
		fichierSortie << "| Matricule             : " << setw(35) << matricule << " |\n";
		fichierSortie << "| ------------------------------------------------------------- |\n";
		fichierSortie << "| Profession            : " << setw(35) << profession << " |\n";
		fichierSortie << "| ------------------------------------------------------------- |\n";
		fichierSortie << "| Annee de recrutement  : " << setw(35) << annee << " |\n";
		fichierSortie << "| ------------------------------------------------------------- |\n";
		fichierSortie << "| Salaire horaire       : " << setw(35) << fixed << setprecision(2) << salaireh << " |\n";
		fichierSortie << "| ------------------------------------------------------------- |\n";
		fichierSortie << "| Salaire d'une semaine : " << setw(35) << fixed << setprecision(2) << salaireSemaine << " |\n";
		fichierSortie << "+===============================================================+\n";

		numero++;
	}

	fichier.close();
	fichierSortie.close();
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
