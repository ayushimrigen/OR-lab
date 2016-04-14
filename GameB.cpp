#include <iostream>
#include <vector>
#include <iomanip>
#define Ep 0.00001
#define INF 100000
#define vvd vector<vector<double> >
#include <cmath>
using namespace std;


void printvec(vector<int> A)
{
  int m=A.size();
  cout<<"\t(";
  for(int i=0;i<m;i++)
    {
      if(i!=m-1)
	cout<<A[i]<<",";
      else cout<<A[i]<<")\t";
    }
}

void printvec(vector<double> A)
{
  int m=A.size();
  cout<<"\t(";
  for(int i=0;i<m;i++)
    {
      if(i!=m-1)
	cout<<A[i]<<",";
      else cout<<A[i]<<")\t";
    }
}
void printvector(vector<vector<double> > A)
{
 
  cout<<"\n";
  for(vector<vector<double> >::iterator i=A.begin();i!=A.end();i++)
    {
      printvec(*i);
      cout<<endl;
    }
}
void printTable(vector<vector<double> > A,vector<int> hor, vector<int> ver)
{

  cout<<"\nCurrent table:\n";
  int m=A.size(),n=A[0].size();
  for(int i=-1;i<m;i++)
    {
      if(i== -1)
	cout<<setw(14)<<' ';
      else if(i==m-1)
	cout<<setw(14)<<'z';
      else
  	if(ver[i]<0)
	  cout<<setw(14)<<'x'<<m-ver[i]-1;
  	else
	  cout<<setw(14)<<'x'<<ver[i];
      for(int j=0;j<n;j++)
	{
	  if(i== -1)
	    {
	      if(j==n-1)
		cout<<right<<setw(15)<<'b';
	      else if(hor[j]==0)
		cout<<'\t';
	      else if(hor[j]<0)
		cout<<setw(14)<<"x"<<(m-hor[j]-1);
	      else
		cout<<setw(14)<<"x"<<hor[j];
	    }
	  else 
	    cout<<setw(15)<<A[i][j];
	}
        
      cout<<endl;
    
      
    }
}
void simplex(vector<vector<double> > A,vector<int> hor, vector<int> ver,vector<vector<double> > T,int last=0)
{

  int m=A.size(),n=A[0].size();
  //printvector(A);
  double flag = 0,minNegPos=0,minNeg=0;
  for(int i=0;i<n-1;i++)
    {
      if(A[m-1][i] < 0)
	flag=1;
      
       if(A[m-1][i]==0)
	flag=-1;
       else if(A[m-1][i]<0 && minNeg >= A[m-1][i])
  	{
	  minNegPos=i;
	  minNeg=A[m-1][i];
  	}
    }

  if(flag==-1 && last ==0)
    {
      cout<<"\n--------------------------------------------------------------------------\nInfinite Solutions exist\n--------------------------------------------------------------------------\n ";
    
    }

  if(flag==0 || flag==-1)
    {
     
      vector<double> x(n-1),z(m-1);
      for(int i=0;i<n-1;i++)
	if(hor[i] < 0)
	  z[-hor[i]-1]=0;
	else
	  x[hor[i]-1]=0;

      for(int i=0;i<m-1;i++)
	if(ver[i] < 0)
	  z[-ver[i]-1]=A[i][n-1];
	else
	  x[ver[i]-1]=A[i][n-1];

      cout<<"  X =";
      printvec(x);
      // cout<<"\nSlack variables = ";
      // printvec(z);
      cout<<endl;
 	 
      double g = 0;
      for(int i=0;i<x.size();i++)
	g+= x[i];
      cout<<"\n\nGamma = "<<g<<endl; 

      cout<<"Probabilities for Player B are:\n";
     
    double game = 0;  
    for(int i=0;i<x.size();i++)
      {
  cout<<"y"<<i+1<<" = "<<x[i]/g<<endl;
  game+= T[0][i]*(x[i]/g);
      }
    if(game<Ep && game>-Ep )
      game=0;
    cout<<"Game Value= "<<game<<endl;
 	 
	return;
 	 
    }
 
 
  double minRatio = INF,minRatioPos=0,unbound=1;

  for(int i=0;i<m-1;i++)
    {
      if(A[i][minNegPos]>0)
	unbound=0;
      double r = A[i][n-1]/A[i][minNegPos];
      if(A[i][minNegPos] >0  && r<minRatio)
	{
	  minRatio = r;
	  minRatioPos = i;
	}
    }
 
  if(unbound==1)
    {
      cout<<"\n\n UNBOUNDED CASE\n";
      // vector<double> x(0);
      return ;
    }
  int temp = hor[minNegPos];
  hor[minNegPos]=ver[minRatioPos];
  ver[minRatioPos]=temp;

  double M =A[minRatioPos][minNegPos];
  if(flag!=-1)
    cout<<"--------------------------------------------------------------------------\nPivot ="<<M <<" At position ("<<minRatioPos<<","<<minNegPos<<")\n";
 
  vector<vector<double> > res=A;

  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      {
	if(i==minRatioPos && j==minNegPos)
	  res[i][j]=1/M;
	else if (i==minRatioPos)
	  res[i][j]=A[i][j]/M;
	else if(j==minNegPos)
	  res[i][j]=-A[i][j]/M;
	else
	  res[i][j]= (A[i][j]*M -A[minRatioPos][j]*A[i][minNegPos])/M;
      }

  // char ch;
  //cin>>ch;
  if(flag!=-1)
    printTable(res,hor,ver);
  if(flag==-1)
    simplex(res,hor,ver,T,1);
  else
    simplex(res,hor,ver,T);
}


int main()
{
  int n,m,r,maxOrMin;
  cout<<"Enter number of columns\n";
  cin>>n;
  cout<<"Enter number of rows\n";
  cin>>m;
  r=m;
  vector<double> temp(m);
  vector< vector<double> > A,table,T(n,temp),newT(n,temp);
  vector<double> z;
  vector<int> hor,ver;
  cout<<"Enter the table\n";
    int isNeg = 0,mostNeg=0;
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
      {
	cin>>T[i][j];
	if(T[i][j]<0)
	  {
	    isNeg=1;
	    mostNeg = T[i][j];
	  }
      }
  newT = T;
  
  if(isNeg==1)
    for(int i=0;i<n;i++)
      for(int j=0;j<m;j++)
	newT[i][j]-=mostNeg;
  
  for(int i=0;i<m;i++)
    {
      ver.push_back(-(i+1));
      vector<double> temp;
      for(int j=0;j<n+1;j++)
  	{

	  int x;
	  if(j<n)
	    x=newT[i][j];
	  else
	    x=1;
	  temp.push_back(x);
  	}
      A.push_back(temp);
    }
  for(int i=0;i<m;i++)
    if(A[i][n]<0)
      {
	cout<<"No solution by this method\n";
	return 0;
      }
  table=A;
  //cout<<"Enter Z\n";
  for(int i=0;i<=n;i++)
    {
      hor.push_back((i+1));
      
      if(i==n)
	z.push_back(0);
      else
	z.push_back(-1);
    }

  table.push_back(z);
  printTable(table,hor,ver);
  double g=0;
  //vector<double> m;
  for(int j=0;j<n;j++)
    {
      int min = INF;
      for(int i=0;i<m;i++)
	if(table[i][j]<min)
	  min=table[i][j];
      if(min>g)
	g=min;
    }
 
  vector<double> Y;
  simplex(table,hor,ver,T);
 

}
/*
3
3
1 2 3 
3 1 2
2 3 1 
*/

/*
4
3
1 3 3 4 
3 6 1 2 
7 3 7 8 
*/
