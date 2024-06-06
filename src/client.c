#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include "network_utils.h"

#define BROKER_ADDRESS "localhost"
#define BROKER_PORT 1883
#define TOPIC "chat"

void on_connect(struct mosquitto *mosq, void *obj, int rc)
{
    if (rc != 0) {
        fprintf(stderr, "Connection failed\n");
        exit(1);
    }
    mosquitto_subscribe(mosq, NULL, TOPIC, 0);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    printf("message: %s\n", (char *)msg->payload);
}

int main(int argc, char *argv[])
{
    struct mosquitto *mosq;
    char message[256];
    char *ip_address = get_ip_address();

    if (ip_address == NULL) {
        return 1;
    }

    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "error\n");
        return 1;
    }

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    if (mosquitto_connect(mosq, BROKER_ADDRESS, BROKER_PORT, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "unable to connect.\n");
        return 1;
    }

    mosquitto_loop_start(mosq);

    printf("--------------------------------.\n");
    while (1) {
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; 

        if (strcmp(message, "exit") == 0) 
            break;
        

        char full_message[300];
        snprintf(full_message, sizeof(full_message), "%s: %s", ip_address, message);

        mosquitto_publish(mosq, NULL, TOPIC, strlen(full_message), full_message, 0, false);
    }

    mosquitto_loop_stop(mosq, true);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    free(ip_address);

    return 0;
}

