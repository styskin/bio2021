#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>


using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;

const int N_GRAM = 2;
const int MASK = 200;

map<pii, vi> searchMap;

int encode(vi& v, int pos) {
    int x = 0;
    for (int i = pos; i < pos + N_GRAM; ++i) {
        if (v[i] < 0) {
            return -1;
        }
        x = x * 3 + v[i]; // 0, 1, 2
    }
    return x;
}

int main(void) {
    int N, M;

    cin >> N >> M;
    vector<vi> gen(N);


    for (int i = 0; i < N; ++i) {
        string s1, s2;
        cin >> s1;
        cin >> s2;
        for (int j = 0; j < s1.length(); ++j) {
            int x = s1[j] - '0' + s2[j] - '0';
            gen[i].push_back(x);
        }
        for (int j = 0; j < gen[i].size() - N_GRAM; ++j) {
            int x = encode(gen[i], j);
            searchMap[pii(j, x)].push_back(i);
            
        }
    }


    for (int i = 0; i < M; ++i) {
        string s;
        cin >> s;
        vector<int> query;
        for (int j = 0; j < s.length(); ++j) {
            query.push_back((s[j] == '?') ? -1 : s[j] - '0');
        }

        // for (int j = 0; j < query.size(); ++j) {
        //     if (query[j] < 0) 
        //         cout << "?";
        //     else
        //         cout << query[j];
        // }
        // cout << endl;


        // Do search candidates
        for (int j = 0; j < query.size(); j += MASK) {
            int endJ = min((int)query.size(), j + MASK);
            // generate known ngrams
            vector<pii> ngrams;

            for (int l = j; l < endJ; ++l) {
                int x = encode(query, l);
                if (x >= 0) {
                    ngrams.push_back(pii(l, x));
                }
            }
            // find candidates
            map<int, int> can;
            for (auto ng : ngrams) {
                auto it = searchMap.find(ng);
                if (it != searchMap.end()) {
                    for (auto gind : it->second) {
                        ++can[gind];
                    }
                }
            }
            vi matches;
            for(auto c : can) {
                matches.push_back(-c.second);
            }
            sort(matches.begin(), matches.end());
            // cerr << -matches[0] << ", " << -matches[1] << endl;


            // chose best fit from top candidates
            for (int l = j; l < endJ; ++l) {
                if (query[l] < 0) {
                    // calc stat
                    vector<int> stat(3);
                    for (auto c : can) {
                        int index = c.first;
                        if (c.second >= -matches[1]) {
                            stat[gen[index][l]] += c.second;
                        }
                    }
                    int mx = 0;
                    int mxc = 0;
                    for (int st = 0; st < stat.size(); ++st) {
                        if (stat[st] > mxc) {
                            mxc = stat[st];
                            mx = st;
                        }
                    }
                    query[l] = mx;
                }
            }
        }
        for (int j = 0; j < query.size(); ++j) {
            if (query[j] < 0) 
                cout << "?";
            else
                cout << query[j];
        }
        cout << endl;

    }
    return 0;
}