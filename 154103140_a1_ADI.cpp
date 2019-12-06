#include <iostream>

#include <math.h>
#include <time.h>
#include <fstream>
using namespace std;

int main()
{
    int n,m,i,j,iter=0;
    double t0[100][100],t1[100][100],t2[100][100],t3[100][100],t4[100][100], error, dx,dy, beta, A[100],C[100],x,y;
    double a[100], b[100], c[100] , d[100], p[100], q[100];

    cout<<" enter n(x axis) and m(y axis) values \n";
    cin>>n>>m;

    double l=1, t=1;
    dx=l/(n-1);
    dy=t/(m-1);
    beta=dx/dy;

    for(i=0; i<n; i++){
        t0[i][0]=1;
        t0[i][m-1]=0;
        t1[i][0]=1;
        t1[i][m-1]=0;}
    for (j=0; j<m; j++){
         t0[0][j]=1;
        t0[n-1][j]=1;
        t1[0][j]=1;
        t1[n-1][j]=1;}
    for(i=1; i<n-1; i++){
        for(j=1; j<m-1; j++){
            t0[i][j]=0;
            t1[i][j]=0;}}
    clock_t begin, end;
    double cpu_time_used;
    begin = clock();

do{ double s=0;
    for(j=1; j<m-1; j++){
        for(i=1; i<n-1; i++){
            a[0]=1;
            b[0]=0;
            c[0]=0;
            d[0]=t0[0][j];
            a[i]=-4;
            b[i]=-1;
            c[i]=-1;
            d[i]=-(t0[i][j-1] + t0[i][j+1]);
            p[0]=b[0]/a[0];
            q[0]=d[0]/a[0];
            p[i]=b[i]/(a[i]-c[i]*p[i-1]);
            q[i]=(d[i]+c[i]*q[i-1])/(a[i]-c[i]*p[i-1]);
}
	for(i=n-2; i>0; i--){
		t3[i][j]=p[i]*t0[i+1][j] + q[i];
		t2[i][j]=t0[i][j];
		t0[i][j]=t3[i][j];
		//s=s+ pow((t1[i][j]-t2[i][j]), 2);
    }

    }
    for(i=1; i<n-1; i++){
        for(j=1; j<m-1; j++){
            a[0]=1;
            b[0]=0;
            c[0]=0;
            d[0]=t1[i][0];
            a[j]=-4;
            b[j]=-1;
            c[j]=-1;
            d[j]=-(t0[i-1][j] + t0[i+1][j]);
            p[0]=b[0]/a[0];
            q[0]=d[0]/a[0];
            p[j]=b[j]/(a[j]-c[j]*p[j-1]);
            q[j]=(d[j]+c[j]*q[j-1])/(a[j]-c[j]*p[j-1]);
}
	for(j=m-2; j>0; j--){
		t1[i][j]=p[j]*t0[i][j+1] + q[j];
		t3[i][j]=t0[i][j];
		t0[i][j]=t1[i][j];
		//s=s+ pow((t1[i][j]-t2[i][j]), 2);
    }

    }
    for(i=1; i<n-1; i++){
        for(j=1; j<m-1; j++){
            s=s+ pow((t1[i][j]-t2[i][j]), 2);
        }
    }
    error= sqrt(s/((m-2)*(n-2))) ;
           	iter++;
           	cout<<" error ="<<error;
} while(error >0.000001);
cout<<" no of iteration ="<<iter;

 ofstream thefile("cfd.txt");

  for(x=0,i=0; i<=n-1; x=x+dx,i++){
    for (y=0,j=0; j<=m-1; y=y+dy,j++){
        thefile<<x<<"\t"<<y<<"\t"<<t0[i][j]<<"\n";
    }
  }

end = clock();
cpu_time_used = ((double) (end - begin))/ CLOCKS_PER_SEC;
cout<<" \n"<<cpu_time_used;
    return 0;
}


