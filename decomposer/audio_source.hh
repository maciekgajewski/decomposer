#pragma once

#include <QObject>

#include <memory>

class QAudioInput;
class QIODevice;

namespace Decomposer {

class AudioBuffer;


class AudioSource : public QObject
{
	Q_OBJECT
public:

	AudioSource(QObject* p = nullptr);
	~AudioSource();

	void setRate(unsigned rate);

public slots:

	void play();
	void stop();

signals:

	void newData(const AudioBuffer& data);

private slots:

	void onNewData(const char* data, qint64 size);

private:

	std::unique_ptr<AudioBuffer> buffer_;
	QAudioInput* input_ = nullptr;
	QIODevice* reader_ = nullptr;
};

}
