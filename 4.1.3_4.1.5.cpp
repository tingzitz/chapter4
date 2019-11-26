#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;


void find_maximum_subarray_square(vector<int>& A, int (&a)[3])    
//time comlexity: square
{
    int sub_sum = 0;
    int i = 0, j = 0;
    for(auto iter1 = A.begin(); iter1 != A.end(); iter1++) {
        sub_sum = 0; j = i;
        for(auto iter2 = iter1; iter2 != A.end(); iter2++) {
            sub_sum += *iter2;
            if (sub_sum > a[2]) {
                a[2] = sub_sum; 
                a[0] = i; 
                a[1] = j;
            }
            ++j;
        } 
        ++i;     
    }
}


int* find_maximum_crossing_subarray(int (&B)[16], int (&a)[3], int low, int mid, int high)     
//find array spanning the midpoint, with the biggest sum
{
    int left_sum = INT_MIN, right_sum = INT_MIN;
    int sub_sum = 0;
    for(int i=mid; i>=low; i--) {
        sub_sum += B[i];
        if (sub_sum > left_sum) {
            left_sum = sub_sum;
            a[0] = i;
        }
    }
    sub_sum = 0;
    for (int j=mid; j<=high; j++) {
        sub_sum += B[j];
        if (sub_sum > right_sum) {
            right_sum = sub_sum;
            a[1] = j;
        }
    }
    a[2] = left_sum + right_sum - B[mid];
    return a;
}


int* find_maximum_subarray_recurrence(int (&B)[16], int (&a)[3], int low, int high)  
//time comlexity: O(nlogn)
{
    if (low == high) {
        a[0] = low;
        a[1] = high;
        a[2] = B[low];
        return a;
    }
    else {
        int mid = (low + high) / 2;
        int* left_a = find_maximum_subarray_recurrence(B, a, low, mid);
        int* right_a = find_maximum_subarray_recurrence(B, a, mid+1, high);
        int* cross_a = find_maximum_crossing_subarray(B, a, low, mid, high);
        if (left_a[2] > right_a[2] && left_a[2] > cross_a[2]) {
            return left_a;
        }
        else if (right_a[2] > left_a[2] && right_a[2] > cross_a[2]) {
            return right_a;
        }
        else 
            return cross_a;
    }
}


void find_maximum_subarray_linear(int (&B)[16], int (&a)[3], int low, int high)
//time complexity: linear
{
    int sub_sum = 0;
    int sub_index = 0;
    for (int i=0; i<=high; i++) {
        sub_sum += B[i];
        if (sub_sum > a[2]) {
            a[2] = sub_sum;
            a[0] = sub_index;
            a[1] = i;
        }
        if (sub_sum < 0) {
            sub_sum = 0;
            sub_index = i+1;
        }
    }
}


int main()                
{
    vector<int> A = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int B[16] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int a[3] = {0, 0, INT_MIN};
    find_maximum_subarray_square(A, a);
    cout << "subarray with the biggist sum is from " << a[0] 
         << " to " << a[1] << ", and sum is: " << a[2] << endl;

    int* b = find_maximum_subarray_recurrence(B, a, 0, 15);
    cout << "subarray with the biggist sum is from " << b[0] 
         << " to " << b[1] << ", and sum is: " << b[2] << endl;

    find_maximum_subarray_linear(B, a, 0, 15);
    cout << "subarray with the biggist sum is from " << a[0] 
         << " to " << a[1] << ", and sum is: " << a[2] << endl;
    return 0;
}
