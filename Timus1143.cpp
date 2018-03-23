#include <stdio.h>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <vector>

const int maxn = 200;

struct point { double x, y; } in[maxn];
double L[maxn][maxn], R[maxn][maxn];

double dist(const point& a, const point& b)
{
    return std::sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        L[0][i] = R[0][i] = 0;
        scanf("%lf %lf", &in[i].x, &in[i].y);
    }
    for(int l = 1; l < n; l++)
    {
        for(int i = 0; i < n; i++)
        {
            R[i][l] = std::min(R[i][l-1]+dist(in[(i+l)%n], in[(i+l-1)%n]), 
                               L[i][l-1]+dist(in[i], in[(i+l)%n]));
            L[i][l] = std::min(L[(i+1)%n][l-1]+dist(in[i], in[(i+1)%n]),
                               R[(i+1)%n][l-1]+dist(in[i], in[(i+l)%n]));
        }
    }
    double ans = std::numeric_limits<double>::infinity();
    for(int i = 0; i < n; i++)
        ans = std::min( { ans, L[i][n-1], R[i][n-1] } );
    printf("%.3lf\n", ans);
}
