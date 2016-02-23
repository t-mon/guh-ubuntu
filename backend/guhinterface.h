/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stuerz <stuerz.simon@gmail.com>               *
 *                                                                         *
 *  This file is part of guh-ubuntu.                                       *
 *                                                                         *
 *  guh-ubuntu is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  guh-ubuntu is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with guh-ubuntu. If not, see <http://www.gnu.org/licenses/>.     *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef GUHINTERFACE_H
#define GUHINTERFACE_H

#include <QObject>
#include <QWebSocket>

class GuhInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString url READ url NOTIFY urlChanged)

public:
    explicit GuhInterface(QObject *parent = 0);

    Q_INVOKABLE void connectGuh(const QString &urlString);
    Q_INVOKABLE void disconnect();

    void sendData(const QByteArray &data);
    void sendRequest(const QVariantMap &request);

    QString url() const;

    bool connected() const;

private:
    QWebSocket *m_socket;
    QString m_webSocketUrl;
    bool m_connected;

    void setConnected(const bool &connected);

signals:
    void urlChanged();
    void connectedChanged();
    void disconnected();
    void dataReady(const QVariantMap &data);
    void websocketError(const QString &errorString);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString &data);
    void onError(QAbstractSocket::SocketError error);
};

#endif // GUHINTERFACE_H
