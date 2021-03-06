#include "glwidget.h"

#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <GL/glu.h>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent){
    setWindowFlags(Qt::Window);
    setWindowTitle(tr("Universo"));
    setMinimumWidth(400);
    setMinimumHeight(400);
    resize(600, 600);
    move(500, 25);

    m_nState = STOP;
    m_Work = NULL;
    m_Thread = new QThread;
    m_Thread->start();
    m_bFirstDisplay = false;
    m_nClick = -1;
    m_Matrix = NULL;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Idle()));
    timer->start(20);
}

GLWidget::~GLWidget(){
    qInfo() << "GLWidget Destructor begin";
    while( !children().isEmpty() )
        delete children()[0];

    if( m_Matrix != NULL ){
        for(uint i=0;i<m_nHeight;i++){
            if( m_Matrix[i] != NULL ){
                delete m_Matrix[i];
            }
        }
        delete m_Matrix;
    }

    if( m_Thread != NULL ){
        m_Thread->terminate();
        if( !m_Thread->wait(1000) )
            qInfo() << "Timeout";
        delete m_Thread;
        m_Thread = NULL;
        if( m_Work != NULL ){
            delete m_Work;
            m_Work = NULL;
        }
    }
    qInfo() << "GLWidget Destructor end";
}

void GLWidget::setRule(QString r){
    std::string str = r.toStdString();

    uint a = str[1] - '0';
    uint b = a;
    if( str[2] >= '0' && str[2] <= '9' )
        b = str[2] - '0';

    int l = str.length();
    uint d = str[l-1] - '0';
    uint c = d;
    if( str[l-2] >= '0' && str[l-2] <= '9' )
        c = str[l-2] - '0';

    if( a > 8 || b > 8 || c > 8 || d > 8 )
        return;
    if( a > b || c > d )
        return;

    m_strRule = r;

    m_nRule[0] = c;
    m_nRule[1] = d;
    m_nRule[2] = a;
    m_nRule[3] = b;
}

void GLWidget::setRule(uint c, uint d, uint a, uint b){
    if( a > 8 || b > 8 || c > 8 || d > 8 )
        return;
    if( a > b || c > d )
        return;

    m_nRule[0] = c;
    m_nRule[1] = d;
    m_nRule[2] = a;
    m_nRule[3] = b;

    m_strRule = "B" + QString::number(a);
    if( a != b )
        m_strRule += QString::number(b);
    m_strRule += "/S" + QString::number(c);
    if( c != d )
        m_strRule += QString::number(d);
}

void GLWidget::play(){
    if( m_nState == STOP ){
        reset();
        m_bFirstDisplay = true;

        if( m_Work != NULL )
            delete m_Work;

        m_Work = new Worker(m_nRule, m_nWidth, m_nHeight, m_nPercent);
        m_Work->moveToThread(m_Thread);

        connect(this, SIGNAL(evolve()), m_Work, SLOT(evolve()));
        connect(m_Work, SIGNAL(update(bool**)), this, SLOT(updateMatrix(bool**)));

        m_Matrix = new bool*[m_nHeight];
        for(uint i=0;i<m_nHeight;i++){
            m_Matrix[i] = new bool[m_nWidth];
            memset(m_Matrix[i], 0, m_nWidth);
        }
    }

    emit evolve();
    m_nState = PLAY;
    update();
}

void GLWidget::pause(){
    m_nState = PAUSE;
}

void GLWidget::reset(){
    m_nState = STOP;
}

void GLWidget::setDelay(int v){
    if( m_nState == PLAY )
        m_Work->setDelay(v);
}

int GLWidget::getDelay(){
    if( m_nState == PLAY )
        return m_Work->getDelay();
    return -1;
}

void GLWidget::Idle(){
    update();
}

void GLWidget::updateMatrix(bool **matrix){
    for(uint i=0;i<m_nHeight;i++)
        for(uint j=0;j<m_nWidth;j++)
            m_Matrix[i][j] = matrix[i][j];

    update();
    if( m_nState == PLAY )
        emit evolve();
    else if( m_nState == STOP ){
        if( m_Work != NULL ){
            delete m_Work;
            m_Work = NULL;
        }
    }
}

