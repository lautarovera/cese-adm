# Preguntas orientadoras
1. Los ARM Cortex-M son procesadores RISC de 32 bits de alta eficiencia debido a su direccionamiento de 32 bits y por utilizar un set de instrucciones con alta densidad de codigo.
- M0 y M0+ son procesadores de bajo consumo, orientado a electronica de consumo. La inclusion del SysTick timer es opcional, por lo que no todos soportan directamente el uso de RTOS. Su arquitectura de memoria es Von Neumann, razon por la cual son mas baratos pero tambien con menos poder de procesamiento. La arquitectura ARM es la ARMv6-M
- M1 tiene las mismas caracteristicas que M0 y M0+ y ademas la posibilidad de incluir TCM (Tightly-Coupled Memory). La principal diferencia radica en que su licencia IP esta orientada para su uso con FPGAs, donde el TCM cobra mayor sentido.
- M3, M4 y M7 son procesadores de mayor capacidad de procesamiento, que incluyen siempre SysTick timer, lo que permite el soporte de RTOS. Son de arquitectura de memoria Harvard, siendo mas costosos pero con mayor poder de procesamiento. Su arquitectura ARM es ARMv7-M para el caso del M3, y ARMv7E-M para el caso del M4 y M7. Esta diferencia de arquitectura ARM del M3 hace que no ofrezca soporte de extensiones DSP y FPU. M4 y M7 soportan DSP, siendo la FPU opcional. Finalmente, el M7 puede incluir tambien el uso de memoria cache y de TCM.
# Cortex M
1. 
