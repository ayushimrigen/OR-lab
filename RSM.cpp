#include <iostream>
#include <vector>
#include <iomanip>
#define Ep 0.00001
#define vvd vector<vector<double> >
#include <cmath>
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
	R[i]+=A[j][i]*C[j];
      if(abs(R[i])<Ep)
	R[i]=0;
 	 
    }
  return R;
}


vector<double> multiply(vvd A,vector<double> C)
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

vvd getI(int n)
{
  vector<double> A(n);
  vvd B(n,A);
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      {
	B[i][j]=0;
	if(i==j)
	  B[i][j]=1;
      }
  return B;
}


double multiply(vector<double> A,vector<double> B)
{
  double S=0;
  int n=A.size();
  for(int i=0;i<n;i++)
    S+=A[i]*B[i];
  return S;
}

void print(vector<double> A)
{
  int n=A.size();
  cout<<"(";
  for(int i=0;i<n;i++)
    cout<<A[i]<<",";
  cout<<")\n";
}
void print(vector<int> A)
{
  int n=A.size();
  cout<<"(";
  for(int i=0;i<n;i++)
    cout<<A[i]<<",";
  cout<<")\n";
}
vvd exchange(vvd A,vector<double> c,int x)
{
  int n=c.size();
  for(int i=0;i<n;i++)
    A[i][x] = c[i];
  return A;
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
  e = multiply(prevB,C);
  //cout<<"e"<<toC+1<<endl;
  // print(e);
  N = getN(e,toC);
  //cout<<"N"<<toC+1<<endl;
  // print(N);
 
  for(int i=0;i<n;i++)
    A[i][toC]=N[i];
  //cout<<"E"<<toC+1<<endl;
  //print(A);
  A=multiply(A,prevB);
  //cout<<"Inverse "<<toC+1<<endl;
  //print(A);
  return A;
}

vvd Inverse(vvd M,int n)
{
  vector<double> temp(n);
  vector<int> diff(n);
  vvd B(n,temp);
  
  for(int i=0;i<n;i++)
    {
 	 
      for(int j=0;j<n;j++)
	{
      
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
  return I;
}
  
void RSM(vvd A,vvd B,vvd Bin,vector<int> diff,vector<double> b,vector<double> cB,vector<double> cN,vector<int> BV,vector<int> NBV)
{

  vector<double> xb,Y,Z,Pj;
  int n=A[0].size();
  int m = A.size();
  cout<<"\n NEW ITERATION \n";
  cout<<"\t B = \n"; print(B);
  cout<<"\t B inverse = \n"; print(Bin);
  xb = multiply(Bin,b);
  cout<<"\t cb = "; print(cB);
  cout<<"\t xb = "; print(xb);
  Y = multiply(cB,Bin);
  cout<<"\t Y = "; print(Y);
  double min = 0;
  int enter,leave;
  for(int i=0;i<n;i++)
    {
      vector<double> c;
      for(int j=0;j<n;j++)
	c.push_back(A[j][i]);
      
      double x = multiply(Y,c) - cN[i];
     
      if(x<min && x<0)
	{
	  min=x;
	  enter=i;
	  Pj = c;
	}
      
    }

  if(min==0)
    {
      cout<<"\n\n"<<"--------------------DONE--------------------------\n";
      for(int i=0;i<n;i++)
	{
	  for(int j=0;j<n;j++)
	    {
	      if(NBV[j]==i)
		cout<<"x"<<i+1<<" = "<<xb[j]<<endl;
	      else if(BV[j]==i)
		cout<<"x"<<i+1<<" = "<<0<<endl;
	    }
	}

     
      cout<<"\t\t Z = "<<multiply(cB,xb)<<endl;
      return;
    }
  cout<<"\t Pj = "; print(Pj);
  vector<double> alpha = multiply(Bin,Pj);
  cout<<"\t alpha = "; print(alpha);
  min=10000;
  for(int i=0;i<n;i++)
    if(alpha[i]>0 && (xb[i]/alpha[i])<min)
      {
	min=(xb[i]/alpha[i]);
	leave = i;
      }

  diff[leave]=1;
  int temp = NBV[enter];

  NBV[enter]= BV[leave];
  BV[leave]= temp;

  double tempd = cN[enter];

  cN[enter]= cB[leave];
  cB[leave]= tempd;
  vvd X=B;
  vvd B1 = exchange(B,Pj,leave);
  vvd I=getI(n);
  vvd B1in = Inverse(B1,n);

  vector<double> c(n);
  for(int i=0;i<n;i++)
    c[i]=B[i][leave];
  vvd A1 = exchange(A,c,enter);

 
  RSM(A1,B1,B1in,diff,b,cB,cN,BV,NBV);
}

 
int main()
{
  int n,m;
  
  cout<<"Enter number of variables\n";
  cin>>n;
  cout<<"Enter number of equations\n";
  cin>>m;
  vector<double> Z(n+1),cb(n),b(m),cN(n);
  vector<int> diff(n),Bv,Nbv;
  vvd A(m,cb);
  for(int i=0;i<m;i++)
    for(int j=0;j<n+1;j++)
      {
	if(j<n)
	  cin>>A[i][j];
	if(j==n)
	  cin>>b[i];
      }
  cout<<"Enter Z\n";
  for(int i=0;i<n+1;i++)
    {
      cin>>Z[i];
      if(i<n)
	{
	  cN[i]=Z[i];
	  Bv.push_back(i);
	  Nbv.push_back(i+n);
	}
    }
  cout<<"b = "; print(b);
  vvd B=getI(n);
  RSM(A,B,B,diff,b,cb,cN,Bv,Nbv);
}
