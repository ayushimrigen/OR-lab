#include <iostream>
#include <vector>
using namespace std;
#define vvd vector<vector <double> >
#define INF 10000

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
  cout<<endl;
}



void printvector(vector<vector<double> > A)
{
 
  cout<<"\n";
  for(vector<vector<double> >::iterator i=A.begin();i!=A.end();i++)
    {
      printvec(*i);
      //cout<<endl;
    }
}

void printtable(vvd table,vector<double> A,vector<double> B)
{
  int m=A.size(),n=B.size();
  cout<<"\t";
   for(int j=0;j<n;j++)
      cout<<"D"<<j+1<<"\t";
   cout<<"A"<<endl;
  for(int i=0;i<=m;i++)
    {
      if(i<m)
	cout<<"S"<<i+1<<"\t";
      else
	cout<<"B \t";
      for(int j=0;j<n;j++)
	{
	   if(i==m)
	    cout<<B[j]<<"\t";
	  else
	    cout<<table[i][j]<<"\t";
	}
      if(i<m)
      cout<<A[i]<<"\t\n";
    }

}

int NWCR(vvd coef,vvd table)
{
  int m=coef.size(),n=coef[0].size();

  vector<double> u(m),v(n);
  for(int i=0;i<m;i++)
    u[i]=-INF;
  for(int j=0;j<n;j++)
    v[j]=-INF;
  cout<<"\n\nEnter guess for u[0]\n";
  cin>>u[0];
  for(int i=0;i<m;i++)
    {
      for(int j=0;j<n;j++)
	{
	  if(table[i][j]>0)
	    {
	      if(v[j]==-INF)
		v[j]=coef[i][j]-u[i];
	      else if(u[i]==-INF)
		u[i]=coef[i][j]-v[j];
	    }
	}
    }
  cout<<"u= "; printvec(u);
  cout<<"v= ";printvec(v);

  for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
	  if(table[i][j]==0)
	    if(u[i]+v[j]>coef[i][j])
	      return 0;

  return 1;


}

int main()
{

  int m,n;
  cout<<"Enter m,n\n";
  cin>>m>>n;
  vector<double> A(m),B(n);
  vvd table(m,B),coef(m,B);
 
  cout<<"Enter coeffs\n";
  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      cin>>coef[i][j];
  cout<<"Enter amounts available\n";
  for(int i=0;i<m;i++)
    cin>>A[i];
  cout<<"Enter amounts required\n";
  for(int j=0;j<n;j++)
    cin>>B[j];


  cout<<"ORIGINAL COEFFICIENTS\n";
  printtable(coef,A,B);
  cout<<"\n\n";
  for(int j=0;j<n;j++)
    {
      //if(B[j]>0)
	for(int i=0;i<m;i++)
	  {
	    if(A[i]>0 && B[j]>0)
	      {
		if(A[i]>B[j])
		  {
		    A[i]=A[i]-B[j];
		    table[i][j]+=B[j];
		    B[j]=0;
		  }
		else 
		  {
		     table[i][j]+=A[i];
		      B[j]-=A[i];
		    A[i]=0;
		   
		   
		  }
		printtable(table,A,B);
		 //printvec(A);
		 // printvec(B);
	    cout<<endl<<endl;
	      }
	   
	  }
    }

  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      if(table[i][j]>0)
	cout<<"x"<<i+1<<j+1<<" = "<<table[i][j]<<endl;
  if(NWCR(coef,table))
    {
      cout<<"The solution is optimal\n\n";
    }
  else
    cout<<"The solution is not optimal\n\n";
}
	
/*
3
4
10 12 20 11
12 7 9 20
10 14 16 18
15 25 5
5 15 15 10
*/
