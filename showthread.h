#ifndef SHOWTHREAD_H
#define SHOWTHREAD_H

#include <QThread>

class ShowThread : public QThread
{
    Q_OBJECT
private:
    void run();
public:
    explicit ShowThread(QObject *parent = nullptr);
    ~ShowThread();
    static void showYuv();
signals:

};

#endif // SHOWTHREAD_H
