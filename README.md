# Calculatrice

## Présentation

Ce programme permet de calculer des opérations basiques (addition, soustraction et multiplication) sur des
entiers sans limite de taille. Cela est fait grâce à des listes chaînées pour représenter les entiers.

## Utilisation

Le programme est exécuté en ligne de commande de façon suivante :

`./calc_unbounded_int -i source.txt -o dest.txt`

L’option `-i` du programme donne le nom de fichier texte qui contient une suite d’instructions à exécuter par l’interprète.
Dans l’option `-o` on passe le nom de fichier où calc_unbounded_int écrira les résultats.

Les deux options sont facultatives : si l’option `-i` est absente `calc_unbounded_int`
lira les instructions depuis le flot d’entrée standard `stdin` et si l’option `-o` est absente le
programme écrira les résultats dans le flot `stdout`.

Le fichier lu par l’interpréteur contient trois types d’instructions, réparties sur des lignes
distinctes :

(A) `variable = entier_ou_variable op entier_ou_variable`

`entier_ou_variable` est soit un entier soit une variable. `op` est une de trois opérations :
*, +, -. L’interpréteur doit effectuer l’opération, le résultat de l’opération devient
la valeur de la variable.

(B) `variable = entier`

`entier` devient la nouvelle valeur de la `variable`.

(C) `print variable`

L’interpréteur écrira dans le fichier de sortie une ligne sous forme

`variable = valeur`

où `valeur` est la valeur de `variable`

## Auteurs

CHERIFI Rayan

DEBBAH Martin
