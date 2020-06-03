#include <cstdio>
#include <cmath>
#include <cstring>

const int MAXN=25;
const double esp=1e-8;

struct point
{
  double x,y;
};

point up[MAXN],down[MAXN];
int n;

int ccw(point a,point b,point c)
{
  double tmp=(b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
  if (fabs(tmp)<=esp) return 0;
  else if (tmp<0) return -1;
  else return 1;
}

bool intersect1(point a1,point b1,point a2,point b2)
{
  int a=ccw(a1,b1,a2);
  int b=ccw(a1,b1,b2);
  return (a*b<=0);
}

bool intersect2(point a1,point b1,point a2,point b2)
{
  int a=ccw(a1,b1,a2);
  int b=ccw(a1,b1,b2);
  return (a*b<0);
}

double intersection(point a1,point b1,point a2,point b2)
{
  double A1,A2,B1,B2,C1,C2;
  A1=a1.y-b1.y; B1=b1.x-a1.x; C1=a1.x*A1+a1.y*B1;
  A2=a2.y-b2.y; B2=b2.x-a2.x; C2=a2.x*A2+a2.y*B2;
  return (C1*B2-B1*C2)/(A1*B2-A2*B1);
}

int main()
{
  while (scanf("%d",&n)&&n)
  {
    for (int i=0; i<n; i++)
    {
      scanf("%lf%lf",&up[i].x,&up[i].y);
      down[i]=up[i]; down[i].y-=1.0;
    }
    double ans=up[0].x;
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<n; j++)
        if (i!=j)
        {
          point a=up[i],b=down[j];
          if (!intersect1(a,b,up[0],down[0])) continue;
          int k;
          for (k=1; k<n; k++)
          {
            if (!intersect1(a,b,up[k],down[k]))
            {
              if (intersect2(a,b,up[k-1],up[k]))
              {
                double tmp=intersection(a,b,up[k-1],up[k]);
                if (tmp>ans) ans=tmp;
                break;
              }
              if (intersect2(a,b,down[k-1],down[k]))
              {
                double tmp=intersection(a,b,down[k-1],down[k]);
                if (tmp>ans) ans=tmp;
                break;
              }
              if (up[k-1].x>ans) ans=up[k-1].x;
              break;
            }
          }
          if (k==n) ans=1/esp;
        }
    }
    if (ans>=up[n-1].x) printf("Through all the pipe.\n");
    else printf("%.2f\n",ans);
  }
  return 0;
}