void GLWidget::initializeGL(){
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.0f, 0.4f, 0.8f, 1.0f);
}

void GLWidget::resizeGL(int w, int h){
    double hp = w*m_nHeight / ((double)m_nWidth);

    if( hp <= h ){
        m_nLeft = 0.0;
        m_nRight = m_nWidth;
        m_nBot = -h*((double)m_nWidth) / w;
        m_nTop = (m_nBot + m_nHeight) / -2.0;
        m_nBot += m_nTop;
    }
    else{
        m_nRight = w*m_nHeight / ((double)h);
        m_nLeft = (m_nRight - m_nWidth) / -2.0;
        m_nRight += m_nLeft;
        m_nBot = -((double)m_nHeight);
        m_nTop = 0.0;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(m_nLeft, m_nRight, m_nBot, m_nTop);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt((m_nRight+m_nLeft)/2, (m_nTop+m_nBot)/2, 10, (m_nRight+m_nLeft)/2, (m_nTop+m_nBot)/2, 0, 0, 1, 0);
}

void GLWidget::paintGL(){
    if( m_bFirstDisplay ){
        int w = this->width(), h = this->height();
        double hp = w*m_nHeight / ((double)m_nWidth);

        if( hp <= h ){
            m_nLeft = 0.0;
            m_nRight = m_nWidth;
            m_nBot = -h*((double)m_nWidth) / w;
            m_nTop = (m_nBot + m_nHeight) / -2.0;
            m_nBot += m_nTop;
        }
        else{
            m_nRight = w*m_nHeight / ((double)h);
            m_nLeft = (m_nRight - m_nWidth) / -2.0;
            m_nRight += m_nLeft;
            m_nBot = -((double)m_nHeight);
            m_nTop = 0.0;
        }

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(m_nLeft, m_nRight, m_nBot, m_nTop);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt((m_nRight+m_nLeft)/2, (m_nTop+m_nBot)/2, 10, (m_nRight+m_nLeft)/2, (m_nTop+m_nBot)/2, 0, 0, 1, 0);
        m_bFirstDisplay = false;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f);

    if( m_Matrix != NULL ){
        for(uint i=0;i<m_nHeight;i++)
            for(uint j=0;j<m_nWidth;j++){
                if( m_Matrix[i][j] )
                    glColor3f(0.0f, 0.0f, 0.0f);
                else
                    glColor3f(1.0f, 1.0f, 1.0f);
                glBegin(GL_TRIANGLE_STRIP);
                    glVertex2i(j, -i-1);
                    glVertex2i(j, -i);
                    glVertex2i(j+1, -i-1);
                    glVertex2i(j+1, -i);
                glEnd();
            }
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
    if( m_nClick == -1 )
        return;

    QPointF p = event->windowPos();
    QPointF q(p.x()*(m_nRight-m_nLeft)/width() + m_nLeft, p.y()*(m_nTop-m_nBot)/height() - m_nTop);
    if( q.x() < 0 || q.y() < 0 || q.x() >= (int)m_nWidth || q.y() >= (int)m_nHeight )
        return;

    int i = q.y(), j = q.x();
    m_Matrix[i][j] = m_nClick;
    m_Work->setCell(i, j, m_nClick);
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    if( event->button() != Qt::LeftButton )
        return;

    QPointF p = event->windowPos();
    QPointF q(p.x()*(m_nRight-m_nLeft)/width() + m_nLeft, p.y()*(m_nTop-m_nBot)/height() - m_nTop);
    if( q.x() < 0 || q.y() < 0 || q.x() >= (int)m_nWidth || q.y() >= (int)m_nHeight )
        return;

    int i = q.y(), j = q.x();
    m_nClick = m_Matrix[i][j]?0:1;
    m_Matrix[i][j] = m_nClick;
    m_Work->setCell(i, j, m_nClick);
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event){
    if( event->button() != Qt::LeftButton )
        return;

    m_nClick = -1;
}
