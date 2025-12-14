void VerificarLogin(){
    FILE *arq_login;
    login log;

    arq_login = fopen("login.bin", "ab");
    if(arq_login == NULL){
        printf("Não ha usuarios cadastrados.");
        return;
    }
    printf("Usuario: ");
    scanf(" %[^\n]", log.usuario);
    printf("\nSenha: ");
    scanf(" %[^\n]", log.senha);

    while (fread(&log, sizeof(login), 1, arq_login) == 1){
        if(strcmp(log.usuario, log.senha) == 0 && strcmp(log.senha, log.usuario) == 0){
            printf("Usuário Encontrado");
        } else {
            printf("Usuario ou senha incorretos, tente novamente (2 tentativas restantes)");
                if(strcmp(log.usuario, log.senha) == 0 && strcmp(log.senha, log.usuario) == 0){
                printf("Usuário Encontrado");
                } else {
                printf("Usuario ou senha incorretos, tente novamente (1 tentativas restantes)");
                    if(strcmp(log.usuario, log.senha) == 0 && strcmp(log.senha, log.usuario) == 0){
                    printf("Usuário Encontrado");
                    } else {
                        printf("Usuario e senha incorretos, retornando para o Menu");
                        return;
                    }   
                }
            }
        }
    fclose(arq_login);
    }
