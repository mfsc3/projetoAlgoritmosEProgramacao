#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char usuario[20];
    char senha[10];
}login;

typedef struct {
    char CRM[7];
    char nome[50];
    char especialidade[20];
    char data_de_nascimento[12];
    float valor_hora_trabalho;
    char telefone[14];
}medico;

typedef struct {
    char CPF[13];
    char nome[30];
    char data_de_nascimento[12];
    char telefone[14];
}paciente;

typedef struct {
    char crm_medico[7];
    char cpf_paciente[13];
    char data[12];
    char sintomas[100];
    char encaminhamentos[100];
}consulta;

typedef struct {
    int posicao; // Posição do registro no arquivo binário
    char chave[7]; // CPF ou CRM
}IndexMedico;

typedef struct {
    char chave[13]; // CPF ou CRM
    int posicao; // Posição do registro no arquivo binário
}IndexPaciente;

int encontrarPosicaoInsercaoMedicos(IndexMedico *v, int tam, char *crm);
int encontrarPosicaoInsercaoPacientes(IndexPaciente *vP, int tam, char *cpf);
void InserirVetorMedicos(char *crm, int num);
void InserirVetorPacientes(char *cpf, int num);
void salvarVetorIndexMedico(IndexMedico * v, int tam);
IndexMedico * lerArquivoIndexMedico();
void salvarVetorIndexPaciente(IndexPaciente * vP, int tam);
IndexPaciente * lerArquivoIndexPaciente();

//DECLARANDO FUNÇÕES LOGIN

void CadastrarNovoUsuario();
int VerificarLogin(char *senha, char *usuario);
int EfetuarLogin();
int VerificarUsuario(char *usuario);

//DECLARANDO FUNÇÕES PACIENTE

void BuscarPacientePorNome();
void AlterarDadosPaciente();
void InserirNovoPaciente();

//DECLARANDO FUNÇÕES MEDICO

void InserirNovoMedico();
void BuscarMedicoPorEspecialidade();
void AlterarDadosMedico();
void BuscarMedicoPorNome();
int ValidarPaciente(char *cpf);
int ValidarMedico(char *CRM);

//DECLARANDO FUNÇÔES CONSULTA

void InserirNovaConsulta();
void ListarConsultasPorMedico();
void ListarConsultasPorPaciente();
void ListarConsultasPorData();

IndexMedico *v = NULL;
IndexPaciente *vP = NULL;
int count = 0, countP = 0;


