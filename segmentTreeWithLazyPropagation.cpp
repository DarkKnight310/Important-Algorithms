//https://ide.geeksforgeeks.org/5QarR56KbS

#include <bits/stdc++.h>
using namespace std;

void createSegmentTrees(vector<int>& v, vector<int>& segV, int l, int r, int p){
    if(l == r) {
        segV[p] = v[l];
        return;
    }
    
    int mid = l + (r-l)/2, chL = 2*p + 1, chR = chL + 1;
    
    createSegmentTrees(v, segV, l, mid, chL);
    createSegmentTrees(v, segV, mid+1, r, chR);
    
    segV[p] = segV[chL] + segV[chR];
}

void updateLazily(vector<int>& segV, vector<int>& lazyV, int ul, int ur, int val, int l, int r, int p){
    int mid = l + (r-l)/2, chL = 2*p + 1, chR = chL + 1;
    if(ul > r || ur < l || l > r) return;
    
    if(l == r) {
        lazyV[p] += val;
        segV[p] += lazyV[p];
        lazyV[p] = 0;
        return;
    }
    
    
    if(ul <= l && r <= ur){
        lazyV[p] += val;
        segV[p] += ((r-l+1)*lazyV[p]);
        lazyV[chL] += lazyV[p];
        lazyV[chR] += lazyV[p];
        lazyV[p] = 0;
        return;
    }
    else{
        segV[p] += ((r-l+1)*lazyV[p]);
        lazyV[chL] += lazyV[p];
        lazyV[chR] += lazyV[p];
        lazyV[p] = 0;
        updateLazily(segV, lazyV, ul, ur, val, l, mid, chL);
        updateLazily(segV, lazyV, ul, ur, val, mid+1, r, chR);
        segV[p] = segV[chL] + segV[chR];
    }
}

int lazySegmentSum(vector<int>& segV, vector<int>& lazyV, int ul, int ur, int l, int r, int p){
    int mid = l+(r-l)/2, chL = 2*p+1, chR = chL+1;
    if(ul > r || ur < l) return 0;
    if(l == r) {
        segV[p] += lazyV[p];
        lazyV[p] = 0;
        return segV[p];
    }
    
    segV[p] += ((r-l+1)*lazyV[p]);
    lazyV[chL] += lazyV[p];
    lazyV[chR] += lazyV[p];
    lazyV[p] = 0;
    
    if(ul <= l && ur >= r) return segV[p];
    
    int leftSum = lazySegmentSum(segV, lazyV, ul, ur, l, mid, chL);
    int rightSum = lazySegmentSum(segV, lazyV, ul, ur, mid+1, r, chR);
    
    //cout << leftSum << " " << rightSum << endl;
    
    return (leftSum + rightSum);
}

int main() {
	//code for segment trees with lazy propagation
	int i, segmentSum;
	vector<int> v = {2,4,3,1,7,8,5,6};
	vector<int> segV(15, 0);
	vector<int> lazyV(15, 0);
	
	createSegmentTrees(v, segV, 0, 7, 0);
	cout << segV[0] << endl;
	
	updateLazily(segV, lazyV, 0, 5, 6, 0, 7, 0);
	cout << segV[0] << endl;
	
	segmentSum = lazySegmentSum(segV, lazyV, 3, 6, 0, 7, 0);
	cout << segmentSum << endl;
	
	return 0;
}
