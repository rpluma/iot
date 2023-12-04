## Ali Express

El VL53L0X de ST Microelectronics es un sistema de rango de tiempo de vuelo integrado en un módulo compacto. Esta placa es un soporte para el VL53L0X, por lo que recomendamos la lectura cuidadosa de la hoja de datos VL53L0X (1MB PDF) antes de usar este producto.

El VL53L0 utiliza la tecnología FlightSense de ST para medir con precisión el tiempo que tardan los pulsos emitidos de luz láser infrarroja en llegar al objeto más cercano y reflejarse de vuelta a un detector, por lo que puede considerarse un Sistema LIDAR pequeño y autónomo. Esta medición del tiempo de vuelo (TOF) le permite determinar con precisión la distancia absoluta a un objetivo sin que la reflectancia del objeto influya en gran medida en la medición. El sensor puede informar de distancias de hasta 2 m (6,6 pies) con resolución de 1mm, pero su alcance efectivo y precisión (ruido) depende en gran medida de las condiciones ambientales y las características del objetivo como la reflectancia y el tamaño, así como la configuración del sensor. (La precisión del sensor se especifica para variar desde ± 3% en el mejor de los casos a más de ± 10% en condiciones menos óptimas).

Las mediciones de rango están disponibles a través de la interfaz I⊃ 2;C (TWI) del sensor, que también se utiliza para configurar la configuración del sensor, y el sensor proporciona dos pines adicionales: una entrada de apagado y una salida de interrupción.

El VL53L0X es un gran IC, pero su paquete LGA pequeño y sin cables dificulta su uso para el estudiante o aficionado típico. También funciona a un voltaje recomendado de 2,8 V, lo que puede dificultar la interfaz para los microcontroladores que funcionan a 3,3 V o 5 V. Nuestra Placa de conexión aborda estos problemas, facilitando el uso del sensor, manteniendo el tamaño general lo más pequeño posible.
Descripción PIN
VDD Regulado 2,8 V salida. Casi 150 mA está disponible para alimentar componentes externos. (Si desea omitir El regulador interno, puede usar este PIN como una entrada de 2,8 V con el VIN desconectado).
VIN Esta es la conexión principal de la fuente de alimentación de 2,6 V a 5,5 V. Los cambiadores de nivel SCL y SDA tiran de las líneas I⊃ 2;C hasta este nivel.
GND La conexión a tierra (0 V) para su fuente de alimentación. Tu fuente de control I⊃2;C también debe compartir un terreno común con esta tabla.
SDA nivel desplazado I⊃ 2; Línea DE DATOS C: ALTO es VIN, BAJO es 0 V
SCL nivel desplazado I⊃ 2; Línea de reloj C: ALTO es VIN, BAJO es 0 V
XSHUT este pin es una entrada de apagado activo-bajo; la placa tira de VDD para activar el sensor por defecto. Conducir este PIN bajo pone el sensor en espera de hardware. Esta entrada no tiene cambio de nivel.
El paquete incluye:
1x Sensor de distancia de tiempo de vuelo L53L0X de 1/2"