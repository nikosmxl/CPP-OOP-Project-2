#include <iostream>
#include "bank.h"

int main(int argc, char *argv[]){

    if (argc != 5){
        std::cout << "Give the right data" << std::endl;
        return 1;
    }

    const unsigned int K = std::stoi(argv[1]);
    const unsigned int M = std::stoi(argv[2]);
    const unsigned int N = std::stoi(argv[3]);
    const unsigned int L = std::stoi(argv[4]);

    Bank bank(K, L);

    int customers_remained = 0;

    for (int i = 0 ; i < M ; i++){
        for (int j = 0 ; j < N ; j++){
            if (bank.enter() == false){
                customers_remained++;
            }
        }
        for (int j = 0 ; j < N ; j++){
            bank.serve();
        }
    }
    
    for (int i = 0 ; i < customers_remained ; i++){
        if (bank.enter() == true){
            bank.serve();
        }
    }
    
}