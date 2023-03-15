#include <QFileInfo>
#include <QDebug>
#include <QCoreApplication>

#include "AudioNotesRepo.h"
#include "AudioNote.h"
#include "AudioNotesModel.h"
#include "Scanner.h"

AudioNotesRepo::AudioNotesRepo(const QString & path,
                               QObject *parent)
    : QObject{parent},
    m_path{ path },
    m_notesModel{ std::make_unique<AudioNotesModel>() }
{

}

void AudioNotesRepo::init()
{
    update();
}

AudioNotesModel *AudioNotesRepo::_notesModel() const
{
    return m_notesModel.get();
}

QString AudioNotesRepo::name() const
{
    return QFileInfo(m_path).fileName();
}

const QString &AudioNotesRepo::path() const
{
    return m_path;
}

void AudioNotesRepo::addNote(AudioNoteInstance note)
{
    if (!m_notesModel)
    {
        qDebug() << "Internal pointer is not valid. Terminating.";
        QCoreApplication::exit(-1);
    }
    m_notesModel->addIfNotExists(std::move(note));
}

void AudioNotesRepo::update()
{
    auto scanner = std::make_shared<Scanner>();
    connect(scanner.get(), &Scanner::scanComplete, [this](const QString &, const QStringList & audioNotes){
        for(auto &&notePath: audioNotes) {
            m_notesModel->addIfNotExists(std::move(AudioNote::build(notePath)));
        }
    });
    scanner->scanFolder(m_path);
}
