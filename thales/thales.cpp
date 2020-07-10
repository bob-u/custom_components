#include "thales.h"
#include "esphome/core/log.h"

namespace esphome {
namespace thales {

static const char *TAG = "thales";

static const uint8_t THALES_CMD_READ_HOLDING_REGISTERS = 0x03;
static const uint8_t THALES_REGISTER_COUNT = 2;  // 2x 16-bit registers

void THALES::on_modbus_data(const std::vector<uint8_t> &data) {
  if (data.size() < 4) {
    ESP_LOGW(TAG, "Invalid size for THALES!");
    return;
  }

  auto thales_get_16bit = [&](size_t i) -> uint16_t {
    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  };

  uint32_t raw_humidity = thales_get_16bit(0);
  float humidity = raw_humidity / 10.0f;

  uint16_t raw_temperature = thales_get_16bit(2);
  float temperature = raw_temperature / 10.0f;


  ESP_LOGD(TAG, "THALES: T=%.1f °C, H=%.1f %%", temperature, humidity);
  if (this->temperature_sensor_ != nullptr)
    this->temperature_sensor_->publish_state(temperature);
  if (this->humidity_sensor_ != nullptr)
    this->humidity_sensor_->publish_state(humidity);
}

// void THALES::setup() {
//   ESP_LOGCONFIG(TAG, "Setting up THALES...");
// }

void THALES::update() {
  this->send(THALES_CMD_READ_HOLDING_REGISTERS, 0, THALES_REGISTER_COUNT);
}
void THALES::dump_config() {
  ESP_LOGCONFIG(TAG, "THALES:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  LOG_SENSOR("", "Temperature", this->temperature_sensor_);
  LOG_SENSOR("", "Humidity", this->humidity_sensor_);
}

}  // namespace thales
}  // namespace esphome
