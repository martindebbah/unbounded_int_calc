#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "unbounded_int.h"

#define MAX 1025

typedef struct variable {
   char *s;
   unbounded_int n;
   struct variable *suivante;
}variable;

typedef struct variables {
   variable *premiere;
   variable *derniere;
}variables;

variable *getVar(char *s, variables *vars);
unbounded_int resultat(unbounded_int a, unbounded_int b, char op);
variables *add(variable *v, variables *vars);

// J'ai pas mal avancé, le programme boucle sur tout le fichier et reconnaît les commandes.
// On peut lire/écrire depuis/sur la sortie/entrée standard ou un fichier
// Le seul problème que j'ai maintenant c'est que je n'arrive pas à faire fonctionner mon struct.
// C'est à dire que les variables ne sont pas enregistrées.
// J'ai l'impression que ça vient soit de la fonction add() soit de getVar().
// Je push comme ça pour le moment désole c'est un peu de la merde mais je m'y remettrai demain.

// PS: faudra pas qu'on oublie d'enlever ce setUp(), je l'ai laissé pour le moment si tu en as encore besoin.

void setUp(){
   FILE *line = fopen("line.txt","w");
   int i =0;
   while((i = fgetc(line)) !=EOF){
      printf("%c  \n",i);
   }
}

// Renvoie 1 si la ligne commence par print, 0 sinon
int isAPrint(char* line) {
   char *sep = " 0";
   char *p = strtok(line, sep);
   if (strcmp(p, "print") != 0) {
      return 0;
   }
   return 1;
}

// Ecrit dans le flot out
variables *print(char* lex, FILE *out, variables *vars) {
   lex = strtok(NULL, " \n");
   variable *v = getVar(lex, vars);
   char *name = v -> s;
   char *value = unbounded_int2string(v -> n);
   char *str = malloc(strlen(name) + strlen(value) + 3 * sizeof(char) + 2);
   strcpy(str, name);
   strcat(str, " = ");
   strcat(str, value);
   strcat(str, "\n");
   fputs(str, out);
   vars = add(v, vars);
   return vars;
}

// Affecte la valeur à la variable
variables *affect(char *lex, variables *vars) {
   char *var = lex; // Le nom de la variable (avant le '=')
   lex = strtok(NULL, " =\n");
   if (lex == NULL) // Si la ligne est sans instruction
      return vars;
   char *val = lex; // La première valeur (après le '=')
   lex = strtok(NULL, " =");
   variable *v = malloc(sizeof(variable));
   v -> s = var;
   if (lex == NULL) { // Affectation "normale"
      if (val[0] == '-' || val[0] == '+' || (val[0] >= '0' && val[0] <= '9')) { // C'est une valeur
         unbounded_int n = string2unbounded_int(val);
         v -> n = n;
      }else { // C'est une variable
         variable *v2 = getVar(val, vars);
         v -> n = v2 -> n;
      }
   }else { // Affectation d'une opération
      char op = lex[0];
      lex = strtok(NULL, " \n");
      char *val2 = lex;
      unbounded_int a, b;
      if (val[0] == '-' || val[0] == '+' || (val[0] >= '0' && val[0] <= '9')) { // C'est une valeur
         a = string2unbounded_int(val);
      }else { // C'est une variable
         variable *v2 = getVar(val, vars);
         a = v2 -> n;
      }
      if (val2[0] == '-' || val2[0] == '+' || (val2[0] >= '0' && val2[0] <= '9')) { // C'est une valeur
         b = string2unbounded_int(val2);
      }else { // C'est une variable
         variable *v3 = getVar(val, vars);
         b = v3 -> n;
      }
      unbounded_int n = resultat(a, b, op);
      v -> n = n;
   }
   vars = add(v, vars);
   return vars;
}

unbounded_int resultat(unbounded_int a, unbounded_int b, char op) {
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

// Retourne la variable de nom s
variable *getVar(char *s, variables *vars) {
   if (vars -> premiere == NULL) { // Il n'y a aucune variable
      variable *v = malloc(sizeof(variable));
      v -> n = string2unbounded_int("0");
      v -> s = malloc(strlen(s) + 1);
      strcpy(v -> s, s);
      return v;
   }
   variable *current = vars -> premiere;
   while (strcmp(current -> s, s) != 0 && current -> suivante != NULL) {
      current = current -> suivante;
   }
   if (strcmp(current -> s, s) == 0) { // La variable existe
      return current;
   }
   // La variable n'existe pas
   variable *v = malloc(sizeof(variable));
   v -> n = string2unbounded_int("0");
   v -> s = malloc(strlen(s) + 1);
   strcpy(v -> s, s);
   return v;
}

// Ajoute v aux variables
variables *add(variable *v, variables *vars) {
   if (vars -> derniere == NULL) { // Il n'y a aucune variable
      vars -> premiere = v;
      vars -> derniere = vars -> premiere;
      printf("prems\n");
      return vars;
   }
   variable *current = vars -> premiere;
   while (strcmp(current -> s, v -> s) != 0 && current -> suivante != NULL) {
      current = current -> suivante;
   }
   if (strcmp(current -> s, v -> s) == 0) { // La variable existe déjà
      current -> n = v -> n;
      return vars;
   }
   // La variable n'existe pas
   vars -> derniere -> suivante = v;
   vars -> derniere = vars -> derniere -> suivante;
   return vars;
}

void printv(variables *v) {
   variable *c = v -> premiere;
   while (c != NULL) {
      printf("Variable : s = %s, v = %s\n", c -> s, unbounded_int2string(c -> n));
      c = c -> suivante;
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
   
   char *str = malloc(MAX);
   //print(str, out);
   char *sepdeb = " 0=";
   char *lex = malloc(MAX);

   variables *vars = malloc(sizeof(variables));

   while (fgets(str, MAX, in) != NULL) {
      lex = strtok(str, sepdeb);
      if (strcmp(lex, "print") == 0) {
         vars = print(str, out, vars);
      }else {
         vars = affect(lex, vars);
      }
      printv(vars);
   }

   //setUp();
   fclose(in);
   fclose(out);
   return 0;
}
