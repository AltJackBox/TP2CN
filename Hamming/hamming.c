#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define max(a,b) (a<b ? b : a)

#define min(a,b) (a>b ? b : a)

int plus(int a, int b) {
    return ((a && b) || (!a && !b) ? 0 : 1);
}

int partieEntiereSup(float a) {
    int b = (int)a;
    return (a==b ? b : b+1);
}

typedef struct Hamcode{
    int *tab;
    int k;
    int r;
} *code;

typedef struct posBin {
    int *tab; //bit de poid faible à gauche
    int n;
} *binary;

binary createBin(int n) {
    binary b = (binary)malloc(sizeof(struct posBin));
    b->n = n;
    b->tab = (int*)malloc(sizeof(int)*n);
    for (int i=0; i<n; i++) {
        b->tab[i] = 0;
    }
    return b;
}

void destructBin(binary b) {
    free(b->tab);
    free(b);
}

void tradBin(int n, binary b) {
    // printf("1!\n");
    int idx = 0;
    while (n>0) {
        if (n%2 == 0) {
            b->tab[idx] = 0;
            n = n/2;
        } else {
            b->tab[idx] = 1;
            n = (n-1)/2;
        }
        idx++;
    }
    for (; idx<b->n; idx++) {
        b->tab[idx] = 0;
    }
}

int tradBinInverse(binary b) {
    int res = 0;
    for (int i=0; i<b->n; i++) {
        if (b->tab[i]) {
            res += pow(2,i);
        }
    }
    return res;
}

void afficherBin(binary b) {
    for (int i=0; i<b->n; i++) {
        printf("%d",b->tab[i]);
    }
    printf("\n");
}

code creerCode(int k,char *tab) {
    int r = partieEntiereSup(log(k)/log(2))+1;
    code mot = (code)malloc(sizeof(struct Hamcode));
    mot->tab = (int*)malloc(sizeof(int)*(r+pow(2,r-1)));
    mot->k = k;
    mot->r = r;
    int posMot = 0;
    int puissanceDe = 0;
    int i;
    for (i=1; i<=r+k; i++) {
        if (i == pow(2,puissanceDe)) {
            puissanceDe++;
            mot->tab[i-1] = 0;
        } else {
            mot->tab[i-1] = (int)(tab[posMot]-'0');
            posMot++;
        }
    }
    for (; i<=r+pow(2,r-1); i++) {
        mot->tab[i-1] = 0;
    }
    return mot;
}

void destructCode(code mot) {
    free(mot->tab);
    free(mot);
}

void encode(code mot) {
    for (int i=0; i<mot->r; i++) {
        int j = pow(2,i)-1;
        while (j < mot->k+mot->r) {
            for (int k=0; k<pow(2,i); k++) {
                mot->tab[((int)pow(2,i))-1] = plus(mot->tab[((int)pow(2,i))-1],mot->tab[j]);
                j++;
            }
            for (int k=0; k<pow(2,i); k++) {
                j++;
            }
        }
    }
}

void plusBin(binary a, binary b) {
    if (a->n<b->n) {
        a->tab = (int*)realloc(a->tab,sizeof(int)*b->n);
        a->n = b->n;
    }
    int i;
    for (i=0; i<b->n; i++) {
        a->tab[i] = plus(a->tab[i],b->tab[i]);
    }
}

int *decode(code mot) {
    int *dec = (int*)malloc(sizeof(int)*mot->k);

    binary res = createBin(mot->r+1);
    binary temp = createBin(mot->r+1);
    for (int i=0; i<mot->k+mot->r; i++) {
        if (mot->tab[i]) {
            tradBin(i+1,temp);
            plusBin(res,temp);
        }
    }
    afficherBin(res);
    int pos = tradBinInverse(res);
    printf("pos = %d\n",pos);
    if (pos) {
        mot->tab[pos-1] = plus(mot->tab[pos-1],1);
    }
    int posMot = 0;
    int puissanceDe = 0;
    int i;
    for (i=1; i<=mot->r+mot->k; i++) {
        if (i == pow(2,puissanceDe)) {
            puissanceDe++;
        } else {
            dec[posMot] = mot->tab[i-1];
            posMot++;
        }
    }

    // destructBin(res);
    // destructBin(temp);
    return dec;
}

void afficher(code mot) {
    printf("mot code : ");
    for (int i=0; i<mot->k+mot->r; i++) {
        printf("%c",mot->tab[i]+'0');
    }
    printf("\n");
    printf("k : %d\nr : %d\n",mot->k,mot->r);
}

void afficherErr(code mot, int err) {
    printf("Erreur : ");
    for (int i=0; i<mot->k+mot->r; i++) {
        if (i == err) {
            printf ("\033[31;01m%c\033[00m",mot->tab[i]+'0');
        } else {
            printf("%c",mot->tab[i]+'0');
        }
    }
    printf("\n");
}

void afficherRes(code mot, int err) {
    printf("Resolu : ");
    for (int i=0; i<mot->k+mot->r; i++) {
        if (i == err) {
            printf ("\033[32;01m%c\033[00m",mot->tab[i]+'0');
        } else {
            printf("%c",mot->tab[i]+'0');
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("erreur\n");
        return 1;
    }

    code mot = creerCode(strlen(argv[1]),argv[1]);
    encode(mot);
    afficher(mot);

    srand(time(NULL));
    int erreur = rand()%(mot->k+mot->r);
    mot->tab[erreur] = plus(mot->tab[erreur],1);
    afficherErr(mot,erreur);

    int *dec = decode(mot);
    afficherRes(mot,erreur);
    printf("mot decode : ");
    for (int i=0; i<mot->k; i++) {
        printf("%d",dec[i]);
    }
    printf("\n");
    // destructCode(mot);
    // free(dec);
}
