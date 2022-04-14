# Preguntas orientadoras
------------------------
## 1. Describa brevemente los diferentes perfiles de familias de microprocesadores/microcontroladores de ARM. Explique alguna de sus diferentes características.
+ **Cortex A**: Los ARM Cortex-A son procesadores RISC de 32 bits y 64 bits, de alto poder de procesamiento, que se destacan en la capacidad de manejar múltiples tareas, sin ser tan restrictivos en cuanto a la latencia de las mismas (más enfocados para su uso con SO de propósito general). La letra A proviene de *application*, ya que su uso está enfocado en dispositivos con aplicaciones de usuario, como *smartphones* y *tablets*. Por ejemplo, el iPhone 4 llevaba un ARM Cortex-A8.
+ **Cortex R**: Los ARM Cortex-R son procesadores RISC de 32 bits y 64 bits, que se destacan por estar optimizados para aplicaciones de tiempo real estricto (*hard real-time*) y seguridad crítica (*safety-critical*). La letra R priviene de *real-time*, ya que su uso está enfocado en aplicaciones en la que los requisitos de latencia deben ser estrictamente cumplidos, ya que su no cumplimiento supone peligro para la vida humana. Algunos ejemplos de su aplicación es en dispositivos médicos, automoción (ECU), aviónica, entre otros.
+ **Cortex M**: Los ARM Cortex-M son procesadores RISC de 32 bits de alta eficiencia debido a su direccionamiento de 32 bits y por utilizar un set de instrucciones con alta densidad de codigo. La letra M proviene de *microcontroller*, ya que su uso está enfocado para ser el CPU de los microcontroladores usandos en dispositivos de electrónica de consumo, automoción, telecomunicaciones, entre otros.
    - M0 y M0+ son procesadores de bajo consumo, orientado a electronica de consumo. La inclusion del SysTick timer es opcional, por lo que no todos soportan directamente el uso de RTOS. Su arquitectura de memoria es Von Neumann, razon por la cual son mas baratos pero tambien con menos poder de procesamiento. La arquitectura ARM es la ARMv6-M
    - M1 tiene las mismas caracteristicas que M0 y M0+ y ademas la posibilidad de incluir TCM (*Tightly-Coupled Memory*). La principal diferencia radica en que su licencia IP esta orientada para su uso con FPGAs, donde el TCM cobra mayor sentido.
    - M3, M4 y M7 son procesadores de mayor capacidad de procesamiento, que incluyen siempre SysTick timer, lo que permite el soporte de RTOS. Son de arquitectura de memoria Harvard, siendo más costosos pero con mayor poder de procesamiento. Su arquitectura ARM es ARMv7-M para el caso del M3, y ARMv7E-M para el caso del M4 y M7. Esta diferencia de arquitectura ARM del M3 hace que no ofrezca soporte de extensiones DSP y FPU. M4 y M7 soportan DSP, siendo la FPU opcional. Finalmente, el M7 puede incluir tambien el uso de memoria cache y de TCM.
# Cortex-M
----------
## 1. Describa brevemente las diferencias entre las familias de procesadores Cortex M0, M3 y M4.
La principal diferencia entre las familias M0, M3 y M4 son las siguientes:
 + Arquitectura de memoria: M0 posee arquitectura Von Neumann mientras que M3 y M4 poseen arquitectura Harvard, esto se traduce en un *trade off* entre el costo y el procesamiento, siendo los M0 mas baratos pero con menor procesamiento (los datos y las instrucciones usan el mismo bus), y los M3 y M4 mas caros pero con mayor procesamiento (buses dedicados para los datos y las instrucciones).
 + Soporte de RTOS directo: los M3 y M4 ofrecen soporte para RTOS, razon por la cual estos incluyen siempre SysTick timer. Los M0 pueden incluirlo pero aun asi no llegan a soportar todas sus caracteristicas de manera directa.
 + Soporte DSP y FPU: Solo el M4 incluye instrucciones para DSP, y puede llegar a incluir para FPU. Cuando incluyen FPU se los suele designar M4F.
