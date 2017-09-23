#include <bits/stdc++.h>
using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matrix;


// Para eliminacion con flotantes.

const double ERROR = 1e-9;

bool EsCero(double a) {
    return fabs(a) < ERROR;
}

// En caso de no permitir el pivoteo (eg. cuando
// requieran sacar una matriz inversa) simplemente
// comenten o borren la seccion <comment>.

vector<Vector> EliminacionGaussiana(Matrix m) {
    for (int i = 0; i < m.size(); ++i) {
    	/*/ <comment>
        int fila_mayor = i;
        for (int j = i + 1; j < m.size(); ++j)
            if (fabs(m[fila_mayor][i]) <
                fabs(m[j][i])) fila_mayor = j;
        swap(m[i], m[fila_mayor]);
        / </comment>*/

        if (EsCero(m[i][i])) continue;
        for (int j = m[i].size() - 1; j >= i; --j)
            m[i][j] = m[i][j] / m[i][i];
        for (int j = 0; j < m.size(); ++j) {
            if (i == j || EsCero(m[j][i])) continue;
            for (int k = m[j].size() - 1; k >= i; --k)
                m[j][k] = m[j][k] - m[i][k] * m[j][i];
        }
    }
    return m;
}

void print_matrix(Matrix m)
{
    for(int i = 0; i < m.size(); i++)
    {
        for(int j = 0 ; j < m[i].size(); j++)
        {
            if(j) cout<<' ';
            cout<<m[i][j];
        }
        cout<<'\n';
    }
    return;
}

int main()
{
    int n;

    cin>>n;
    Matrix m(n);
    for(int i = 0 ; i < n; i++)
        for(int j = 0 ; j < n; j++)
        {
            double x;
            cin>>x;
            m[i].push_back(x);
        }
    
    for(int i = 0; i < n; i++)
    {
        double x;
        cin>>x;
        m[i].push_back(x);
    }
    
    Matrix ME = EliminacionGaussiana(m);
    print_matrix(ME);
    
   map<int,int> res;
    int cas = 0;
    vector < vector<int> > values;
    for(int i = 0 ; i < ME.size(); i++)
    {
        for(int j = 0; j < ME[i]; i++)
        {
            if(ME[i][j] != 0) values[j].push_back(ME[i][j]);
        }
    }

    for(int i = 0; i < n ;i++)
    {
        for(int j = 0; j < n; j++)
        {
            
        }
    }

    
    


}