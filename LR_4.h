#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <random>
#include <iomanip>

using namespace std;

struct BankTransaction {
    std::string cardHolderName;
    std::string cardNumber;
    std::string date; // Формат: YYYY-MM-DD
    std::string operation; // пополнение/снятие/перевод/оплата
    double amount;
};
vector<BankTransaction> generateBankTransactions(int count);
