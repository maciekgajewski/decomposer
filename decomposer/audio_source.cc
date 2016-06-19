#include "audio_source.hh"

#include <decomposer/audio_buffer.hh>

#include <QAudioInput>
#include <QDebug>

#include <algorithm>
#include <iterator>

namespace Decomposer {

class DataReader : public QIODevice
{
	Q_OBJECT
public:

	DataReader(QObject* p) : QIODevice(p)
	{
		open(WriteOnly);
	}

	qint64	readData(char*, qint64) override
	{
		return 0;
	}

	qint64	writeData(const char *data, qint64 maxSize) override
	{
		emit newData(data, maxSize);
		return maxSize;
	}

signals:

	void newData(const char* data, qint64 maxSize);

private:
};

#include "audio_source.moc"

AudioSource::AudioSource(QObject* p)
	: QObject(p)
{
	DataReader* reader = new DataReader(this);
	connect(reader, SIGNAL(newData(const char*,qint64)), this, SLOT(onNewData(const char*,qint64)));
	reader_ = reader;
}

AudioSource::~AudioSource()
{
}

void AudioSource::setRate(unsigned rate)
{
	buffer_ = std::make_unique<AudioBuffer>(rate);

	QAudioFormat format;
	format.setSampleRate(rate);
	format.setChannelCount(1);
	format.setSampleSize(16);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);

	QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
	if (!info.isFormatSupported(format))
	{
		qWarning() << "Default format not supported, trying to use the nearest.";
		format = info.nearestFormat(format);
		qDebug() << format;
	}
	else
	{
		qDebug() << "Format supported";
	}

	delete input_;
	input_ = new QAudioInput(format, this);
}

void AudioSource::play()
{
	if (!input_)
	{
		throw std::runtime_error("Rate not set");
	}
	input_->start(reader_);
}

void AudioSource::stop()
{
	Q_ASSERT(input_);
	input_->stop();
}

void AudioSource::onNewData(const char* data, qint64 size)
{
	Q_ASSERT(buffer_);

	qint64 samples = size / 2;

	buffer_->clear();
	buffer_->reserve(samples);

	const qint16* first = reinterpret_cast<const qint16*>(data);

	std::transform(first, first + samples, std::back_inserter(*buffer_),
		[](qint16 sample)
		{
			return Sample(sample) / std::numeric_limits<qint16>::max();
		});

	emit newData(*buffer_);
}

}
