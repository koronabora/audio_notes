#pragma once

#include <QAbstractListModel>
#include <QUrl>
#include <memory>

class AudioNotesRepo;

typedef std::unique_ptr<AudioNotesRepo> AudioNotesRepoInctance;

class AudioNotesReposModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AudioNotesReposModel(QObject *parent = nullptr);
    ~AudioNotesReposModel();

    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addRepo(const QUrl &path);
    void addRepo(const QString &path);

private:
    QList<AudioNotesRepoInctance> m_items;

    void _addRepo(AudioNotesRepoInctance repo);
};

