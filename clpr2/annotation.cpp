#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void task() {
    int M, K, N;
    cin >> M >> K >> N;
    vector<double> am;
    map<double, int> amm;

    vector<double> ak;

    for (int i = 0; i < M; ++i) {
        double x;
        cin >> x;
        am.push_back(x);
        amm[x] = i;
    }
    for (int i = 0; i < K; ++i) {
        double x;
        cin >> x;
        ak.push_back(x);
    }

    for (int i = 0; i < N; ++i) {
        double x;
        cin >> x;
        // x = am + ak + delta
        // x - ak


        double mdelta = 100000;
        int mi, ki;


        for (int j = 0; j < K; ++j) {
            double s = x - ak[j];  // am + delta
            // cerr << "$ " << s << endl;
            auto it = amm.upper_bound(s);
            if (it != amm.end()) {
                double d = abs(s - it->first);
                if (d < mdelta && it->first + ak[j] > 0) {
                    mi = it->second;
                    ki = j;
                    // cerr << "K: " << mi << " " << ki << " = " << d << endl;
                    mdelta = d;
                }
            }
            --it;
            if (it != amm.end()) {
                double d = abs(s - it->first);
                if (d < mdelta && it->first + ak[j] > 0) {
                    mi = it->second;
                    ki = j;
                    // cerr << "K: " << mi << " " << ki << " = " << d << endl;
                    mdelta = d;
                }

            }
        }
        cout << mi + 1 << " " << ki + 1 << endl;
    }

}


int main(void) {
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        task();
    }
    return 0;
}