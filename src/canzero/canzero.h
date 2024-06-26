#ifndef CANZERO_H
#define CANZERO_H
#include <cinttypes>
#include <cstddef>
#define MAX_DYN_HEARTBEATS 10
typedef enum {
  node_id_gamepad = 0,
  node_id_mother_board = 1,
  node_id_motor_driver = 2,
  node_id_guidance_board_front = 3,
  node_id_guidance_board_back = 4,
  node_id_levitation_board1 = 5,
  node_id_levitation_board2 = 6,
  node_id_levitation_board3 = 7,
  node_id_input_board = 8,
  node_id_power_board12 = 9,
  node_id_power_board24 = 10,
  node_id_led_board = 11,
  node_id_count = 12,
} node_id;
typedef struct {
  uint16_t m_od_index;
  uint8_t m_client_id;
  uint8_t m_server_id;
} get_req_header;
typedef struct {
  uint8_t m_sof;
  uint8_t m_eof;
  uint8_t m_toggle;
  uint16_t m_od_index;
  uint8_t m_client_id;
  uint8_t m_server_id;
} set_req_header;
typedef enum {
  led_board_command_NONE = 0,
  led_board_command_DO_SHIT = 1,
} led_board_command;
typedef struct {
  uint8_t m_sof;
  uint8_t m_eof;
  uint8_t m_toggle;
  uint16_t m_od_index;
  uint8_t m_client_id;
  uint8_t m_server_id;
} get_resp_header;
typedef enum {
  set_resp_erno_Success = 0,
  set_resp_erno_Error = 1,
} set_resp_erno;
typedef struct {
  uint16_t m_od_index;
  uint8_t m_client_id;
  uint8_t m_server_id;
  set_resp_erno m_erno;
} set_resp_header;
typedef enum {
  led_board_state_INIT = 0,
  led_board_state_STARTUP = 1,
} led_board_state;
typedef enum {
  sdc_status_OPEN = 0,
  sdc_status_CLOSED = 1,
} sdc_status;
typedef enum {
  error_flag_OK = 0,
  error_flag_ERROR = 1,
} error_flag;
typedef enum {
  error_level_OK = 0,
  error_level_INFO = 1,
  error_level_WARNING = 2,
  error_level_ERROR = 3,
} error_level;
typedef struct {
  uint16_t m_year;
  uint8_t m_month;
  uint8_t m_day;
  uint8_t m_hour;
  uint8_t m_min;
  uint8_t m_sec;
} date_time;
typedef enum {
  bool_t_FALSE = 0,
  bool_t_TRUE = 1,
} bool_t;
typedef struct {
  float m_info_thresh;
  float m_info_timeout;
  float m_warning_thresh;
  float m_warning_timeout;
  float m_error_thresh;
  float m_error_timeout;
  bool_t m_ignore_info;
  bool_t m_ignore_warning;
  bool_t m_ignore_error;
} error_level_config;
static const node_id CANZERO_NODE_ID = node_id_led_board;
typedef struct {
  uint32_t id;
  uint8_t dlc;
  uint8_t data[8];
} canzero_frame;
typedef enum : uint32_t {
  CANZERO_FRAME_IDE_BIT = 0x40000000, // 1 << 30
  CANZERO_FRAME_RTR_BIT = 0x80000000, // 1 << 31
} can_frame_id_bits;
typedef struct {
  uint32_t mask;
  uint32_t id;
} canzero_can_filter;
extern void canzero_can0_setup(uint32_t baudrate, canzero_can_filter* filters, int filter_count);
extern void canzero_can0_send(canzero_frame* frame);
extern int canzero_can0_recv(canzero_frame* frame);
extern void canzero_can1_setup(uint32_t baudrate, canzero_can_filter* filters, int filter_count);
extern void canzero_can1_send(canzero_frame* frame);
extern int canzero_can1_recv(canzero_frame* frame);
extern void canzero_request_update(uint32_t time);
extern uint32_t canzero_get_time();
extern void canzero_enter_critical();
extern void canzero_exit_critical();
static inline uint64_t canzero_get_config_hash() {
  extern uint64_t __oe_config_hash;
  return __oe_config_hash;
}
static inline date_time canzero_get_build_time() {
  extern date_time __oe_build_time;
  return __oe_build_time;
}
static inline led_board_state canzero_get_state() {
  extern led_board_state __oe_state;
  return __oe_state;
}
static inline led_board_command canzero_get_command() {
  extern led_board_command __oe_command;
  return __oe_command;
}
static inline sdc_status canzero_get_sdc_status() {
  extern sdc_status __oe_sdc_status;
  return __oe_sdc_status;
}
static inline double canzero_get_loop_frequency() {
  extern double __oe_loop_frequency;
  return __oe_loop_frequency;
}
static inline error_flag canzero_get_error_heartbeat_miss() {
  extern error_flag __oe_error_heartbeat_miss;
  return __oe_error_heartbeat_miss;
}
static inline float canzero_get_mcu_temperature() {
  extern float __oe_mcu_temperature;
  return __oe_mcu_temperature;
}
static inline error_level canzero_get_error_level_mcu_temperature() {
  extern error_level __oe_error_level_mcu_temperature;
  return __oe_error_level_mcu_temperature;
}
static inline error_level_config canzero_get_error_level_config_mcu_temperature() {
  extern error_level_config __oe_error_level_config_mcu_temperature;
  return __oe_error_level_config_mcu_temperature;
}
typedef struct {
  get_resp_header m_header;
  uint32_t m_data;
} canzero_message_get_resp;
static const uint32_t canzero_message_get_resp_id = 0xFD;
typedef struct {
  set_resp_header m_header;
} canzero_message_set_resp;
static const uint32_t canzero_message_set_resp_id = 0x11D;
typedef struct {
  led_board_state m_state;
  sdc_status m_sdc_status;
} canzero_message_led_board_stream_state;
static const uint32_t canzero_message_led_board_stream_state_id = 0xDB;
typedef struct {
  error_flag m_error_heartbeat_miss;
  error_level m_error_level_mcu_temperature;
} canzero_message_led_board_stream_errors;
static const uint32_t canzero_message_led_board_stream_errors_id = 0xBB;
typedef struct {
  uint8_t m_node_id;
  uint8_t m_unregister;
  uint8_t m_ticks_next;
} canzero_message_heartbeat_can0;
static const uint32_t canzero_message_heartbeat_can0_id = 0x12E;
typedef struct {
  uint8_t m_node_id;
  uint8_t m_unregister;
  uint8_t m_ticks_next;
} canzero_message_heartbeat_can1;
static const uint32_t canzero_message_heartbeat_can1_id = 0x12D;
typedef struct {
  get_req_header m_header;
} canzero_message_get_req;
static const uint32_t canzero_message_get_req_id = 0xFE;
typedef struct {
  set_req_header m_header;
  uint32_t m_data;
} canzero_message_set_req;
static const uint32_t canzero_message_set_req_id = 0x11E;
typedef struct {
  led_board_command m_led_board_command;
} canzero_message_mother_board_stream_led_board_command;
static const uint32_t canzero_message_mother_board_stream_led_board_command_id = 0x4A;
void canzero_can0_poll();
void canzero_can1_poll();
uint32_t canzero_update_continue(uint32_t delta_time);
void canzero_init();
static inline void canzero_set_config_hash(uint64_t value){
  extern uint64_t __oe_config_hash;
  __oe_config_hash = value;
}

