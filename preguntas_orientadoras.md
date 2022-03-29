# Preguntas orientadoras
1. Los ARM Cortex-M son procesadores RISC de 32 bits de alta eficiencia debido a su direccionamiento de 32 bits y por utilizar un set de instrucciones con alta densidad de codigo.
- M0 y M0+ son procesadores de bajo consumo, orientado a electronica de consumo. La inclusion del SysTick timer es opcional, por lo que no todos soportan directamente el uso de RTOS. Su arquitectura de memoria es Von Neumann, razon por la cual son mas baratos pero tambien con menos poder de procesamiento. La arquitectura ARM es la ARMv6-M
- M1 tiene las mismas caracteristicas que M0 y M0+ y ademas la posibilidad de incluir TCM (Tightly-Coupled Memory). La principal diferencia radica en que su licencia IP esta orientada para su uso con FPGAs, donde el TCM cobra mayor sentido.
- M3, M4 y M7 son procesadores de mayor capacidad de procesamiento, que incluyen siempre SysTick timer, lo que permite el soporte de RTOS. Son de arquitectura de memoria Harvard, siendo mas costosos pero con mayor poder de procesamiento. Su arquitectura ARM es ARMv7-M para el caso del M3, y ARMv7E-M para el caso del M4 y M7. Esta diferencia de arquitectura ARM del M3 hace que no ofrezca soporte de extensiones DSP y FPU. M4 y M7 soportan DSP, siendo la FPU opcional. Finalmente, el M7 puede incluir tambien el uso de memoria cache y de TCM.
# Cortex M
1. La principal diferencia entre las familias M0, M3 y M4 son las siguientes:
- Arquitectura de memoria: M0 posee arquitectura Von Neumann mientras que M3 y M4 poseen arquitectura Harvard, esto se traduce en un "trade off" entre el costo y el procesamiento, siendo los M0 mas baratos pero con menor procesamiento (los datos y las instrucciones usan el mismo bus), y los M3 y M4 mas caros pero con mayor procesamiento (buses dedicados para los datos y las instrucciones).
- Soporte de RTOS directo: los M3 y M4 ofrecen soporte para RTOS, razon por la cual estos incluyen siempre SysTick timer. Los M0 pueden incluirlo pero aun asi no llegan a soportar todas sus caracteristicas de manera directa.
- Soporte DSP y FPU: Solo el M4 incluye instrucciones para DSP, y puede llegar a incluir para FPU. Cuando incluyen FPU se los suele designar M4F.
2. A continuacion, se enumeran algunas de las caracteristicas que hacen de Thumb un ISA con alta densidad de codigo:
- Thumb es un subconjunto de instrucciones de longitud de 2 bytes (16 bits), en lugar del juego estandar de ARM que son de 4 bytes (32 bits). Esto hace que tenga mayor densidad de codigo, obteniendo incluso mejor rendimiento que un codigo de 32 bits cuando el ancho de bus de memoria es menor a 32 bits.
- En el caso de Thumb-2, permite a las instrucciones de 16-bit y las instrucciones de 32-bit de trabajar juntas, siendo compatibles sin tener que cambiar entre una u otra.
- Modos de acceso a memoria especiales para un acceso efectivo a memoria.
- Una simple instruccion puede manejar multiples accesos a memoria.
- En el caso de M3 y M4, soporte de instrucciones de division por hardware y "Multiply and Accumulate" (MAC).
- En el caso de M4, instrucciones "Single Instruction, Multiple Data" (SIMD).
