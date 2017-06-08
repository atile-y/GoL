#include "worker.h"

#include <QDebug>
#include <QThread>
#include <QTime>

#include <chrono>
#include <random>
using namespace std;

Worker::Worker(uint *r, uint w, uint h, double p){
    for(int i=0;i<4;i++)
        m_nRule[i] = r[i];
    m_nWidth = w;
    m_nHeight = h;
    m_nDelay = 100;
    m_Matrix = new bool*[m_nHeight];
    for(uint i=0;i<m_nHeight;i++){
        m_Matrix[i] = new bool[m_nWidth];
        memset(m_Matrix[i], 0, m_nWidth);
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<uint> distJ(0, m_nWidth-1);
    uniform_int_distribution<uint> distI(0, m_nHeight-1);
    uniform_real_distribution<double> d(0.0, 1.0);

    double numCells = p * m_nWidth * m_nHeight / 100.0;
    uint m = (uint)numCells, i, j;
    if( d(generator) < numCells - m )
        m++;

    for(uint k=0;k<m;k++){
        do{
            i = distI(generator);
            j = distJ(generator);
        }
        while( m_Matrix[i][j] );
        m_Matrix[i][j] = true;
    }
}

Worker::~Worker(){
    qInfo() << "Worker destructor begin";
    for(uint i=0;i<m_nHeight;i++)
        delete m_Matrix[i];
    delete m_Matrix;
    qInfo() << "Worker destructor end";
}

void Worker::setCell(uint i, uint j, bool v){
    if( i >= m_nHeight || j >= m_nWidth )
        return;

    m_Matrix[i][j] = v;
}

void Worker::evolve(){
    int suma;
    int di[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dj[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    bool mat[m_nHeight][m_nWidth];

    QTime time;
    time.start();

    for(uint i=0;i<m_nHeight;i++)
        for(uint j=0;j<m_nWidth;j++)
            mat[i][j] = m_Matrix[i][j];

    for(uint i=0;i<m_nHeight;i++){
        for(uint j=0;j<m_nWidth;j++){
            suma = 0;
            for(int k=0;k<8;k++)
                suma += mat[(i+di[k]+m_nHeight)%m_nHeight][(j+dj[k]+m_nWidth)%m_nWidth];
            m_Matrix[i][j] = rule(mat[i][j], suma);
        }
    }

    if( time.elapsed() < m_nDelay )
        QThread::msleep(m_nDelay - time.elapsed());
    emit update(m_Matrix);
}

bool Worker::rule(bool c, uint s){
    bool a = c && m_nRule[0] <= s && s <= m_nRule[1];
    bool b = !c && m_nRule[2] <= s && s <= m_nRule[3];

    return a || b;
}
