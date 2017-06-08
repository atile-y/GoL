#ifndef GLWIDGET_H
#define GLWIDGET_H

#define STOP    1
#define PAUSE   2
#define PLAY    3

#include "worker.h"

#include <QOpenGLWidget>
#include <QThread>

class GLWidget : public QOpenGLWidget {
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QString getRule(){ return m_strRule; }
    uint *getRulev(){ return m_nRule; }
    uint getWidth(){ return m_nWidth; }
    uint getHeight(){ return m_nHeight; }
    uint getTao(){ return m_nTao; }
    Function getFunction(){ return m_Function; }
    double getPercent(){ return m_nPercent; }

    void setRule(QString);
    void setRule(uint, uint, uint, uint);
    void setWidth(uint w){ m_nWidth = w; }
    void setHeight(uint h){ m_nHeight = h; }
    void setTao(uint t){ m_nTao = t; }
    void setFunction(Function f){ m_Function = f; }
    void setPercent(double p){ m_nPercent = p; }

    void play();
    void pause();
    void reset();
    void setDelay(int);
    int getDelay();

public slots:
    void Idle();
    void updateMatrix(bool **);

signals:
    void evolve();

protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    //void wheelEvent(QWheelEvent *);

private:
    QString m_strRule; // B<a><b>/S<c><d>
    uint m_nRule[4]; // [c, d, a, b]
    uint m_nWidth;
    uint m_nHeight;
    uint m_nTao;
    Function m_Function;
    double m_nPercent;
    bool **m_Matrix;

    ushort m_nState;
    bool m_bFirstDisplay;
    GLdouble m_nLeft, m_nRight, m_nBot, m_nTop;
    int m_nClick;
    Worker *m_Work;
    QThread *m_Thread;
};

#endif // GLWIDGET_H
