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
typedef enum {
  global_state_INIT = 0,
  global_state_IDLE = 1,
  global_state_ARMING45 = 2,
  global_state_PRECHARGE = 3,
  global_state_DISARMING45 = 4,
  global_state_READY = 5,
  global_state_START_LEVITATION = 6,
  global_state_LEVITATION_STABLE = 7,
  global_state_START_GUIDANCE = 8,
  global_state_GUIDANCE_STABLE = 9,
  global_state_ACCELERATION = 10,
  global_state_CONTROLLER = 11,
  global_state_CRUISING = 12,
  global_state_DECELERATION = 13,
  global_state_STOP_LEVITATION = 14,
  global_state_STOP_GUIDANCE = 15,
  global_state_SHUTDOWN = 16,
  global_state_RESTARTING = 17,
  global_state_CALIBRATING = 18,
} global_state;
typedef enum {
  global_command_NONE = 0,
  global_command_START_45 = 1,
  global_command_STOP_45 = 2,
  global_command_START_LEVITATION = 3,
  global_command_STOP_LEVITATION = 4,
  global_command_START_PROPULSION = 5,
  global_command_STOP_PROPULSION = 6,
  global_command_START_CONTROLLER = 7,
  global_command_STOP_CONTROLLER = 8,
  global_command_ABORT = 9,
  global_command_EMERGENCY = 10,
  global_command_SHUTDOWN = 11,
  global_command_RESTART = 12,
  global_command_CALIBRATE = 13,
} global_command;
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
  led_board_state_LIFTOFF = 2,
  led_board_state_BREATHE = 3,
  led_board_state_RAINBOW = 4,
  led_board_state_SHUTDOWN = 5,
} led_board_state;
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
static inline sdc_status canzero_get_sdc_status() {
  extern sdc_status __oe_sdc_status;
  return __oe_sdc_status;
}
static inline error_flag canzero_get_assertion_fault() {
  extern error_flag __oe_assertion_fault;
  return __oe_assertion_fault;
}
static inline error_flag canzero_get_error_heartbeat_miss() {
  extern error_flag __oe_error_heartbeat_miss;
  return __oe_error_heartbeat_miss;
}
static inline error_level canzero_get_error_level_mcu_temperature() {
  extern error_level __oe_error_level_mcu_temperature;
  return __oe_error_level_mcu_temperature;
}
static inline led_board_command canzero_get_command() {
  extern led_board_command __oe_command;
  return __oe_command;
}
static inline double canzero_get_loop_frequency() {
  extern double __oe_loop_frequency;
  return __oe_loop_frequency;
}
static inline float canzero_get_mcu_temperature() {
  extern float __oe_mcu_temperature;
  return __oe_mcu_temperature;
}
static inline error_level_config canzero_get_error_level_config_mcu_temperature() {
  extern error_level_config __oe_error_level_config_mcu_temperature;
  return __oe_error_level_config_mcu_temperature;
}
static inline global_state canzero_get_global_state() {
  extern global_state __oe_global_state;
  return __oe_global_state;
}
static inline global_command canzero_get_global_command() {
  extern global_command __oe_global_command;
  return __oe_global_command;
}
static inline error_flag canzero_get_mother_board_error_any() {
  extern error_flag __oe_mother_board_error_any;
  return __oe_mother_board_error_any;
}
static inline error_level canzero_get_mother_board_error_level_over_temperature_system() {
  extern error_level __oe_mother_board_error_level_over_temperature_system;
  return __oe_mother_board_error_level_over_temperature_system;
}
static inline sdc_status canzero_get_mother_board_system_sdc_status() {
  extern sdc_status __oe_mother_board_system_sdc_status;
  return __oe_mother_board_system_sdc_status;
}
static inline error_level canzero_get_input_board_error_level_bat24_under_voltage() {
  extern error_level __oe_input_board_error_level_bat24_under_voltage;
  return __oe_input_board_error_level_bat24_under_voltage;
}
typedef struct {
  get_resp_header m_header;
  uint32_t m_data;
} canzero_message_get_resp;
static const uint32_t canzero_message_get_resp_id = 0x19D;
typedef struct {
  set_resp_header m_header;
} canzero_message_set_resp;
static const uint32_t canzero_message_set_resp_id = 0x1BD;
typedef struct {
  led_board_state m_state;
  sdc_status m_sdc_status;
} canzero_message_led_board_stream_state;
static const uint32_t canzero_message_led_board_stream_state_id = 0x76;
typedef struct {
  uint64_t m_config_hash;
} canzero_message_led_board_stream_config_hash;
static const uint32_t canzero_message_led_board_stream_config_hash_id = 0x177;
typedef struct {
  error_flag m_assertion_fault;
  error_flag m_error_heartbeat_miss;
  error_level m_error_level_mcu_temperature;
} canzero_message_led_board_stream_errors;
static const uint32_t canzero_message_led_board_stream_errors_id = 0x56;
typedef struct {
  uint8_t m_node_id;
  uint8_t m_unregister;
  uint8_t m_ticks_next;
} canzero_message_heartbeat_can0;
static const uint32_t canzero_message_heartbeat_can0_id = 0x1D4;
typedef struct {
  uint8_t m_node_id;
  uint8_t m_unregister;
  uint8_t m_ticks_next;
} canzero_message_heartbeat_can1;
static const uint32_t canzero_message_heartbeat_can1_id = 0x1D3;
typedef struct {
  get_req_header m_header;
} canzero_message_get_req;
static const uint32_t canzero_message_get_req_id = 0x19E;
typedef struct {
  set_req_header m_header;
  uint32_t m_data;
} canzero_message_set_req;
static const uint32_t canzero_message_set_req_id = 0x1BE;
typedef struct {
  led_board_command m_led_board_command;
} canzero_message_mother_board_stream_led_board_command;
static const uint32_t canzero_message_mother_board_stream_led_board_command_id = 0x70;
typedef struct {
  global_state m_state;
  global_command m_command;
  sdc_status m_system_sdc_status;
} canzero_message_mother_board_stream_state;
static const uint32_t canzero_message_mother_board_stream_state_id = 0x90;
typedef struct {
  error_flag m_error_heartbeat_miss;
  error_flag m_error_any;
  error_level m_error_level_over_temperature_system;
} canzero_message_mother_board_stream_errors;
static const uint32_t canzero_message_mother_board_stream_errors_id = 0x50;
typedef struct {
  error_flag m_error_assertion_fault;
  error_flag m_error_acceleration_out_of_range;
  error_flag m_error_lateral_acceleration_out_of_range;
  error_flag m_error_vertical_acceleration_out_of_range;
  error_flag m_error_acceleration_calibration_failed;
  error_flag m_error_bat24_voltage_invalid;
  error_flag m_error_bat24_current_invalid;
  error_flag m_error_supercap_voltage_invalid;
  error_flag m_error_link24_current_invalid;
  error_flag m_error_link45_voltage_invalid;
  error_flag m_error_link45_current_invalid;
  error_flag m_error_cooling_cycle_pressure_invalid;
  error_flag m_error_mcu_temperature_invalid;
  error_flag m_error_cooling_cycle_temperature_invalid;
  error_flag m_error_bat24_temperature_invalid;
  error_flag m_error_supercap_temperature_invalid;
  error_flag m_error_buck_temperature_invalid;
  error_flag m_error_ebox_temperature_invalid;
  error_flag m_error_ambient_temperature_invalid;
  error_flag m_error_heartbeat_miss;
  error_level m_error_level_bat24_under_voltage;
  error_level m_error_level_bat24_over_voltage;
  error_level m_error_level_bat24_over_current;
  error_level m_error_level_supercap_under_voltage;
  error_level m_error_level_supercap_over_voltage;
  error_level m_error_level_link24_over_current;
  error_level m_error_level_link45_under_voltage;
  error_level m_error_level_link45_over_voltage;
  error_level m_error_level_link45_over_current;
  error_level m_error_level_cooling_cycle_over_pressure;
  error_level m_error_level_mcu_temperature;
  error_level m_error_level_cooling_cycle_temperature;
  error_level m_error_level_bat24_temperature;
  error_level m_error_level_supercap_temperature;
  error_level m_error_level_buck_temperature;
  error_level m_error_level_ebox_temperature;
  error_level m_error_level_ambient_temperature;
} canzero_message_input_board_stream_errors;
static const uint32_t canzero_message_input_board_stream_errors_id = 0x52;
void canzero_can0_poll();
void canzero_can1_poll();
uint32_t canzero_update_continue(uint32_t delta_time);
void canzero_init();
void canzero_set_config_hash(uint64_t value);

