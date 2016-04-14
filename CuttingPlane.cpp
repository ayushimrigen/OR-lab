#include <iostream>
#include <vector>
#include <iomanip>
#define Ep 0.00001
#define INF 100000
#define M 100000
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
  int mm=m;
  for(int i=0;i<hor.size();i++)
    if(hor[i]<-99)
      mm--;
   for(int i=0;i<ver.size();i++)
    if(ver[i]<-99)
      mm--;
  for(int i=-1;i<m;i++)
    {
      if(i== -1)
	cout<<setw(14)<<' ';
      else if(i==m-1)
	cout<<setw(14)<<'z';
      else
	if(ver[i]<-99)
		cout<<setw(14)<<"s"<<(-ver[i])/100 -mm +1;
  	else if(ver[i]<0)
	  cout<<setw(14)<<'x'<<mm-ver[i];
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
	      else if(hor[j]<-90)
		cout<<setw(14)<<"s"<<(-hor[j])/100 -mm +1;
	      else if(hor[j]<0)
		cout<<setw(14)<<"x"<<(mm-hor[j]);
	      else
		cout<<setw(14)<<"x"<<hor[j];
	    }
	  else 
	    cout<<setw(15)<<A[i][j];
	}
        
      cout<<endl;
    
      
    }
}

void dualsimplex(vector<vector<double> > A,vector<int> hor, vector<int> ver,int last=0)
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
	cout<<"\n--------------------------------------------------------------------------\nMaximum = "<<A[m-1][n-1]<<endl;
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

      cout<<"  x =";
      printvec(x);


      cout<<"\nSlack variables = ";
      printvec(z);
      cout<<endl;
     
     int Flag = 0;
      for(int i=0;i<x.size();i++)
	if(x[i] - (int)x[i] != 0)
	  Flag = 1;
     
      if(Flag ==1)
	{
	  double max = 0;
	  int maxFracRow = -1;
	  for(int i=0;i<m;i++)
	    if(A[i][n-1]-(int)A[i][n-1]>max)
	      {
		max= A[i][n-1] -(int)A[i][n-1];
		maxFracRow=i;
	      }
	  vector<double> temp;
	  for(int i=0;i<n;i++)
	    temp.push_back(-(A[maxFracRow][i] - (int)A[maxFracRow][i]));
	  A.insert(A.end()-1,temp);
	  ver.push_back(-(m*100));
	
      cout<<"Max is at"<<maxFracRow<<endl;
      // char ch;
       printTable(A,hor,ver);
       //cin>>ch;
      // 
      // printvec(hor);
      // printvec(ver);
      dualsimplex(A,hor,ver);
	}
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
      if(A[minNegPos][i]<0 && r<minRatio)
	{
	  minRatio = r;
	  minRatioPos = i;
	}
    }

  int temp = ver[minNegPos];
  ver[minNegPos]=hor[minRatioPos];
  hor[minRatioPos]=temp;

  double Mn =A[minNegPos][minRatioPos];
  if(flag!=-1)
    cout<<"--------------------------------------------------------------------------\nPivot ="<<Mn <<" At position ("<<minNegPos<<","<<minRatioPos<<")\n";
 
  vector<vector<double> > res=A;

  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      {
	if(j==minRatioPos && i==minNegPos)
	  res[i][j]=1/Mn;
	else if (j==minRatioPos)
	  res[i][j]=-A[i][j]/Mn;
	else if(i==minNegPos)
	  res[i][j]=A[i][j]/Mn;
	else
	  res[i][j]= (A[i][j]*Mn -A[i][minRatioPos]*A[minNegPos][j])/Mn;
      }
  if(flag!=-1)
    printTable(res,hor,ver);
  //char ch;
  //cin>>ch;
  if(flag==-1)
    dualsimplex(res,hor,ver,1);
  else
    dualsimplex(res,hor,ver);
}




