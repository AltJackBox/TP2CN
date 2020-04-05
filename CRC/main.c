#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"

int main (int argc, char * argv[]){

    if (argc == 4){

        // Lecture de G(X)
        char * generateur_tmp = argv[2];
        int size_gen = strlen(generateur_tmp);
        int generateur [size_gen];
        for (int i = 0 ; i < size_gen ; i++){
            generateur[i] = generateur_tmp[i] -  '0';
            if ((generateur[i] != 0) && (generateur[i] != 1)){;
                printf("\nErreur de lecture : le mot générateur de code n'est pas un mot binaire\n\n");
                return 0;
            }
        }
        // Lecture du mode : Codage (C/c) ou Decodage (D/d)
        char mode = argv[3][0]; 

        if ((mode == 'C') || (mode == 'c')){
                // Lecture de D(X)
                char * message_tmp = argv[1]; 
                int size_mess = strlen(message_tmp);
                int message [size_mess];
                for (int i = 0 ; i < size_mess ; i++){
                    message[i] = message_tmp[i] - '0';
                    if ((message[i] != 0) && (message[i] != 1)){
                        printf("\nErreur de lecture : le message n'est pas un mot binaire\n\n");
                        return 0;
                    }
                }
                // Tableau qui va contenir le résultat du codage (le mot binaire de C(X))
                int size_code = size_mess + size_gen - 1;
                int code [size_code];
                codage(message, generateur, code, size_mess, size_gen, size_code);
                printf("\n");
                printf("Codage résultat : \n");
                printf("Message :\n");
                for (int i = 0; i < size_mess ; i++){
                    printf("%d ", message[i]);
                }
                printf("\nReste :\n");
                for (int i = size_mess; i < size_code ; i++){
                    printf("%d ", code[i]);
                }
                printf("\nCodage :\n");
                for (int i = 0; i < size_code ; i++){
                    printf("%d ", code[i]);
                }
                printf("\n");
                printf("\n");
                return 1;
        } else if ((mode == 'D') || (mode == 'd')){
                // Lecture de C(X)
                char * code_tmp = argv[1]; 
                int size_code = strlen(code_tmp); 
                int code [size_code];
                for (int i = 0 ; i < size_code ; i++){
                    code[i] = code_tmp[i] - '0';
                    if ((code[i] != 0) && (code[i] != 1)){
                        printf("\nErreur de lecture : le code n'est pas un mot binaire\n\n");
                        return 0;
                    }
                }
                // Tableau qui va contenir le résultat du décodage
                int size_mess = size_code - size_gen + 1;
                int message [size_mess];
                int erreur;
                erreur = decodage(code, generateur, message, size_mess, size_gen, size_code);
                printf("\n");
                printf("Décodage résultat : \n");
                printf("Message :\n");
                for (int i = 0; i < size_mess ; i++){
                    printf("%d ", message[i]);
                }
                printf("\nReste :\n");
                for (int i = size_mess; i < size_code ; i++){
                    printf("%d ", code[i]);
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
            printf("Entrez le mot binaire de C(X) ou D(X), le mot binaire de G(X), et le mode (codage = C / décodage = D) :\n");
            printf("Exemple : ./essai_codage 1011 10 C (pour le codage du mot D = 1011 par le mot générateur G = 10\n");
            printf("Exemple : ./essai_codage 10110 10 D (pour le decodage du mot D = 10110 par le mot générateur G = 10)\n");
            printf("\n");
            return 0;
        }
    }else{
        printf("\n");
        printf("Nombre incorrect d'arguments\n");
        printf("Entrez le mot binaire de C(X) ou D(X), le mot binaire de G(X), et le mode (codage = C / décodage = D) :\n");
        printf("Exemple : ./essai_codage 1011 10 C (pour le codage du mot D = 1011 par le mot générateur G = 10\n");
        printf("Exemple : ./essai_codage 10110 10 D (pour le decodage du mot D = 10110 par le mot générateur G = 10)\n");
        printf("\n");
        return 0;
    }
}