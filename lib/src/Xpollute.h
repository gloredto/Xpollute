#ifndef XPOLLUTE_H
#define XPOLLUTE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Team Identification Number Length
#define ID_LENGTH 2 
// Since all message have maximum of 8 bytes (1 for startBit, 2 for team ID, 1 for Message Id, 4 for payload)
#define MAX_MSG_LENGTH 8

/* Message ID details */
// Boundary Checking variable
#define MIN_MSG_ID 0
#define MAX_MSG_ID 3
// Message ID
#define ROCKETLINK_MSG_ID_HUMIDITY 0
#define ROCKETLINK_MSG_ID_TEMP 1
#define ROCKETLINK_MSG_ID_MQ2 2
#define ROCKETLINK_MSG_ID_MQ7 3

/* Type definition [ID] */
typedef int32_t humidityType;   //[0] hold humidityType
typedef int32_t tempType;       //[1] hold tempType
typedef int32_t mq2Type;        //[2] hold mq2Type
typedef int32_t mq7Type;        //[3] hold mq7Type

typedef struct xpollute_header {
    uint8_t startBit;
    uint8_t id[ID_LENGTH];
    uint8_t messageId;
} xpollute_header_t;

typedef struct xpollute_message {
    xpollute_header_t header;
    uint8_t* payload;
    //add crc
} xpollute_message_t;

/* Construct message function */
uint8_t construct_xpollute_humidity(xpollute_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 humidityType payload_data);

uint8_t construct_xpollute_temperature(xpollute_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 tempType payload_data);

uint8_t construct_xpollute_mq2(xpollute_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 mq2Type payload_data);

uint8_t construct_xpollute_mq7(xpollute_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 mq7Type payload_data);


/* Extractor function */


humidityType extract_humidity(uint8_t *payload_data);

tempType extract_temperature(uint8_t *payload_data);

mq2Type extract_mq2(uint8_t *payload_data);

mq7Type extract_mq7(uint8_t *payload_data);


/* Helper Function */
// Helper function for the Construct Rocketlink Message
void construct_xpollute_message(xpollute_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier, 
                                 uint8_t msg_id,
                                 uint8_t *payload_data);

void construct_xpollute_header(xpollute_header_t *header, 
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier, 
                                 uint8_t msg_id);
void construct_rocketlink_payload(uint8_t **output_message,
                                  uint8_t *input_message,
                                  uint8_t msg_id);

// Utility Function
uint8_t return_byte_size(uint8_t message_id);


// Breakdown rocketlink message into character array
void deconstruct_message(uint8_t **output_message,
                       xpollute_message_t *input_message);


uint8_t reconstruct_xpollute(xpollute_message_t *output_message,
                        uint8_t *input_message);

void print_xpollute(xpollute_message_t *message);

uint8_t parseXpollute(xpollute_message_t* constructed_message,
                        uint8_t incoming_byte,
                        uint8_t unique_word,
                        uint8_t *team_identifier);

#endif

