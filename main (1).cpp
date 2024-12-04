#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Function to check if the system is in a safe state
bool isSafeState(const vector<vector<int>>& ALLOCATION, const vector<vector<int>>& NEED, vector<int> AVAILABLE) {
    int N = ALLOCATION.size();  // Number of processes
    int M = AVAILABLE.size();   // Number of resource types
    
    vector<bool> finish(N, false);  // Track completed processes
    vector<int> work = AVAILABLE;   // Copy AVAILABLE to simulate allocation

    int count = 0;
    while (count < N) {
        bool found = false;
        for (int i = 0; i < N; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < M; ++j) {
                    if (NEED[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    // Simulate allocation: add ALLOCATION back to work
                    for (int j = 0; j < M; ++j)
                        work[j] += ALLOCATION[i][j];
                    
                    finish[i] = true;
                    found = true;
                    ++count;
                }
            }
        }

        if (!found) return false;  // No progress means unsafe state
    }
    return true;  // Safe state
}

// Function to display matrices and vectors
void displayMatrices(const vector<vector<int>>& MAX, const vector<vector<int>>& ALLOCATION, 
                     const vector<vector<int>>& NEED, const vector<int>& AVAILABLE) {
    cout << "\nMAX Matrix:\n";
    for (const auto& row : MAX) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }

    cout << "\nALLOCATION Matrix:\n";
    for (const auto& row : ALLOCATION) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }

    cout << "\nNEED Matrix:\n";
    for (const auto& row : NEED) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }

    cout << "\nAVAILABLE Vector:\n";
    for (int val : AVAILABLE) cout << val << " ";
    cout << "\n";
}

int main() {
    int N, M;
    ifstream inputFile("resources.txt");
    
    if (!inputFile) {
        cerr << "Error opening file.\n";
        return 1;
    }

    // Read N and M using getline and stringstream
    string line;
    getline(inputFile, line);
    stringstream ss(line);
    ss >> N >> M;
    cout << "Number of processes (N): " << N << ", Number of resource types (M): " << M << endl;

    // Read MAX matrix
    vector<vector<int>> MAX(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        getline(inputFile, line);
        stringstream ss(line);
        for (int j = 0; j < M; ++j) {
            ss >> MAX[i][j];
        }
    }

    // Read AVAILABLE vector
    vector<int> AVAILABLE(M);
    getline(inputFile, line);
    stringstream ssAvailable(line);
    for (int i = 0; i < M; ++i) {
        ssAvailable >> AVAILABLE[i];
    }

    vector<vector<int>> ALLOCATION(N, vector<int>(M, 0));  // Start with zero allocation
    vector<vector<int>> NEED = MAX;  // Initially, NEED is the same as MAX

    displayMatrices(MAX, ALLOCATION, NEED, AVAILABLE);

    while (true) {
        int process;
        cout << "\nEnter process number (-1 to exit): ";
        cin >> process;
        if (process == -1) break;

        if (process < 0 || process >= N) {
            cout << "Invalid process number.\n";
            continue;
        }

        vector<int> request(M);
        cout << "Enter request vector: ";
        for (int i = 0; i < M; ++i)
            cin >> request[i];

        // Validate request
        bool validRequest = true;
        for (int i = 0; i < M; ++i) {
            if (request[i] > NEED[process][i]) {
                validRequest = false;
                cout << "Request exceeds the maximum need.\n";
                break;
            }
            if (request[i] > AVAILABLE[i]) {
                validRequest = false;
                cout << "Request exceeds available resources.\n";
                break;
            }
        }

        if (!validRequest) continue;

        // Temporarily allocate resources
        for (int i = 0; i < M; ++i) {
            AVAILABLE[i] -= request[i];
            ALLOCATION[process][i] += request[i];
            NEED[process][i] -= request[i];
        }

        // Check if the system is in a safe state
        if (isSafeState(ALLOCATION, NEED, AVAILABLE)) {
            cout << "Request granted. System is in a safe state.\n";
        } else {
            cout << "Request denied. System would be in an unsafe state.\n";
            // Rollback allocation
            for (int i = 0; i < M; ++i) {
                AVAILABLE[i] += request[i];
                ALLOCATION[process][i] -= request[i];
                NEED[process][i] += request[i];
            }
        }

        displayMatrices(MAX, ALLOCATION, NEED, AVAILABLE);
    }

    cout << "\nFinal Resource Allocation State:\n";
    displayMatrices(MAX, ALLOCATION, NEED, AVAILABLE);

    return 0;
}
