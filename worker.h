#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject{
    Q_OBJECT
public:
    Worker(uint *, uint, uint, double);
    ~Worker();

    int getDelay(){ return m_nDelay; }

    void setDelay(int d){ m_nDelay = d; }

signals:
    void update(bool **);

public slots:
    void evolve();

private:
    bool rule(bool, uint);

    bool **m_Matrix;
    uint m_nRule[4];
    uint m_nWidth;
    uint m_nHeight;
    int m_nDelay;
};

#endif // WORKER_H
