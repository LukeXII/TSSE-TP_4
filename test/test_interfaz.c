#include "unity.h"
#include "interfaz_edfa.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_gpio.h"

/*

 Archivo de test para el subsistema "Interfaz EDFA" perteneciente
 al proyecto "Tester para amplificador optico"

 La interfaz del EDFA cuenta con:
 - 4 alarmas conectadas a GPIOs (salidas)
 - 3 señales de control conectadas a GPIOs (entradas)
 - 2 señales analogicas proporcionales a las potencias opticas de entrada y salida (0V a 3.3V)

 Los detalles sobre el funcionamiento de la interfaz se encuentran en el documento "Pruebas de Sistemas y de Aceptacion"

*/

void setUp(void)
{
    
}

// Prueba para setear la maxima potencia optica de salida
void test_setear_max_potencia_de_salida(void)
{
    setMaxOutputPower(30.0);
    TEST_ASSERT_FLOAT_WITHIN(1.0, 30.0, getMaxOutputPower());
}

// Prueba para setear la maxima potencia optica de salida saturando el valor
void test_setear_max_potencia_de_salida_fuera_de_rango(void)
{
    setMaxOutputPower(50.0);
    TEST_ASSERT_FLOAT_WITHIN(1.0, OUTPUT_POW_MAX_VALUE, getMaxOutputPower());
}

// Prueba para setear el rango de potencia optica de entrada
void test_setear_rango_valido_potencia_de_entrada(void)
{
    TEST_ASSERT_EQUAL(0, setInputPowerRange(-30.0, 0.0));
    TEST_ASSERT_FLOAT_WITHIN(1.0, 0.0, getMaxInputPower());
    TEST_ASSERT_FLOAT_WITHIN(1.0, -30.0, getMinInputPower());
}

// Prueba para setear un rango invertido de potencia optica de entrada
void test_setear_rango_invalido_potencia_de_entrada(void)
{
    TEST_ASSERT_EQUAL(-1, setInputPowerRange(-20.0, -30.0));
}

// Prueba para obtener un valor de potencia optica de entrada
void test_obtener_valor_potencia_de_entrada(void)
{
    float power = getInputPower();

    TEST_ASSERT_GREATER_THAN(INPUT_POW_MIN_VALUE, power);
    TEST_ASSERT_LESS_OR_EQUAL(INPUT_POW_MAX_VALUE, power);
}

// Prueba para obtener un valor de potencia optica de salida
void test_obtener_valor_potencia_de_salida(void)
{
    float power = getOutputPower();

    TEST_ASSERT_GREATER_THAN(0, power);
    TEST_ASSERT_LESS_OR_EQUAL(OUTPUT_POW_MAX_VALUE, power);
}
