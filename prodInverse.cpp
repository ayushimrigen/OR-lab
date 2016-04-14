#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#define vvd vector<vector <double> >
#define Ep 0.00001
using namespace std;


vvd multiply(vvd A, vvd B)
{
  int n = A.size();
  vvd C(n,A[0]);
  for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
  	{
    C[i][j]=0;
    for(int k=0;k<n;k++)
      C[i][j]+=A[i][k]*B[k][j];
  	}
  return C;
}

vector<double> multiply(vector<double> C,vvd A)
{
  int n=C.size();
  vector<double> R(n);
  for(int i=0;i<n;i++)
	{
  	R[i]=0;
  	for(int j=0;j<n;j++)
      R[i]+=A[i][j]*C[j];
  	if(abs(R[i])<Ep)
    R[i]=0;
 	 
	}
  return R;
}

vector<double> getN(vector<double> e,int toC)
{
  double r = e[toC];
  e[toC]=1/r;
  for(int i=0;i<e.size();i++)
	if(i!=toC)
  	e[i]=-e[i]/r;
  return e;
}
void print(vvd A)
{
 
  for(int i=0;i<A.size();i++)
	{
  	cout<<"\t";
  	for(int j=0;j<A.size();j++)
    cout<<setw(16)<<A[i][j];
  	cout<<endl;
	}
  cout<<"\n\n";
}
void print(vector<double> A)
{
 
  for(int i=0;i<A.size();i++)
	cout<<A[i]<<endl;
  cout<<"\n";
}
vvd getInverse(vvd M,vvd B,vvd prevB,vector<int> diff)
{
 
  int n = diff.size(),toC,nC=0;
  for(int i=0;i<n;i++)
	if(diff[i]==1)
  	{
    toC = i;
    nC++;
  	}

  if(nC > 1)
	{
  	vvd nM=M;
  	for(int i=0;i<n;i++)
    if(i==toC)
      nM[i][toC]=1;
    else
      nM[i][toC]=0;
  	diff[toC]=0;
  	vvd I=getInverse(nM,B,prevB,diff);
	 
  	prevB=multiply(I,prevB);
  	cout<<endl;
 	 
	}

  vvd A = B;
  vector<double> e,N,C;
  for(int i=0;i<n;i++)
	C.push_back(M[i][toC]);
  e = multiply(C,prevB);
  //cout<<"e"<<toC+1<<endl;
  // print(e);
  N = getN(e,toC);
  //cout<<"N"<<toC+1<<endl;
  // print(N);
 
  for(int i=0;i<n;i++)
	A[i][toC]=N[i];
  cout<<"E"<<toC+1<<endl;
  print(A);
  A=multiply(A,prevB);
  cout<<"Inverse "<<toC+1<<endl;
  print(A);
  return A;
}
 
int main()
{
  int n;
  cout<<"Enter n\n";
  cin>>n;
  vector<double> temp(n);
  vector<int> diff(n);
  vvd M(n,temp),B(n,temp);
  cout<<"Enter M\n";
  for(int i=0;i<n;i++)
	{
 	 
  	for(int j=0;j<n;j++)
    {
      cin>>M[i][j];
      B[i][j]=0;
      if(i==j)
    	B[i][j]=1;
      if(j==i && M[i][j]!=1)
    	diff[j]=1;
   	if(j!=i && M[i][j]!=0)
    	diff[j]=1;
    }
	}

  vvd I =getInverse(M,B,B,diff);
 }
