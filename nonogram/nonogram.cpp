//剩下propagate要弄清楚，還有S 
#include <iostream>
#include <fstream>
#include <ctime>
#define SIZE 25
using namespace std;

//變數 
int first = 0;
char C[SIZE+1][SIZE+1];//25*25nonogram
char S[SIZE+1];//line
int D[2*SIZE][SIZE/2+1];//一題中每行中所讀取到的數字 
int d[SIZE/2+1];//等於D[某行][SIZE/2+1] 
int store[2*SIZE];//一題中每行有幾個讀取到的數字
int num = 0;//讀取到的數字 
int isConflict = 0;
int rowChange[SIZE+1];
int colChange[SIZE+1];
int x = 0;
//propagate
int fix(int i, int j);
int fix0(int i,int j);
int fix1(int i, int j);
int paint(int i, int j);
int paintP(int i, int j);
int paint0(int i, int j);
int paint1(int i, int j);
int merge(int i, int j);
int mergeC(char s[], char t[]);
//function 
int init_C();
int init_D();
int init_Store();
int init();
int init_RowChange();
int init_ColChange();
int getInt(char character);
int propagationCol(int col);
int propagationRow(int row);
void propagate();
int print();


//main----------------------------------------------------
int main()
{
	clock_t start_time,end_time;
    start_time=clock();
    
    char ch;
    fstream file;
    file.open("nono_input.txt",ios::in);
    if(!file)
    {
    	cerr<<"Can't open file!";
    	exit(1);
	}
	else
	{
		while(file.get(ch))
		{
			x = 0;
            init_C();
            init_D();
            init_Store();
            init_RowChange();
            init_ColChange();
            
			//if(ch==EOF) break;
			if(first==1)
			{
				file.get(ch);
				cout<<"Q"<<ch;
				while(file.get(ch))
				{
					if(ch=='\n')
					{
						cout<<":\n";
						break;
					}
					cout<<ch;
				}
			}
			if(ch=='$' && first==0)
			{
				first=1;
				file.get(ch);
				cout<<"Q"<<ch<<":\n";
				file.get(ch);//讀換行 
				//file.get(ch);
			}
			
			for(int i=0;i<SIZE*2;i++)
			{
				int j=0;
				while(file.get(ch))
				{
					int flag=0;
					while(ch>='1'&&ch<='9')
					{
						if(flag==0)
						{
							num=getInt(ch);
							flag=1;
						}
						else if(flag==1)
						{
							num=num*10+getInt(ch);
						}
						file.get(ch);
						if(file.eof()) break;//讀到最後一個 
					}
					
					D[i][j]=num;
					j++;
					
					/*for(int k=0;k<25/2+1;k++)
                    {
                    	printf("%d ", D[i][k] );
					}*/
					if(ch=='\n') break;
				}
				store[i]=j; 
			}
			propagate();
			print();
			cout<<"\n";
			
        }
        file.close();
	} 
    
    
    end_time=clock();
    cout<<"時間: "<<(double)(end_time-start_time)/CLOCKS_PER_SEC<<" 秒";
}
//end main---------------------------------------------

//propagate
void propagate()
{
    x = 0;
    while(x < 2*SIZE)
	{
        if(x < SIZE)
		{
            propagationCol(x);
            if(isConflict == 1) return;
            if(isConflict != 1)
			{
                for(int i = 0; i < SIZE+1; i++)
				{
                    C[i][x+1] = S[i];
                }
            }
        }
        else
		{
            propagationRow(x);
            if(isConflict == 1 ) return;
            if( isConflict != 1){
                for(int i = 0; i < SIZE+1; i++)
				{
                    if(C[(x%25)+1][i] != S[i])
					{
                        colChange[i] = 1;
                    }
                    C[(x%25)+1][i] = S[i];
                }
            }
        }
        init();
        x++;
    }
    
    
    while(1)
	{ 
        int rowConfirm = 0;
        int colConfirm = 0;
        
        x = 0;
        while(x < 2*SIZE)
		{
            if(x < SIZE)
			{
                if(colChange[x+1] == 1 )
				{
                    propagationCol(x);
                    if(isConflict == 1 ) return;
                    if( isConflict != 1)
					{
                        for( int i = 0; i < SIZE+1; i++ )
						{
                            if(C[i][x+1] != S[i])
							{
                                rowChange[i] = 1;
                                rowConfirm++;
                                C[i][x+1] = S[i];
                            }
                        }
                    }
                }
            }
            else
			{
                if(x == SIZE)
				{
                    init_ColChange();
                }
                
                if( rowChange[(x%SIZE)+1] == 1 )
				{
                    propagationRow(x);
                    if(isConflict == 1 ) return;
                    if( isConflict != 1)
					{
                        for( int i = 0; i < SIZE+1; i++ )
						{
                            if(C[(x%SIZE)+1][i] != S[i])
							{
                                colChange[i] = 1;
                                colConfirm++;
                                C[(x%SIZE)+1][i] = S[i];
                            }
                        }
                    }
                }
            }
            init();
            x++;
        }
        init_RowChange();
        if( rowConfirm == 0 && colConfirm == 0 ) break;
    }
    
}

