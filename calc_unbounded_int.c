#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
   while((i = fgetc(line)) !=EOF){
      printf("%c  \n",i);
   }
}


int isaPrint(char* line){
   /*code*/
   return 0;
}

int isAnAffectation(char* line){
   /*code*/
   return 0;
}


int isAnOperation(char* line){
   /*code*/
   return 0;
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




int main(int argc, char **argv) {
   int n = argc - 1;
   FILE *in;
   FILE *out;
   if (n == 4) { // Ouverture des flots en fonction des arguments
      if (strcmp(argv[1], "-i") == 0) {
         in = fopen(argv[2], "r");
      }else if (strcmp(argv[3], "-i") == 0) {
         in = fopen(argv[4], "r");
      }else {
         in = stdin;
      }
      if (strcmp(argv[1], "-o") == 0) {
         out = fopen(argv[2], "w");
      }else if (strcmp(argv[3], "-o") == 0) {
         out = fopen(argv[4], "w");
      }else {
         out = stdout;
      }
   }else if (n == 2) {
      if (strcmp(argv[1], "-i") == 0) {
         in = fopen(argv[2], "r");
         out = stdout;
      }
      if (strcmp(argv[1], "-o") == 0) {
         in = stdin;
         out = fopen(argv[2], "w");
      }
   }else {
      in = stdin;
      out = stdout;
   }

   //setUp();
   return 0;
}
