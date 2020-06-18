# OPGG_Add-on
OP.GG와 롤 클라이언트를 연동 해 룬 복사, 자동 멀티 서치 등. OP.GG의 기능을 확장 한 Windows 프로그램입니다.

### 할 일 노트
  - Overlay 방식으로 인게임 내에 전적 표시 구현
  - 내전/대회 방송용 인터페이스 / 기능 구현
  - 아이템 복사 구현
  - 일부 유저에게 인스톨 진행이 막히는 버그 수정

### 사용언어 : C/C++, QML, JS 


### 배포판 다운로드 : https://storage.googleapis.com/opgg-add-on-repository/OPGG_Add-on_Installer.exe


### 코드 종속성
1. QT 5.12.5 이상 (프레임워크)
2. MSVC 2015 이상 (컴파일러) > Mingw로 컴파일은 불가능합니다.
3. OpenSSL 1.1.1


### 외부 API
- riot.h/cpp : [Riot API](https://developer.riotgames.com/apis) > 라이엇 서버 연동 (미사용)
- lcu.h/cpp : [LCU API](https://riot-api-libraries.readthedocs.io/en/latest/lcu.html) > 롤 클라이언트 연동
- datadragon.h/cpp : [Data Dragon API](https://developer.riotgames.com/docs/lol#data-dragon) > 롤 정적 데이터 API


### 외부 라이브러리
- 3rdparty/QGumboParser : [gumbo-parser](https://github.com/google/gumbo-parser) > C++ HTML 파서


# 핵심 기능
- op.gg 챔피언 분석페이지의 룬페이지를 롤 클라이언트로 복사
- 롤 클라이언트 매칭시, 픽창연동 및 자동 멀티서치
- 선택한 챔피언의 전적을 실시간으로 표시
-기타 편의 기능 등 (자동 업데이트등)

![KDA](https://user-images.githubusercontent.com/45027993/83393479-d01aee00-a431-11ea-95dc-491e62b075ae.JPG)
![runeCopy](https://user-images.githubusercontent.com/45027993/82983614-62cf1d80-a02b-11ea-94b4-d085744aab8c.png)
