#include "AudioNotesReposModel.h"
#include "AudioNotesRepo.h"
#include <QUrl>
#include <QDebug>

AudioNotesReposModel::AudioNotesReposModel(QObject* parent)
    : QAbstractListModel{ parent }
{
}

AudioNotesReposModel::~AudioNotesReposModel()
{
    m_items.clear();
}

int AudioNotesReposModel::rowCount(const QModelIndex&) const
{
    return m_items.size();
}

QVariant AudioNotesReposModel::data(const QModelIndex& index, int) const
{
    return QVariant::fromValue(m_items.at(index.row())->name());
}

QHash<int, QByteArray> AudioNotesReposModel::roleNames() const
{
    static QHash<int, QByteArray> sNames = { { 1, "repo" } };
    return sNames;
}

void AudioNotesReposModel::addRepo(const QUrl& path)
{
    AudioNotesRepoInctance newRepo = std::make_unique<AudioNotesRepo>(path.toLocalFile(), this);
    newRepo->init();
    _addRepo(std::move(newRepo));
}

void AudioNotesReposModel::addRepo(const QString& path)
{
    AudioNotesRepoInctance newRepo = std::make_unique<AudioNotesRepo>(path, this);
    newRepo->init();
    _addRepo(std::move(newRepo));
}

void AudioNotesReposModel::_addRepo(AudioNotesRepoInctance repo)
{
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.append(std::move(repo));
    endInsertRows();
}
