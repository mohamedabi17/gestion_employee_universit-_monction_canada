#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

/*
Entetes des fonctions (prototypes)
*/
string listeprofessions();
int menu();
int sousmenu();
bool employeexiste(int matricule);
void nouveau();
void consulter();
void listematricule();
void entete_listematricule();
void corps_listematricule();
void bas_listematricule();
void liste2semaines();
void entete_liste2semaines();
void corps_liste2semaines();
void bas_liste2semaines();
void listeemployees();

/*
Variables globales
*/
string Vemplois[5] = {
	"Rectrice/Recteur",
	"Doyenne/Doyen",
	"Enseignante/Enseignant",
	"Agente/Agent de bureau",
	"Technicienne/Technicien"
};
int mat;
string nom;
int annee;
float salaireh;
string profession;
float montant;
float total;
int numero;
