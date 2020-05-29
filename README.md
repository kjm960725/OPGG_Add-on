# OPGG_Add-on
OP.GG와 롤 클라이언트를 연동해 룬복사,자동 멀티서치등. OP.GG의 기능을 확장한 프로그램입니다.

### 사용언어 : C/C++, QML, JS 


### 배포판 다운로드 : https://drive.google.com/open?id=1V7jXsV4Y1ns3x3UC7WVzVXPBmHFxMuAn


### 코드 종속성
1. QT 5.12.5 이상 (프레임워크)
2. MSVC 2015 이상 (컴파일러) > Mingw로 컴파일은 불가능합니다.
3. OpenSSL 1.1.1


### 외부 API
- riot.h/cpp : [Riot API](https://developer.riotgames.com/apis) > 라이엇 서버 연동 (미사용)
- lcu.h/cpp : [LCU API](https://riot-api-libraries.readthedocs.io/en/latest/lcu.html) > 롤 클라이언트 연동
- datadragon.h/cpp : [Data Dragon API](https://developer.riotgames.com/docs/lol#data-dragon) > 롤 정적 데이터 API


# 핵심 기능
- op.gg 챔피언 분석페이지의 룬페이지를 롤 클라이언트로 복사
- 롤 클라이언트 매칭시, 픽창연동 및 자동 멀티서치
- 기타 편의기능 등


![runeCopy](https://user-images.githubusercontent.com/45027993/82983614-62cf1d80-a02b-11ea-94b4-d085744aab8c.png)
![픽창연동](https://user-images.githubusercontent.com/45027993/82985093-5ef0ca80-a02e-11ea-9deb-cf40d0f421a2.PNG)
