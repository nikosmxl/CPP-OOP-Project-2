#include <iostream>

class Cashier{
    bool open_flag;
    bool serving_flag;
    int customers_served;
    int L;

    public:
    Cashier(int L1);
    void open();
    void close();
    void serve();
    bool free();

    bool is_open() const;
    bool is_free() const;
};

class Bank{
    int last_customer;
    int curr_serving;
    Cashier** cashiers;
    int last_serving_cashier;
    short open_cashiers_num;
    short next_to_open;
    int K;
    
    void open(int);
    void close(int);
    void exit();
    bool check_to_open() const;
    bool check_to_close() const;
    int waiting_customers() const;
    int open_cashiers() const;

    public:
    Bank(int K_given, int L_given);
    ~Bank();
    bool enter();
    void serve();
    
};