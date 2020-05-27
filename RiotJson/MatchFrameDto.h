// MatchFrameDto.h
#ifndef MATCHFRAMEDTO_H
#define MATCHFRAMEDTO_H

#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QMap>
#include "MatchParticipantFrameDto.h"
#include "MatchEventDto.h"
#include "JsonObject.h"

namespace riot {
class MatchFrameDto : public JsonObject
{
public:
	// participantFrames
	QMap<QString, MatchParticipantFrameDto> participantFrames() const {
		QMap<QString, MatchParticipantFrameDto> result;
		auto object = this->value("participantFrames").toObject();
		for (auto key : object.keys()) result.insert(key, static_cast<MatchParticipantFrameDto&&>(object.value(key).toObject()));
		return result;
	}
	void setParticipantFrames(const QMap<QString, MatchParticipantFrameDto> &participantFrames) {
		QJsonObject object;
		for (auto key : participantFrames.keys()) object.insert(key, participantFrames.value(key));
		this->insert("participantFrames", object);
	}
	
	// events
	QList<MatchEventDto> events() const {
		QList<MatchEventDto> result;
		auto arr = this->value("events").toArray();
		for (auto val : arr) result.append(static_cast<MatchEventDto&&>(val.toObject()));
		return result;
	}
	void setEvents(const QList<MatchEventDto> &events) {
		QJsonArray arr;
		for (auto v : events) arr.append(v);
		this->insert("events",arr);
	}
	
	// timestamp
	long timestamp() const { return long(this->value("timestamp").toVariant().toLongLong()); }
	void setTimestamp(long timestamp) { this->insert("timestamp", qlonglong(timestamp)); }
	
};
}

#endif // MATCHFRAMEDTO_H
