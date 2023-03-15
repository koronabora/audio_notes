#include <QFile>
#include <QDebug>
#include <QPointer>

#include "AudioNotesModel.h"
#include "AudioNote.h"

AudioNotesModel::AudioNotesModel(QObject* parent)
    : QAbstractListModel{ parent }
{
}

int AudioNotesModel::rowCount(const QModelIndex&) const
{
    return m_items.size();
}

QVariant AudioNotesModel::data(const QModelIndex& index, int) const
{
    return QVariant::fromValue(m_items.at(index.row())->name());
}

QHash<int, QByteArray> AudioNotesModel::roleNames() const
{
    static QHash<int, QByteArray> sNames = { { 1, "note" } };
    return sNames;
}

void AudioNotesModel::addIfNotExists(AudioNoteInstance note)
{
    if (!note)
    {
        qDebug() << "An empty pointer received while adding new note.";
        return;
    }

    auto& item = std::find_if(m_items.begin(), m_items.end(),
        [path = note->path()](auto const& item)
        {
            return item && item->path() == path;
        });
    if (item != m_items.end())
        return;

    connect(note.get(), &AudioNote::removeNode, this, &AudioNotesModel::removeNote);
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.append(std::move(note));
    endInsertRows();
}

void AudioNotesModel::removeNote()
{
    AudioNote* object{ qobject_cast<AudioNote*>(sender()) };
    if (!object)
    {
        qDebug() << "Could not recognise <removeNote> signal's sender. Signal igonred.";
        return;
    }

    int index = -1;
    for (auto const& item : m_items)
    {
        ++index;
        if (object == item.get())
            break;
    }
    
    if (index == -1)
    {
        qDebug() << "Could not detect sender's position. Signal ignored.";
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_items.removeAt(index);
    endRemoveRows();
}
