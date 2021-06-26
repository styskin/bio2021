#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;

int N, D, Q;
vector<vii> isoform;


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
        // cerr << pr.first << "-" << pr.second << endl;
        answer.push_back(pr);
    }
    {
        string p = s.substr(pos);
        pii pr;
        size_t del = p.find('-');
        pr.first = stoi(p.substr(0, del));
        pr.second = stoi(p.substr(del + 1));
        // cerr << pr.first << "-" << pr.second << endl;
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
            ++ia;
            ++ib;
            first = 0;
        } else if (last && abs(b[ib].first - a[ia].first) <= d && b[ib].second < a[ia].second) {
            ++ia;
            ++ib;
        } else {
            // cerr << "NO" << endl;
            return 0;
        }
    }
    // cerr << ia << " < " << a.size() << " vs " << ib << " < " << b.size() << endl; 

    return ib == b.size();
}


pii calc(vii& r) {
    int ind = -1;
    int count = 0;
    // for (int i = 0; i < r.size(); ++i) {
    //     cerr << r[i].first << "-" << r[i].second << endl;
    // }

    for (int i = 0; i < N; ++i) {
        // cerr << "Try " << i << endl;
        if (check(isoform[i], r, D)) {
            if (ind < 0) {
                ind = i;
            } 
            ++count;
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
    }
    return 0;
} 