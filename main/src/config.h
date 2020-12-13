#include <WString.h>

const String NODE_TOKEN = "starburst_stream";
const String DEVICE_CONFIG = "{\"token\":\"deadbeef\",\"input_devices\":[{\"hid\":\"a0dc72230878a4cfc03cb1da52ad8e\",\"name\":\"BH1750\",\"min_input\":5,\"max_input\":57,\"unit\":\"\"},{\"hid\":\"cb4d49748f0dc9fc17a49b7b441ff8\",\"name\":\"DHT\",\"min_input\":6,\"max_input\":67,\"unit\":\"\"},{\"hid\":\"f86e193224fee588ddb5036ea0548d\",\"name\":\"MoistureSensor\",\"min_input\":7,\"max_input\":77,\"unit\":\"\"}],\"output_devices\":[{\"hid\":\"e6e81072d2289b4e062b4b95a9fcbe\",\"name\":\"YF-S201 FlowController\",\"min_output\":8,\"max_output\":87,\"unit\":\"\"}]}";
const int JSON_BUFFER_SIZE = 1000;