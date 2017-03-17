#include <iostream>
#include <fstream>

using namespace std;

int used[100][2];   
int cs[100];     
int weightSum;


void toAdjacency(int adjacencyMatrix[][100], char *filename, int *nrOfVertices)     //building the adjacency matrix from a file which contains the vertices and the waights
{
    ifstream f(filename);
    f>>*nrOfVertices;
    for(int i=0;i<*nrOfVertices;++i)
    {
       for(int j=0;j<*nrOfVertices;++j)
       {
           adjacencyMatrix[i][j]=0;
       }
    }
    int x,y;
    for(int i=0;f>>x;++i)
    {
        f>>y;
        --x;
        --y;
        f>>adjacencyMatrix[x][y];
        adjacencyMatrix[y][x]=adjacencyMatrix[x][y];
    }
    for(int i=0;i<*nrOfVertices;++i)
    {
       for(int j=0;j<*nrOfVertices;++j)
       {
            if(adjacencyMatrix[i][j]==0 && i!=j)
            {
                adjacencyMatrix[i][j]=20000;
            }
       }
    }
}

void printAdj(int adjacencyMatrix[][100], int nrOfVertices)             //print the adjacency matrix for debugging reasons
{
    cout << "toAdjacency matrix:" << endl;
    for(int i=0;i<nrOfVertices;++i)
    {
       for(int j=0;j<nrOfVertices;++j)
       {
           cout.width(1);
           if(adjacencyMatrix[i][j]!=20000)
           cout << adjacencyMatrix[i][j] << " ";
           else cout << char(236) << " ";
       }
       cout << endl;
    }
}
bool free(int x)
{
    for(int i=0;cs[i]!=20000;++i)
    {
        if(x==cs[i])
        {
            return false;
        }
    }
    return true;
}
void minimum(int w,int adjacencyMatrix[][100], int nrOfVertices)
{

    int mi=20000;
    int j;
    for(j=0;cs[j]!=20000;++j)
    {
        for(int i=0;i<nrOfVertices;++i)
        {
            if(adjacencyMatrix[cs[j]][i] < mi && adjacencyMatrix[cs[j]][i]!=0 && free(i))
            {
                mi=adjacencyMatrix[cs[j]][i];
                used[w][0]=cs[j];
                used[w][1]=i;
            }
        }
    }
    cs[j]=used[w][1];
    cs[j+1]=20000;
    weightSum+=adjacencyMatrix[used[w][0]][used[w][1]];
    adjacencyMatrix[used[w][0]][used[w][1]]=20000;
    adjacencyMatrix[used[w][1]][used[w][0]]=20000;
}

void prim(int adjacencyMatrix[][100],int nrOfVertices)
{

    int m=20000;                        //max
    for(int i=0;i<nrOfVertices;++i)
    {
        for(int j=i+1;j<nrOfVertices;++j)
        {
            if(adjacencyMatrix[i][j]<m)
            {
                m=adjacencyMatrix[i][j];
                used[0][0]=i;
                used[0][1]=j;
                weightSum=adjacencyMatrix[i][j];
            }
        }
    }
    cs[0]=used[0][0];
    cs[1]=used[0][1];
    cs[2]=20000;
    adjacencyMatrix[used[0][0]][used[0][1]]=20000;
    adjacencyMatrix[used[0][1]][used[0][0]]=20000;

    for(int i=1;i<nrOfVertices-1;++i)
    {
        minimum(i,adjacencyMatrix, nrOfVertices);
    }
}
void printAnswer(int nrOfVertices)
{
    cout << "The minimum spanning tree: " << endl;
    for(int i=0;i<nrOfVertices-1;++i)
    {
        cout << used[i][0]+1 << " " << used[i][1]+1 << endl;
    }
    cout << "Sum of the weights of the minimum spanning tree:" << weightSum << endl;
}
int main(int argc, char *argv[])
{

    if ( argc != 2 ) // argc should be 2 for correct execution
    {
        cout<<"usage: "<< argv[0] <<" <filename>\n";
        return 0;
    }
    int adjacencyMatrix[100][100];
    int nrOfVertices;
    toAdjacency(adjacencyMatrix, argv[1], &nrOfVertices);
    prim(adjacencyMatrix, nrOfVertices);
    printAnswer(nrOfVertices);
    return 0;
}
