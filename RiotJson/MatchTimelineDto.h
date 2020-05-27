// MatchTimelineDto.h
#ifndef MATCHTIMELINEDTO_H
#define MATCHTIMELINEDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "MatchFrameDto.h"
#include "JsonObject.h"

namespace riot {
class MatchTimelineDto : public JsonObject
{
public:
	// frames
	QList<MatchFrameDto> frames() const {
		QList<MatchFrameDto> result;
		auto arr = this->value("frames").toArray();
		for (auto val : arr) result.append(static_cast<MatchFrameDto&&>(val.toObject()));
		return result;
	}
	void setFrames(const QList<MatchFrameDto> &frames) {
		QJsonArray arr;
		for (auto v : frames) arr.append(v);
		this->insert("frames",arr);
	}
	
	// frameInterval
	long frameInterval() const { return long(this->value("frameInterval").toVariant().toLongLong()); }
	void setFrameInterval(long frameInterval) { this->insert("frameInterval", qlonglong(frameInterval)); }

};
}

#endif // MATCHTIMELINEDTO_H
