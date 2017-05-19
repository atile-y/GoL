#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QVector>

enum Function{ MAX, MIN, PAR };

class Worker : public QObject{
    Q_OBJECT
public:
    Worker(uint *, uint, uint, uint, Function, double);
    ~Worker();

    int getDelay(){ return m_nDelay; }

    void setDelay(int d){ m_nDelay = d; }

signals:
    void update(bool **);

public slots:
    void evolve();

private:
    bool rule(bool, uint);
    bool func(uint, uint);

    QVector<bool **> m_vMatrix;
    uint m_nRule[4];
    uint m_nWidth;
    uint m_nHeight;
    uint m_nTao;
    Function m_Function;
    int m_nDelay;
};

#endif // WORKER_H
