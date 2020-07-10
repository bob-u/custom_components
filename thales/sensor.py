import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, modbus
from esphome.const import CONF_ID, CONF_TEMPERATURE, CONF_HUMIDITY, UNIT_CELSIUS, \
    UNIT_PERCENT, ICON_THERMOMETER, ICON_WATER_PERCENT

AUTO_LOAD = ['modbus']

thales_ns = cg.esphome_ns.namespace('thales')
THALES = thales_ns.class_('THALES', cg.PollingComponent, modbus.ModbusDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(THALES),
    cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(UNIT_CELSIUS, ICON_THERMOMETER, 1),
    cv.Optional(CONF_HUMIDITY): sensor.sensor_schema(UNIT_PERCENT, ICON_WATER_PERCENT, 1),
}).extend(cv.polling_component_schema('60s')).extend(modbus.modbus_device_schema(0x01))


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield modbus.register_modbus_device(var, config)

    if CONF_TEMPERATURE in config:
        conf = config[CONF_TEMPERATURE]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_temperature_sensor(sens))
    if CONF_HUMIDITY in config:
        conf = config[CONF_HUMIDITY]
        sens = yield sensor.new_sensor(conf)
        cg.add(var.set_humidity_sensor(sens))
