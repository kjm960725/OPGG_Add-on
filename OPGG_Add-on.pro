QT += quick network webengine

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS_WARN_ON-= -w34100
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        challenge.cpp \
#        competconfig.cpp \
#        competmacth.cpp \
#        competmanager.cpp \
#        competteam.cpp \
#        competuser.cpp \
        datadragon.cpp \
        lcu.cpp \
        main.cpp \
        observerfilemanager.cpp \
        qmlclipboardadapter.cpp \
        riot.cpp \
        updatetool.cpp

RC_ICONS = $$PWD/Icons/OPGG.ico
RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
LIBS += -luser32
HEADERS += \
    RiotJson/JsonObject.h \
    RiotJson/BannedChampion.h \
    RiotJson/ChampionInfo.h \
    RiotJson/ChampionMasteryDTO.h\
    RiotJson/CurrentGameInfo.h \
    RiotJson/CurrentGameParticipant.h \
    RiotJson/GameCustomizationObject.h \
    RiotJson/Incident.h \
    RiotJson/LeaderboardDto.h \
    RiotJson/LeagueEntryDTO.h \
    RiotJson/LeagueItemDTO.h \
    RiotJson/LeagueListDTO.h \
    RiotJson/LobbyEventDTO.h \
    RiotJson/LobbyEventDTOWrapper.h \
    RiotJson/MasteryDto.h \
    RiotJson/MatchDto.h \
    RiotJson/MatchEventDto.h \
    RiotJson/MatchFrameDto.h \
    RiotJson/MatchParticipantFrameDto.h \
    RiotJson/MatchPositionDto.h \
    RiotJson/MatchTimelineDto.h \
    RiotJson/Message.h \
    RiotJson/MiniSeriesDTO.h \
    RiotJson/Observer.h \
    RiotJson/ParticipantDto.h \
    RiotJson/ParticipantIdentityDto.h \
    RiotJson/ParticipantStatsDto.h \
    RiotJson/ParticipantTimelineDto.h \
    RiotJson/Perks.h \
    RiotJson/PlayerDto.h \
    RiotJson/RuneDto.h \
    RiotJson/Service.h \
    RiotJson/ShardStatus.h \
    RiotJson/SummonerDTO.h \
    RiotJson/TeamBansDto.h \
    RiotJson/TeamDto.h \
    RiotJson/TeamStatsDto.h \
    RiotJson/TournamentCodeDTO.h \
    RiotJson/TournamentDto.h \
    RiotJson/TournamentPhaseDto.h \
    RiotJson/Translation.h \
    RiotJson/_RiotJsonInclude.h \
    challenge.h \
#    competconfig.h \
#    competmacth.h \
#    competmanager.h \
#    competteam.h \
#    competuser.h \
    datadragon.h \
    lcu.h \
    observerfilemanager.h \
    qmlclipboardadapter.h \
    riot.h \
    updatetool.h

DISTFILES +=


INCLUDEPATH += $$PWD/3rdparty/include
LIBS += -L$$PWD/3rdparty -lQGumboParser
