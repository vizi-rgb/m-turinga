#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -1 means no further move
static int fstate[][3] = { 
                   {1, 5, -1},
                   {1, 2, -1},
                   {3, 2, 4},
                   {3, 3, 0},
                   {4, 4, 6},
                   {5, 5, 6} };

// 0 means no further move
static int direction[][3] = { 
                      {1, 1, 0},
                      {1, 1, 0},
                      {-1, 1, -1},
                      {-1, -1, 1},
                      {-1, -1, 1},
                      {1, 1, 1} };

// x means no further move
static char f_c[][3] = { 
                {'B', 'B', 'x'},
                {'0', '1', 'x'},
                {'1', '1', 'B'},
                {'0', '1', 'B'},
                {'0', 'B', '0'},
                {'B', 'B', 'B'} };

typedef struct {
    int state;
    char curr_c;
    int position;
} *m_t;

char *unary(int m[2]) {
    int i;

    if (m[0] < 0 || m[1] < 0)
        return NULL;

    char *string = malloc(sizeof *string * (m[0] + m[1] + 2));

    for (i = 0; i < m[0] + m[1] + 1; i++) 
        string[i] = i == m[0] ? '1' : '0';

    string[i] = '\0';
    
    return string;

}

void initial_print() {
    printf("\tEmulator maszyny Turina obliczajacy roznice wlasciwa: \n"
           " Q: {q0, q1, q2, q3, q4, q5, q6}\n"
           " Symbole wejsciowe: {0, 1}\n"
           " Symbole tasmowe: {0, 1, B}\n"
           " Symbol pusty: B\n"
           " Stan poczatkowy: q0\n"
           " Stan koncowy: -\n");
}

int move(m_t MT, char *ucode) {
    MT -> curr_c = ucode[MT -> position];

    if (MT -> curr_c != 'B' && MT -> curr_c != '\0') {
        ucode[MT -> position] = f_c[MT -> state][MT -> curr_c - '0'];
        MT -> position += direction[MT -> state][MT -> curr_c - '0'];
        MT -> state = fstate[MT -> state][MT -> curr_c - '0'];
    } else {
        ucode[MT -> position] = f_c[MT -> state][2];
        MT -> position += direction[MT -> state][2];
        MT -> state = fstate[MT -> state][2];
    }

    if (MT -> state == 6) {
        return 0;
    } else if (MT -> curr_c == 'x' || MT -> position < 0 || MT -> state == -1)
        return -1;

    return 1;

}

void print_temp_s(m_t MT, char *ucode) {
    int i = 0;
    while (*(ucode + i)) {
        if (i == MT -> position) 
            printf(" q%d ", MT -> state);

        printf("%c", ucode[i]);
        i++;
    }
    // pozycja 5 dlugosc 4 wydrukuje sie np BBBB i nie 
    // bedzie stanu
    if (MT -> position >= (int)strlen(ucode))
        printf(" q%d ", MT -> state);

    printf("\n");
}


int main(void) {
    int number[2];
    char *unary_code;
    int exit_code;
    m_t MT = malloc(sizeof *MT);
    MT -> state = 0;
    MT -> position = 0;

    initial_print();
    printf("Podaj dwie liczby calkowite nieujemne m i n: ");

    if (scanf("%d %d", number, number + 1) != 2) { 
        printf("Podano zle dane wejsciowe\n");
        return -1;
    }


    if ( (unary_code = unary(number)) == NULL ) {
        printf("Prosze podac liczby calkowite nieujemne\n");
        return -2;
    }

    print_temp_s(MT, unary_code);
    while ((exit_code = move(MT, unary_code)) != 0) {
        print_temp_s(MT, unary_code);
        if (exit_code == -1) {
            printf("blad\n");
            return -1;
        }
    }
    print_temp_s(MT, unary_code);

    return 0;
}
