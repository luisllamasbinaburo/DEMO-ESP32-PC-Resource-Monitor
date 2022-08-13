# DEMO-ESP32-PC-Resource-Monitor


Monitor de consumo de recursos de un PC, realizado en NET6 + ESP32 (M5StickC Plus). Comunicación via MQTT.

### Instruccions
- Clonar el repo
- En aplicación NET6, sustituir IP por la dirección de tu broker MQTT
- En aplicación ESP32, susituir los datos de tu red WiFi
- Subir ficheros al ESP32
- Ejecutar aplicación consola NET
- Disfrutar

## Dependencias

Se requiere la librería ESP-Color disponible aqui https://github.com/luisllamasbinaburo/ESP-Color


## Themes

La librería es compatible con distintos Themes. Por el momento se incluyen los themes classic y modern.

Siéntete libre de añadir y jugar con los Themes que quieras, y hacer un PR si encuentras uno que te guste ;)

![classic theme](https://github.com/luisllamasbinaburo/DEMO-ESP32-PC-Resource-Monitor/blob/main/screenshots/classic_theme.jpg)

![modern theme](https://github.com/luisllamasbinaburo/DEMO-ESP32-PC-Resource-Monitor/blob/main/screenshots/modern-theme.jpg)

### Referencias
- https://github.com/openhardwaremonitor/openhardwaremonitor
- https://stackoverflow.com/questions/56830434/c-sharp-get-total-usage-of-gpu-in-percentage
- http://www.keyvan.ms/how-to-calculate-network-utilization-in-net
- https://stackoverflow.com/questions/1195112/how-can-i-get-the-cpu-temperature
