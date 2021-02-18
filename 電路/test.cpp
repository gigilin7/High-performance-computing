#include <iostream>
using namespace std;
int main()
{
	int ans;
	for(int a=0;a<2;a++)
		for(int b=0;b<2;b++)
			for(int c=0;c<2;c++)
				for(int d=0;d<2;d++)
					for(int e=0;e<2;e++)
						for(int f=0;f<2;f++)
							for(int g=0;g<2;g++)
								for(int h=0;h<2;h++)
									for(int i=0;i<2;i++)
										for(int j=0;j<2;j++)
											for(int k=0;k<2;k++)
												for(int l=0;l<2;l++)
													for(int m=0;m<2;m++)
														for(int n=0;n<2;n++)
															for(int o=0;o<2;o++)
																for(int p=0;p<2;p++){
																	ans=((((a||b)&&(!b||!d))&&((c||d)&&(!d||!e)))&&(((e||!f)&&(f||g))&&((f||!g)&&(h||!i))))&&((((i||j)&&(i||!j))&&((!j||!k)&&(k||l)))&&(((l||j)&&(m||n))&&((!h||!n)&&((n||!o)&&((o||p)&&(!p||g))))));	
																	if(ans==1)
																		cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<g<<" "<<h<<" "<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<m<<" "<<n<<" "<<o<<" "<<p<<'\n';
																}
																	
																	
																			
			
			
	
} 
