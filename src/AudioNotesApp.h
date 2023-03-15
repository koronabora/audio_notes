#pragma once

#include <QObject>
#include <QVector>
#include <QUrl>
#include <QPointer>

class AudioNotesReposModel;

class AudioNotesApp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AudioNotesReposModel* reposModel READ reposModel CONSTANT)
    Q_PROPERTY(bool emptyNotes READ emptyNotes CONSTANT)
public:
    explicit AudioNotesApp(QObject *parent = nullptr);

    bool isRepoListEmpty() const;

    void init();
    void save();

signals:
    void updateWindow();

public slots:
    void addAudioRepo(const QUrl &path);

private:
    QPointer<AudioNotesReposModel> m_reposModel;
    QList<QUrl> m_repos;

    QPointer<AudioNotesReposModel> _reposModel() const;
};

