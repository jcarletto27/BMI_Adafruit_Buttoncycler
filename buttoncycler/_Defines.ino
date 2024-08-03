#define SPIFFS LittleFS
#define FORMAT_LITTLEFS_IF_FAILED true
#define BUTTON_PIN D8
#define PIXEL_PIN D10
#define PIXEL_COUNT 3
//Enums kinda
#define ENUM_BMI_HOST_NAME "bmi_host_name"
#define ENUM_BMI_HOST_PASSWORD "bmi_host_password"
#define ENUM_PIXEL_0 "pixel_0"
#define ENUM_PIXEL_1 "pixel_1"
#define ENUM_PIXEL_2 "pixel_2"
#define ENUM_BRIGHTNESS_RANGE "brightness_range"
#define ENUM_MODE_SELECTION "modeSelection"
#define ENUM_BMI_HOST_NAME "bmi_host_name"
#define VOLTAGE_QUERY_PIN A0

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRBW + NEO_KHZ800);
AsyncEventButton b1(GPIO_NUM_8, HIGH);

uint32_t WHITE = strip.Color(255, 255, 255);
uint32_t RED = strip.Color(255, 0, 0);
uint32_t GREEN = strip.Color(0, 255, 0);
uint32_t BLUE = strip.Color(0, 0, 255);
uint32_t ORANGE = strip.Color(255, 250, 0);
uint32_t BLANK = strip.Color(0, 0, 0);

uint32_t pixel_0_color = WHITE;
uint32_t pixel_1_color = WHITE;
uint32_t pixel_2_color = WHITE;
int mode = 9;
int brightness = 10;
int halfBrightness = 5;
boolean activateChangeMode = false;
boolean changeLEDColor = false;

DNSServer dnsServer;
AsyncWebServer server(80);
Preferences preferences;


IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

String defaultHostName = "";
String bmi_host_name_var = "";
String bmi_pass_value = "";
float maxVoltage = 2.70;

boolean setupMode = false;

String hexID = "";
boolean scheduleReboot = false;
uint32_t chipID = 0;
