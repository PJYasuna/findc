#include <bits/stdc++.h>
using namespace std;

ifstream ifile;
map<int, set<int>> neigh;
map<int, vector<int>> hashvalues;
int nodeNumber = 0;
int edgeNumber = 0;
int p = pow(2,31) - 1;
vector<int> all_a, all_b;
int k = 128;
double threshold;

void readfile() {
    int id1, id2;
    ifile.open("facebook_combined.txt");
    // ifile.open("web_Stanford.txt");

    while(ifile >> id1) {
        ifile >> id2;
        neigh[id1].insert(id2);
        neigh[id2].insert(id1);
        edgeNumber++;
    }
    ifile.close();
}


int minhash(int a, int b, set<int> s) {
    int ans = p;
    for (int i : s) {
        ans = min(ans, (a * i + b) % p);
    }
    return ans;
}

void randomab() {
    for (int i = 0; i < k; i++) {
        all_a.push_back(rand() % (p - 1) + 1);
        all_b.push_back(rand());
    }
    
}

vector<int> probabilityKFunc(set<int>s) {
    vector<int> ans;
    for (int i = 0; i < k; i++) {
        ans.push_back(minhash(all_a[i],all_b[i],s));
    }
    return ans;
}

void getMinhashValues() {
    for (auto p : neigh) {
        hashvalues[p.first] = probabilityKFunc(p.second);
    }
}

double jaccard(int node1, int node2) {
    vector<int> v1 = hashvalues[node1];
    vector<int> v2 = hashvalues[node2];
    int ans = 0;
    for (int i = 0; i < k; i++) {
        if (v1[i] == v2[i]) ans++;
    }
    return double(ans) / double(k);
}

int main() {
    int ans = 0;

    readfile();
    nodeNumber = neigh.size();
    //threshold = double(edgeNumber) / double(nodeNumber);
    // threshold = 0.82;
    // threshold = 0.83;
    threshold = 0.828;
    randomab();
    getMinhashValues();



    for (auto p : neigh) {
        int tmpans = 1;
        set<int> set1 = p.second;
        for (int i : set1) {
            double tmp = jaccard(p.first, i);
            if (tmp> threshold) tmpans++;
        }


        ans = max(ans,tmpans);
    }
    cout << "The best clique with threshold = " << threshold << " has " << ans << " nodes" << endl;
//    cout << "hello" <<endl;
    return 0;
}