int main(){
    int opcaoMenuInicial, validarLogin = 1, opcaoMenuLogin, opcaoMenuLoginSec;

    //FILE *pointMed, *pointPac;
    //pointMed = fopen("indiceMedicos.bin", );
    v = lerArquivoIndexMedico();
    vP = lerArquivoIndexPaciente();

    /*for(int i = 0; i < count; i++){
        printf("%s\n", v[i].chave);
        printf("%d\n", v[i].posicao);
    }*/

    do{
        printf("\n-----MENU INICIAL-----");
        printf("\n1 - Efetuar Login");
        printf("\n2- Cadastrar Usuário");
        printf("\n0- Encerrar Programa");
        printf("\nSelecione uma das opcoes acima: ");
        scanf("%d", &opcaoMenuInicial);

        switch(opcaoMenuInicial){
        case 0:
            printf("\nEncerrando Programa...");
            opcaoMenuInicial = 0;
        break;
        case 1:
            validarLogin = EfetuarLogin();

            if(validarLogin == 1){
                do{
                    printf("\n-----MENU-----");
                    printf("\n1 - Pacientes\n2 - Medicos\n3 - Consultas\n0 - Voltar");
                    printf("\nSelecione uma das opcoes acima: ");
                    scanf("%d", &opcaoMenuLogin);

                    switch(opcaoMenuLogin){
                    case 0:
                        opcaoMenuLogin = 0;
                    break;
                    case 1:
                        do{
                            printf("\n-----MENU PACIENTE-----");
                            printf("\n1 - Cadastrar Paciente\n2 - Buscar Paciente (Por Nome)\n3 - Alterar Dados do Paciente\n0 - Voltar");
                            printf("\nSelecione uma das opcoes acima: ");
                            scanf("%d", &opcaoMenuLoginSec);

                            switch(opcaoMenuLoginSec){
                                case 0:
                                    opcaoMenuLoginSec = 0;
                                break;
                                case 1:
                                    InserirNovoPaciente();
                                break;
                                case 2:
                                    BuscarPacientePorNome();
                                break;
                                case 3:
                                    AlterarDadosPaciente();
                                break;
                                default:
                                    printf("\nOpcao invalida!");
                                break;
                            }

                        }while(opcaoMenuLoginSec != 0);
                    break;
                    case 2:
                        do{
                            printf("\n-----MENU MEDICO-----");
                            printf("\n1 - Cadastrar Medico\n2 - Buscar Medico (Por Nome)\n3 - Listar Medico por Especialidade\n4 - Alterar Dados do Medico\n0 - Voltar");
                            printf("\nSelecione uma das opcoes acima: ");
                            scanf("%d", &opcaoMenuLoginSec);

                            switch(opcaoMenuLoginSec){
                            case 0:
                                opcaoMenuLoginSec = 0;
                            break;
                            case 1:
                                InserirNovoMedico();
                            break;
                            case 2:
                                BuscarMedicoPorNome();
                            break;
                            case 3:
                                BuscarMedicoPorEspecialidade();
                            break;
                            case 4:
                                AlterarDadosMedico();
                            break;
                            default:
                                printf("\nOpcao invalida!");
                            break;
                            }
                        }while(opcaoMenuLoginSec != 0);
                    break;
                    case 3:
                        do{
                            printf("\n-----MENU CONSULTAS-----");
                            printf("\n1 - Cadastrar Consulta\n2 - Listar Consultas (Por Medico)\n3 - Listar Consultas (Por Paciente)\n4 - Listar Consultas (Por Data)\n0 - Voltar");
                            printf("\nSelecione uma das opcoes acima: ");
                            scanf("%d", &opcaoMenuLoginSec);

                            switch(opcaoMenuLoginSec){
                                case 0:
                                    opcaoMenuLoginSec = 0;
                                break;
                                case 1:
                                    InserirNovaConsulta();
                                break;
                                case 2:
                                    ListarConsultasPorMedico();
                                break;
                                case 3:
                                    ListarConsultasPorPaciente();
                                break;
                                case 4:
                                    ListarConsultasPorData();
                                break;
                                default:
                                    printf("\nOpcao invalida!");
                                break;
                            }
                        }while(opcaoMenuLoginSec != 0);
                    break;
                    default:
                        printf("Opcao invalida!");
                    break;
                }
            }while(opcaoMenuLogin != 0);
        }
        else{
            validarLogin = 0;
        }
        break;
        case 2:
            CadastrarNovoUsuario(); //tem que completar aqui ainda quando as funções tiverem prontas
        break;
        default:
            printf("\nOpcao invalida tente novamente");
        break;
        }
    } while (opcaoMenuInicial != 0 && validarLogin != 0);

    salvarVetorIndexMedico(v,count);
    salvarVetorIndexPaciente(vP, countP);

    free(v);
    free(vP);

    return 0;
}

int encontrarPosicaoInsercaoMedicos(IndexMedico *v, int tam, char *crm) {
    int i = 0, f = tam - 1, meio;

    while (i <= f) {
        meio = (i + f) / 2;

        if (strcmp(v[meio].chave, crm) == 0) {
            return meio;
        }
        if (strcmp(crm, v[meio].chave) > 0) {
            i = meio + 1;
        } else {
            f = meio - 1;
        }
    }
    return i;
}

int encontrarPosicaoInsercaoPacientes(IndexPaciente *vP, int tam, char *cpf) {
    int i = 0, f = tam - 1, meio;

    while (i <= f) {
        meio = (i + f) / 2;

        if (strcmp(vP[meio].chave, cpf) == 0) {
            return meio;
        }
        if (strcmp(cpf, vP[meio].chave) > 0) {
            i = meio + 1;
        } else {
            f = meio - 1;
        }
    }
    return i;
}

void salvarVetorIndexMedico(IndexMedico * v, int tam){
    FILE *point;

    point = fopen("IndexMedico.bin", "wb");

    if (point == NULL) {
        return;
    }

    fwrite(&tam, sizeof(int), 1, point);

    fwrite(v, sizeof(IndexMedico), tam, point);

    fclose(point);
}

