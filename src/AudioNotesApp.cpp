#include "AudioNotesApp.h"

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QUrl>
#include <QDebug>

#include "AudioNotesRepo.h"
#include "AudioNotesReposModel.h"
#include "Settings.h"

AudioNotesApp::AudioNotesApp(QObject *parent)
    : QObject{parent},
    m_reposModel{ new AudioNotesReposModel(this) }
{
}

bool AudioNotesApp::isRepoListEmpty() const
{
    if (!m_reposModel)
    {
        qDebug() << trUtf8("Internal repo model is not valid. Terminating!");
        QCoreApplication::exit(-1);
    }
    return m_reposModel->rowCount(QModelIndex()) == 0;
}

void AudioNotesApp::init()
{
    m_repos.clear();
    QFile file("init.txt");
    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while (!in.atEnd()){
            if(auto &&path = in.readLine(); path != ""){
                m_repos.append(QUrl(path));
            }
        }
        file.close();
    }
    for(auto &url : m_repos){
        m_reposModel->addRepo(i.toLocalFile());
    }
    if(!isRepoListEmpty()){
        emit updateWindow();
    }
}

void AudioNotesApp::save()
{
    Settings::i().beginWriteArray("repos");
    for (size_t i = 0; i < m_repos.size(); ++i) {
        Settings::i().setArrayIndex(i);
        Settings::i().setValue("url", m_repos.at(i));
    }
    Settings::i().endArray();
}

void AudioNotesApp::addAudioRepo(const QUrl &path)
{
    m_reposModel->addRepo(path);
    m_repos.append(path);
    save();
}

QPointer<AudioNotesReposModel> AudioNotesApp::_reposModel() const
{
    return m_reposModel;
}
