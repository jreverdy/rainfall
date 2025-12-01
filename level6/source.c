
void n(void)

{
  system("/bin/cat /home/user/level7/.pass");
  return;
}

void m(void *param_1,int param_2,char *param_3,int param_4,int param_5)

{
  puts("Nope");
  return;
}

int main(int argc, char **argv)
{
    char *buffer;
    void (**func_ptr)();

    // buffer de 64 octets (0x40)
    buffer = malloc(64);

    // pointeur vers une fonction (4 octets)
    func_ptr = malloc(sizeof(void (*)()));

    // écrire l’adresse de la fonction m() dans func_ptr
    *func_ptr = m;

    // COPIE SANS PROTECTION -> VULNÉRABLE À BUFFER OVERFLOW
    strcpy(buffer, argv[1]);

    // appelle la fonction pointée par func_ptr -> m() normalement,
    // mais modifiable si overflow ! 
    (*func_ptr)();

    return 0;
}

