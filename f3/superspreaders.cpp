#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

typedef pair<int, double> pid;

const double EPS = 1e-7;

void task() {
    int N, D;
    cin >> N >> D;
    vector< vector< vector<pid > > > data(D, vector< vector<pid > >(N, vector<pid>()) );

    map<int, double> ed;

    for (int i = 0; i < D; ++i) {
        int C;
        cin >> C;

        for (int j = 0; j < C; ++j) {
            int a, b;
            double p;
            cin >> a >> b >> p;
            --a;
            --b;
            ed[a] += (1 + p) * (D - j);
            data[i][a].push_back(pid(b, p));
        }
    }
    vector<pair<double, int> > edv;
    for(auto e : ed) {
        edv.push_back(pair<double, int>(-e.second, e.first));
    }
    vector<int> candidates;
    sort(edv.begin(), edv.end());

    // Replay many times with different starts
    int ind = 0;
    double mx = 0;

    for (int ii = 0; ii < 10000; ++ii) {
        int i = edv[ii].second;
        // cerr << i << " with " << edv[ii].first << " i: " << ii << endl;
        vector<vector<double> >  prob(D+1, vector<double>(N, 0.));
        prob[0][i] = 1.0;
        // set<int> cur;
        // cur.insert(i);
        for (int j = 0; j < D; ++j) {
            // cerr << "Day " << j << " cur: "  << cur.size() << endl;
            for (int a = 0; a < N; ++a) {
            // for (auto a : cur) {
                if (prob[j][a] > EPS) {
                    prob[j + 1][a] += prob[j][a];
                    for (int k = 0; k < data[j][a].size(); ++k) {
                        int b = data[j][a][k].first;
                        double pr = data[j][a][k].second;
                        prob[j+1][b] += (1 - prob[j][b]) * prob[j][a] * pr;
                        // cur.insert(b);
                    }
                }
            }
        }
        double sum = 0;
        cerr << "Person " << i << " " << ii << endl;
        for (int a = 0; a < N; ++a) {
            // cerr << prob[D][a] << endl;
            if (prob[D][a] > 0.5 - EPS) {
                sum += 1;
            }
        }
        if (sum > mx) {
            mx = sum;
            ind = i;
            // cerr << ind << " with " << mx << endl;  
        }
    }
    cout << (ind + 1) << endl;
    cout.flush();
}

int main(void) {
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        cerr << "test " << i << endl;
        task();
    }
    return 0;
}