static inline void canzero_set_build_time(date_time value){
  extern date_time __oe_build_time;
  __oe_build_time = value;
}

static inline void canzero_set_state(led_board_state value){
  extern led_board_state __oe_state;
  __oe_state = value;
}

static inline void canzero_set_command(led_board_command value){
  extern led_board_command __oe_command;
  __oe_command = value;
}

static inline void canzero_set_sdc_status(sdc_status value){
  extern sdc_status __oe_sdc_status;
  __oe_sdc_status = value;
}

static inline void canzero_set_loop_frequency(double value){
  extern double __oe_loop_frequency;
  __oe_loop_frequency = value;
}

void canzero_set_error_heartbeat_miss(error_flag value);

static inline void canzero_set_mcu_temperature(float value){
  extern float __oe_mcu_temperature;
  __oe_mcu_temperature = value;
}

void canzero_set_error_level_mcu_temperature(error_level value);

static inline void canzero_set_error_level_config_mcu_temperature(error_level_config value){
  extern error_level_config __oe_error_level_config_mcu_temperature;
  __oe_error_level_config_mcu_temperature = value;
}

void canzero_send_config_hash();

void canzero_send_build_time();

void canzero_send_state();

void canzero_send_command();

void canzero_send_sdc_status();

void canzero_send_loop_frequency();

void canzero_send_error_heartbeat_miss();

void canzero_send_mcu_temperature();

void canzero_send_error_level_mcu_temperature();

void canzero_send_error_level_config_mcu_temperature();

#endif