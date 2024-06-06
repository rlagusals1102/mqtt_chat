#sudo apt-get update
#sudo apt-get install mosquitto mosquitto-clients libmosquitto-dev build-essential
make clean
make
mosquitto -c /etc/mosquitto/mosquitto.conf
./build/client

