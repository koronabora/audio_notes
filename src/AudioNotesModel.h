#pragma once

#include <QAbstractListModel>

//class AudioNote;
typedef std::unique_ptr<AudioNote> AudioNoteInstance;

class AudioNotesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AudioNotesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addIfNotExists(AudioNoteInstance note);

public slots:
    void removeNote();

public:
    QList<AudioNoteInstance> m_items;
};

