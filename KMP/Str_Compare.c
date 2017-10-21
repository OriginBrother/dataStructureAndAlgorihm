#include<stdio.h>
#include<string.h>

#define KMP_S ("ababcbcabcabcdeabc")  // 自定义主串
#define MAX_SIZE (20) 			//目标串最大设置值




int* _get_next(char *m,int length)
{
		int *next;
		int j = 0;
		int k = -1;

		next[j] = k;		
		while(j<length)
		{
				if(k==-1||m[j]==m[k])
						next[++j] = ++k;
				else k = next[k];
		}

		return next;
}

int KMPCompare(char *s,int s_length,char *m,int m_length,int *next)
{
		int i =0;  // s
		int j =0; // m
		while(i<s_length && j< m_length)
		{
				if(j==-1 || s[i]==m[j]){
						++i;
						++j;
				}else {
						j = next[j];
				}
		}
		if(j<m_length)
				return -1;
		else return i-m_length;
}

int main()
{
		char *s =KMP_S;   //
		char m[MAX_SIZE];
		
		printf("进行匹配的主串为%s\n",s);
		printf("请输入进行匹配的模式串：\n");
		fgets(m,MAX_SIZE,stdin);
		
		int m_length = strlen(m)-1;
		int s_length = strlen(s);
		int* next = _get_next(m,m_length);

		int i;
		printf("next 数组为：\n");
		for(i=0;i<m_length;i++)
		{
				printf("%d ",next[i]);
		}
		printf("\n");

		int result = KMPCompare(s,s_length,m,m_length,next);
		if(result==-1)
				printf("没有相匹配的串\n");
		else printf("存在，模式串在主串第 %d位置后\n",result);

		return 0;
}