//col
int propagationCol(int col)
{
    int ii = SIZE+1;
    int jj = 0;
    int isConflict = 0;
    
    init();//初始化d 
    
    //每個col有幾個數字
    jj = store[col];
    
    //每個col有哪些數字
    for( int i = 0; i < jj; i++ )
	{
        d[i] = D[col][i];
    }
    
    //S=C (因paint需要用到S)
    for( int i = 0; i < SIZE+1; i++ )
	{				//x
        S[i] = C[i][col+1];//捨左第一排 
    }
    
    paint(ii, jj);
    return 0;
}

//row 
int propagationRow(int row)
{
    int ii = SIZE+1;
    int jj = 0;
    int isConflict = 0;
    
    init();//初始化d 
    
    //每個row有幾個數字 
    jj = store[row];
    
    //每個row有哪些數字 
    for( int i = 0; i < jj; i++ )
	{
        d[i] = D[row][i];
    }
    
    row = row % SIZE;//col:0~24 row:25~49
    
    //S=C (因paint需要用到S)
    for( int i = 0; i < SIZE+1; i++ )
	{
        S[i] = C[row+1][i];//捨上第一排 
    }
    
    paint(ii, jj);
    return 0;
}

//fix
int fix(int i, int j)
{
    if(i==0 && j==0)
        return 1;
    else if(i==0 && j>= 1)
        return 0;
    else
	{
        if(fix0(i, j)==1 || fix1(i, j)==1) 
            return 1;
        else
            return 0;
    }
}

int fix0(int i, int j)
{
    if(S[i-1]!='1')
        return (fix(i-1, j));
    else
        return 0;
}

int fix1(int i, int j)
{
    int countone = 0;
    int shouldone = 0;
    int confirm = 0;
    
    int total=0;
    for(int counter=0;counter<j;counter++)
	{
        total+=(d[counter]+1);
    }
    
    if(j>=1 && i>=(d[j-1]+1) && i>=total )
	{
        for(int counter=0;counter<d[j-1];counter++ )
		{
            if(S[i-1-counter]=='0')
                return 0;
        }
        
        if(S[i-d[j-1]]=='0' )
            return 0;
        
        if( S[i-d[j-1]-1]=='1')
            return 0;
        
        //已經是黑色的數量 
        for(int counter=0;counter<i-(d[j-1]);counter++)
		{
            if(S[counter] == '1')
                countone++;
                //printf("counter = %d\n", counter );
        }
        
        //黑色應該有的數量 
        for(int counter=0;counter<(j-1);counter++)
		{
            shouldone+=d[counter];
        }
        
        //printf("countone = %d\n", countone);
        //printf("shouldone = %d\n", shouldone );
        
        if(countone>shouldone)
            return 0;
        
        return (fix(i-d[j-1]-1, j-1));
    }
    else
	{
        return 0;
    }
}

//paint
int paint(int i, int j)
{
    if(i==0)
        return 0;
    else
        paintP(i, j);
        
    return 0;
}

int paintP(int i, int j)
{
    if(fix0(i, j)==1 && fix1(i, j)==0)
	{
        paint0(i, j);
    }
    else if(fix0(i, j)==0 && fix1(i, j)==1)
	{
        paint1(i, j);
    }
    else if(fix0(i, j)==1 && fix1(i, j)==1)
	{
        merge(i, j);
    }
    else
	{
        isConflict = 1;
        return 0;
    }
    
    return 0;
}

