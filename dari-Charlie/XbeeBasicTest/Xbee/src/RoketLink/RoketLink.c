#include "RoketLink.h"

uint8_t construct_rocketlink_altitude(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 altType payload_data)
{
    uint8_t *holder = (uint8_t*) &payload_data;
    uint8_t msg_id = 0;
    construct_rocketlink_message(output_message, unique_word, team_identifier, msg_id, holder);
    return 0;
}

uint8_t construct_rocketlink_latitude(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 latType payload_data)
{
    uint8_t *holder = (uint8_t*) &payload_data;
    uint8_t msg_id = 1;
    construct_rocketlink_message(output_message, unique_word, team_identifier,msg_id, holder);
    return 0;
}

uint8_t construct_rocketlink_longitude(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 lonType payload_data)
{
    uint8_t *holder = (uint8_t*) &payload_data;
    uint8_t msg_id = 2;
    construct_rocketlink_message(output_message, unique_word, team_identifier,msg_id, holder);
    return 0;
}

uint8_t construct_rocketlink_pressure(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 preType payload_data)
{
    uint8_t *holder = (uint8_t*) &payload_data;
    uint8_t msg_id = 3;
    construct_rocketlink_message(output_message, unique_word, team_identifier,msg_id, holder);
    return 0;
}

uint8_t construct_rocketlink_temperature(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 tempType payload_data)
{
    uint8_t *holder = (uint8_t*)&payload_data;
    uint8_t msg_id = 4;
    construct_rocketlink_message(output_message, unique_word, team_identifier,msg_id, holder);
    return 0;
}

uint8_t construct_rocketlink_tracker_yaw(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 trackerYawType payload_data)
{
    uint8_t *holder = (uint8_t*)&payload_data;
    uint8_t msg_id = 5;
    construct_rocketlink_message(output_message, unique_word, team_identifier,msg_id, holder);
    return 0;
}

uint8_t construct_rocketlink_tracker_pitch(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 trackerPitchType payload_data)
{
    uint8_t *holder = (uint8_t*)&payload_data;
    uint8_t msg_id = 6;
    construct_rocketlink_message(output_message, unique_word, team_identifier,msg_id, holder);
    return 0;
}

uint8_t construct_rocketlink_payload_roll(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 payloadRollType payload_data)
{
    uint8_t *holder = (uint8_t*)&payload_data;
    uint8_t msg_id = 7;
    construct_rocketlink_message(output_message, unique_word, team_identifier,msg_id, holder);
    return 0;
}

uint8_t construct_rocketlink_payload_pitch(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 payloadPitchType payload_data)
{
    uint8_t *holder = (uint8_t*)&payload_data;
    uint8_t msg_id = 8;
    construct_rocketlink_message(output_message, unique_word, team_identifier,msg_id, holder);
    return 0;
}

uint8_t construct_rocketlink_payload_yaw(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 payloadYawType payload_data)
{
    uint8_t *holder = (uint8_t*)&payload_data;
    uint8_t msg_id = 9;
    construct_rocketlink_message(output_message, unique_word, team_identifier,msg_id, holder);
    return 0;
}

uint8_t construct_rocketlink_humidity(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 humidityType payload_data)
{
    uint8_t *holder = (uint8_t*)&payload_data;
    uint8_t msg_id = 11;
    construct_rocketlink_message(output_message, unique_word, team_identifier,msg_id, holder);
    return 0;
}


/* Extractor */
altType extract_altitude(uint8_t *payload_data) {
    return(*((altType*) payload_data));
}

latType extract_latitude(uint8_t *payload_data) {
    return(*((latType*) payload_data));
}

lonType extract_longitude(uint8_t *payload_data) {
    return(*((lonType*) payload_data));
}

preType extract_pressure(uint8_t *payload_data) {
    return(*((preType*) payload_data));
}

tempType extract_temperature(uint8_t *payload_data) {
    return(*((tempType*) payload_data));
}

trackerYawType extract_tracker_yaw(uint8_t *payload_data) {
    return(*((trackerYawType*) payload_data));
}

trackerPitchType extract_tracker_pitch(uint8_t *payload_data) {
    return(*((trackerPitchType*) payload_data));
}

payloadRollType extract_payload_roll(uint8_t *payload_data) {
    return(*((payloadRollType*) payload_data));
}

payloadPitchType extract_payload_pitch(uint8_t *payload_data) {
    return(*((payloadPitchType*) payload_data));
}

payloadYawType extract_payload_yaw(uint8_t *payload_data) {
    return(*((payloadYawType*) payload_data));
}

humidityType extract_humidity(uint8_t *payload_data) {
    return(*((humidityType*) payload_data));
}

/*
  Takes a payload data and message id. Preprends unique word (0Dh) and
  unique team identifier. Return the constructed message.

  Assumption: output message haven't malloc'ed yet
*/
void construct_rocketlink_message(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 uint8_t msg_id,
                                 uint8_t *payload_data)
{
    rocketlink_message_t *pOut = output_message;
    
    // Fill in details for header
    construct_rocketlink_header(&(pOut->header), unique_word, team_identifier, msg_id);

    // construct payload data
    construct_rocketlink_payload(&(pOut->payload), payload_data, msg_id);
}

/* 
  Filling the header for the message
 */