## 2. ¿Por qué se dice que el set de instrucciones Thumb permite mayor densidad de código? Explique
A continuacion, se enumeran algunas de las caracteristicas que hacen de Thumb un ISA con alta densidad de codigo:
 + Thumb es un subconjunto de instrucciones de longitud de 2 bytes (16 bits), en lugar del juego estandar de ARM que son de 4 bytes (32 bits). Esto hace que tenga mayor densidad de codigo, obteniendo incluso mejor rendimiento que un codigo de 32 bits cuando el ancho de bus de memoria es menor a 32 bits.
 + En el caso de Thumb-2, permite a las instrucciones de 16-bit y las instrucciones de 32-bit de trabajar juntas, siendo compatibles sin tener que cambiar entre una u otra.
 + Modos de acceso a memoria especiales para un acceso efectivo a memoria.
 + Una simple instruccion puede manejar multiples accesos a memoria.
 + En el caso de M3 y M4, soporte de instrucciones de division por hardware y *Multiply and Accumulate* (MAC).
 + En el caso de M4, instrucciones *Single Instruction, Multiple Data* (SIMD).
## 3. ¿Qué entiende por arquitectura load-store? ¿Qué tipo de instrucciones no posee este tipo de arquitectura?
Se denomina "load-store" a la arquitectura que tienen ciertos procesadores en la cual poseen un numero determinado de registros dentro del nucleo del procesador llamado *register bank*, cuyo proposito es el control y el procesamiento de los datos. Las instrucciones de procesamiento de datos que soporten esta arquitectura generalmente especifican un registro origen y un registro destino.  
En la arquitectura ARM, si un dato en memoria tiene que ser procesado, debe ser cargado desde la memoria hacia lo registros en el "banco de registros", procesados, y luego escritos nuevamente en la memoria de ser necesario. Las instrucciones involucradas en esta arquitectura en ARM son LDR (load) y STR (store), siendo las unicas instrucciones capaces de escribir y leer en memoria.
## 4. ¿Cómo es el mapa de memoria de la familia?
El mapa de memoria de la familia de microprocesadores ARM Cortex-M posee un direccionamiento de 32 bits, lo que significa que el espacio máximo de memoria permitido es de 4GB.  
El mapa de memoria está unificado, lo que quiere decir que todas las direcciones correspondientes a código de programa, datos, periféricos, entre otros estan localizados dentro de esos 4GB.  
Respecto al *endianess*, la mayoría de los Cortex-M usan *little endian*, pero en particular los M3 y M4 pueden operar tanto en *little endian* como en *big endian*.  
## 5. ¿Qué ventajas presenta el uso de los “shadowed pointers” del PSP y el MSP?
La ventaja de utilizar dos *stack pointers* como el MSP y el PSP se enfatiza en sistemas que utilizan OS o RTOS, donde las excepciones, incluidas las del *kernel*, usan el MSP, y las tareas de la aplicación usan el PSP. Cada tarea tiene su propio *stack* dedicado y cada vez que existe un cambio de contexto, el OS actualiza el PSP apuntando al *stack* correspondiente.
Como se ha mencionado, esto tiene varios beneficios:
 + Si alguna tarea sufre una corrupción del *stack*, el *stack* usado por el *kernel* y otras tareas aún sigue intacto.
 + El *stack* de cada tarea no necesita incluir espacio para ISR, ya que éste se localiza únicamente en el *main stack*.
 + Facilita el desarrollo de un OS eficiente para procesadores Cortex-M.
 + Si existe soporte de MPU, éste se puede utilizar para disparar una *MemManage fault exception* cuando exista un *stack overflow* para evitar que una tarea escriba fuera del espacio de memoria inicialmente dedicado.
