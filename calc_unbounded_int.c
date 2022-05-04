#include<stdio.h>
#include<stdlib.h>
#include "unbounded_int.h"

/*bon martin la c'est la merde;
On va devoir ouvrir le fichier et en extraire les lignes une par une et les traiter pour voir si c'st une commande ou pas
Je sais pas si on peut les mettre dans un tableau mais du coup pour ça il nous faudrait le nb de ligne du fichier ou sinon on traite les lignes une par une
sans les stocker d'abord(genre on prend un fichier sur le quel on ecrira la ligne puis on va l'analyser sur ce fichier temporaire)
putain j'ai fais aucun tp je sais pas ce qu'on peut ou pas faire sur un fichier en vrai j'essaye de regarder mais je suis crevé */
//Fais pas gaffe a setup j'eessayais juste les fct de File
void setUp(){
   FILE *line = fopen("line.txt","w");
   int i =0;
   while(i = fgetc(line) !=EOF){
      printf("%c  \n",i);
   }
}


int isaPrint(char* line){
   /*code*/
}

int isAnAffectation(char* line){
   /*code*/
}


int isAnOperation(char* line){
   /*code*/
}

unbounded_int resultat(char* intA,char* intB,char op){
   unbounded_int a = string2unbounded_int(intA);
   unbounded_int b = string2unbounded_int(intB); 
   if(op == '-'){
      return unbounded_int_difference(a,b);
   }
   else if(op == '+'){
      return unbounded_int_somme(a,b);
   }
   else{
      return unbounded_int_produit(a,b);
   }
}




int main(int argc, char const *argv[])
{
   setUp();
   return 0;
}