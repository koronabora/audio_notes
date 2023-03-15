#pragma once

#include <QObject>

class AudioNote;
class AudioNotesModel;

class AudioNotesRepo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(AudioNotesModel* notesModel READ _notesModel CONSTANT)
public:
    explicit AudioNotesRepo(const QString & path = QString(), QObject *parent = nullptr);
    void init();

    QString name() const;
    const QString & path()const;

    void addNote(AudioNoteInstance note);

public slots:
    void update();

private:
    std::unique_ptr<AudioNotesModel> m_notesModel;
    QString m_path;

    AudioNotesModel* _notesModel() const;
};
