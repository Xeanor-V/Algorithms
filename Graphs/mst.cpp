#include <bits/stdc++.h>
using namespace std;



typedef int Costo;
typedef pair<int, int> Arista;
typedef pair<Costo, int> CostoNodo;
typedef pair<Costo, Arista> Ponderada;

typedef pair< pair<int,int> , int> estado;


const Costo INF = 1 << 30;
// Conjuntos disjuntos con Union-Find.
struct UnionFind {

    int n; vector<int> padre, tam;

    UnionFind(int N) : n(N),
        tam(N, 1), padre(N) {
        while (--N) padre[N] = N;
    }

    int Raiz(int u) {
        if (padre[u] == u) return u;
        return padre[u] = Raiz(padre[u]);
    }

    bool SonConexos(int u, int v) {
        return Raiz(u) == Raiz(v);
    }

    void Unir(int u, int v) {
        int Ru = Raiz(u);
        int Rv = Raiz(v);
        if (Ru == Rv) return;
        --n, padre[Ru] = Rv;
        tam[Rv] += tam[Ru];
    }

    int Tamano(int u) {
        return tam[Raiz(u)];
    }
};


struct GrafoPonderado {

    int n; bool bi;
    vector<vector<CostoNodo>> ady;
    GrafoPonderado(int N, bool B = true)
        : n(N), bi(B), ady(N) {}

    void AgregarArista(int u, int v, Costo c) {
        if (bi) ady[v].push_back(CostoNodo(c, u));
        ady[u].push_back(CostoNodo(c, v));
    }

    // Obtiene el arbol de expansion minima de un
    // grafo bidireccional. Para obtener el arbol
    // de expansion maxima descomentar el reverse.
    // En caso de tener varias componentes conexas,
    // obtiene el bosque de expansion minima.

    pair<int,vector<pair<int,int> > > Kruskal() {
    	int res = 0;
        vector<Ponderada> todas;
        for (int u = 0; u < n; ++u)
            for (CostoNodo arista : ady[u])
                todas.push_back(
                    Ponderada(arista.first,
                    Arista(u, arista.second)));
        sort(todas.begin(), todas.end());
        // reverse(todas.begin(), todas.end());

        vector<pair<int,int> > mst;
        UnionFind componentes(n);
        for (Ponderada arista : todas) {
            int u = arista.second.first;
            int v = arista.second.second;
            if (!componentes.SonConexos(u, v))
                componentes.Unir(u, v),
                mst.push_back(make_pair(u,v)),
                res += arista.first;
        }
        return make_pair(res,mst);
    }
};

int main()
{
    int n,m;
    while(cin>>n>>m)
    {
        if(n == 0 && m == 0) break;
        GrafoPonderado grafo(n);
        for(int i = 0 ; i < m; i++)
        {
            int a,b,c;
            cin>>a>>b>>c;
            grafo.AgregarArista(a,b,c);
        }
        auto res = grafo.Kruskal();
        if(res.second.size() == 0)
        {
            cout<<"Impossible\n";
            continue;
        }
        cout<<res.first<<'\n';
        auto mst = res.second;
        sort(mst.begin(),mst.end());
        for(int i = 0; i < mst.size(); i++)
        {
            cout<<mst[i].first<<' '<<mst[i].second<<'\n';
        }
    }
}