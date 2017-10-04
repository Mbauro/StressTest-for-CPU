#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#define FFLUSH while(getchar() != '\n')

//Definisco la Flag per fare interrompere il loop
int sig;

void flag(int u){
    printf("\nSegnale ricevuto....\n");
    sig = 1;
}

void *thread_function(void *arg){
    
    while(sig == 0){}
    
    printf("\033[1;36m");
    printf("Ciclo infinito terminato!\n");
    //printf("\033[0m");
    pthread_exit(NULL);
}


int main(void){
    int res;
    short threads_num;
    short num_of_threads;
    void* thread_result;
    //Pulisce lo schermo e riallinea il testo in alto a sx
    printf("\033[2J\033[1;1H");
    //Blue color
    printf("\033[1;34m"); 
    printf("\t\t\t***************************************************\n");
    printf("\t\t\t***************************************************\n");
    printf("\t\t\tBenvenuto in Stress Test per CPU. \n\t\t\tIl programma farà partire diversi thread per sforzare la CPU\n\t\t\tin modo da poterne monitorare la temperatura\n");
    printf("\t\t\t***************************************************\n");
    printf("\t\t\t***************************************************\n");
    //Color reset
    printf("\033[0m");
    printf("\033[1;36m");
    printf("Inserisci il numero di Threads da far partire ------> ");
    scanf("%hu",&num_of_threads);
    FFLUSH;
    //Indicizzo un vettore di Threads
    pthread_t thread[num_of_threads];
    //Creo i threads
    for(threads_num = 1; threads_num <= num_of_threads;threads_num++){
        res = pthread_create(&(thread[threads_num]),NULL,thread_function,NULL);
        if(res != 0){
            printf("Threads creation failed...");
            exit(EXIT_FAILURE);
        }
    }
    printf("I threads stanno generando %hu cicli infiniti\n",num_of_threads);
    sleep(2);

    
    printf("\033[0m");
    //Aspetto il segnale per finire il programma
    (void) signal(SIGINT,flag);
    
        
    while(sig == 0 && num_of_threads >0){
        //Red
        printf("\033[2J\033[1;50H");
        printf("\033[1;31m");
        printf("STRESS TEST IN CORSO.....\n");
        printf("\033[0m");
        system("sensors -A");
        printf("\033[1;36m");
        printf("Premi CTRL + C per terminare il test\n");
        printf("\033[0m");
        sleep(4);
    }
    
    
    for(threads_num = num_of_threads;threads_num > 0 ;threads_num--){
        res = pthread_join(thread[threads_num],&thread_result);
        if(res != 0){
            printf("Impossible for thread to join!\n");
            exit(EXIT_FAILURE);
        }
    }
    sleep(1);
    printf("Tutti i Thread hanno terminato la loro funzione\n");
    printf("Stress Test Completato\n");
    printf("\033[0m");
    exit(EXIT_SUCCESS);
}