void simplex(vector<vector<double> > A,vector<int> hor, vector<int> ver,int nvar, vector<double> Z,vector<char>sign,int last=0)
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
      return;
    
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
      for(int i=0;i<m-1;i++)
	{
	  if(sign[i]!='<' && z[i]!=0)
	    {
	      cout<<"THE PROBLEM IS INFEASIBLE\n";
	      return;
	    }
	}
      cout<<"  X =";
      vector<double> xOr;
  	for(int i=0;i<nvar;i++)
	  {
	    xOr.push_back(x[i]);
	    if(x[i]==0)
	      flag=-1;
	  }
	    printvec(xOr);
       cout<<"\nSlack and Artificial variables = ";
       printvec(z);
      cout<<endl;
      double sum=0;
      for(int i=0;i<nvar;i++)
    	sum+=xOr[i]*Z[i];
 
     for(int i=0;i<nvar;i++)
    	sum+=x[i]*Z[i];
  	 int Flag = 0;
      for(int i=0;i<x.size();i++)
	if(x[i] - (int)x[i] != 0)
	  Flag = 1;
     
      if(Flag ==1)
	{
	  double max = 0;
	  int maxFracRow = -1;
	  for(int i=0;i<m;i++)
	    if(A[i][n-1]-(int)A[i][n-1]>max)
	      {
		max= A[i][n-1] -(int)A[i][n-1];
		maxFracRow=i;
	      }
	  vector<double> temp;
	  for(int i=0;i<n;i++)
	    temp.push_back(-(A[maxFracRow][i] - (int)A[maxFracRow][i]));
	  A.insert(A.end()-1,temp);
	  ver.push_back(-(hor.size()*100));
	
      printTable(A,hor,ver);
      printvec(hor);
      printvec(ver);
      char ch;
      cin>>ch;
      dualsimplex(A,hor,ver);
	}
       if(flag!=-1 || last==1)
 	 
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

  double Mn =A[minRatioPos][minNegPos];
  if(flag!=-1)
    cout<<"--------------------------------------------------------------------------\nPivot ="<<Mn <<" At position ("<<minRatioPos<<","<<minNegPos<<")\n";
 
  vector<vector<double> > res=A;

  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      {
	if(i==minRatioPos && j==minNegPos)
	  res[i][j]=1/Mn;
	else if (i==minRatioPos)
	  res[i][j]=A[i][j]/Mn;
	else if(j==minNegPos)
	  res[i][j]=-A[i][j]/Mn;
	else
	  res[i][j]= (A[i][j]*Mn -A[minRatioPos][j]*A[i][minNegPos])/Mn;
      }

 
  if(flag!=-1)
    printTable(res,hor,ver);
 
  if(flag==-1)
    simplex(res,hor,ver,nvar,Z,sign,1);
  else
    simplex(res,hor,ver,nvar,Z,sign);
}


int main()
{
  int n,m,r,maxOrMin;
  vector<char> sign;
  cout<<"Enter number of variables\n";
  cin>>n;
  cout<<"Enter number of equations\n";
  cin>>m;
  r=m;
  vector< vector<double> > A,table;
  vector<int> MTable(n+1);
  vector<double> z;
  vector<int> hor,ver;
  cout<<"Enter the equations\n";
  for(int i=0;i<m;i++)
	{
  	ver.push_back(-(i+1));
	vector<double> temp;
	for(int j=0;j<n+1;j++)
  	{
        	int x;
     	cin>>x;
     temp.push_back(x);
  	}
	A.push_back(temp);
	char ch;
	cin>>ch;
	sign.push_back(ch);
	}
  for(int i=0;i<m;i++)
	if(A[i][n]<0)
  	{
    cout<<"No solution by this method\n"<<A[i][n-1];
    return 0;
  	}
  table=A;
  cout<<"Press - for min and + for max\n";
  char choice;
  cin>>choice;
  cout<<"Enter Z\n ";
  for(int i=0;i<=n;i++)
	{
  	hor.push_back((i+1));
  	double temp;
  	cin>>temp;
  	if(choice=='+')
    {
  	if(i==n)
	  z.push_back(temp);
  	else
	  z.push_back(-temp);
    }
  	else
    {
      if(i==n)
    	z.push_back(-temp);
      else
    	z.push_back(temp);
    }
	}
  int nvar = n;
 

  for(int i=0;i<m;i++)
       
    if(sign[i]=='>')
      {
  
   	hor.push_back(hor.size()+1);
   	n++;
	for(int j=0;j<m;j++)
	  if(i==j)
	    table[j].insert(table[j].end()-1,-1);
	  else
	    table[j].insert(table[j].end()-1,0);
      }
  vector<double> tmp(n+1);
  table.push_back(tmp);
  //cout<<"n="<<n<<endl;
  for(int j=0;j<n;j++)
    {
      table[m][j]=0;
      for(int i=0;i<m;i++)
	{
	  if(sign[i]=='>')
	    table[m][j]-= M*table[i][j];
	}
      table[m][j]-=z[j];
    }
  table[m][n]=z[nvar];
printvector(table);


  printTable(table,hor,ver);
  simplex(table,hor,ver,nvar,z,sign);
}
/*
2
2
2 -1 5
2 3 13
18 12 0
*/
