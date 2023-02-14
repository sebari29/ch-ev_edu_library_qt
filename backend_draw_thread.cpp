#include "backend_draw_thread.h"
#include "common.h"

pthread_mutex_t m_drawMutex;
pthread_cond_t m_drawCond;
int draw_pause;
int polgon_draw_idx;

Backend_Draw_Thread::Backend_Draw_Thread(QObject *parent) :
    QThread(parent)
{
    setTerminationEnabled(true);
    threadStop = false;
    drawRemove = 0;

    pthread_mutex_init(&m_drawMutex,NULL);
    pthread_cond_init(&m_drawCond,NULL);
}

Backend_Draw_Thread::~Backend_Draw_Thread()
{

}

void Backend_Draw_Thread::startDrawThread()
{
    if (!threadStop) {
        threadStop = true;
        start();
    }
}

void Backend_Draw_Thread::stopDrawThread()
{
    threadStop = false;
}

void Backend_Draw_Thread::run()
{
    while(1) {

        if (!threadStop) break;

        /*if (bStartAddPol == TRUE) {
            Sleep(1);
            continue;
        }*/
        //if (is_myDrawPolygon()) {
        if (polgon_draw_idx < polgon_saved_idx) {
            float x1, x2, y1, y2;
            int i, k;
                //TRACE("..len: (%d) %d", j, polygon_saved[j].len);
            for (i = 0; i < polygon_saved[polgon_draw_idx].len; i++) {
                if (polygon_saved[polgon_draw_idx].len == 2 && i > 0) break;
                k = (i < polygon_saved[polgon_draw_idx].len - 1) ? (i + 1) : (0);
                //TRACE("drawOutPoly...1: %d, %d, %d, %0.1f, %0.1f, %0.1f, %0.1f", j, i, k, polygon_saved[j].vert[i].x, polygon_saved[j].vert[i].y, polygon_saved[j].vert[j].x, polygon_saved[j].vert[j].y);
                x1 = polygon_saved[polgon_draw_idx].vert[i].x;
                y1 = polygon_saved[polgon_draw_idx].vert[i].y;
                y2 = polygon_saved[polgon_draw_idx].vert[k].y;
                x2 = polygon_saved[polgon_draw_idx].vert[k].x;
                //TRACE("drawOutPoly...2: %d, %d, %d, %0.1f, %02232.1f, %0.1f, %0.1f", j, i, k, x1, y1, x2, y2);
                msleep(1);
                if (i == 0) {
                    if (!drawRemove) {
                        drawRemove = 1;
                        emit threadSigDrawOutPoly(x1, y1, x2, y2, polygon_saved[polgon_draw_idx].color);
                    } else {
                        emit threadSigDrawOutOnePoly(x1, y1, x2, y2, polygon_saved[polgon_draw_idx].color);
                    }
                } else {
                    emit threadSigDrawOutOnePoly(x1, y1, x2, y2, polygon_saved[polgon_draw_idx].color);
                }
            }

            polgon_draw_idx++;
        } else {
            msleep(1);
            drawRemove = 0;
        }
    }
}
