#include <iostream>
#include "bank.h"

Cashier::Cashier(int L1){
    open_flag = false;
    serving_flag = false;
    customers_served = 0;
    L = L1;
}

void Cashier::open(){
    open_flag = true;
    customers_served = 0;
}

void Cashier::close(){
    open_flag = false;
    serving_flag = false;
}

void Cashier::serve(){
    serving_flag = true;
}

bool Cashier::free(){
    serving_flag = false;
    if (++customers_served == L){
        open_flag = false;
        return false;
    }
    return true;
}

bool Cashier::is_open() const{
    return open_flag;
}

bool Cashier::is_free() const{
    return !serving_flag;
}

void Bank::open(int i){
    cashiers[i]->open();
    std::cout << "Cashier no " << i + 1 << " just opened." << std::endl;
    open_cashiers_num++;
    next_to_open = (i + 1)%5;
}

void Bank::close(int i){
    cashiers[i]->close();
    std::cout << "Cashier no " << i + 1 << " just closed." << std::endl;
    open_cashiers_num--;
}

int Bank::waiting_customers() const{
    int waiting = last_customer - curr_serving;
    std::cout << waiting << " customers are waiting." << std::endl;
    return waiting;
}

int Bank::open_cashiers() const{
    std::cout << open_cashiers_num << " cashiers are opened." << std::endl;
    return open_cashiers_num;
}

bool Bank::check_to_open() const{
    return (waiting_customers() > open_cashiers_num*K);
}

bool Bank::check_to_close() const{
    return (waiting_customers() <= (open_cashiers_num - 1)*K);
}

Bank::Bank(int K_given, int L_given){
    K = K_given;
    open_cashiers_num = 0;
    next_to_open = 0;
    last_serving_cashier = -1;

    cashiers = new Cashier*[5];

    for (int i = 0 ; i < 5 ; i++){
        cashiers[i] = new Cashier(L_given);
    }
    open(0);                    // Opens the first cashier
    last_customer = 1;
    curr_serving = 1;
}

Bank::~Bank(){
    for(int i = 0 ; i < 5 ; i++){
        delete cashiers[i];
    }

    delete[] cashiers;
}

bool Bank::enter(){
    if (check_to_open() == false){
        last_customer++;
        return true;
    }
    else if (cashiers[next_to_open]->is_open() == false){
        open(next_to_open);
        last_customer++;
        return true;
    }

    std::cout << "Sorry you cannot enter until some customers are served!" << std::endl;
    return false;
}

void Bank::exit(){
    curr_serving++;

    if (check_to_close() == true){
        close((next_to_open + (5 - open_cashiers_num)) % 5);
    }
}

void Bank::serve(){
    bool allclosed = true;
    for (int i = 0 ; i < 5 ; i++){
        if (cashiers[i]->is_open() == true){
            allclosed = false;
        }
    }
    if (allclosed == true){
        open(0);
        std::cout << "Customer no: " << curr_serving << " by cashier no: 1" << std::endl;
        cashiers[0]->serve();
        last_serving_cashier = 0;
        if (cashiers[0]->free() == false){
            std::cout << "Cashier no: 1 is overused. Cashier closed." << std::endl;
        }
        exit();
        return;
    }
    
    while (true){
        last_serving_cashier = (last_serving_cashier + 1) % 5;
        if (cashiers[last_serving_cashier]->is_open() && cashiers[last_serving_cashier]->is_free()){
            std::cout << "Customer no: " << curr_serving << " by cashier no: " << last_serving_cashier + 1 << std::endl;
            cashiers[last_serving_cashier]->serve();
            if (cashiers[last_serving_cashier]->free() == false){
                std::cout << "Cashier no: " << last_serving_cashier + 1 << " is overused. Cashier closed." << std::endl;
            }
            exit();
            return;
        }
    }
    
}