int paint0(int i, int j)
{
    S[i-1]='0';
    paint(i-1, j);
    return 0;
}

int paint1(int i, int j)
{
    int total=0;
    //是黑色的數量 
    for(int counter=0;counter<j;counter++)
	{
        total+=(d[counter]+1);
    }
    
    //i:SIZE+1 j:store的值 
    if(i>=total && j>=0)
	{
        for(int counteri=0;counteri<d[j-1];counteri++){
            S[i-1]='1';
            i--;
        }
        S[i-1]='0';
        i--;
        
        paint(i, j-1);//i:剩下沒被決定為0或1的數量 
    }
    else
	{
        paint(0, j);
    }
    
    return 0;
}

//merge
int merge(int i, int j)
{
    char s1[SIZE+1];
    char s2[SIZE+1];
    char temp[SIZE+1];
    
    for(int counteri=0;counteri<SIZE+1;counteri++)//初始化為u 
	{
        s1[counteri]='u';
        s2[counteri]='u';
        temp[counteri]='u';
    }
    
    //temp=S (先存起來因為S經過paint0會改變)
    for(int counteri=0;counteri<SIZE+1;counteri++)
	{
        temp[counteri] = S[counteri];
    }
    paint0(i, j);
    //s1=S 
    for(int counteri=0;counteri<SIZE+1;counteri++)
	{
        s1[counteri]=S[counteri];
    }
    
    
    //S=temp (還原S) 
    for(int counteri=0;counteri<SIZE+1;counteri++)
	{
        S[counteri]=temp[counteri];
    }
    paint1(i, j);
    //s2=S
    for(int counteri=0;counteri<SIZE+1;counteri++)
	{
        s2[counteri]=S[counteri];
    }
    
    mergeC(s1, s2);
    return 0;
}

int mergeC(char s[], char t[])
{
    char s1[SIZE+1];
    char s2[SIZE+1];
    
    for(int counteri=0;counteri<SIZE+1;counteri++)//換個名稱表示 
	{
        s1[counteri]=s[counteri];
        s2[counteri]=t[counteri];
    }
    
    for(int i=0;i<SIZE+1;i++)
	{
        if(s1[i]=='1' && s2[i]=='1')
		{
            S[i]='1';
        }
        else if(s1[i]=='0' && s2[i]=='0')
		{
            S[i]='0';
        }
        else
		{
            S[i]='u';
        }
    }
    return 0;
}

//其他
int getInt(char ch)
{
	if(ch == '0') return 0;
    if(ch == '1') return 1;
    if(ch == '2') return 2;
    if(ch == '3') return 3;
    if(ch == '4') return 4;
    if(ch == '5') return 5;
    if(ch == '6') return 6;
    if(ch == '7') return 7;
    if(ch == '8') return 8;
    if(ch == '9') return 9;
} 


//初始化 
int init_C()
{
    for( int i=0; i<SIZE+1; i++ )
	{
        for( int j=0; j<SIZE+1; j++ )
		{
            C[i][j] = 'u';
        }
    }
    return 0;
}

int init_D()
{
    for( int i = 0; i<2*SIZE; i++ )
	{
        for( int j = 0; j < SIZE/2+1; j++ )
		{
            D[i][j] = 0;
        }
    }
    return 0;
}

int init_Store()
{
    for( int i = 0; i < 2*SIZE; i++ )
	{
        store[i] = 0;
    }
    return 0;
}

int init()
{
    for( int i = 0; i < SIZE/2+1; i++ )
	{
        d[i] = 0;
    }
    return 0;
}

int init_RowChange()
{
    for( int i = 0; i < SIZE+1; i++ )
	{
        rowChange[i] = 0;
    }
    return 0;
}

int init_ColChange()
{
    for( int i = 0; i < SIZE+1; i++ )
	{
        colChange[i] = 0;
    }
    return 0;
}

//印結果 
int print(){
    for( int i = 1; i < SIZE+1; i++ )
	{
        for( int j = 1; j < SIZE+1; j++ )
		{
            printf("%-3c", C[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}


