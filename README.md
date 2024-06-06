# MQTT 채팅 구현<br>

~~본 구현은 Ubuntu(linux) local에서만~~
## 기능 추가 예정
- 다른 클라이언트 접속
- 사용자 등록 및 로그인
- 채팅방 개설 (그룹 채팅)
- 이미지, 파일 전송
- 사용자 삭제 및 Time out

### Linux
```sh
sudo apt-get update
sudo apt-get install mosquitto mosquitto-clients libmosquitto-dev build-essential

make clean
make

mosquitto -c /etc/mosquitto/mosquitto.conf
./build/client
```
