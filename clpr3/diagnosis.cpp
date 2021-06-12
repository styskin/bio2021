#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>

using namespace std;

const int CSIZE = 10;

typedef vector<int> vi;
typedef vector<vi> vii;


vector<int> tree;
vector<int> treeH;
vector<int> IC;

vector<set<int> > candidates;

int height(int i) {
    if (treeH[i] != -1) {
        return treeH[i];
    }
    treeH[i] = height(tree[i]) + 1;
    return treeH[i];
}

int LCA(int a, int b) {
    int ha = treeH[a];
    int hb = treeH[b];
    while (ha > hb) {
        a = tree[a];
        --ha;
    }
    while (hb > ha) {
        b = tree[b];
        --hb;
    }
    while (a != b) {
        a = tree[a];
        b = tree[b];
    }
    return a;
}

int calc(vii& dis, vi& p) {
    int msum = 0;
    int md = 0;

    // GET from candidates
    set<int> cur_candidates;

    for (auto q : p) {
        int x = q;
        int h = treeH[x];
        int prev_size = cur_candidates.size();
        // 10 - for task3, 100 for task7
        while (h > 1 && (cur_candidates.size() - prev_size) < 10) {
            cur_candidates.insert(candidates[x].begin(), candidates[x].end());
            x = tree[x];
            --h;
        }
    }
    // cerr << "Cand size " << cur_candidates.size() << endl;

    // for (int i = 0; i < dis.size(); ++i) {
    for (auto i : cur_candidates) {
        vi& d = dis[i];

        int sum = 0;
        for (auto q : p) {
            int mx = 0;
            for (auto di : d) {
                mx = max(mx, IC[LCA(q, di)]);
            }
            sum += mx;
        }
        if (sum > msum) {
            // cerr << sum << " " << i << endl;
            md = i;
            msum = sum;
        }

    }
    return md;
}


int main(void) {
    int N; // ONTOLOGY
    cin >> N;
    tree.push_back(-1);
    for (int t = 1; t < N; ++t) {
        int x;
        cin >> x;
        tree.push_back(x - 1);  // ZERO BASED
    }
    treeH.resize(tree.size(), -1);
    treeH[0] = 0;
    for (int i = 0; i < tree.size(); ++i) {
        height(i);
    }

    for (int t = 0; t < N; ++t) {
        int x;
        cin >> x;
        IC.push_back(x);
    }

    int M; // diseases
    cin >> M;
    vector<vector<int> > dis(M);
    for (int i = 0; i < M; ++i) {
        int x;
        cin >> x;
        for (int j = 0; j < x; ++j) {
            int y;
            cin >> y;
            dis[i].push_back(y - 1); // ZERO BASED
        }
    }

    int Q; // diseases
    cin >> Q;
    vector<vector<int> > pat(Q, vi());
    for (int i = 0; i < Q; ++i) {
        int x;
        cin >> x;
        for (int j = 0; j < x; ++j) {
            int y;
            cin >> y;
            pat[i].push_back(y - 1); // ZERO BASED
        }
    }

    // PRECALC candidated
    candidates.resize(N);
    queue<int> queue;
    for (int i = 0; i < M; ++i) {
        for (auto d : dis[i]) {
            candidates[d].insert(i);
            queue.push(d);
        }
    }
    cerr << "HERE" << endl;
    while (queue.size()) {
        int x = queue.front();
        queue.pop();
        if (x == 0) {
            continue;
        }
        int r = tree[x];
        if (r > 0 && candidates[r].size() < CSIZE) {
            candidates[r].insert(candidates[x].begin(), candidates[x].end());
            queue.push(r);
        }
    }
    cerr << "HERR" << endl;

    for (int i = 0; i < Q; ++i) {
        if (i % 100 == 0)
            cerr << "P: " << i << endl;
        cout << (calc(dis, pat[i]) + 1 ) << endl;
    }
    return 0;
}