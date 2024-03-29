#pragma once

#include <QObject>
#include <QPointer>

class QBuffer;
class QMediaPlayer;

class AudioNotePlayback : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qint64 postition READ postition WRITE position NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(bool active READ active NOTIFY activeChanged)

public:
    explicit AudioNotePlayback(QByteArray content = QByteArray(), QObject *parent = nullptr);

    qint64 postition() const;
    void position(qint64 newPostition);

    qint64 duration() const;

    const QByteArray & content()const;
    bool active() const;

public slots:
    void play();
    void stop();

signals:
    void positionChanged();
    void durationChanged();
    void activeChanged();

private:
    qint64 m_postition = 0;

    qint64 m_duration = 0;

    QByteArray m_content;
    QPointer<QMediaPlayer> player;
    QPointer<QBuffer> playbackBuffer;
};

