#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#define INF 100000
using namespace std;
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
  for(int i=0;i<m-1;i++)
	{
  	if(A[i][n-1] < 0)
  	flag=1;
  
	if(minNeg >= A[i][n-1])
  	{
    minNegPos=i;
    minNeg=A[i][n-1];
  	}
	}

  if(flag==0 || flag==-1)
	{
	 if(last==0)
	   cout<<"\n--------------------------------------------------------------------------\n Gamma = "<<-A[m-1][n-1]<<endl;
  	else
    cout<<"\nAlternative Solution :\n";
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
  	//cout<<"\nSlack variables = ";
  	//printvec(z);
  	cout<<endl<<endl;
 	 
	 double g = -A[m-1][n-1];
    
    double game = 0;  
    for(int i=0;i<x.size();i++)
      {
  cout<<"x"<<i+1<<" = "<<x[i]/g<<endl;
  game+= T[0][i];
      }

    cout<<"Game Value= "<<game<<endl;

  	if(flag!=-1 || last==1)
 	 
    return;
 	 
	}
 
 
  double minRatio = INF,minRatioPos=0,unbound=1;

  for(int i=0;i<n-1;i++)
	{
	  
	  double r;
	  if(A[minNegPos][i] < 0)
	    {
	    r = abs(A[m-1][i]/A[minNegPos][i]);
	    }
  	if(r<minRatio)
    {
      minRatio = r;
      minRatioPos = i;
    }
	}

  int temp = ver[minNegPos];
  ver[minNegPos]=hor[minRatioPos];
  hor[minRatioPos]=temp;

  double M =A[minNegPos][minRatioPos];
  if(flag!=-1)
  cout<<"--------------------------------------------------------------------------\nPivot ="<<M <<" At position ("<<minNegPos<<","<<minRatioPos<<")\n";
 
  vector<vector<double> > res=A;

  for(int i=0;i<m;i++)
	for(int j=0;j<n;j++)
  	{
    if(j==minRatioPos && i==minNegPos)
      res[i][j]=1/M;
    else if (j==minRatioPos)
     res[i][j]=-A[i][j]/M;
    else if(i==minNegPos)
      res[i][j]=A[i][j]/M;
    else
      res[i][j]= (A[i][j]*M -A[i][minRatioPos]*A[minNegPos][j])/M;
  	}
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
  cout<<"Enter number of columns in the table\n";
  cin>>m;
  cout<<"Enter number of rows in the table\n";
  cin>>n;
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
	  //	int x;
	  //	cin>>x;
	  if(j<n)
	    temp.push_back(-newT[j][i]);
	  else
	    temp.push_back(-1);
	  
  	}
	A.push_back(temp);
	}
  for(int i=0;i<m;i++)
	if(A[i][n]>0)
  	{
    cout<<"No solution by this method\n";
    return 0;
    }
  table=A;
  //cout<<"Enter Z\n";
  for(int i=0;i<=n;i++)
	{
  	hor.push_back((i+1));
  	//double temp;
	//	cin>>temp;
  	if(i==n)
    z.push_back(0);
  	else
    z.push_back(1);
	}

  table.push_back(z);
  printTable(table,hor,ver);
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

/*
3
3
1 3 5
5 4 1
2 3 2
*/
