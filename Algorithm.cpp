#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class BankersAlgorithm {
public:
    void run();

private:
    int numProcesses;
    int numResources;
    vector<int> available;
    vector<vector<int>> max;
    vector<vector<int>> allocation;
    vector<vector<int>> need;

    void input();
    bool isSafe();
    void calculateNeed();
    bool requestResources(int process, const vector<int>& request);
};

void BankersAlgorithm::input() {
    cout << "Введите количество процессов: ";
    cin >> numProcesses;
    cout << "Введите количество ресурсов: ";
    cin >> numResources;

    available.resize(numResources);
    cout << "Введите доступные ресурсы: ";
    for (int i = 0; i < numResources; ++i) {
        cin >> available[i];
    }

    max.resize(numProcesses, vector<int>(numResources));
    cout << "Введите максимальные ресурсы для каждого процесса:\n";
    for (int i = 0; i < numProcesses; ++i) {
        cout << "Процесс " << i << ": ";
        for (int j = 0; j < numResources; ++j) {
            cin >> max[i][j];
        }
    }

    allocation.resize(numProcesses, vector<int>(numResources));
    cout << "Введите выделенные ресурсы для каждого процесса:\n";
    for (int i = 0; i < numProcesses; ++i) {
        cout << "Процесс " << i << ": ";
        for (int j = 0; j < numResources; ++j) {
            cin >> allocation[i][j];
        }
    }

    calculateNeed();
}

void BankersAlgorithm::calculateNeed() {
    need.resize(numProcesses, vector<int>(numResources));
    for (int i = 0; i < numProcesses; ++i) {
        for (int j = 0; j < numResources; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool BankersAlgorithm::isSafe() {
    vector<int> work = available;
    vector<bool> finish(numProcesses, false);
    vector<int> safeSequence;

    int count = 0;
    while (count < numProcesses) {
        bool found = false;
        for (int p = 0; p < numProcesses; ++p) {
            if (!finish[p]) {
                // Check if need <= work
                bool canProceed = true;
                for (int j = 0; j < numResources; ++j) {
                    if (need[p][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    for (int j = 0; j < numResources; ++j) {
                        work[j] += allocation[p][j];
                    }
                    safeSequence.push_back(p);
                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            cout << "Система не в безопасном состоянии.\n";
            return false;
        }
    }

    cout << "Система в безопасном состоянии.\n";
    cout << "Безопасная последовательность: ";
    for (int p : safeSequence) {
        cout << p << " ";
    }
    cout << endl;

    return true;
}

bool BankersAlgorithm::requestResources(int process, const vector<int>& request) {
    // Check if request <= need
    for (int j = 0; j < numResources; ++j) {
        if (request[j] > need[process][j]) {
            cout << "Ошибка: Запрос превышает потребность.\n";
            return false;
        }
    }

    // Check if request <= available
    for (int j = 0; j < numResources; ++j) {
        if (request[j] > available[j]) {
            cout << "Ошибка: Запрос превышает доступные ресурсы.\n";
            return false;
        }
    }

    // Pretend to allocate resources
    for (int j = 0; j < numResources; ++j) {
        available[j] -= request[j];
        allocation[process][j] += request[j];
        need[process][j] -= request[j];
    }

    // Check if the system is in a safe state
    if (isSafe()) {
        return true;
    } else {
        // Rollback
        for (int j = 0; j < numResources; ++j) {
            available[j] += request[j];
            allocation[process][j] -= request[j];
            need[process][j] += request[j];
        }
        cout << "Система вернулась в небезопасное состояние после запроса.\n";
        return false;
    }
}

void BankersAlgorithm::run() {
    input();

    // Пример запроса ресурсов
    int process;
    cout << "Введите номер процесса для запроса ресурсов: ";
    cin >> process;

    vector<int> request(numResources);
    cout << "Введите запрос ресурсов для процесса " << process << ": ";
    for (int i = 0; i < numResources; ++i) {
        cin >> request[i];
    }

    requestResources(process, request);
}

int main() {
   system("chcp 1251");
    BankersAlgorithm bankers;
    bankers.run();

    return 0;
}