void construct_rocketlink_header(rocketlink_header_t *header,
                      uint8_t unique_word, 
                      uint8_t *team_identifier,  
                      uint8_t msg_id)
{
    header->startBit   = unique_word;
    header->id[0]      = team_identifier[0];
    header->id[1]      = team_identifier[1];
    header->messageId  = msg_id;
}

/*
  Convert the message to rocketlink_payload depends on the message id
*/

void construct_rocketlink_payload(uint8_t** output_message,
                                uint8_t* input_message,
                                uint8_t msg_id)
{
    uint8_t nByte;
    nByte = return_byte_size(msg_id);
    uint8_t *buffer = (uint8_t*) malloc(nByte);
    memcpy(buffer, input_message, nByte);
    *output_message = buffer;
}

/*
  Takes a rocketlink message.
  Return the constructed array of char message

  Assumption: output message haven't malloc'ed yet
*/
void deconstruct_message(uint8_t **output_message,
                       rocketlink_message_t *input_message)
{
    rocketlink_message_t *message = input_message;
    uint8_t nByte;
    nByte = return_byte_size(message->header.messageId);

    uint8_t *pOut = (uint8_t *) (malloc(sizeof(message->header) + sizeof(char)*nByte));
    *output_message = pOut;

    // Append the header
    *pOut = message->header.startBit; pOut++;
    *pOut = message->header.id[0]; pOut++;
    *pOut = message->header.id[1]; pOut++;
    *pOut = message->header.messageId; pOut++;
    // Append the payload data
    memcpy(pOut, message->payload, nByte);
}
//fungsi parse

/* Reconstructing Message */
// Assumption: input is already a valid rocketlink message (Checked on other function)
// payload haven't malloc'ed
uint8_t reconstruct_rocketlink(rocketlink_message_t *output_message,
                        uint8_t *input_message)
{
    uint8_t nByte;
    uint8_t *pInput = input_message;
    
    output_message->header.startBit = *pInput; pInput++;
    output_message->header.id[0] = *pInput; pInput++;
    output_message->header.id[1] = *pInput; pInput++;
    output_message->header.messageId = *pInput; pInput++;
    
    nByte = return_byte_size(output_message->header.messageId);
    
    output_message->payload = (uint8_t*) malloc(nByte);
    memcpy(output_message->payload, pInput, nByte);
    return 0;
}

void print_rocketlink(rocketlink_message_t *message) 
{
    printf("Start bit: %.2x \n", message->header.startBit);
    printf("Team ID: 0x%.2x%.2x \n", message->header.id[0], message->header.id[1]);
    printf("Message ID: %d \n", message->header.messageId);
    
    int *pInt = (int*) message->payload;
    float *pFloat = (float*) message->payload;
    printf("Payload value (integer): %d \n", *pInt);
    printf("Payload value (float): %f \n", *pFloat);
    printf("\n");
}

uint8_t return_byte_size(uint8_t message_id) 
{
    uint8_t nByte;
    switch (message_id) {
        case 0:
            nByte = sizeof(altType);
            break;
        case 1:
            nByte = sizeof(latType);
            break;
        case 2:
            nByte = sizeof(lonType);
            break;
        case 3:
            nByte = sizeof(preType);
            break;
        case 4:
            nByte = sizeof(tempType);
            break;
        case 5:
            nByte = sizeof(trackerYawType);
            break;
        case 6:
            nByte = sizeof(trackerPitchType);
            break;
        case 7:
            nByte = sizeof(payloadRollType);
            break;
        case 8:
            nByte = sizeof(payloadPitchType);
            break;
        case 9:
            nByte = sizeof(payloadYawType);
            break;
        case 10:
            // photo_convert(pMessage, input_message);
            break;
        case 11:
            nByte = sizeof(humidityType);
            break;
        default:
            break;
    }
    return nByte;
}


/* Get the input character and construct rocket link return 0 if done, return 1 otherwise */
uint8_t parseRocketlink(rocketlink_message_t *output_message,
                        uint8_t incoming_byte, 
                        uint8_t unique_word,
                        uint8_t *team_identifier)
{
    static uint8_t state = 0;
    static uint8_t buffer[MAX_MSG_LENGTH];
    
    switch (state) {
        case 0:
            // Header bit checking
            if (incoming_byte == unique_word) {
                buffer[state] = incoming_byte;
                state++;
            }
            break;
        case 1:
            // ID Checking
            if (incoming_byte == team_identifier[0]) {
                buffer[state] = incoming_byte;
                state++;
            } else {
                // Wrong ID
                state = 0;
            }
            break;
        case 2:
            // Second ID Checking
            if (incoming_byte == team_identifier[1]) {
                buffer[state] = incoming_byte;
                state++;
            } else {
                // Wrong second ID
                state = 0;
            }
            break;
        case 3:
            // Incoming Message ID
            // Boundary Checking
            if ((incoming_byte >= MIN_MSG_ID) && (incoming_byte <= MAX_MSG_ID)){
                buffer[state] = incoming_byte;
                state++;
            } else {
                // False Message
                state = 0;
            }
            break;
        default:
            // Filling the payload section
            if (state < MAX_MSG_LENGTH) {
                buffer[state] = incoming_byte;
                state++;
            } else {
                state = 0;
                return (reconstruct_rocketlink(output_message, buffer));
            }
    }
    return 1;
}
