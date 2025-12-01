
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

    buffer = malloc(64);
    func_ptr = malloc(sizeof(void (*)()));
    *func_ptr = m;
    strcpy(buffer, argv[1]);
    (*func_ptr)();

    return 0;
}

