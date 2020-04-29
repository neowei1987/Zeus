#include <iostream>
#include <algorithm>
typedef pair<float, float> PFF;
using namespace std;

bool cmp(PFF& a, PFF& b) {
    return a.first < b.first;
}

int main() {
    //int a;
    //cin >> a;
    
    vector<PFF> segs;
    if (segs.size() == 1) {
        //TODO
        return 0;
    }
    
    sort(segs.begin(), segs.end(), cmp);
    float res = 0.0f;  
    float st = segs[0].first;
    float ed = segs[0].second;
    
    for (int i = 1; i < segs.size(); ++i) {
        if (segs[i].first > ed) {
            res += (ed - st);
            st = segs[i].first;
            dt = segs[i].second;
        }
        else {
            ed = max(ed, segs.second);
        }
    }
    //last one
    res += (ed - st); 
    
    cout << res;
    
    return 0;
}