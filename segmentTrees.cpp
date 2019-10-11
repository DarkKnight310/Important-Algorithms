//https://ide.geeksforgeeks.org/2LoeGbK7NL

#include <bits/stdc++.h>
using namespace std;

void createSegmentTree(vector<int>& v, vector<int>& segV, int l, int r, int p){
    if(l == r){
        segV[p] = v[l];
        return;
    }
    
    int mid = l + (r-l)/2;
    int chL = (2*p) + 1,  chR = chL + 1;
    
    createSegmentTree(v, segV, l, mid, chL);
    createSegmentTree(v, segV, mid+1, r, chR);
    
    segV[p] = segV[chL] + segV[chR];
}

int find(vector<int> segV, int ql, int qr, int rl, int rr, int p){
    if(ql <= rl && qr >= rr) return segV[p];
    else if( ql > rr || qr < rl) return 0;
    
    int mid = rl + (rr-rl)/2;
    
    int num1 = find(segV, ql, qr, rl, mid, (2*p) + 1);
    int num2 = find(segV, ql, qr, mid + 1, rr, (2*p) + 2);
    
    return (num1+num2);
}

void update(vector<int>& segV, int pos, int val, int l, int r, int p){
    if(l == r){
        if(l == pos) segV[p] += val;
        return;
    }
    
    int chL = (2*p) + 1, chR = chL + 1;
    int mid = l + (r-l)/2;
    
    if(pos < l || pos > r) return;
    
    update(segV, pos, val, l, mid, chL);
    update(segV, pos, val, mid+1, r, chR);
    
    segV[p] += val;
}

int main() {
	vector<int> v = {2,3,1,5,4,7,5,10};
	vector<int> segV(15, 0);
	
	//cout << 1;
	createSegmentTree(v, segV, 0, 7, 0);
	
	int sumInRange = find(segV, 2, 7, 0, 7, 0);
	cout << sumInRange << endl;
	
	update(segV, 2, 14, 0, 7, 0);
	
	sumInRange = find(segV, 2, 7, 0, 7, 0);
	cout << sumInRange << endl;
	
	return 0;
}