IndexMedico * lerArquivoIndexMedico(){
    FILE *point;
    point = fopen("IndexMedico.bin", "rb");

    if (point == NULL) {
        return NULL;
    }

    fread(&count, sizeof(int), 1, point);

    if (count == 0){
        fclose(point);
        return NULL;
    }

    v = (IndexMedico *)malloc(count * sizeof(IndexMedico));


    fread(v, sizeof(IndexMedico), count, point);

    fclose(point);
    return v;
}
void salvarVetorIndexPaciente(IndexPaciente * vP, int tam){
    FILE *point;

    point = fopen("IndexPaciente.bin", "wb");

    if (point == NULL) {
        return;
    }

    fwrite(&tam, sizeof(int), 1, point);

    fwrite(vP, sizeof(IndexPaciente), tam, point);

    fclose(point);
}

IndexPaciente * lerArquivoIndexPaciente(){
    FILE *point;
    point = fopen("IndexPaciente.bin", "rb");

    if (point == NULL) {
        return NULL;
    }

    fread(&countP, sizeof(int), 1, point);


    if (countP == 0){
        fclose(point);
        return NULL;
    }

    vP = (IndexPaciente *)malloc(countP * sizeof(IndexPaciente));

    fread(vP, sizeof(IndexPaciente), countP, point);

    fclose(point);
    return vP;
}

void InserirVetorPacientes(char *cpf, int num){
    int posicao = encontrarPosicaoInsercaoPacientes(vP, countP, cpf);

    countP++;

    vP = (IndexPaciente *)realloc(vP, countP * sizeof(IndexPaciente));

    for (int i = countP - 1; i > posicao; i--) {
        vP[i] = vP[i - 1];
    }

    strcpy(vP[posicao].chave, cpf);
    vP[posicao].posicao = num;
}

void InserirVetorMedicos(char *crm, int num){
    int posicao = encontrarPosicaoInsercaoMedicos(v, count, crm);
    count++;

    v = (IndexMedico *)realloc(v, count * sizeof(IndexMedico));

    for (int i = count - 1; i > posicao; i--) {
        v[i] = v[i - 1];
    }

    strcpy(v[posicao].chave, crm);
    v[posicao].posicao = num;
}

//FUNCOES MENU INICIAL

int VerificarUsuario(char *usuario){

    FILE *pont;
    login log;

    pont = fopen("login.bin", "rb");

    while(fread(&log, sizeof(login), 1, pont) == 1){
        if(strcmp(log.usuario, usuario) == 0){
            return 1;
        }
    }
    fclose(pont);

    return 0;
}

int EfetuarLogin(){
    login log;
    int tentativa = 0;

    printf("\n-----LOGIN-----");
    do{
        printf("\nDigite seu usuario: ");
        scanf(" %[^\n]", log.usuario);
        printf("\nDigite sua senha: ");
        scanf(" %[^\n]", log.senha);

        if(VerificarLogin(log.senha, log.usuario) != 1){
            printf("\nErro: usuario ou senha invalidos");
            tentativa++;
        }
        else{
            printf("\nLogin autenticado!");
            return 1;
        }

    }while(tentativa < 3);

    printf("\nMaximo de tentativas alcancada!");
    return 0;
}

int VerificarLogin(char *senha, char *usuario){

    FILE *pont;
    login log;

    pont = fopen("login.bin", "rb");

    while(fread(&log, sizeof(login), 1, pont) == 1){
        if(strcmp(log.usuario, usuario) == 0 && strcmp(log.senha, senha) == 0){
            return 1;
        }
    }
    fclose(pont);

    return 0;
}

void CadastrarNovoUsuario(){
    FILE *arq_login;
    login log;

    arq_login = fopen("login.bin", "ab");

    if(arq_login == NULL){
        printf("Nenhum arquivo encontrado!");
        return;
    }

    printf("\n-----CADASTRAR USUARIO-----");
    printf("\nInsira o novo usuario: ");
    scanf(" %[^\n]", log.usuario);

    printf("Insira a nova senha: ");
    scanf(" %[^\n]", log.senha);

    if(VerificarUsuario(log.usuario) != 1){
        fwrite(&log, sizeof(login), 1, arq_login);
        fclose(arq_login);

        printf("\nUsuario cadastrado");
    }
    else{
        printf("\nUsuario ja existente!");
    }
}

//FUNCOES MENU MEDICOS

int ValidarMedico(char *CRM){
    int busca = encontrarPosicaoInsercaoMedicos(v, count, CRM);

    if (count == 0)
        return 0;
    if(strcmp(v[busca].chave, CRM) == 0)
        return 1;

    return 0;
}

