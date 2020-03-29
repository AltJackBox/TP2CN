#include <stdio.h>
#include <stdlib.h>
#include "code.h"

int main (int argc, char * argv[]){

    if (argc == 6){

        // Lecture de G(X)
        int size_gen = atoi(argv[4]); 
        char * generateur_tmp = argv[3];
        int generateur [size_gen];
        for (int i = 0 ; i < size_gen ; i++){
            generateur[i] = generateur_tmp[i] -  '0';
        }
        // Lecture du mode : Codage (C/c) ou Decodage (D/d)
        char mode = argv[5][0]; 

        if ((mode == 'C') || (mode == 'c')){
                // Lecture de D(X)
                int size_mess = atoi(argv[2]); 
                char * message_tmp = argv[1]; 
                int message [size_mess];
                for (int i = 0 ; i < size_mess ; i++){
                    message[i] = message_tmp[i] - '0';
                }
                // Tableau qui va contenir le résultat du codage (le mot binaire de C(X))
                int size_code = size_mess + size_gen - 1;
                int code [size_code];
                codage(message, generateur, code, size_mess, size_gen, size_code);
                printf("\n");
                printf("Codage résultat : \n");
                for (int i = 0; i < size_code ; i++){
                    printf("%d ", code[i]);
                }
                printf("\n");
                return 1;
        } else if ((mode == 'D') || (mode == 'd')){
                // Lecture de C(X)
                int size_code = atoi(argv[2]); 
                char * code_tmp = argv[1]; 
                int code [size_code];
                for (int i = 0 ; i < size_code ; i++){
                    code[i] = code_tmp[i] - '0';
                }
                // Tableau qui va contenir le résultat du décodage
                int size_mess = size_code - size_gen + 1;
                int message [size_mess];
                int erreur;
                erreur = decodage(code, generateur, message, size_mess, size_gen, size_code);
                printf("\n");
                printf("Décodage résultat : \n");
                for (int i = 0; i < size_mess ; i++){
                    printf("%d ", message[i]);
                }
                printf("\n");
                if (erreur == 0){
                    printf("Aucune erreur détectée\n");
                }else {
                    printf("Erreur détectée\n");
                }
                printf("\n");
                return 1;
        }else{
            printf("\n");
            printf("Le mode est incorrect\n");
            printf("Entrez le mot binaire de C(X) ou D(X) puis sa taille, le mot binaire de G(X) puis sa taille, et le mode (codage = C / décodage = D) :\n");
            printf("Exemple : ./essai_codage 1011 4 10 2 C (pour le codage du mot D = 1011 par le polynôme générateur G = 10\n");
            printf("Exemple : ./essai_codage 10110 5 10 2 D (pour le decodage du mot D = 10110 par le polynôme générateur G = 10)\n");
            printf("\n");
            return 0;
        }
    }else{
        printf("\n");
        printf("Nombre incorrect d'arguments\n");
        printf("Entrez le mot binaire C(X) ou D(X) puis sa taille, le mot binaire G(X) puis sa taille, et le mode (codage = C / décodage = D) :\n");
        printf("Exemple : ./essai_codage 1011 4 10 2 C (pour le codage du mot D = 1011 par le polynôme générateur G = 10\n");
        printf("Exemple : ./essai_codage 10110 5 10 2 D (pour le decodage du mot D = 1011 par le polynôme générateur G = 10)\n");
        printf("\n");
        return 0;
    }
}