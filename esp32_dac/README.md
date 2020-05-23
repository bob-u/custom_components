# ESP32 DAC component

```yaml
output:
  - platform: esp32_dac
    pin: GPIO25
    id: dac_output
    
on_...:
  then:
    - output.set_level:
        id: dac_output
        level: 50%
```

