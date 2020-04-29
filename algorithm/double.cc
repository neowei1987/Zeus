#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
int T;
LL N, M, K;

LL nums[50010];
LL bak[50010];

void merge(int l, int m ,int r)
{
    for (int i = l; i <= r; ++i)  bak[i] = nums[i]; 
    int i = l;
    int j = m + 1;
    int k = l;
    while (i <= m && j <= r) {
        if (bak[i] < bak[j])  nums[k++] = bak[i++];
        else nums[k++] = bak[j++];
    }
    
    while (i <= m) nums[k++] = bak[i++];
    while (j <= r) nums[k++] = bak[j++];
}

void merge_sort(int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, mid, r);
}

bool calc_t(int left, int right) {
    merge_sort(left, right);
    
    LL sum =0;
    for (int i = 0; i < M; ++i) {
        if (right - i <= left + i) break;
        //cout << nums[i] <<  " " << nums[right-i] << endl;
        LL a = nums[left + i] - nums[right - i];
        sum += a * a;
    }
    //cout << left << " " << right << " " << sum << endl;
    return sum <= K;
}

void work() {
    cin >> N >> M >> K;   
    for (int i = 0; i < N; i++) 
    {
        cin >> nums[i];
    }
    
    int l = 0;
    int r = 0;
    int res = 0;
    int p = 1;
    while (l < N) {
        p = 1;
        //cout << "start from i:"  << t << endl;
        while (p != 0) {
            if (r + p < N && calc_t(l, r + p)) {
                r += p;
                //cout << i << " DOUBLE TO " << p * 2 << endl;
                p *= 2;
            }
            else {
                p /= 2;
                //cout << i << " DIVIDE TO " << p / 2 << endl;
            }
        }
        r++;
        l = r;
        res ++;
    }
  
    cout << res << "\n";
}
int main() {
    cin >> T;
    for (int i = 0;i < T ; ++i) {
        work();
    }
}