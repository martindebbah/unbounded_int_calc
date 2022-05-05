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
}variables;

static variable *getVar(char *s, variables *vars);
static unbounded_int resultat(unbounded_int a, unbounded_int b, char op);
static void add(variable *v, variables *vars);

// PS: faudra pas qu'on oublie d'enlever ce setUp(), je l'ai laissé pour le moment si tu en as encore besoin.

void setUp(){
   FILE *line = fopen("line.txt","w");
   int i =0;
   while((i = fgetc(line)) !=EOF){
      printf("%c  \n",i);
   }
}

// Ecrit dans le flot out
static void print(char* lex, FILE *out, variables *vars) {
   lex = strtok(NULL, " \n"); // Le nom de la variable
   char *var = malloc(strlen(lex) + 1);
   strcpy(var, lex);
   if (lex == NULL || lex[0] == '=' || strcmp(lex, "print") == 0) { // Pas de variable vide ou qui commence par '=' ou de nom print
      return;
   }
   variable *v = getVar(var, vars);
   char *name = v -> s;
   char *value = unbounded_int2string(v -> n);
   char *str = malloc(strlen(name) + strlen(value) + 3 * sizeof(char) + 2);
   strcpy(str, name);
   strcat(str, " = ");
   strcat(str, value);
   strcat(str, "\n");
   fputs(str, out);
}

static int isCorrect(unbounded_int a) { // J'ai pas trouvé comment l'importer de unbounded_int.c donc pour le moment je la réécris ici
    if (a.signe == '*')
        return 0; // False
    return 1; // True
}

// Affecte la valeur à la variable
static void affect(char *lex, variables *vars) {
   char *var = malloc(strlen(lex) + 1); // Le nom de la variable (avant le '=')
   strcpy(var, lex);
   lex = strtok(NULL, " =\n");
   if (lex == NULL) // Si la ligne est sans instruction
      return;
   char *val = malloc(strlen(lex) + 1); // La première valeur (après le '=')
   strcpy(val, lex);
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
      char *val2 = malloc(strlen(lex) + 1); // Affectation de la deuxième valeur (après l'opérateur)
      strcpy(val2, lex);
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
         variable *v3 = getVar(val2, vars);
         b = v3 -> n;
      }
      unbounded_int n = resultat(a, b, op);
      v -> n = n;
   }
   if (isCorrect(v -> n))
      add(v, vars);
}

static unbounded_int resultat(unbounded_int a, unbounded_int b, char op) {
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
static variable *getVar(char *s, variables *vars) {
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
static void add(variable *v, variables *vars) {
   if (vars -> premiere == NULL) { // Il n'y a aucune variable
      vars -> premiere = v;
      return;
   }
   variable *current = vars -> premiere;
   while (strcmp(current -> s, v -> s) != 0 && current -> suivante != NULL) {
      current = current -> suivante;
   }
   if (strcmp(current -> s, v -> s) == 0) { // La variable existe déjà
      current -> n = v -> n;
      return;
   }
   // La variable n'existe pas
   current -> suivante = v;
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

   if (in == NULL || out == NULL) { // Si erreur lors de l'ouverture des flots
      printf("Erreur lors de l'ouverture des flots.\n");
      return 1;
   }
   
   char *str = malloc(MAX);
   char *sepdeb = " =";
   char *lex = malloc(MAX);

   variables *vars = malloc(sizeof(variables));

   while (fgets(str, MAX, in) != NULL) {
      lex = strtok(str, sepdeb);
      if (strcmp(lex, "print") == 0) {
         print(lex, out, vars);
      }else {
         affect(lex, vars);
      }
   }

   fclose(in);
   fclose(out);
   return 0;
}
