#include<cstdio>

const int W = 10000;
int m,n,less,equal,great;
double a[100][100];
int nbv[100];
int bv[100];
int dif;

void print(double fn[])
{
    printf("\n");
  int i,j;
  for(i=0;i<n;i++)
    {
      printf("\t\t x%d",nbv[i]);
    }
  printf("\t\t 1");
    printf("\n\t\t");
  for(i=0;i<n+1;i++)
    {
      printf("----------------");
    }
    printf("\n");
  for(i=0;i<m;i++)
    {
      printf("\t");
      for(j=0;j<n;j++)
      	{
	        	printf("\t %lf",a[i][j]);
      	}
      printf("\t %lf\t| x%d \n",a[i][j],bv[i]);
    }
  printf("\t");
  for(i=0;i<=n;i++)
    {
      printf("\t %lf",fn[i]);
    }
  printf("\t| z\n\n");
}
void sol_print(double fn[])
{
    int i;
    printf("\n\t\t The solution is:\n\n");
    for(i=0;i<m;i++)
    {
      printf("\t\t x%d = %lf\n",bv[i],a[i][n]);
    }    
    printf("\n\t\t z = %lf \n",fn[n]);
    printf("\n\t\t Other variables are 0\n\n");
}    
void change(int r,int c,double fn[])
{
  int t,i,j;
  t=nbv[c];
  nbv[c]=bv[r];
  bv[r]=t;

  double b;
  double key=a[r][c];

  for(i=0;i<m;i++)
    {
      if(i==r)
	continue;
      for(j=0;j<=n;j++)
	{
	  if(j==c)
	    continue;
	  b=(a[i][j]*key-a[i][c]*a[r][j])/key;
	  a[i][j]=b;
	}
    }
  for(i=0;i<m;i++)
    {
      if(i==r)
	continue;
      a[i][c]=(-1)*a[i][c]/key;
    }

  for(i=0;i<=n;i++)
    {
      if(i==c)
	continue;
      b=(fn[i]*key-a[r][i]*fn[c])/key;
      fn[i]=b;
      a[r][i]=a[r][i]/key;
    }
  fn[c]=(-1)*fn[c]/key;
  a[r][c]=1/key;
}

int ratio(int p,double fn[])
{
  int i,l=-1,c=0;
  double r;
  for(i=0;i<m;i++)
    {
      double k;
      k=a[i][n]/a[i][p];
      if(k>0&&c==0)
	{
	  c=1;
	  r=k;
	  l=i;
	  continue;
	}
      if(k>0&&k<r)
	{
	  r=k;
	  l=i;
	}
    }
  return l;
}

int find_min(double fn[])
{
  int i;
  int p=0;
  for(i=1;i<n;i++)
    {
      if(fn[i]<fn[p])
	{
	  p=i;
	}
    }
  return p;
}

int main()
{
  int i,j;
double fn[100],fn1[100],fn2[100];
 printf("Enter no of equations\n");
 scanf("%d",&m);
printf("Enter the  no of variables \n");
 scanf("%d",&n);

  dif=n-m;

  printf("Enter the no. of equations with <=, = and >= sign respectively:\n");
  scanf("%d %d %d",&less,&equal,&great);
 
  if(less>0)
    printf("Enter the equation coefficients for <= sign\n");
    for(i=0;i<=n+great;i++)
    {
    fn1[i]=0;
    fn2[i]=0;
}    
    
  for(i=0;i<less;i++)
    {
       
      for(j=0;j<n;j++)
      {
           fn1[j]=0;
           fn2[j]=0;
          
            scanf("%lf",&a[i][j]);
	  } 
     
      scanf("%lf",&a[i][j+great]);
    }
    fn1[n+great]=0;
    fn2[n+great]=0;
  if(equal>0)
    printf("Enter the equation coefficients for = sign\n");
  for(i=less;i<less+equal;i++)
    {
        
      for(j=0;j<n;j++)
      {
	
            scanf("%lf",&a[i][j]);
            fn1[j]-=a[i][j];
	  } 
     
      scanf("%lf",&a[i][j+great]);
      fn1[n+great]-=a[i][j+great];
    }
  if(great>0)  
    printf("Enter the equation coefficients for >= sign\n");
  for(i=0;i<great;i++)
    {
      for(j=0;j<n;j++)
      {
	
            scanf("%lf",&a[less+equal+i][j]);
            fn1[j]-=a[less+equal+i][j];
            
    
	  } 
	  for(j=n;j<n+great;j++)
	  {
	      fn2[j]=0;
	     if(i==j-n)
            a[less+equal+i][j] = -1;
         else
            a[less+equal+i][j] = 0;
         fn1[j]-=a[less+equal+i][j];
	  }    
	  //  printf("constant: ");
      scanf("%lf",&a[less+equal+i][n+great]);
      fn1[n+great]-=a[less+equal+i][n+great];
    }
    //printf("%lf\n",fn1[0]);
  for(i=0;i<m;i++)
    {
      bv[i]=n+great+i+1;
    }
  int t;
  double sum=0.0;
  printf("Enter function coefficients \n");
  for(i=0;i<n;i++)
    {
      nbv[i]=i+1;
      // printf("x%d: ",(i+1));
      scanf("%lf",&fn[i]);
      fn[i]=0-fn[i];
      fn2[i]=fn[i];
    }  
    for(i=n;i<n+great;i++)
    {
        fn[i]=0;        fn2[i]=0;        nbv[i]=i+1;
    }            
    scanf("%lf",&fn[n+great]);
     n=n+great;
  int p;  int x;
  print(fn1);
   p=find_min(fn1);
  while(fn1[p]<0)
    {
      x=ratio(p,fn1);
      if(x==-1)
      {
          printf("\n\t\tNo solution\n");          break;
      }    
      change(x,p,fn1);      print(fn1);
      p=find_min(fn1);
    }
    if(x!=-1)
    {
        printf("Solution after phase 1:\n");        sol_print(fn1);
    }    
    if(fn1[p]==0)
    {
        for(i=0;i<n;i++)
        {
            if(nbv[i]>n)
            {
                for(j=0;j<m;j++)
                {
                    a[j][i]=0;
                }    
                fn2[i]=0;
            }    
        } 
        int ch=0;
        for(i=0;i<m;i++)   
        {
            if(bv[i]<=n-great)
            {
                ch++;
                for(j=0;j<n;j++)
                {
                    if(nbv[j]<=n)
                    {
                        if(ch==1)
                        fn2[j]=fn[j];
                        fn2[j]-=(fn[bv[i]-1]*a[i][j]);
                    }    
                } 
                fn2[j]-=(fn[bv[i]-1]*a[i][j]);   
            }    
        }
        print(fn2);
        p=find_min(fn2);
          while(fn2[p]<0)
          {
              x=ratio(p,fn2);
              if(x==-1)
              {
                            printf("\n\t\tNo solution\n");
                            break;
              }    
              change(x,p,fn2);
              print(fn2);
              p=find_min(fn2);
          }
          if(x!=-1)
          {
                    printf("Solution after phase 2:\n");
                    sol_print(fn2);
          }
          /*if(fn2[p]==0)
    {
        printf("\n\t\tAlternate Solution:\n\n");
        
      x=ratio(p,fn2);
      if(x==-1)
      {
          printf("No solution\n");
      }    
      else{
      change(x,p,fn2);
      print(fn2);
      sol_print(fn2);}
    }*/      
    }
    else
        printf("No soln");    
    return 0;
} 
