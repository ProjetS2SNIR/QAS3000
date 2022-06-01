#include <iostream> 
#include <ctime> 
#include <string> 
#include "horaires.cpp"
using namespace std; 
int main() 
{ 
	horaires ljj; 
	cout << "L'établissement est " << ljj.etat << 
	endl << "La raison : " << ljj.raison << endl;
	return 0;
}
