# ITP - Segunda Avaliação: Boletim de uma pequena turma

## Identificação

- **Nome:** EMERSON ANTOINNE SANTOS DE ARAUJO
- **Projeto escolhido:** Opção 1 - Boletim de uma pequena turma

## Descrição

O programa registra três notas de cada estudante de uma pequena turma e apresenta um resumo dos resultados.

Funcionalidades implementadas:

- Leitura da quantidade de estudantes, aceitando apenas valores entre 1 e 10.
- Leitura do nome de cada estudante com a máscara `scanf (" %30[^\n]", nome)`, que respeita a capacidade do vetor (até 30 caracteres), aceita espaços entre os nomes e não permite nome vazio.
- Leitura de três notas por estudante, aceitando apenas valores entre 0 e 10. Entradas como `11` ou `abc` são rejeitadas e solicitadas novamente.
- Depois de cada leitura numérica, a máscara `scanf ("%*[^\n]")` descarta o que sobrou na linha, para que letras digitadas por engano não atrapalhem a próxima leitura.
- Armazenamento das notas na matriz `notas[10][3]` (linhas = estudantes, colunas = avaliações) e dos nomes na matriz de caracteres `nomes[10][31]`.
- Cálculo da média de cada estudante, armazenada em um vetor alocado dinamicamente com `malloc`, com uma posição por estudante. A função `calculamedias` recebe um ponteiro para esse vetor e escreve as médias nele.
- Exibição de uma tabela com nome, notas, média e situação: "atingiu a meta" (média maior ou igual a 6) ou "abaixo da meta".
- Exibição da média geral da turma e do nome de quem obteve a maior média. Em caso de empate, todos os nomes empatados são exibidos.
- Verificação do retorno do `malloc`, inicialização do vetor antes do uso e liberação com `free` ao final.

Organização do código (`main.c`):

| Função | Responsabilidade |
|---|---|
| `lenome` | Lê e valida o nome de um estudante |
| `lenota` | Lê e valida uma nota entre 0 e 10 |
| `calculamedias` | Calcula as médias e escreve no vetor dinâmico recebido por ponteiro |
| `main` | Lê a quantidade, aloca e libera a memória, exibe a tabela e o resumo |

## Compilação e execução

Com GCC no Linux ou macOS:

```bash
gcc -std=c11 -Wall -Wextra main.c -o programa
./programa
```

No Windows (MinGW):

```bash
gcc -std=c11 -Wall -Wextra main.c -o programa.exe
programa.exe
```

Observação: as notas com casas decimais devem ser digitadas com ponto (ex.: `7.5`). Se for digitada vírgula (`7,5`), o programa lê apenas a parte antes da vírgula (`7`).

## Testes

### Teste 1 - funcionamento normal (com empate na maior média)

Entradas:

```
Quantidade de estudantes: 3
Estudante 1: Ana         notas: 5, 6, 7
Estudante 2: Bruno Souza notas: 8, 9, 10
Estudante 3: Carla       notas: 9, 10, 8
```

Resultado esperado:

```
NOME                            NOTA1  NOTA2  NOTA3  MEDIA   SITUACAO
Ana                              5.00   6.00   7.00   6.00   atingiu a meta
Bruno Souza                      8.00   9.00  10.00   9.00   atingiu a meta
Carla                            9.00  10.00   8.00   9.00   atingiu a meta

Media geral da turma: 8.00
Maior media (9.00) obtida por:
   - Bruno Souza
   - Carla
```

A média de Ana (5, 6 e 7) é exatamente 6, por isso ela "atingiu a meta". Bruno e Carla empataram com 9.00 e os dois aparecem como maior média.

### Teste 2 - entradas inválidas e situações de limite

| Entrada | Resultado esperado |
|---|---|
| Quantidade `0` | `Quantidade invalida! Tente novamente.` e nova solicitação |
| Quantidade `11` | `Quantidade invalida! Tente novamente.` e nova solicitação |
| Quantidade `abc` | `Quantidade invalida! Tente novamente.` e nova solicitação |
| Nome vazio (apenas Enter) | O programa ignora o Enter e continua esperando o nome |
| Nota `11` | `Nota invalida! Digite um valor entre 0 e 10 (use ponto para decimais).` e a mesma nota é solicitada novamente |
| Nota `xyz` | Mesma mensagem de nota inválida e nova solicitação |
| Nome com mais de 30 caracteres | O nome é guardado com os 30 primeiros caracteres e o excesso é descartado |
| Notas `0` e `10` | Aceitas, pois são os limites do intervalo |

### Teste 3 - média no limite da meta

Entradas: estudante com notas `5.9`, `6` e `6.1`.

Resultado esperado: média `6.00` e situação "atingiu a meta". O programa usa uma pequena tolerância na comparação para que erros de arredondamento do `float` não deixem essa média como 5.9999.

## Vídeo

Link da apresentação no YouTube: https://youtu.be/xBW8fEkG1lE

## Referências

- Material das aulas 6 a 11 da disciplina ITP (matrizes, tipos de dados, strings, estrutura de memória, memória estática e heap, ponteiros e alocação dinâmica).
- W3Schools: https://www.w3schools.com/
- SCHILDT, Herbert. Turbo C: guia do usuário. 2. ed. São Paulo: McGraw-Hill, 1988. 414 p.