## 6. Describa los diferentes modos de privilegio y operación del Cortex M, sus relaciones y como se conmuta de uno al otro. Describa un ejemplo en el que se pasa del modo privilegiado a no priviligiado y nuevamente a privilegiado.
Los Cortex-M3 y Cortex-M4 poseen dos **estados de operación**:
 + **Debug state**: Cuando el procesador está detenido (*halted*), entra en *debug state* y detiene la ejecución de instrucciones.
 + **Thumb state**: Cuando el procesador está corriendo código de programa (instrucciones *Thumb*), se encuentra en *Thumb state*.  
A su vez, soportan dos **niveles de acceso**:
 + **Privileged**: Por defecto, los procesadores empiezan en modo privilegiado.
 + **Unprivileged**: Cuando se utiliza un OS, la ejecución de las tareas de usuarios pueden ser llevadas a cabo en modo no privilegiado, forzando ciertas restricciones como el acceso a algunos registros del NVIC. Otro ejemplo es su uso con la MPU, para prevenir que tareas no privilegiadas accedan a ciertas regiones de memorias, y así evitar que corrompan areas de memoria utilizadas por el kernel del OS.  
Finalmente, los Cortex-M3 y M4 poseen dos **modos de operación**:
 + **Handler mode**: Cuando se está ejecutando una *exception handler* (e.g. una ISR). En este modo, el procesador tiene siempre el nivel de acceso *privilegiado*.
 + **Thread mode**: Cuando se está ejecutando código de aplicación. En este modo, el procesador puede estar tanto con nivel de acceso *privilegiado* como *no privilegiado*. El nivel de acceso es controlado por un registro especial llamado *CONTROL*.  

Estando en *privileged Thread mode*, el software puede conmutar hacia *unprivileged Thread mode*, pero luego no puede conmutar nuevamente hacia *privileged*. Si esto es necesario, la conmutación nuevamente hacia *privileged* debe hacerse usando una excepción (e.g. una ISR).
## 7. ¿Qué se entiende por modelo de registros ortogonal? Dé un ejemplo.
Se dice un microcontrolador posee arquitectura ortogonal cuando las instrucciones pueden utilizar cualquier elemento de la arquitectura como fuente o destino. Es decir, el tipo de instrucción y el modo de direccionamiento varían de manera independiente. Esto trae como ventaja el ahorro significativo en el número de instrucciones, ya que no se requiere una instrucción específica para utilizar un registro específico, por lo que hay menos superposición de la funcionalidad de la instrucción.  
Un ejemplo de ortogonalidad puede ser el caso de los microcontroladores PIC frente a otros microcontroladores tradicionales del momento. En microcontroladores tradicionales todas las operaciones se realizaban sobre el acumulador, ya que la salida del mismo esta conectada a una de las entradas de la ALU, siendo siempre uno de los operandos de la operación. El microntrolador PIC agregaba un registro llamado *work register* a la salida de la ALU, pudiéndose guardar el resultado tanto en la memoria de datos como en el registro W. La ventaja aquí es que cualquier instrucción que opere con la memoria puede dejarse en la misma posición de memoria o en el registro W.
## 8. ¿Qué ventajas presenta el uso de intrucciones de ejecución condicional (IT)? Dé un ejemplo.
La principal ventaja de las instrucciones IT es la reducción del tamaño del código, ya que una instrucción IT puede encadenar hasta 4 instrucciones condicionales subsecuentes. Otra gran ventaja es que permite controlar el flujo de programa de manera más sencilla, a diferencia de una instrucción de salto condicional.
## 9. Describa brevemente las excepciones más prioritarias (reset, NMI, Hardfault).
Las tres excepciones más prioritarias son:
 + Reset.
 + NMI.
 + HardFault.  

