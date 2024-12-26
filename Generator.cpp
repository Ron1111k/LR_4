#include "LR_4.h"

string generateRandomName() {
    const vector<string> names = {
        "Иван Иванов", "Петр Петров", "Сергей Сергеев", "Алексей Алексеев", "Мария Мариева"
    };
    return names[rand() % names.size()];
}

string generateRandomCardNumber() {
    string cardNumber = "4";
    for (int i = 0; i < 15; ++i) {
        cardNumber += to_string(rand() % 10);
    }
    return cardNumber;
}

string generateRandomDate() {
    int year = 2023; // Текущий год
    int month = rand() % 12 + 1;
    int day = rand() % 28 + 1; // Упрощаем, чтобы избежать проблем с количеством дней в месяце
    ostringstream dateStream;
    dateStream << setw(4) << setfill('0') << year << "-"
               << setw(2) << setfill('0') << month << "-"
               << setw(2) << setfill('0') << day;
    return dateStream.str();
}

string generateRandomOperation() {
    const vector<string> operations = {
        "пополнение", "снятие", "перевод", "оплата"
    };
    return operations[rand() % operations.size()];
}

double generateRandomAmount() {
    return (rand() % 10000) / 100.0; // Сумма в диапазоне от 0 до 100.00
}

vector<BankTransaction> generateBankTransactions(int count) {
    vector<BankTransaction> transactions;
    for (int i = 0; i < count; ++i) {
        BankTransaction transaction;
        transaction.cardHolderName = generateRandomName();
        transaction.cardNumber = generateRandomCardNumber();
        transaction.date = generateRandomDate();
        transaction.operation = generateRandomOperation();
        transaction.amount = generateRandomAmount();
        transactions.push_back(transaction);
    }
    return transactions;
}