static inline void canzero_set_build_time(date_time value){
  extern date_time __oe_build_time;
  __oe_build_time = value;
}

static inline void canzero_set_state(led_board_state value){
  extern led_board_state __oe_state;
  __oe_state = value;
}

static inline void canzero_set_sdc_status(sdc_status value){
  extern sdc_status __oe_sdc_status;
  __oe_sdc_status = value;
}

void canzero_set_assertion_fault(error_flag value);

void canzero_set_error_heartbeat_miss(error_flag value);

void canzero_set_error_level_mcu_temperature(error_level value);

static inline void canzero_set_command(led_board_command value){
  extern led_board_command __oe_command;
  __oe_command = value;
}

static inline void canzero_set_loop_frequency(double value){
  extern double __oe_loop_frequency;
  __oe_loop_frequency = value;
}

static inline void canzero_set_mcu_temperature(float value){
  extern float __oe_mcu_temperature;
  __oe_mcu_temperature = value;
}

static inline void canzero_set_error_level_config_mcu_temperature(error_level_config value){
  extern error_level_config __oe_error_level_config_mcu_temperature;
  __oe_error_level_config_mcu_temperature = value;
}

static inline void canzero_set_global_state(global_state value){
  extern global_state __oe_global_state;
  __oe_global_state = value;
}

