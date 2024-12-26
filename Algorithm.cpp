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
    cout << "������� ���������� ���������: ";
    cin >> numProcesses;
    cout << "������� ���������� ��������: ";
    cin >> numResources;

    available.resize(numResources);
    cout << "������� ��������� �������: ";
    for (int i = 0; i < numResources; ++i) {
        cin >> available[i];
    }

    max.resize(numProcesses, vector<int>(numResources));
    cout << "������� ������������ ������� ��� ������� ��������:\n";
    for (int i = 0; i < numProcesses; ++i) {
        cout << "������� " << i << ": ";
        for (int j = 0; j < numResources; ++j) {
            cin >> max[i][j];
        }
    }

    allocation.resize(numProcesses, vector<int>(numResources));
    cout << "������� ���������� ������� ��� ������� ��������:\n";
    for (int i = 0; i < numProcesses; ++i) {
        cout << "������� " << i << ": ";
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
            cout << "������� �� � ���������� ���������.\n";
            return false;
        }
    }

    cout << "������� � ���������� ���������.\n";
    cout << "���������� ������������������: ";
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
            cout << "������: ������ ��������� �����������.\n";
            return false;
        }
    }

    // Check if request <= available
    for (int j = 0; j < numResources; ++j) {
        if (request[j] > available[j]) {
            cout << "������: ������ ��������� ��������� �������.\n";
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
        cout << "������� ��������� � ������������ ��������� ����� �������.\n";
        return false;
    }
}

void BankersAlgorithm::run() {
    input();

    // ������ ������� ��������
    int process;
    cout << "������� ����� �������� ��� ������� ��������: ";
    cin >> process;

    vector<int> request(numResources);
    cout << "������� ������ �������� ��� �������� " << process << ": ";
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