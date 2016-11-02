// Code du programme de génération d'anagrammes
//#include <iostream.h>
#include <string.h>
using namespace std;
 
string permuter_lettres (string Mot, int position1, int position2); //Déclaration de la fonction permuter_lettres
void anagramme (string Mot,int Pos, int DimMot); //Déclaration de la fonction anagramme
 
 
int main()           // code programme principal
{
  /* déclaration des variables*/
  string Lettres; // Variable contenant les lettres du mot
  int LongueurMot; // Nombre de lettres dans le mot
   
    /* instructions de main() */
  cout << "Entrer les lettres : "; // On demande la saisie des lettres du mot
  cin >> Lettres; //Saisie des lettres
  LongueurMot = Lettres.size(); // Définition de la variable LongueurMot grâce à la fonction Lettres.size()
  anagramme (Lettres, 0, LongueurMot); //Lancement de la fonction anagramme
    system("PAUSE");
  return 0;
}
 
 
 
string permuter_lettres (string Mot, int position1, int position2) //Fonction petmuter-lettres : permutte deux lettres, non récursive
{                                                                  //Permutte les lettres du mot des positions Position1 et Position2
   char Lettre;                                                    //Fonction réutilisée dans la fonction anagramme (l. 52)
   Lettre = Mot[position1];                                        //
   Mot[position1] = Mot[position2];
   Mot[position2] = Lettre;  
   return Mot;   
}
 
void anagramme (string Mot,int Pos, int DimMot) // On lui rentre le mot, un entier Pos(ition), un entier DimMot (??)
{
  int j; //Déclaration de la variable j
 
  if (Pos == DimMot-1) //Si position (pos) est égal à DimMot (nombre de lettres ds le mot) -1 (posit° de la dernière lettre), alors :
    {cout << "  Mot: " << Mot << endl;}
     else
       {
              for (j = Pos; j < DimMot; j++)
                  {
                       Mot = permuter_lettres (Mot, Pos, j);
                       anagramme (Mot, Pos+1, DimMot);
                       Mot = permuter_lettres (Mot, Pos, j);
                  }
       }      
}