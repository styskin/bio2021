#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;

int N, D, Q;
vector<vii> isoform;


map<int, int> cc;
multimap<pii, int> cache;

vii readI(const string& s) {
    vii answer;
    size_t pos = 0, curpos;
    while ((curpos = s.find(',', pos)) != string::npos) {
        string p = s.substr(pos, curpos);
        pos = curpos + 1;
        pii pr;
        size_t del = p.find('-');
        pr.first = stoi(p.substr(0, del));
        pr.second = stoi(p.substr(del + 1));
        answer.push_back(pr);
    }
    {
        string p = s.substr(pos);
        pii pr;
        size_t del = p.find('-');
        pr.first = stoi(p.substr(0, del));
        pr.second = stoi(p.substr(del + 1));
        answer.push_back(pr);
    }
    return answer;
}

int check(vii& a, vii& b, int d) {
    // cerr << "CHECK" << endl;
    int ia = 0, ib = 0;
    while(b[ib].first > a[ia].second && ia < a.size()) {
        ++ia;
    }
    int first = 1;
    int last = 0;

    for (;ia < a.size() && ib < b.size(); ) {
        // cerr << ia << " vs " << ib << endl;
        // cerr << a[ia].first << "-" << a[ia].second << " && " << b[ib].first << "-" << b[ib].second << endl;
        if (ib == b.size() - 1) {
            last = 1;
        }
        if (abs(b[ib].second - a[ia].second) <= d && abs(b[ib].first - a[ia].first) <= d) {
            ++ia;
            ++ib;
        } else if (first && abs(b[ib].second - a[ia].second) <= d) {
            if (b[ib].first < a[ia].first - d) {
                return 0;
            }
            ++ia;
            ++ib;
        } else if (last && abs(b[ib].first - a[ia].first) <= d && b[ib].second < a[ia].second) {
            ++ia;
            ++ib;
        } else {
            // cerr << "NO" << endl;
            return 0;
        }
        first = 0;
    }
    // cerr << ia << " < " << a.size() << " vs " << ib << " < " << b.size() << endl; 

    return ib == b.size();
}


pii calc(vii& r) {
    int ind = -1;
    int count = 0;
    // need subset of candidates

    int iter = 0;

    int cnt = 0;

    map<int, int> candidates;
    for (int i = 0; i < r.size(); ++i) {
        if (cc[(r[i].first + D) / 1000] < 30000 || cc[(r[i].first - D) / 1000] < 30000) {
            ++cnt;
        } else {
            continue;
        }
        // r[i].first + d  -- should be between a&b
        auto it = cache.lower_bound(pii(r[i].first + D, 0));
        for (; it != cache.end(); --it) {
            if ((it->first.first <= r[i].first + D) && (it->first.second >= r[i].second - D)) {
                // cerr << "B "  << it->second << ": " << it->first.first << "-" << it->first.second << " && " <<  r[i].first << "-" << r[i].second << endl;
                ++candidates[it->second];
            }
            if (r[i].first - D > it->first.second) {
                // cerr << "B "  << it->second << ": " << it->first.first << "-" << it->first.second << " && " <<  r[i].first << "-" << r[i].second << endl;
                break;
            }
            ++ iter;
        }
    }
    set<int> finalCandidates;
    for (auto c : candidates) {
        if (c.second >= cnt - 1) {
            finalCandidates.insert(c.first);
        }
    }
    cerr << "Final candidates size: " << finalCandidates.size() << " iterated " << iter << endl;

    for (int i = 0; i < N; ++i) {
    // for (auto i : finalCandidates) {
        // cerr << "Try " << i << endl;
        if (check(isoform[i], r, D)) {
            if (ind < 0) {
                ind = i;
            } 
            ++count;

            if (finalCandidates.find(i) == finalCandidates.end() || count == 1) {
                if (count == 1) {
                    cout << "C: " << i << endl;
                } else {
                    cout << "I: " << i << endl;
                }
                for(auto p : isoform[i]) {
                    cout << "," << p.first << "-" << p.second;
                }
                cout << endl;
            } 
        }
    }
    return pii(ind, count);
}

int main(void) {

    cin >> N >> D;
    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        isoform.push_back(readI(s));
    }

    for (int i = 0; i < isoform.size(); ++i) {
        for (int j = 0; j < isoform[i].size(); ++j) {
            ++cc[isoform[i][j].first / 1000];


            // if (isoform[i][j].first > FILTER) {
            //     cache.insert(pair<pii, int>(isoform[i][j], i));
            // }
        }
    }
    // for (auto m : cc) {
    //     if (m.second > 10)
    //         cerr << m.first << " = " << m.second << endl;
    // }
    // if (1) {
    //     return -1;
    // }
    for (int i = 0; i < isoform.size(); ++i) {
        for (int j = 0; j < isoform[i].size(); ++j) {
            if (cc[isoform[i][j].first / 1000] < 30000) {
                cache.insert(pair<pii, int>(isoform[i][j], i));
                if ((isoform[i][j].first - D) / 1000 != isoform[i][j].first / 1000) {
                    cache.insert(pair<pii, int>(isoform[i][j], i));
                }
                if ((isoform[i][j].first + D) / 1000 != isoform[i][j].first / 1000) {
                    cache.insert(pair<pii, int>(isoform[i][j], i));
                }
            }
        }
    }
    cerr << "Total cache size: " << cache.size() << endl;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        if (i % 100 == 0) {
            cerr << "Query: " << i << endl;
        }
        string s;
        cin >> s;
        vii r = readI(s);
        pii answer = calc(r);
        cout << answer.first << " " << answer.second << endl;
        cout.flush();
    }
    return 0;
} 