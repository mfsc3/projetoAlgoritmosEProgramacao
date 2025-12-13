void CadastrarNovoUsuario(){
  FILE *arq_login;
  login log;


  arq_login = fopen("login.bin", "ab");
      if(arq_login == NULL){
          printf("Nenhum arquivo encontrado!");
        return;
    }
  printf("Insira o novo usuario: ");
  scanf(" %[^\n]", log.usuario);

  printf("Insira a nova senha: ");
  scanf(" %[^\n]", log.senha);

  fwrite(&log, sizeof(login), 1, arq_login); 
  fclose(arq_login);

  printf("Usuario cadastrado");
    }
