//menu

int menu(){
do{

int n;

printf("Menu: ");
printf("\n1 - Efetuar Login");
printf("\n2- Cadastrar Usuário");
printf("\n0- Encerrar Programa");
printf("\nSelecione uma das opcoes acima: ");
scanf("%d", n);

swtich(n){
    case 1:
        VerificarLogin(); //tem que completar aqui ainda quando as funções tiverem prontas
        break;
    case 2:
        CadastrarNovoUsuario(); //tem que completar aqui ainda quando as funções tiverem prontas
        break;
    case 0:
        printf("Encerrando Programa...\n");
        break;
    default:
        printf("Opcao invalida tente novamente");
        break;
    }
} while (n != 0);
return 0;

}
