#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

class Solution {
private:

    // Function to compute the GCD and also the coefficients of x and y in the equation ax + by = gcd(a, b)
    // We can also use normal GCD function to calculate gcd
    int extendedGCD(int a, int b, int &x, int &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        int x1, y1;
        int gcd = extendedGCD(b, a % b, x1, y1);
        x = y1;
        y = x1 - (a / b) * y1;
        return gcd;
    }
    
    void findOperations(int x, int y, int target, vector<string>& operations) {
        int x_coef, y_coef;
        int gcd = extendedGCD(x, y, x_coef, y_coef);
        
        if (target % gcd != 0) {
            operations.push_back("No solution possible.");
            return;
        }
        
        // Find specific x and y for the target 
        // Removing it won't affect the code it's just for coefficients understanding
        int scale = target / gcd;
        x_coef *= scale;
        y_coef *= scale;

        int jugA = 0, jugB = 0;
        while (jugA != target && jugB != target) {
            if (jugA == 0) {
                operations.push_back("Fill Jug A");
                jugA = x;
            } else if (jugB == y) {
                operations.push_back("Empty Jug B");
                jugB = 0;
            } else {
                int pour = min(jugA, y - jugB);
                operations.push_back("Pour Jug A into Jug B");
                jugA -= pour;
                jugB += pour;
                if (jugA == target || jugB == target) {
                    break;
                }
            }
            if (jugB == target) {
                operations.push_back("Jug B has the target amount");
                return;
            }
            if (jugA == target) {
                operations.push_back("Jug A has the target amount");
                return;
            }
        }
    }

public:
    vector<string> measureWater(int x, int y, int target) {
        vector<string> operations;
        findOperations(x, y, target, operations);
        return operations;
    }
};

int main() {
    Solution sol;
    int x = 5;
    int y = 3;
    int target = 4;
    vector<string> operations = sol.measureWater(x, y, target);
    
    for (const string &op : operations) {
        cout << op << endl;
    }
    return 0;
}
