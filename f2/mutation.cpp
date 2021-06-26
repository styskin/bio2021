#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;


// CAGT
int encode(char c) {
    switch(c) {
        case 'C': return 0;
        case 'A': return 1;
        case 'G': return 2;
        case 'T': return 3;
    }
    return 0;

}

char decode(int c) {
    switch(c) {
        case 0: return 'C';
        case 1: return 'A';
        case 2: return 'G';
        case 3: return 'T';
    }
    return 'C';

}


void task() {
    int N, L;
    cin >> N >> L;
    vector<string> genome(N);
    vector<int> des(N);
    int dcount = 0;
    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        des[i] = s == "+";
        if (des[i]) {
            ++dcount;
        }
        cin >> s;
        genome[i] = s;
    }
    // cout << "Des: " << dcount << endl;

    vector<int> mask(L);
    for (int l = 0; l < L; ++l) {
        int stat[4][2];
        memset(stat, 0, sizeof(int) * 4 * 2);
        for (int i = 0; i < N; ++i) {
            ++stat[encode(genome[i][l])][ des[i] ];
        }
        // cout << l << ": " << endl; 

        int mx = 0;
        int mxc = 0;
        for (int i = 0; i < 4; ++i) {
            if (stat[i][1] > mxc) {
                mx = i;
                mxc = stat[i][1];
            }
            // cout << decode(i) << ": " << (1.0 * stat[i][1] / (stat[i][0] + stat[i][1]) ) << " " << stat[i][1] << endl;
        }
        mask[l] = mxc;
    }
    vector<int> maskC(mask);
    sort(maskC.begin(), maskC.end());
//    cout << maskC[maskC.size() - 1] << " " << L << endl;

    int C = 10;
    int a = 100000000, b = -1;
    for (int l = 0; l < L; ++l) {
        cout << " " << mask[l];
        if (mask[l] > maskC[maskC.size() - C]) {
            a = min(a, l);
            b = max(b, l);
        }
    }
    cout << endl;
    for (int l = 0; l < L; ++l) {
        cout << " " << mask[l];
    }
    cout << endl;

    for (int l = 0; l < L; ++l) {
        cout << " " << (mask[l] > maskC[maskC.size() - C]);
    }
    cout << endl;

    cout << a << " " << b << endl;
}

int main(void) {
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        task();

    }
    return 0;
}