#include <iostream> 
#include <string>
using namespace std; 

class horaires { 
private: 
	int n_annee; 
	int n_mois; 
	int n_jour; 
	int n_heure; 
	int jour; 
	string sjour;
 public: 
	string etat; 
	string raison;
// méthodes
	horaires(); 
	void weekend(); 
	void soir(); 
	void ete(); 
	void toussaint(); 
	void noel(); 
	void fevrier(); 
	void paques(); 
	void verification();
	bool state();
};