static inline void canzero_set_global_command(global_command value){
  extern global_command __oe_global_command;
  __oe_global_command = value;
}

static inline void canzero_set_mother_board_error_any(error_flag value){
  extern error_flag __oe_mother_board_error_any;
  __oe_mother_board_error_any = value;
}

static inline void canzero_set_mother_board_error_level_over_temperature_system(error_level value){
  extern error_level __oe_mother_board_error_level_over_temperature_system;
  __oe_mother_board_error_level_over_temperature_system = value;
}

static inline void canzero_set_mother_board_system_sdc_status(sdc_status value){
  extern sdc_status __oe_mother_board_system_sdc_status;
  __oe_mother_board_system_sdc_status = value;
}

static inline void canzero_set_input_board_error_level_bat24_under_voltage(error_level value){
  extern error_level __oe_input_board_error_level_bat24_under_voltage;
  __oe_input_board_error_level_bat24_under_voltage = value;
}

void canzero_send_config_hash();

void canzero_send_build_time();

void canzero_send_state();

void canzero_send_sdc_status();

void canzero_send_assertion_fault();

void canzero_send_error_heartbeat_miss();

void canzero_send_error_level_mcu_temperature();

void canzero_send_command();

void canzero_send_loop_frequency();

void canzero_send_mcu_temperature();

void canzero_send_error_level_config_mcu_temperature();

void canzero_send_global_state();

void canzero_send_global_command();

void canzero_send_mother_board_error_any();

void canzero_send_mother_board_error_level_over_temperature_system();

void canzero_send_mother_board_system_sdc_status();

void canzero_send_input_board_error_level_bat24_under_voltage();

#endif