Las tres tienen prioridades negativas, siendo *Reset* la de mayor prioridad (-3), le sigue *NMI* (-2) y finalmente *HardFault* (-1). El hecho de que sean negativas indican de alguna manera que no son configurables, ya que la configuracion de prioridades arranca desde 0.
La excepción de *Reset* se dispara cuando una de los tres tipos de reset tiene lugar (*Power On Reset*, *System Reset*, *Processor Reset*). 
Las excepciones *NMI* (*Non-Maskable Interrupt*) suelen ser disparadas por *watchdogs* o detectores de *brownout*. En el caso del *Reset* y el *HardFault*, quien dispara estas excepciones es el mismo núcleo del procesador y se las llama excepciones del sistema.
Las excepciones *HardFault* son disparadas cuando existe un evento de falla o *fault event*, como la ejecución de una instrucción indefinida, o cuando el bus de sistema retorna error en respuesta a un acceso a memoria (direcciones de memoria indefinidas). Por defecto, las excepciones *Bus Fault*, *Usage Fault*, *Memory Management Fault*)  están desactivadas y todos los eventos de falla disparan la excepción *HardFault*, la cual está siempre activada. El programador puede configurar las tres excepciones por separado para que sean manejadas de manera diferente. 
## 10. Describa las funciones principales de la pila. ¿Cómo resuelve la arquitectura el llamado a funciones y su retorno?
La mayoría de las arquitecturas de procesadores necesitan una memoria de pila (*stack memory*) y los Cortex-M no son la excepción. Para operar sobre la pila, se necesita un puntero de pila (*stack pointer* o SP) que en los ARM Cortex-M es el registro R13. Este registro puede conmutar entre dos tipos de punteros, el MSP (*main stack pointer*) y el PSP (*process stack pointer*). El uso del MSP está reservado para el modo *Handler*, mientras que el uso del PSP está reservado para el modo *Thread*.
La pila tiene una estructura de datos tipo LIFO (*Last-In-First-Out*). Los procesadores ARM tienen una instrucción PUSH para almacenar datos en la pila, y una instrucción POP para tomar datos de la pila.  
Algunos de los usos de la pila son:
 + Cuando un programa ejecuta una función que utiliza los registros del *register bank*, los datos del programa que llamo a la función son almacenados temporalmente en la pila para ser luego restaurados al final de la ejecución de la función y así no perder sus datos.
 + Almacenamiento de variables locales.
 + Almacenamiento del estado del procesador y los valores de los registros en el caso de una excepción (e.g. una interrupción).
 + Almacenamiento de los parámetros de funciones y subrutinas, siguiendo el *Procedure Call Standard*. Del parámetro 1 a 4 se almacenan en los registros R0 a R3. A partir del quinto parámetro, éstos se almacenan en el stack.  

Los Cortex-M utilizan un modelo de pila llamado *full-descending stack*. Cuando el procesador arranca, el SP se sitúa al final del espacio de memoria reservado para la pila.  
Para cada instrucción PUSH, el procesador primero decrementa el SP y luego almacena el valor en la dirección de memoria apuntada por el SP. Durante las operaciones, el SP apunta a la posición de memoria donde el último dato fue "empujado" (*pushed*) hacia la pila.  
Para cada instrucción POP, se lee el valor de la posición de memoria apuntada por el SP y luego el valor del SP se incrementa automáticamente.  
El uso más común de las instrucciones PUSH y POP es el de almacenar el contenido del banco de registros del procesador cuando se llama a una función o subrutina. Al inicio de la llamada el contenido de algunos registros se guardan en la pila mediante PUSH, y luego cuando finaliza la llamada se restauran dichos registros a sus valores originales mediante POP.
## 11. Describa la secuencia de reset del microprocesador.
Luego del reset y antes de que el procesador comience con la ejecución del programa, los procesadores Cortex-M lees las dos primeras palabras (una palabra son 2 bytes, por lo tanto dos palabras son 4 bytes o 32 bits) de la memoria. El principio del espacio de la memoria contiene la tabla de vectores o *vector table*, y las dos primeras palabras de dicha tabla corresponden al valor inicial del MSP y al vector de reset (*reset vector*), el cual es la dirección de inicio del *reset handler*. Luego de que estas dos palabras son leídas, entonces el procesador configura el MSP y el PC con dichos valores. El "seteo" del MSP es necesario porque algunas excepciones como NMI o HardFault pueden ocurrir justo luego del reset. La mayoría de los códigos de startup en los entornos de desarrollo en C también actualizan el valor del MSP antes de entrar en el programa principal *main()*. Esta inicialización de la pila en dos pasos permite a un microcontrolador con memoria externa usar dicha memoria externa para la pila.
## 12. ¿Qué entiende por “core peripherals”? ¿Qué diferencia existe entre estos y el resto de los periféricos?
Los llamados "core peripherals" son aquellos componentes que hacen al procesador pero que no son el núcleo del mismo, sino que le brindan soporte para cumplir con la funcionalidad del procesador. Algunos de ellos son:
 + NVIC (*Nested Vector Interrupt Controller*).
 + Memoria SRAM (*Static Random Access Memory*).
 + Memoria flash.
 + *SysTick timer*.
 + TPU (Tighly Coupled Memory) en M1 y M7.
 + MPU (Memory Protection Unit) en M0+, M3, M4 y M7.
 + Banco de registros (*Register Bank*).
 + SCB (*System Control Block*).  

