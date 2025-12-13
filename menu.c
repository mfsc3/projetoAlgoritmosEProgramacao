//menu

int menu(){
do{

int n;

printf("Selecione uma das opcoes abaixo: ");
printf("1 - Efetuar Login");
printf("2- Cadastrar Usuário");
printf("0- Encerrar Programa");

swtich(n){
    case 1:
        VerificarLogin();
        break;
    case 2:
        CadastrarNovoUsuario();
        break;
    default:
        printf("Opcao invalida tente novamente");
        break;
    }
} while (n != 3);
printf("Encerrando Programa");
return 0;
}