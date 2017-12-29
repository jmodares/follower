#ifndef UBNETWORK_H
#define UBNETWORK_H

#include <QTcpSocket>

class UBNetwork : public QTcpSocket
{
    Q_OBJECT
public:
    explicit UBNetwork(QTcpSocket *parent = 0);

signals:
    void dataReady(quint8 srcID, QByteArray data);

public slots:
    void setID(quint8 id) {m_id = id;}
    void sendData(quint8 desID, QByteArray data);

protected slots:
    void dataReadyEvent();

private:
    quint8 m_id;
    QByteArray m_data;
};

#endif // UBNETWORK_H
