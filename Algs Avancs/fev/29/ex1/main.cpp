#include <iostream>

using namespace std;

#define MAX_N 200000

int v[MAX_N];
bool b[MAX_N];
int n;
int aux;

//4 3 2 1 5
//0 0 0 0 0 0

bool isSortable() {
    bool somethingChanged = true;
    bool sortable = true;
    
    while (somethingChanged) {
        somethingChanged = false;
        for (int i = 1; i < n; i++)
        {
            if (v[i] < v[i-1]) {
                //Fora de ordem

                if (!b[i-1]) {
                    sortable = false;
                    goto fora;
                }
                else {
                    somethingChanged = true;
                    aux = v[i];
                    v[i] = v[i-1];
                    v[i-1] = aux;
                } 
            }
        }
    }
    fora:
    return sortable;        
}

int main(int argc, char const *argv[])
{
    cin >> n;
    char c;
    for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = 0; i < n-1; i++) { cin >> c; b[i] = c == '1'; }    
    
    cout << (isSortable()?"YES":"NO") << endl;
    
    return 0;
}
