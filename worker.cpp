#include "worker.h"

#include <QDebug>
#include <QThread>
#include <QTime>

#include <chrono>
#include <random>
using namespace std;

Worker::Worker(uint *r, uint w, uint h, uint t, Function f, double p){
    for(int i=0;i<4;i++)
        m_nRule[i] = r[i];
    m_nWidth = w;
    m_nHeight = h;
    m_nTao = t;
    m_Function = f;
    m_nDelay = 100;
    m_vMatrix.reserve(m_nTao);

    bool **a = new bool*[m_nHeight];
    for(uint i=0;i<m_nHeight;i++){
        a[i] = new bool[m_nWidth];
        memset(a[i], 0, m_nWidth);
    }
    m_vMatrix.append(a);

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
        while( m_vMatrix.at(0)[i][j] );
        m_vMatrix.at(0)[i][j] = true;
    }
}

Worker::~Worker(){
    qInfo() << "Worker destructor begin";
    for(uint t=0;t<m_nTao;t++){
        if( m_vMatrix.at(t) != NULL ){
            for(uint i=0;i<m_nHeight;i++)
                delete m_vMatrix.at(t)[i];
            delete m_vMatrix.at(t);
        }
    }
    m_vMatrix.clear();
    qInfo() << "Worker destructor end";
}

void Worker::evolve(){
    int suma;
    int di[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dj[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    bool **mat = new bool*[m_nHeight];
    for(uint i=0;i<m_nHeight;i++){
        mat[i] = new bool[m_nWidth];
        memset(mat[i], 0, m_nWidth);
    }

    QTime time;
    time.start();

    if( ((uint)m_vMatrix.size()) < m_nTao ){
        for(uint i=0;i<m_nHeight;i++){
            for(uint j=0;j<m_nWidth;j++){
                suma = 0;
                for(int k=0;k<8;k++)
                    suma += m_vMatrix.last()[(i+di[k]+m_nHeight)%m_nHeight][(j+dj[k]+m_nWidth)%m_nWidth];
                mat[i][j] = rule(m_vMatrix.last()[i][j], suma);
            }
        }

        m_vMatrix.append(mat);
    }
    else{
        bool **inter = new bool*[m_nHeight];
        for(uint i=0;i<m_nHeight;i++){
            inter[i] = new bool[m_nWidth];
            for(uint j=0;j<m_nWidth;j++)
                inter[i][j] = func(i, j);
        }

        for(uint i=0;i<m_nHeight;i++){
            for(uint j=0;j<m_nWidth;j++){
                suma = 0;
                for(int k=0;k<8;k++)
                    suma += inter[(i+di[k]+m_nHeight)%m_nHeight][(j+dj[k]+m_nWidth)%m_nWidth];
                mat[i][j] = rule(inter[i][j], suma);
            }
        }

        m_vMatrix.append(mat);
        m_vMatrix.pop_front();
    }

    if( time.elapsed() < m_nDelay )
        QThread::msleep(m_nDelay - time.elapsed());
    emit update(m_vMatrix.last());
}

bool Worker::rule(bool c, uint s){
    bool a = c && m_nRule[0] <= s && s <= m_nRule[1];
    bool b = !c && m_nRule[2] <= s && s <= m_nRule[3];

    return a || b;
}

bool Worker::func(uint i, uint j){
    uint zeros = 0;
    uint ones = 0;

    for(int t=0;t<m_vMatrix.size();t++){
        if( m_vMatrix.at(t)[i][j] )
            ones++;
        else
            zeros++;
    }

    switch(m_Function){
    case Function::MAX:
        if( ones == zeros )
            return m_vMatrix.last()[i][j];
        return ones > zeros;

    case Function::MIN:
        if( ones == zeros )
            return m_vMatrix.last()[i][j];
        return ones < zeros;

    case Function::PAR:
        return ones%2;

    default:
        return false;
    }
}
