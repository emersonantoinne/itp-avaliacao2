// ITP - Segunda avaliacao
// Opcao 1 - Boletim de uma pequena turma
//
// O programa le o nome e as tres notas de cada estudante, guarda as notas
// em uma matriz, calcula as medias em um vetor alocado dinamicamente e
// exibe a tabela da turma, a media geral e quem obteve a maior media.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// limites do projeto, facilita alterações se desejar aumentar o numero de dados
#define MAXALUNOS 10    // quantidade maxima de estudantes
#define NUMNOTAS 3      // quantidade de notas por estudante
#define TAMNOME 31      // capacidade do vetor de nome (30 letras + o '\0' que marca o fim da string)
#define TOLERANCIA 0.001  // margem para comparar numeros float

// le o nome de um estudante usando uma mascara de leitura no scanf
void lenome (char nome[], int numaluno){
   printf ("Digite o nome do estudante %d: ", numaluno);
   // o espaco inicial pula o enter que sobrou (assim o nome nunca fica vazio),
   // %30 respeita o tamanho do vetor e [^\n] le tudo, inclusive espacos, ate o enter
   scanf (" %30[^\n]", nome);
   // joga fora o que passou de 30 caracteres
   scanf ("%*[^\n]");
}

// le uma nota e so aceita valores numericos entre 0 e 10, devolve nota (do tipo float)
float lenota (int numnota){
   float nota;
   int leunumero;
   bool valido;

   nota = 0;
   valido = false;
   while (!valido){
      printf ("   Digite a nota %d (entre 0 e 10): ", numnota);
      // o scanf devolve 1 quando conseguiu ler um numero e 0 quando o usuario digitou letras
      leunumero = scanf ("%f", &nota);
      // joga fora o que sobrou na linha ate o enter
      scanf ("%*[^\n]");

      // testa a nota e verifica se ela está dentro do intervalo permitido
      if ((leunumero == 1) && (nota >= 0) && (nota <= 10))
         valido = true;
      else
         printf ("   Nota invalida! Digite um valor entre 0 e 10 (use ponto para decimais).\n");
   }
   return (nota);
}

// calcula a media de cada estudante e escreve o resultado na area de memoria
// apontada por medias, que pertence a quem chamou a funcao (o main)
void calculamedias (float notas[][NUMNOTAS], int qtd, float *medias){
   int i, j;
   float soma;

   for (i = 0; i < qtd; i++){
      soma = 0;
      // percorre as colunas da linha i, no caso as tres notas do aluno
      for (j = 0; j < NUMNOTAS; j++){
         soma += notas[i][j];
      }
      // soma eh float, entao a divisao e real e nao perde as casas decimais
      medias[i] = soma / NUMNOTAS;
   }
}

int main() {
   char nomes[MAXALUNOS][TAMNOME];   // matriz de caracteres, cada linha e o nome de um estudante, com no maximo 30 caracteres
   float notas[MAXALUNOS][NUMNOTAS]; // matriz de notas, onde cada linha é um aluno e as colunas são as 3 notas
   float *medias;                    // vetor dinamico de medias 
   float somamedias, mediageral, maiormedia;
   int qtd, i, j, leunumero;
   bool valido;

   printf ("===== BOLETIM DA TURMA =====\n\n");

   // le a quantidade de estudantes, aceitando apenas valores entre 1 e MAXALUNOS
   qtd = 0;
   valido = false;
   while (!valido){
      printf ("Digite a quantidade de estudantes (entre 1 e %d): ", MAXALUNOS);
      leunumero = scanf ("%d", &qtd);
      scanf ("%*[^\n]");

      if ((leunumero == 1) && (qtd >= 1) && (qtd <= MAXALUNOS))
         valido = true;
      else
         printf ("Quantidade invalida! Tente novamente.\n");
   }

   // aqui ja aloco na memória o vetor de medias, com exatamente uma posicao por estudante
   medias = (float *) malloc (qtd * sizeof (float));
   // verifica se a alocacao deu certo antes de usar a memoria
   if (medias == NULL){
      printf ("Erro: nao foi possivel alocar memoria para as medias.\n");
      return (1);
   }
   // inicializa todas as posicoes do vetor 0, podia ter usado calloc, mas assim ficou mais didático
   for (i = 0; i < qtd; i++){
      medias[i] = 0;
   }

   // le o nome e as tres notas de cada estudante, preenchendo as matrizes
   printf ("\n");
   for (i = 0; i < qtd; i++){
      //chama a função lenome, passando a linha i da matriz de nomes e o numero do aluno,
      //acrescido de um, para que os alunos não comecem de zero.
      lenome (nomes[i], i + 1);
      for (j = 0; j < NUMNOTAS; j++){
         notas[i][j] = lenota (j + 1);
      }
      printf ("\n");
   }

   // passa o endereco do vetor dinamico para a funcao escrever as medias nele
   calculamedias (notas, qtd, medias);

   // exibe a tabela com nome, notas, media e situacao
   printf ("%-30s %6s %6s %6s %6s   %s\n", "NOME", "NOTA1", "NOTA2", "NOTA3", "MEDIA", "SITUACAO");
   for (i = 0; i < qtd; i++){
      printf ("%-30s", nomes[i]);
      for (j = 0; j < NUMNOTAS; j++){
         printf (" %6.2f", notas[i][j]);
      }
      printf (" %6.2f   ", medias[i]);
      // a tolerancia evita que uma media como 5.9999 seja tratada como sendo abaixo de 6
      if (medias[i] >= (6 - TOLERANCIA))
         printf ("atingiu a meta\n");
      else
         printf ("abaixo da meta\n");
   }

   // calcula a media geral da turma e descobre qual foi a maior media
   somamedias = 0;
   maiormedia = medias[0];
   for (i = 0; i < qtd; i++){
      somamedias += medias[i];
      if (medias[i] > maiormedia)
         maiormedia = medias[i];
   }
   mediageral = somamedias / qtd;   // somamedias e float, entao a divisao nao e inteira

   printf ("\nMedia geral da turma: %.2f\n", mediageral);

   // exibe todos os estudantes que tiveram a maior media (trata o caso de empate)
   printf ("Maior media (%.2f) obtida por:\n", maiormedia);
   for (i = 0; i < qtd; i++){
      if ((maiormedia - medias[i]) < TOLERANCIA)
         printf ("   - %s\n", nomes[i]);
   }

   // libera a area da heap, que nao sera mais usada
   free (medias);
   medias = NULL;

   return (0);
}
