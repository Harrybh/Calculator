#include "data.h"
Data operator / (const Data &x, const Data &y)
{ 
   Data rlt, Rlt;
    vector left, right;
    int leftPoint, rightPoint, len1, len2;
    left.init();
    right.init();
    rlt.number.init();
    Rlt.number.init();
leftPoint = x.point;
rightPoint = y.point;
left = x.number;
right = y.number;
int n= 50-(leftpoint-rightpoint);
for(int m=0,r=0;r<n;r++)
{
    left.push_back(m);
}

void sub() 
{
	int i = 0, j;
	while (1)
	{
		if (left[i] == '0')  
			i++;
		else 
		{
			j = i;
			break;
		}
	}
	for (; i < len2; i++)
		left[i] = left[i] - right[i] + '0';
	for (i = len2 - 1; i > j; i--) 
	{
		if (left[i] < '0')
		{
			left[i] += 10;
			left[i - 1]--;
		}
	}
}
 
		int p, i;
		len1 = strlen(left);
		len2 = strlen(right);
		if ((len2 == 1 && right[0] == '0') && (len1 == 1 && left[0] == '0'))
			printf("error\n");
		else 
			if (len2 == 1 && right[0] == '0')
			printf("error\n");
		else 
        if (len1 < len2 || (len1 == len2 && strncmp(left, right, len2) < 0))
            rlt.number=0
        else
		{
			p = 0;
			while (1) 
			{
				rlt.number[p] = 0;
				while (strncmp(left, right, len2) >= 0)
				{  
					sub();
					rlt.number[p]++;
				}
				p++;
				if (len1 == len2) break;
				for (i = len2 - 1; i >= 0; i--)  
					right[i + 1] = right[i];
				right[0] = '0';
				len2++;
				right[len2] = '\0';
			}
			i = 0;
			while (1) 
			{
				if (rlt.number[i] == 0) 
                 i++;
				else
					break;
			}
			for (int z=0; i < p; i++,z++)
				{
                    Rlt.number[z]=rlt.number[i];
                }
                Rlt.point=50;
                if(x.symbol==y.symbol)
                Rlt.symbol=1;
                else
                Rlt.symbol=-1;
	            return Rlt;
		}

    rlt.point=50
    if(x.symbol==y.symbol)
    rlt.symbol=1;
    else
    rlt.symbol=-1;
	return rlt;
}