La diferencia entre estos y otros periféricos es los *core peripherals* corresponden a los periféricos del procesador, mientras que los periféricos corresponden de manera genérica a los periféricos de los microcontroladores, como por ejemplo una UART, un I2C, un SPI, los GPIO del microcontrolador y cualquier componente externo al procesador.
## 13. ¿Cómo se implementan las prioridades de las interrupciones? Dé un ejemplo.
Los Cortex-M3 y Cortex-M4 tienen un controlador de interrupciones configurable que puede soportar hasta 240 interrupciones vectorizadas y niveles de prioridades comenzando con 8 hasta 256. La asignación de las prioridades sirven para reducir el tiempo de respuesta de la aplicación. Por ejemplo, periféricos que son críticos pueden tener asignado interrupciones con alta prioridad, entonces si la interrupción se dispara cuando el procesador está atendiendo otra interrupción de menor prioridad, dicha interrupción de menor prioridad es suspendida, permitiendo a la interrupción de mayor prioridad ser atendida inmediatamente.  
La configuración de estas prioridades se logra programando el NVIC, activando la interrupción y asignandole un nivel de prioridad. Los registros del NVIC están mapeados en memoria y su localización es fija y su modelo es consistente entre todos los Cortex-M. La manera estándar de acceder a ellos es a través de las definiciones y las APIs de la librería CMSIS-Core.
## 14. ¿Qué es el CMSIS? ¿Qué función cumple? ¿Quién lo provee? ¿Qué ventajas aporta?
CMSIS (Cortex Microcontroller Software Interface Standard) es un estándar desarrollado por ARM para permitir a los fabricantes de microncontroladores y desarrolladores de software usar una infraestructura de software consistente para desarrollar soluciones en los microcontroladores Cortex-M.  
Existen numerosos fabricantes de microntroladores, FPGAs, ASICs, depuradores, compiladores, sistemas operativos y middlewares y la función de CMSIS es proveer a todos ellos un estándar en común sobre el cual basar sus desarrollos y así asegurar la interoperabilidad entre ellos.  
Su proveedor es ARM y algunas de las ventajas que aporta son:
 + Reutilización del software.
 + Compatibilidad del software.
 + Independencia del *toolchain*.
