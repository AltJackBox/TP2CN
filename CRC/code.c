#include "code.h"

void codage(int *message, int *generateur, int *resultat, int size_mess, int size_gen, int size_code){

    // G : mot binaire représentant le polynôme générateur
    // D : mot binaire représentant le message à coder
    // T : mot binaire représentant le dividende 

    // Bit de poids fort dans le tableau resultat, il est décalé après chaque Xor avec G
    int idx_res = 0; 
    int idx_res_tmp;
    int idx_gen;

    // Afin d'effectuer le codage, nous effectuons une division euclidienne entre des mots binaires, représentés sous forme de tableaux d'entiers.
    // Le tableau resultat est utilisé afin d'effectuer le calcul du reste de la division entre T et G
    // Au début de l'algorithme, il est initialisé de telle sorte que resultat représente T (le dividende).
    // Le tableau resultat est modifié par des additions modulo 2 (Xor) successives avec G, et à la fin de la boucle do while, les d derniers 
    // éléments du tableau contiennent le reste de la division euclidienne

    for (int i = 0; i < size_mess; i++){
        resultat[i] = message[i];
    }
    for (int i = size_mess; i < size_code; i++){
        resultat[i] = 0;
    }
    do{
        if (idx_res < size_mess){
            idx_res_tmp = idx_res;
            // Xor entre le dividende et G(X)
            for (idx_gen = 0; idx_gen < size_gen; idx_gen++){
                resultat[idx_res_tmp] = (resultat[idx_res_tmp] + generateur[idx_gen]) % 2;
                idx_res_tmp++;
            }
            // Repositionnement du bit de poids fort
            // Si le bit de poids fort est après la position size_mess, resultat contient le reste de la division euclidienne
            while ((resultat[idx_res] != 1) && (idx_res < size_mess)){
                idx_res++;
            }
        }else{
            break;
        }
    } while (1);

    // On remplace le début de resultat par le contenu du message à envoyer
    // Ainsi, les size_mess premiers éléments de resultat contiennent le message et les d derniers éléments contiennent le reste de la division 
    // euclidienne de T par G, et le codage est achevé
    for (int i = 0; i < size_mess; i++){
            resultat[i] = message[i];
    }
}

int decodage(int *code, int *generateur, int *message, int size_mess, int size_gen, int size_code){

    int idx_res = 0;
    int idx_res_tmp;
    int idx_gen;

    // Afin de réaliser le décodage, nous réalisons une divison euclidienne entre le code et le polynôme générateur
    // Ici, nous devons également tester la présence ou non d'erreur lors de la transmission du message en vérifiant que 
    // Le reste calculé est égal à 0
    // Nous utilisons ici le tableau code afin de réaliser les Xor avec G

    // Le message est contenu dans les size_mess premiers bits du code  
    for (int i = 0; i < size_mess; i++){
        message[i] = code[i];
    }
    do{
        if (idx_res < size_mess){
            idx_res_tmp = idx_res;
            // Xor entre le dividende et G(X)
            for (idx_gen = 0; idx_gen < size_gen; idx_gen++){
                code[idx_res_tmp] = (code[idx_res_tmp] + generateur[idx_gen]) % 2;
                idx_res_tmp++;
            }
            // Repositionnement du bit de poids fort
            while ((code[idx_res] != 1) && (idx_res < size_mess)){
                idx_res++;
            }
        }else{
            break;
        }
    } while (1);

    // Si le reste est non nul, il y a une erreur
    for (int i = size_mess; i < size_code; i++){
        if (code[i] != 0){
            return 1;
        }
    }
    return 0;
    
}