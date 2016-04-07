#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>

#include <algorithm>
#define E 0.000001
#define INF 10000000
using namespace std;

void printvec(vector<double> A)
{
  int m=A.size();
  cout<<"\t(";
  for(int i=0;i<m;i++)
    {
      if(i!=m-1)
	cout<<A[i]<<",";
      else cout<<A[i]<<")\n";
    }
}
void printvector(vector<vector<double> > A)
{
  
  cout<<"\n";
  for(vector<vector<double> >::iterator i=A.begin();i!=A.end();i++)
    {
      printvec(*i);
    }
}

int findRank(vector<vector<double> > A,int m, int n)
{
  int rank = m;
  for(int piv=0;piv<m;piv++)
    {
      int div = A[piv][piv];
      if(div==0) continue;
      for(int j=0;j<n+1;j++)
	A[piv][j]/=div;
     
      for(int j=0;j<m;j++)
	{
	  if(j==piv)
	    continue;
	  int toSub = A[j][piv];
	 
	  for(int i=0;i<n+1;i++)
	    {
	      A[j][i]=A[j][i]-A[piv][i]*toSub;
	      if(A[j][i]>=E && A[j][i]<=-E)
		A[i][j]=0;
	    }
	 
	}
    }


 
   for(int i=0;i<m;i++)
    {
      int k=0;
      for(int j=0;j<n+1;j++)
	if(A[i][j]!=0)
	  k=1;
      if(k==0)
	rank--;
      }
  return rank;
}



vector<vector<int> > comb(int N, int K)
{
  vector<vector<int> >res;
    string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // print integers and permute bitmask
    do {
      vector<int> temp;
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
	  if (bitmask[i]) temp.push_back( i);
        }
	res.push_back(temp);
       
    } while (prev_permutation(bitmask.begin(), bitmask.end()));
   
    return res;
}


vector<double> gauss(vector< vector<double> > A,vector<double> B) {
    int n = A.size();
    for(int i=0;i<n;i++)
      A[i].push_back(B[i]);
    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k=i; k<n+1;k++) {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            double c = -A[k][i]/A[i][i];
            for (int j=i; j<n+1; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    vector<double> x(n);
    for (int i=n-1; i>=0; i--) {
        x[i] = A[i][n]/A[i][i];
        for (int k=i-1;k>=0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}

vector<vector<double> > getBFS(vector<vector<double> >A,int m, int n,vector<vector<int> > AC)
{
  
  vector<vector<double> > result,allBFS;
   cout<<"All Basic solutions are:\n";
  for(vector<vector<int> >::iterator i=AC.begin();i!=AC.end();i++)
    {
       vector<double> B(m);
      vector<vector<double> > C(m,B);
     
      vector<double> finalRes(n);
      fill(finalRes.begin(),finalRes.end(),0);
      for(int j=0;j<m;j++)
	{
	  vector<double> temp;
	  for(int k=0;k<m;k++)
	    {
	      
	      //temp.push_back(A[k][(*i)[j]]);
	      C[k][j]=A[k][(*i)[j]];
	    }
	  // C.push_back(temp);
	  B[j]=(A[j][n]);
	  
	 }
      
     
      
      vector<double>res = gauss(C,B);
     
      vector<int>::iterator k=(*i).begin();
      int flag=0;
	for(vector<double>::iterator j=res.begin();j!=res.end();j++,k++)
	{
	 
	  finalRes[*k]=(*j);
	  if(finalRes[*k]<0)
	    flag=1;
	}
	
	printvec(finalRes);

      if(flag==0)
	allBFS.push_back(finalRes);
      
     
    }
 
  return allBFS;
}
	  
int main()
{
  int n,m,r;
  cout<<"Enter number of variables\n";
  cin>>n;
  cout<<"Enter number of equations\n";
  cin>>m;
  r=m;
  vector< vector<double> > A;
  vector<double> zmax,zmin;
  cout<<"Enter the equations\n";
  for(int i=0;i<m;i++)
    {
    vector<double> temp;
    for(int j=0;j<n+1;j++)
      {
	int x;
         cin>>x;
	 temp.push_back(x);
      }
    A.push_back(temp);
    }
  
  r = findRank(A,m,n);
  cout<<"\nRank="<<r<<endl;
  cout<<"Enter Zmax\n";
  for(int i=0;i<n;i++)
    {
      int temp;
      cin>>temp;
      zmax.push_back(temp);
    }
 cout<<"Enter Zmin\n";
 for(int i=0;i<n;i++)
    {
      int temp;
      cin>>temp;
      zmin.push_back(temp);
    }
  vector<vector<int> > allComb = comb(n,r);
  vector<vector<double> > allBFS = getBFS(A,r,n,allComb);
  cout<<"All Basic Feasible Solutions are:";
  printvector(allBFS);
  double max=0,min=INF;

  vector<double> maxat,minat;
  for(vector<vector<double> >::iterator i = allBFS.begin();i!=allBFS.end();i++)
    {
      double currmax=0,currmin=0;
      for(int j=0;j<n;j++)
	{
	  
	  currmax+=(*i)[j]*zmax[j];
	  currmin+=(*i)[j]*zmin[j];
	 
	}
     
      if(currmax>max)
	{
	  max=currmax;
	  maxat=*i;
	}
      if(currmin<min)
	{
	  min=currmin;
	  minat=*i;
	}
    }

  cout<<"Maximum = "<<max<<" at ";
  printvec(maxat);
  cout<<"Minimum = "<<min<<" at ";
  printvec(minat);
  return 0;
}
