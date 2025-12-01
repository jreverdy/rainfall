## Le programme
Le programme utilise la fonction atoi sur le premier argument passé au programme dans l'entrée standard.

## La faille
Il vérifie ensuite si la valeur de cet argument est égal à '0x1a7' en binaire ce qui équivaut à 423.

Un shell est ensuite executé et nous permet d'accéder flag de level1.
`-rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0`

le `s` dans les permissions permet d'executer le binaire `level0` comme si on était le user `level1`. 

## La solution

`./level0 423`