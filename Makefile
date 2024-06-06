CC = gcc
CFLAGS = -Wall -I/usr/include/mosquitto
LDFLAGS = -lmosquitto
BUILD_DIR = build
SRC_DIR = src

all: $(BUILD_DIR) $(BUILD_DIR)/client

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/client: $(SRC_DIR)/client.c $(BUILD_DIR)/network_utils.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/network_utils.o: $(SRC_DIR)/network_utils.c $(SRC_DIR)/network_utils.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

debug: CFLAGS += -g
debug: clean all

release: CFLAGS += -O2
release: clean all

$(SRC_DIR)/client.d: $(SRC_DIR)/client.c
	$(CC) $(CFLAGS) -MM -MT '$(@:.d=.o)' $< > $@

$(SRC_DIR)/network_utils.d: $(SRC_DIR)/network_utils.c
	$(CC) $(CFLAGS) -MM -MT '$(@:.d=.o)' $< > $@

-include $(SRC_DIR)/client.d $(SRC_DIR)/network_utils.d

.PHONY: all clean debug release