void InserirNovoMedico() {
    FILE *arq = fopen("medicos.bin", "ab");
    medico m;
    int posicao = 0;

    if (arq == NULL) return;

    printf("\n-----CADASTRAR MEDICO-----");
    printf("\nDigite o CRM do medico: ");
    scanf(" %[^\n]", m.CRM);

    if(ValidarMedico(m.CRM) == 0)
    {
        printf("Digite o nome do medico: ");
        scanf(" %[^\n]", m.nome);
        printf("Digite a especialidade do medico: ");
        scanf(" %[^\n]", m.especialidade);
        printf("Digite a data de nascimento do medico: ");
        scanf(" %[^\n]", m.data_de_nascimento);
        printf("Digite o valor da hora trabalhada pelo medico: ");
        scanf("%f", &m.valor_hora_trabalho);
        printf("Digite o telefone do medico: ");
        scanf(" %[^\n]", m.telefone);

        fwrite(&m, sizeof(medico), 1, arq);

        posicao = ftell(arq) / sizeof(medico);

        InserirVetorMedicos(m.CRM, posicao);
    }
    else{

        printf("\nMedico ja cadastrado!");
    }
    fclose(arq);
}

void BuscarMedicoPorNome(){
    FILE *arq = fopen("medicos.bin", "rb");
    medico m;
    char nomeBusca[50];

    if (arq == NULL) return;

    printf("\n-----BUSCAR MEDICO (PELO NOME)-----");
    printf("\nDigite o nome do medico para a busca: ");
    scanf(" %[^\n]", nomeBusca);

    while (fread(&m, sizeof(medico), 1, arq))
        if (strcmp(m.nome, nomeBusca) == 0)
            printf("%s %s\n", m.CRM, m.especialidade);

    fclose(arq);
}

void BuscarMedicoPorEspecialidade(){
    FILE *arq = fopen("medicos.bin", "rb");
    medico m;
    char especialidade[50];

    if (arq == NULL) return;

    printf("\n-----BUSCAR MEDICO (POR ESPECIALIDADE)-----");
    printf("\nDigite a especialidade para fazer a busca: ");
    scanf(" %[^\n]", especialidade);

    while (fread(&m, sizeof(medico), 1, arq) == 1)
        if (strcmp(m.especialidade, especialidade) == 0)
            printf("%s %s\n", m.nome, m.CRM);
    fclose(arq);
}

void AlterarDadosMedico() {
    FILE *f = fopen("medicos.bin", "r+b");
    medico m;
    char crm[7];

    if (!f) return;

    printf("CRM do medico: ");
    scanf(" %[^\n]", crm);

    if(ValidarMedico(crm) == 1)
    {
        while (fread(&m, sizeof(medico), 1, f)) {
            if (strcmp(m.CRM, crm) == 0) {
                printf("Nome: "); scanf(" %[^\n]", m.nome);
                printf("Especialidade: "); scanf(" %[^\n]", m.especialidade);
                printf("Data de nascimento: "); scanf(" %[^\n]", m.data_de_nascimento);
                printf("Valor da hora trabalhada: "); scanf("%f", &m.valor_hora_trabalho);
                printf("Novo telefone: "); scanf(" %[^\n]", m.telefone);
                fseek(f, -sizeof(medico), SEEK_CUR);
                fflush(f);
                fwrite(&m, sizeof(medico), 1, f);
                break;
            }
        }
    }
    else{
        printf("\nCRM nao encontrado!");
    }
    fclose(f);
}

//FUNCOES PACIENTES

int validarPaciente(char *cpf){

    int busca = encontrarPosicaoInsercaoPacientes(vP, countP, cpf);

    if (countP == 0)
        return 0;
    if(strcmp(vP[busca].chave, cpf) == 0)
        return 1;

    return 0;
}

void AlterarDadosPaciente() {
    FILE *f = fopen("pacientes.bin", "r+b");
    paciente p;
    char cpfBusca[13];

    if (!f) return;

    printf("CPF do paciente: ");
    scanf(" %[^\n]", cpfBusca);

    if(validarPaciente(cpfBusca) == 1)
    {
        while (fread(&p, sizeof(paciente), 1, f)) {
            if (strcmp(p.CPF, cpfBusca) == 0) {
                printf("Nome: "); scanf(" %[^\n]", p.nome);
                printf("Novo telefone: "); scanf(" %[^\n]", p.telefone);
                printf("Data de nascimento: "); scanf(" %[^\n]", p.data_de_nascimento);
                fseek(f, -sizeof(paciente), SEEK_CUR);
                fflush(f);
                fwrite(&p, sizeof(paciente), 1, f);
                break;
            }
        }
    }
    else{
        printf("\nPaciente Nao Encontrado!");
    }
    fclose(f);
}

