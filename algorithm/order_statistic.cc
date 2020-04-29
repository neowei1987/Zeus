
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

class Solution {
public:
    /****************顺序统计**************************/
    int _partition(vector<int>& a, int p, int r)
    {
        int x = a[p];
        int i = p + 1;
        int j = r;
        while (true) {
            while (i <= j && a[j] >= x) j--;
            if (i > j) break;
            while (i <= j && a[i] < x) i++;
            if (i > j) break;
            std::swap(a[i++], a[j--]);
        }
        std::swap(a[j], a[p]);
        return j;
    }

    void _getLeastNumbers(vector<int>& arr, int left, int right, int k) {
        int pivot = _partition(arr, left, right);
        fprintf(stdout, "[%d~%d] pivot:%d, k:%d\n", left, right, pivot, k);
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i] << ",";
        }
        cout << "\n";
        int left_size = pivot - left + 1;
        if (left_size == k) {
            return;
        }
        else if (left_size < k) { //左边不足
            return _getLeastNumbers(arr, pivot + 1, right, k - left_size);
        }
        else { //左边超出
            return _getLeastNumbers(arr, left, pivot - 1, k);
        }
    }

    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> ret;
        _getLeastNumbers(arr, 0, arr.size() - 1, k);
        for (int i = 0; i < k; ++i) {
            ret.push_back(arr[i]);
        }
        return ret;
    }
};

int quick_sort(int q[], int l, int r, int k){
    if(l>=r)return q[l];
    int i=l-1,j=r+1,x=q[l+r>>1];
    while(i<j){
        while(q[++i]<x);
        while(q[--j]>x);
        if(i<j)swap(q[i],q[j]);
    }
    if(j-l+1>=k)return quick_sort(q,l,j,k);
    else return quick_sort(q,j+1,r,k-(j-l+1));
}


int main() 
{ 
    std::stringstream ss;
    ss << "[1,2,3,4]";  
    std::vector<int> pushed;
    std::vector<int> popped;
    int k = 0;
    //std::cin >> nums;
    //std::cin >> k;
    ss >> pushed;

    ss.str("");
    ss << "[7,5,6,4]";
    ss >> popped;

    Solution problem;
    //problem.printNumbers(5);
    //cout << problem.validateStackSequences(pushed, popped);
    //cout << problem.search(nums, k);
    //problem.permute(pushed);
    //cout << problem.majorityElement(popped);
    //problem.getLeastNumbers(popped, 0);
    problem.reversePairs(popped);
    cout << "result: " << popped << "\n";

	return 0; 
} 
