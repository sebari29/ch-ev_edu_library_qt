#ifndef BACKEND_DRAW_THREAD_H
#define BACKEND_DRAW_THREAD_H

#include <QThread>
#include <QWaitCondition>
#include <QMutex>

class Backend_Draw_Thread: public QThread
{
    Q_OBJECT

public:
    explicit Backend_Draw_Thread(QObject *parent = 0);
    ~Backend_Draw_Thread();

    QWaitCondition  m_waitCondition;
    QMutex m_mutex;

    void startDrawThread();
    void stopDrawThread();

    bool threadStop;
    int drawRemove;

private:
    void run();

signals:
    void threadSigDrawOutPoly(float x0, float y0, float x1, float y1, unsigned long color__, int wakeStatus);
    void threadSigDrawOutOnePoly(float x0, float y0, float x1, float y1, unsigned long color__, int wakeStatus);

public slots:

};

#endif // BACKEND_DRAW_THREAD_H
