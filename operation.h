#include"data.h"
#include<stdbool.h>

bool operator > (const Data &x, const Data &y)
{
    if(x.number.size()-x.point!=y.number.size()-y.point) return x.number.size()-x.point>y.number.size()-y.point;
    for(int i=x.number.size()-1,j=y.number.size()-1;i>=x.point&&j>=y.point;i--,j--)
        if(x.number[i]!=y.number[i]) return x.number[i]>y.number[i];
    for(int i=x.point-1,j=y.point-1;i>=0||j>=0;i--,j--)
        if((i>=0?x.number[i]:0)!=(j>=0?y.number[i]:0)) return (i>=0?x.number[i]:0)>(j>=0?y.number[i]:0);
    return false;
}

Data operator - (const Data &x, const Data &y)
{
	Data rlt;
    vector left,right;
    int leftPoint,rightPoint;
    left.init();
    right.init();
	rlt.number.init();
    if(x>y) left=x.number,right=y.number,leftPoint=x.point,rightPoint=y.point,rlt.symbol=1;
    else left=y.number,right=x.number,leftPoint=y.point,rightPoint=x.point,rlt.symbol=-1;
	rlt.number.push_back(0);
	for(int i=0,j=0;i<left.size();i++,j++){
        int leftNow,rightNow;
        if(i<leftPoint-rightPoint) rightNow=0,j--;
        else rightNow=right[j];
        if(j<rightPoint-leftPoint) leftNow=0,i--;
        else leftNow=left[i];
		if(right.size()>j){
			rlt.number[i]+=leftNow>rightNow?leftNow-rightNow:leftNow+10-rightNow;
			if(i+1<left.size()) rlt.number.push_back(leftNow>=rightNow?0:-1);
		}
		else{
			rlt.number[i]+=leftNow;
			if(i+1<left.size()) rlt.number.push_back(0);
		}
	}
    while(!rlt.number[rlt.number.size()-1]) rlt.number.pop_back();
    rlt.point=leftPoint>rightPoint?leftPoint:rightPoint;
	return rlt;
}