## 15. Cuando ocurre una interrupción, asumiendo que está habilitada ¿Cómo opera el microprocesador para atender a la subrutina correspondiente? Explique con un ejemplo.
Una interrupción es un tipo de excepción del microcontrolador, y por lo tanto sigue las mismas secuencias de las excepciones:
 + **Secuencia de entrada**:
    - Se ejecuta un *push* de los registros del microcontrolador, incluso la dirección apuntada por el *stack pointer* (PSP o MSP) antes de que ocurra la excepción.
    - Se ejecuta un *fetch* del vector de excepción (en el caso de interrupciones, corresponde a la dirección de inicio de la ISR).
    - Una vez determinada la dirección de inicio de la ISR, se ejecuta un *fetch* de las instrucciones de la ISR.
    - Se actualizan los registros del NVIC y del *Core*, como el PSR (*Program Status Register*), el LR (*Link Register*), el PC (*Program Counter*) y el SP (*Stack Pointer*). Según qué *stack* se estaba usando, el SP se ajustará al PSP o al MSP. El PC se ajusta al valor de inicio de la ISR. El LR se ajusta con un valor especial llamado *EXC_RETURN*, el cual es un valor de 32 bits cuyos 27 MSB se ajustan a 1 y los 5 LSB contienen información acerca de la secuencia de la excepción (por ejemplo, qué *stack* se usó para hacer *push* de los registros del procesador).
 + **Ejecución de la ISR/*exception handler* de la excepción**:
    - El procesador ha entrado a modo *Handler*, en el cual el SP es el MSP y el nivel de acceso es privilegiado.
    - En esta etapa pueden llegar otras interrupciones/excepciones de mayor o menor prioridad. Si la nueva interrupción es de menor prioridad quedará en el estado *pending* y será atendida cuando la ISR actual termine. En caso de ser una interrupción/excepción de mayor prioridad, ésta será aceptada, la ISR actual suspendida y la ISR/*exception handler* de mayor prioridad ejecutada.
    - Al final de la ejecución de la ISR, el PC se carga con el valor del LR (*EXC_RETURN*), disparando el mecanismo de retorno.
 + **Secuencia de retorno**:
    - Se ejecuta un *pop* de los valores de los registros previamente apilados durante la secuencia de entrada y se restauran nuevamente al banco de registros.
    - Se actualizan los registros del NVIC y del *Core*.
    - Se comienza a hacer *fetch* de las instrucciones del programa previamente interrumpido.
## 16. ¿Cómo cambia la operación de stacking al utilizar la unidad de punto flotante?
De acuerdo con el PCS, los registros R0-R3, R12, LR y PSR se conocen como "registros de almacenamiento de llamador" (*caller saved registers*) y los registros R4-R11 se conocen como "registros de almacenamiento del destinatario" (*callee saved registers*).  
En cuanto a los *caller saved registers*, el código de programa que llama a una subrutina o función necesita guardar el contenido de estos registros en el *stack* antes de dicha llamada porque dichos valores son frecuentemente necesarios luego de la llamada a subrutina o función para restaurar el estado del código de programa. En cuanto a los *callee saved registers*, la subrutina o función debe restaurar el valor de dichos registros a su valor original antes de salir de la función.  
EL mismo PCS aplica para operaciones con FPU, donde:
 + S0-S15 son los *caller saved registers*.
 + S16-S31 son los  *callee saved registers*.  

Estos registros se encuentran dentro de la FPU, y no del Core del procesador (ARM Cortex-M4).
## 17. Explique las características avanzadas de atención a interrupciones: tail chaining y late arrival.
+ **Tail chaining:** Cuando ocurre una excepción/interrupción y el procesador está atendiendo otra excepción de igual o mayor prioridad, dicha excepción/interrupción entrará en el estado *pending*. Cuando el procesador termina la ejecución del manejador de la excepción/interrupción (*exception handler* o ISR) que tenía lugar, puede continuar con el procesamiento de la excepción/interrupción pendiente. En lugar de restaurar los registros desde el *stack* para luego nuevamente apilarlos, el procesador saltea estos pasos y directamente entra en el *exception handler*/ISR de la excepción/interrupción pendiente lo antes posible, reduciendo considerablemente el tiempo entre dos *exception handlers*. El *tail chaining* también hace al sistema más eficiente, ya que reduce el número de accesos al *stack*, y cada transferencia de memoria consume energía.
+ **Late arrival:** Cuando ocurre una excepción/interrupción, el procesador acepta la solicitud de excepción/interrupción y comienza la operación de "apilar" (*stacking*). Si durante este momento otra excepción/interrupción de mayor prioridad tiene lugar, la excepción/interrupción de mayor prioridad de "llegada tardía" (*late arrival*) será atendida primero.
## 18. ¿Qué es el systick? ¿Por qué puede afirmarse que su implementación favorece la portabilidad de los sistemas operativos embebidos?
Los procesadores Cortex-M poseen un pequeño temporizador (*timer*) integrado llamado *SysTick timer* (de *System Tick timer*). Está integrado en la NVIC del procesador, de manera que pueda generar la excepción *SysTick* (*SysTick exception*). El SysTick es un contador de 24 bits decremental, y puede correr tanto a la frecuencia del procesador como con otra fuente de referencia, normalmente *on-chip*.  
El *SysTick timer* es de suma importancia para sistemas operativos embebidos, debido a que una interrupción periódica es mandatoria para asegurar que el *kernel* sea invocado de manera precisa y regular para, por ejemplo, poder gestionar la ejecución de tareas y el cambio de contexto.  
La portabilidad de dichos sistemas operativos embebidos se ve favorecida por el *SysTick timer*, ya que al está integrado dentro del procesador, siendo el *SysTick timer* el mismo entre distintos microcontroladores cuyos procesadores sean un Cortex-M3/M4. Es decir, un OS usado en un microcontrolador con Cortex-M3/M4 puede ser reutilizado por otro microncontrolador con Cortex-M3/M4.
## 19. ¿Qué funciones cumple la unidad de protección de memoria (MPU)?
La MPU es una funcionalidad opcional que los procesadores Cortex-M3/M4 soportan, es decir, algunos microcontroladores la incluyen y otros no.  
Es un dispositivo programable que se utiliza para definir los permisos de acceso (acceso privilegiado o acceso total) y atributos (búfer o caché) para diferentes regiones de memoria.
La función de la MPU es hacer a un sistema embebido más robusto y más seguro:  
+ Evita que tareas de usuario corrompan la pila de otras tareas o del propio *kernel*.
+ Evita que tareas con acceso no privilegiado accedan a ciertos periféricos que son críticos para asegurar la fiabilidad del sistema.
+ Evita ataques del tipo *code injection* si se define el espacio de la SRAM como no ejecutable (*eXecute Never*, XN).
## 20. ¿Cuántas regiones pueden configurarse como máximo? ¿Qué ocurre en caso de haber solapamientos de las regiones? ¿Qué ocurre con las zonas de memoria no cubiertas por las regiones definidas?
La MPU en los Cortex-M3/M4 soportan hasta 8 regiones programables de memoria.  
En caso de solapamiento de regiones, los permisos y atributos utilizados por la localización de memoria afectada serán los de la región cuya numeración sea la más alta.  
El acceso a zonas de memoria que no son parte de las regiones definidas causará una violación de las reglas de acceso definidas por la MPU, y disparará un *MemManage fault* (*Memory Management Fault*) si la excepción está activada. En su defecto, disparará una *Hard Fault*.
## 21. ¿Para qué se suele utilizar la excepción PendSV? ¿Cómo se relaciona su uso con el resto de las excepciones? Dé un ejemplo.
La excepción PendSV (*Pended Service Call*) se suele utilizar para la operación de cambio de contexto de los sistemas operativos, ya que evita que el *SysTick* se "apropie" (*preempt*) del contexto cuando una interrupción tuvo lugar justo antes, disparando incluso la excepción *Usage fault* (ingresa al modo Thread cuando una interrupción está activa). Lo que hace el PendSV es retrasar el cambio de contexto hasta que todos los manejadores de las interrupciones hayan completado su ejecución. Para lograr esto, el PendSV se programa para que sea la excepción de menor prioridad (es una excepción con nivel de prioridad programable).  
Por ejemplo, se relaciona con la excepción SVC cuando existe un cambio de tarea en un OS: una tarea A llama a SVC, el OS atiende la solicitud de SVC, y pone el estado de PendSV en *pending*. Cuando la ejecución de SVC se completa, inmediatamente entra PendSV y ejecuta el cambio de contexto. Al finalizar PendSV, se regresa al estado Thread y se ejecuta la tarea B.  
Lo mismo sucede si una interrupción tiene lugar y antes de que se complete la ejecución de su ISR el *SysTick timer* se apropia de la CPU: el OS al atender el *SysTick* pone el estado de PendSV en *pending*, haciendo que cuando la excepción del *SysTick* termine, se retorne a la ISR. Finalmente cuando la ISR se completa, el PendSV tiene lugar y realiza las operaciones de cambio de contexto.
## 22. ¿Para qué se suele utilizar la excepción SVC? Expliquelo dentro de un marco de un sistema operativo embebido.
La excepción SVC (*Supervisor Call*) se dispara mediante la llamada de la instrucción SVC. Es una interrupción disparada por software, como las generadas por la escritura del registro STIR (*Software Trigger Interrupt Register*) de la NVIC, pero el SVC se diferencia de la escritura de STIR por generar una interrupción precisa, i.e. que cuando se escribe en STIR, hasta que la interrupción tiene lugar, varias instrucciones pudieron ser ejecutadas, en cambio, la interrupción SVC tiene lugar inmediatamente después de la ejecución de la instrucción SVC.  
La excepción SVC suele ser utilizada en los OS embebidos para comunicar las tareas con el *kernel*, aprovechando el valor requerido por la instrucción SVC. El manejador de SVC puede luego extraer dicho valor y ejecutar una lógica de decisión de que acción ejecutar. En otras palabras, el SVC puede ser usado por las tareas como una API para acceder a recursos del sistema o ejecutar un cambio de contexto.
# ISA
-----
## 1. ¿Qué son los sufijos y para qué se los utiliza? Dé un ejemplo.
Los sufijos pueden entenderse como un modificador para algunas instrucciones. Como su nombre lo indica, se colocan inmediatamente al final del mnemónico.  
Existen tres tipos principales de sufijos:  
+ **Sufijo S**: Las instrucciones de procesamiento de datos pueden opcionalmente actualizar las banderas del registro APSR. Un ejemplo, en la sintáxis del UAL, sería: MOVS R0, R1 (mueve R1 a R0 y actualiza el APSR).
+ **Sufijos de ejecución condicional**: Se utilizan para controlar el flujo del programa mediante saltos condicionales. Algunos ejemplos comunes de estos sufijos son EQ (*equal*), NE (*not equal*), LT (*less than*), GT (*greater than*), entre otros. Un ejemplo en UAL sería: BEQ label (salta hacia la etiqueta "label" si la instrucción anterior resulta igual o no).
+ **Sufijos de precisión**: Se utilizan en las instruciones de procesamiento de datos para indicar cuantos bits de precisión se deben utilizar en la operación. Algunos ejemplos son .N (de *narrow*, 16 bits) y .W (*wide*, 32 bits). En *assembly* de Cortex-M, existen 3 tipos de datos, *byte* (8 bits), *halfword* (16 bits) y *word* (32 bits). El sufijo H es un "alias" del sufijo .N. Un ejemplo de utilización del sufijo en UAL sería: LDRH R4,R3 (cargar media palabra, 16 bits, del registro R3 en el registro R4.
## 2. ¿Para qué se utiliza el sufijo ‘s’? Dé un ejemplo.
## 3. ¿Qué utilidad tiene la implementación de instrucciones de aritmética saturada? Dé un ejemplo con operaciones con datos de 8 bits.
## 4. Describa brevemente la interfaz entre assembler y C ¿Cómo se reciben los argumentos de las funciones? ¿Cómo se devuelve el resultado? ¿Qué registros deben guardarse en la pila antes de ser modificados?
## 5. ¿Qué es una instrucción SIMD? ¿En qué se aplican y que ventajas reporta su uso? Dé un ejemplo.