void BuscarPacientePorNome() {
    FILE *f = fopen("pacientes.bin", "rb");
    paciente p;
    char nomeBusca[30];

    if (!f) return;

    printf("Nome do paciente: ");
    scanf(" %[^\n]", nomeBusca);

    while (fread(&p, sizeof(paciente), 1, f) == 1) {
        if (strcmp(p.nome, nomeBusca) == 0) {
            printf("CPF: %s | Nome: %s", p.CPF, p.nome);
        }
    }
    fclose(f);
}

void InserirNovoPaciente() {
    FILE *f = fopen("pacientes.bin", "ab");
    paciente p;
    int posicao = 0;

    if (!f) return;

    printf("CPF: ");
    scanf(" %[^\n]", p.CPF);

    if(validarPaciente(p.CPF) == 0){
        printf("Nome: ");
        scanf(" %[^\n]", p.nome);
        printf("Nascimento: ");
        scanf(" %[^\n]", p.data_de_nascimento);
        printf("Telefone: ");
        scanf(" %[^\n]", p.telefone);

        fwrite(&p, sizeof(paciente), 1, f);

        posicao = ftell(f) / sizeof(paciente);

        InserirVetorPacientes(p.CPF, posicao);
    }
    else{
        printf("\nPaciente Ja Cadastrado!");
    }
    fclose(f);
}

//FUNCOES CONSULTAS

void InserirNovaConsulta() {
    FILE *f = fopen("consultas.bin", "ab");
    consulta c;

    if (!f) return;

    printf("CRM do médico: ");
    scanf(" %[^\n]", c.crm_medico);

   if(ValidarMedico(c.crm_medico) == 1){
        printf("CPF do paciente: ");
        scanf(" %[^\n]", c.cpf_paciente);
        if(validarPaciente(c.cpf_paciente) == 1){
            printf("Data: ");
            scanf(" %[^\n]", c.data);
            printf("Sintomas: ");
            scanf(" %[^\n]", c.sintomas);
            printf("Encaminhamentos: ");
            scanf(" %[^\n]", c.encaminhamentos);

            fwrite(&c, sizeof(consulta), 1, f);
        }
        else{
            printf("\nPaciente Nao Cadastrado!");
        }
    }
    else
        printf("\nCRM invalido!");

    fclose(f);
}

void ListarConsultasPorMedico() {
    FILE *f = fopen("consultas.bin", "rb");
    consulta c;
    char crm[7];

    if (!f) return;

    printf("CRM do médico: ");
    scanf(" %[^\n]", crm);

    if(ValidarMedico(crm) == 1){
        while (fread(&c, sizeof(consulta), 1, f) == 1) {
            if (strcmp(c.crm_medico, crm) == 0) {
                printf("\nData: %s | Paciente: %s", c.data, c.cpf_paciente);
            }
        }
    }
    else{
        printf("\nCRM invalido!");
    }
    fclose(f);
}

void ListarConsultasPorPaciente() {
    FILE *f = fopen("consultas.bin", "rb");
    consulta c;
    char cpf[13];

    if (!f) return;

    printf("CPF do paciente: ");
    scanf(" %[^\n]", cpf);

    if(validarPaciente(cpf) == 1){
        while (fread(&c, sizeof(consulta), 1, f) == 1) {
            if (strcmp(c.cpf_paciente, cpf) == 0) {
                printf("Data: %s | Médico: %s", c.data, c.crm_medico);
            }
        }
    }
    else{
        printf("\nPaciente Nao Cadastrado!");
    }
    fclose(f);
}

void ListarConsultasPorData() {
    FILE *f = fopen("consultas.bin", "rb");
    consulta c;
    char data[12];

    if (!f) return;

    printf("Data: ");
    scanf(" %1[^\n]", data);

    while (fread(&c, sizeof(consulta), 1, f)) {
        if (strcmp(c.data, data) == 0) {
            printf("Médico: %s | Paciente: %s", c.crm_medico, c.cpf_paciente);
        }
    }
    fclose(f);
}
