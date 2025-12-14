#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================= ESTRUTURAS ================= */

typedef struct {
    char CRM[6];
    char nome[50];
    char especialidade[20];
    char data_de_nascimento[12];
    float valor_hora_trabalho;
    char telefone[14];
} medico;

typedef struct {
    char CPF[12];
    char nome[30];
    char data_de_nascimento[12];
    char telefone[14];
} paciente;

typedef struct {
    char crm_medico[6];
    char cpf_paciente[12];
    char data[12];
    char sintomas[100];
    char encaminhamentos[100];
} consulta;

/* ================= MÉDICOS ================= */

void InserirNovoMedico() {
    FILE *f = fopen("medicos.bin", "ab");
    medico m;

    if (!f) {
        printf("Erro ao abrir arquivo de médicos.\n");
        return;
    }

    printf("CRM: "); scanf("%5s", m.CRM);
    printf("Nome: "); getchar(); fgets(m.nome, 50, stdin);
    printf("Especialidade: "); fgets(m.especialidade, 20, stdin);
    printf("Data de nascimento: "); scanf("%11s", m.data_de_nascimento);
    printf("Valor hora: "); scanf("%f", &m.valor_hora_trabalho);
    printf("Telefone: "); scanf("%13s", m.telefone);

    fwrite(&m, sizeof(medico), 1, f);
    fclose(f);
}

void BuscarMedicoPorNome() {
    FILE *f = fopen("medicos.bin", "rb");
    medico m;
    char nomeBusca[50];

    if (!f) return;

    printf("Nome do médico: "); getchar(); fgets(nomeBusca, 50, stdin);

    while (fread(&m, sizeof(medico), 1, f)) {
        if (strstr(m.nome, nomeBusca)) {
            printf("CRM: %s | Nome: %s | Esp: %s", m.CRM, m.nome, m.especialidade);
        }
    }
    fclose(f);
}

void ListarMedicosPorEspecialidade() {
    FILE *f = fopen("medicos.bin", "rb");
    medico m;
    char esp[20];

    if (!f) return;

    printf("Especialidade: "); getchar(); fgets(esp, 20, stdin);

    while (fread(&m, sizeof(medico), 1, f)) {
        if (strstr(m.especialidade, esp)) {
            printf("%s - %s", m.nome, m.especialidade);
        }
    }
    fclose(f);
}

void AlterarDadosMedico() {
    FILE *f = fopen("medicos.bin", "r+b");
    medico m;
    char crmBusca[6];

    if (!f) return;

    printf("CRM do médico: "); scanf("%5s", crmBusca);

    while (fread(&m, sizeof(medico), 1, f)) {
        if (strcmp(m.CRM, crmBusca) == 0) {
            printf("Novo telefone: "); scanf("%13s", m.telefone);
            fseek(f, -sizeof(medico), SEEK_CUR);
            fwrite(&m, sizeof(medico), 1, f);
            break;
        }
    }
    fclose(f);
}

/* ================= PACIENTES ================= */

void InserirNovoPaciente() {
    FILE *f = fopen("pacientes.bin", "ab");
    paciente p;

    if (!f) return;

    printf("CPF: "); scanf("%11s", p.CPF);
    printf("Nome: "); getchar(); fgets(p.nome, 30, stdin);
    printf("Nascimento: "); scanf("%11s", p.data_de_nascimento);
    printf("Telefone: "); scanf("%13s", p.telefone);

    fwrite(&p, sizeof(paciente), 1, f);
    fclose(f);
}

void BuscarPacientePorNome() {
    FILE *f = fopen("pacientes.bin", "rb");
    paciente p;
    char nomeBusca[30];

    if (!f) return;

    printf("Nome do paciente: "); getchar(); fgets(nomeBusca, 30, stdin);

    while (fread(&p, sizeof(paciente), 1, f)) {
        if (strstr(p.nome, nomeBusca)) {
            printf("CPF: %s | Nome: %s", p.CPF, p.nome);
        }
    }
    fclose(f);
}

void AlterarDadosPaciente() {
    FILE *f = fopen("pacientes.bin", "r+b");
    paciente p;
    char cpfBusca[12];

    if (!f) return;

    printf("CPF do paciente: "); scanf("%11s", cpfBusca);

    while (fread(&p, sizeof(paciente), 1, f)) {
        if (strcmp(p.CPF, cpfBusca) == 0) {
            printf("Novo telefone: "); scanf("%13s", p.telefone);
            fseek(f, -sizeof(paciente), SEEK_CUR);
            fwrite(&p, sizeof(paciente), 1, f);
            break;
        }
    }
    fclose(f);
}

/* ================= CONSULTAS ================= */

void InserirNovaConsulta() {
    FILE *f = fopen("consultas.bin", "ab");
    consulta c;

    if (!f) return;

    printf("CRM do médico: "); scanf("%5s", c.crm_medico);
    printf("CPF do paciente: "); scanf("%11s", c.cpf_paciente);
    printf("Data: "); scanf("%11s", c.data);
    printf("Sintomas: "); getchar(); fgets(c.sintomas, 100, stdin);
    printf("Encaminhamentos: "); fgets(c.encaminhamentos, 100, stdin);

    fwrite(&c, sizeof(consulta), 1, f);
    fclose(f);
}

void ListarConsultasPorMedico() {
    FILE *f = fopen("consultas.bin", "rb");
    consulta c;
    char crm[6];

    if (!f) return;

    printf("CRM do médico: "); scanf("%5s", crm);

    while (fread(&c, sizeof(consulta), 1, f)) {
        if (strcmp(c.crm_medico, crm) == 0) {
            printf("Data: %s | Paciente: %s", c.data, c.cpf_paciente);
        }
    }
    fclose(f);
}

void ListarConsultasPorPaciente() {
    FILE *f = fopen("consultas.bin", "rb");
    consulta c;
    char cpf[12];

    if (!f) return;

    printf("CPF do paciente: "); scanf("%11s", cpf);

    while (fread(&c, sizeof(consulta), 1, f)) {
        if (strcmp(c.cpf_paciente, cpf) == 0) {
            printf("Data: %s | Médico: %s", c.data, c.crm_medico);
        }
    }
    fclose(f);
}

void ListarConsultasPorData() {
    FILE *f = fopen("consultas.bin", "rb");
    consulta c;
    char data[12];

    if (!f) return;

    printf("Data: "); scanf("%11s", data);

    while (fread(&c, sizeof(consulta), 1, f)) {
        if (strcmp(c.data, data) == 0) {
            printf("Médico: %s | Paciente: %s", c.crm_medico, c.cpf_paciente);
        }
    }
    fclose(f);
}
int main(){




   return 0; 
}