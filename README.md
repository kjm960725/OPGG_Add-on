# OPGG_Add-on
OP.GG와 롤 클라이언트를 연동해 룬복사,자동 멀티서치등. OP.GG의 기능을 확장한 프로그램입니다.


### 코드 종속성
1. QT 5.12.5 이상 (프레임워크)
2. MSVC 2015 이상 (컴파일러) > Mingw로 컴파일은 불가능합니다.
3. OpenSSL 1.1.1


### 사용한 외부 API
- riot.h/cpp : Riot API (https://developer.riotgames.com/apis) > 라이엇 서버 연동 (미사용)
- lcu.h/cpp : LCU API (https://riot-api-libraries.readthedocs.io/en/latest/lcu.html) > 롤 클라이언트 연동
- datadragon.h/cpp : Data Dragon API (https://developer.riotgames.com/docs/lol#data-dragon) > 롤 정적 데이터 API
