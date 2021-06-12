#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main(void) {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, l;
        cin >> n >> l;
        vector<string> marks;
        map<string, int> code;
        for (int j = 0; j < n; ++j) {
            string s;
            cin >> s;
            marks.push_back(s);
        }

        int ind = 0;

        vector<int> answer;
        for (int j = 0; j < l; ++j) {
            vector<char> s;
            for (int k = 0; k < n; ++k) {
                s.push_back(marks[k][j]);
            }
            string ss(s.begin(), s.end());
            const auto& f = code.find(ss);
            if (f != code.end()) {
                answer.push_back(f->second);
            } else {
                ++ind;
                code[ss] = ind;
                answer.push_back(ind);
            }
        }
        cout << ind << endl;
        for (int j = 0; j < answer.size(); ++j) {
            if (j) {
                cout << " "; 
            }
            cout << answer[j];
        }
        cout << endl;
    }
    return 0;
}