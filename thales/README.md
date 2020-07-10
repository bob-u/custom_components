# Thales RS485 Modbus sensor component

```yaml
uart:
  rx_pin: GPIO33
  tx_pin: GPIO32
  baud_rate: 9600
  stop_bits: 1

sensor:
  - platform: thales
    address: 1
    temperature:
      name: "Thales Temperature"
    humidity:
      name: "Thales Humidity"
    update_interval: 60s
```

