#include <stdio.h>
#include <stdlib.h>

／／　判断数组相等
int  IsArrayEqual(int *a,int *b,int n)
{
    int equal = 1;
    int i;
    for(i=0;i<n;i++)
    {
        if(a[i]!=b[i])
            equal = 0;
    }
    return equal;
}

／／变换数组，给出初始数组和变换法则（转换序列），得到目标序列（存放在ｂｅｇｉｎ［］）中
void changeArray(int begin[],int change[],int n)
{
    int i;
    int tmp[n];
    for(i=0;i<n;i++)
    {
        tmp[change[i]]=begin[i];
    }
    for(i=0;i<n;i++)
    {
        begin[i]=tmp[i];
    }
}


／／一直转换数组直到得到目标数组
／／当转换ｎ次后仍然得不到目标数组则说明ｉｍｐｏｓｓｉｂｌｅ；
void test(int beginArr[],int changeArr[],int aimArr[],int n)
{
    int count = 0;
    for(;;)
    {
        changeArray(beginArr,changeArr,n);
        count++;

        if(IsArrayEqual(beginArr,aimArr,n))
        {
            printf("%d\n",count);
            break;
        }
        if(count>n)
        {
            printf("impossible\n");
            break;
        }
    }
}

int main()
{
    int n,i;
    scanf("%d",&n);
    int beginArr[n];
    int changeArr[n];
    int aimArr[n];

    for(i=0;i<n;i++)
    {
        beginArr[i]=i;
    }

    for(i=0;i<n;i++)
    {
        scanf("%d",&changeArr[i]);
    }
    for(i=0;i<n;i++)
    {
        scanf("%d",&aimArr[i]);
    }

    int n1;
    scanf("%d",&n1);
    int beginArr1[n];
    int changeArr1[n];
    int aimArr1[n];

    for(i=0;i<n1;i++)
    {
        beginArr1[i]=i;
    }

    for(i=0;i<n1;i++)
    {
        scanf("%d",&changeArr1[i]);
    }
    for(i=0;i<n1;i++)
    {
        scanf("%d",&aimArr1[i]);
    }
    test(beginArr,changeArr,aimArr,n);
    test(beginArr1,changeArr1,aimArr1,n1);

    return 0;
}
