#include "data.h"
Data operator % (const Data &x, const Data &y)
{
    Data rlt;
    vector left,right;
    left.init();
    right.init();
    rlt.number.init();
    int n=strlen(left);
    left=x.number;
    right=y.number;
    rlt.number=1;
	for (int i = 1; i < n; i++)
	{
		rlt.number = (rlt.number * 10 + x.number[i] - '0') % right;

	}
    rlt.symbol=x.symbol;
    return rlt;

}