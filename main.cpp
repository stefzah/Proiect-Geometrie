#include <iostream>
#include <vector>
#include <fstream>
#include <graphics.h>
#include <cmath>
#include <algorithm>

#define X 500
#define Y 500
#define delX 300
#define delY 300
using namespace std;
struct punct {
    double x, y;
};
vector<punct> v;
int N;
double mn;
int poz;
bool a[55];
punct aux;

double Delta(punct A, punct B, punct C) {
    return B.x * C.y + C.x * A.y + A.x * B.y - B.x * A.y - C.x * B.y - A.x * C.y;
}

bool InTriangle(punct A, punct B, punct C, punct D) {
    return (Delta(A, B, D) <= 0 && Delta(B, C, D) <= 0 && Delta(C, A, D) <= 0)
           || (Delta(A, B, D) >= 0 && Delta(B, C, D) >= 0 && Delta(C, A, D) >= 0);
}

bool Eliminare(int p1, int j, int p2, punct k) {
    bool ok = false;
    if (InTriangle(v[p1], v[j], v[p2], k) == 1)ok = true;
    if (ok)
        cout << "Punctul (" << aux.x << "," << aux.y << ") se afla in triunghiul descris de punctele (" << v[p1].x
             << "," << v[p1].y << "), ("
             << v[j].x << "," << v[j].y << ") si (" << v[p2].x << " " << v[p2].y << ")";
    for (int i = j; i < N - 1; i++) {
        v[i] = v[i + 1];
    }
    N--;
    return ok;
}

bool ok;

void FindMin() {
    for (int i = 0; i < N; i++) {
        if (mn < v[i].x) {
            mn = v[i].x;
            poz = i;
        } else if (mn == v[i].x && v[poz].y < v[i].y) poz = i;
    }
}

void SetStare() {
    for (int i = 0; i < N; i++) {
        int j = (i + poz) % N;
        int p1 = j - 1;
        if (p1 == -1) p1 = N - 1;
        int p2 = (j + 1) % N;
        a[j] = Delta(v[p1], v[j], v[p2]) > 0;
    }
    if (a[poz] == 0)
        for (int i = 0; i < N; i++)
            a[i] = !a[i];
}

int main() {
    ifstream fin("triangulare.in");
    ofstream fout("triangulare.out");

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");


    fin >> N;
    for (int i = 0; i < N; i++) {
        punct p;
        fin >> p.x >> p.y;
        v.push_back(p);
        if (i > 0)
            line(v[i - 1].x * 10 + delX, Y - (v[i - 1].y * 10 + delY), v[i].x * 10 + delX, Y - (v[i].y * 10 + delY));
    }
    line(v[N - 1].x * 10 + delX, Y - (v[N - 1].y * 10 + delY), v[0].x * 10 + delX, Y - (v[0].y * 10 + delY));
    getch();
    fin >> aux.x >> aux.y;
    for (int i = 0; i < N; i++) {
        int j = i % N;
        int p1 = j - 1;
        if (p1 == -1) p1 = N - 1;
        int p2 = (j + 1) % N;
        setcolor(RED);
        line(v[p1].x * 10 + delX, Y - (v[p1].y * 10 + delY), v[j].x * 10 + delX, Y - (v[j].y * 10 + delY));
        getch();
        if (Delta(v[p1], v[j], aux) == 0 && min(v[p1].x, v[j].x) <= aux.x && max(v[p1].x, v[j].x) >= aux.x &&
            min(v[p1].y, v[j].y) <= aux.y && max(v[p1].y, v[j].y) >= aux.y) {
            setcolor(GREEN);
            line(v[p1].x * 10 + delX, Y - (v[p1].y * 10 + delY), v[j].x * 10 + delX, Y - (v[j].y * 10 + delY));
            cout << "Punctul (" << aux.x << "," << aux.y << ") se afla pe segmentul descris de punctele (" << v[p1].x
                 << "," << v[p1].y << ") si ("
                 << v[j].x << "," << v[j].y << ")";
            getch();
            closegraph();
            return 0;
        }
    }
    //closegraph();
    //for (int i = 0; i < N; i++)
    //fout << a[i] << " ";

    while (ok == 0) {
        FindMin();
        SetStare();
        for (int i = 0; i < N; i++)
            fout << a[i] << " ";
        fout << "\n";
        for (int i = 0; i < N; i++) {
            int j = (i + poz) % N;
            int p1 = j - 1;
            if (p1 == -1) p1 = N - 1;
            int p2 = (j + 1) % N;
            if (a[j] == 1) {
                int points[] = {static_cast<int>(v[p1].x * 10 + delX),static_cast<int>(Y - (v[p1].y * 10 + delY)),static_cast<int>(v[j].x * 10 + delX),
                                static_cast<int>(Y - (v[j].y * 10 + delY)), static_cast<int>(v[p2].x * 10 + delX), static_cast<int>(Y - (v[p2].y * 10 + delY)),
                                static_cast<int>(v[p1].x * 10 + delX), static_cast<int>(Y - (v[p1].y * 10 + delY))};
                setfillstyle(XHATCH_FILL, RED);
                fillpoly(4,points);
                getch();
                bool okk = false;
                for (int k = 0; k < N; k++) {

                    if (k != j && k != p1 && k != p2) {
                        if (InTriangle(v[p1], v[j], v[p2], v[k]) == 1) {
                            cout << "\n";

                            okk = true;
                            break;
                        }
                    }
                }
                if (okk == 0 && Eliminare(p1, j, p2, aux) == 1) {
                    setfillstyle(XHATCH_FILL, GREEN);
                    fillpoly(4, points);
                    getch();
                    ok = true;
                    break;
                }
            }
        }
        if (N == 2) break;
    }
    if (ok == 0)cout << "Punctul de afla in afara triunghiului";
    closegraph();
}
