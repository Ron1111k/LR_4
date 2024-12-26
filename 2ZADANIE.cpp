#include "LR_4.h"

mutex mtx;

double calculateSum(const vector<BankTransaction>& transactions, const string& operation, const string& startDate, const string& endDate, int startIdx, int endIdx) {
    double sum = 0.0;
    for (int i = startIdx; i < endIdx; ++i) {
        if (transactions[i].operation == operation && transactions[i].date >= startDate && transactions[i].date <= endDate) {
            sum += transactions[i].amount;
        }
    }
    return sum;
}

// ������� ��� ������������� ���������
void threadCalculateSum(const vector<BankTransaction>& transactions, const string& operation, const string& startDate, const string& endDate, double& result, int startIdx, int endIdx) {
    double sum = calculateSum(transactions, operation, startDate, endDate, startIdx, endIdx);
    lock_guard<mutex> lock(mtx);
    result += sum;
}

int main() {
    system("chcp 1251");
    int numTransactions;
    int numThreads;
    string operation;
    string startDate, endDate;

    cout << "������� ���������� ����������: ";
    cin >> numTransactions;

    cout << "������� ���������� �������: ";
    cin >> numThreads;

    vector<BankTransaction> transactions = generateBankTransactions(numTransactions);

    cout << "������� �������� (����������/������/�������/������): ";
    cin >> operation;
    
    cout << "������� ��������� ���� (YYYY-MM-DD): ";
    cin >> startDate;
    
    cout << "������� �������� ���� (YYYY-MM-DD): ";
    cin >> endDate;

    // ��� ���������������
    auto start = chrono::high_resolution_clock::now();
    double sumWithoutThreads = calculateSum(transactions, operation, startDate, endDate, 0, numTransactions);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedWithoutThreads = end - start;

    cout << "����� ��� ���������������: " << sumWithoutThreads << "\n";
    cout << "����� ��������� ��� ���������������: " << elapsedWithoutThreads.count() << " ������\n";

    // � ����������������

    vector<thread> threads;
    vector<double> results(numThreads, 0.0);

    start = chrono::high_resolution_clock::now();
    int chunkSize = numTransactions / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        int startIdx = i * chunkSize;
        int endIdx = (i == numThreads - 1) ? numTransactions : startIdx + chunkSize; // ��������� ���������� �����
        threads.emplace_back(threadCalculateSum, ref(transactions), operation, startDate, endDate, ref(results[i]), startIdx, endIdx);
    }
    
    for (auto& th : threads) {
        th.join();
    }

    double sumWithThreads = 0.0;
    for (const auto& res : results){
        sumWithThreads += res;
    }

    end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedWithThreads = end - start;

    cout << "����� � �������������� ���������������: " << sumWithThreads << "\n";
    cout << "����� ��������� � �������������� ���������������: " << elapsedWithThreads.count() << " ������\n";

    return 0;
}