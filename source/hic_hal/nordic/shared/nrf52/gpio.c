/**
 * @file    gpio.c
 * @brief   GPIO access functions for nrf52820 HIC
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2021, Arm Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gpio.h"

#include "IO_Config.h"

#if (defined(GPIO_LED_ACTIVE_STATE) && (GPIO_LED_ACTIVE_STATE == 1))
#define GPIO_LED_STATE(state) (state ? 1 : 0)
#else
#define GPIO_LED_STATE(state) (state ? 0 : 1)
#endif

void gpio_init(void)
{
#ifdef LED_PWR
    gpio_cfg_output(GPIO_REG(LED_PWR), GPIO_IDX(LED_PWR));
    gpio_write(GPIO_REG(LED_PWR), GPIO_IDX(LED_PWR), GPIO_LED_STATE(0));
#endif
#ifdef LED_CONNECTED
    gpio_cfg_output(GPIO_REG(LED_CONNECTED), GPIO_IDX(LED_CONNECTED));
#endif
#ifdef LED_RUNNING
    gpio_cfg_output(GPIO_REG(LED_RUNNING), GPIO_IDX(LED_RUNNING));
#endif
    gpio_cfg_output(GPIO_REG(LED_HID), GPIO_IDX(LED_HID));
    gpio_cfg_output(GPIO_REG(LED_MSC), GPIO_IDX(LED_MSC));
    gpio_cfg_output(GPIO_REG(LED_CDC), GPIO_IDX(LED_CDC));
#ifdef PIN_nRESET
    gpio_set(GPIO_REG(PIN_nRESET), GPIO_IDX(PIN_nRESET));
    gpio_cfg(GPIO_REG(PIN_nRESET), GPIO_IDX(PIN_nRESET),
             NRF_GPIO_PIN_DIR_OUTPUT, NRF_GPIO_PIN_INPUT_DISCONNECT,
             NRF_GPIO_PIN_NOPULL, NRF_GPIO_PIN_S0D1, NRF_GPIO_PIN_NOSENSE); // Standard '0', disconnect '1'
    gpio_set(GPIO_REG(PIN_nRESET), GPIO_IDX(PIN_nRESET));
#endif
#ifdef RESET_BUTTON
    gpio_cfg_input(GPIO_REG(RESET_BUTTON), GPIO_IDX(RESET_BUTTON), RESET_BUTTON_PULL);
#endif
#if defined(PIN_POWER)
    gpio_clear(GPIO_REG(PIN_POWER), GPIO_IDX(PIN_POWER));
    gpio_cfg(GPIO_REG(PIN_POWER), GPIO_IDX(PIN_POWER),
             NRF_GPIO_PIN_DIR_OUTPUT, NRF_GPIO_PIN_INPUT_DISCONNECT,
             NRF_GPIO_PIN_NOPULL, NRF_GPIO_PIN_S0S1, NRF_GPIO_PIN_NOSENSE);
    gpio_clear(GPIO_REG(PIN_POWER), GPIO_IDX(PIN_POWER));
#endif
#if defined(UART_TX_PIN)
    gpio_set(GPIO_REG(UART_TX_PIN), GPIO_IDX(UART_TX_PIN));
    gpio_cfg(GPIO_REG(UART_TX_PIN), GPIO_IDX(UART_TX_PIN),
             NRF_GPIO_PIN_DIR_OUTPUT, NRF_GPIO_PIN_INPUT_DISCONNECT,
             NRF_GPIO_PIN_NOPULL, NRF_GPIO_PIN_S0S1, NRF_GPIO_PIN_NOSENSE);
    gpio_set(GPIO_REG(UART_TX_PIN), GPIO_IDX(UART_TX_PIN));
#endif
#if defined(UART_RX_PIN)
    gpio_cfg(GPIO_REG(UART_RX_PIN), GPIO_IDX(UART_RX_PIN),
        NRF_GPIO_PIN_DIR_INPUT, NRF_GPIO_PIN_INPUT_CONNECT,
        NRF_GPIO_PIN_NOPULL, NRF_GPIO_PIN_S0S1, NRF_GPIO_PIN_NOSENSE);
#endif
}

void gpio_set_hid_led(gpio_led_state_t state)
{
    gpio_write(GPIO_REG(LED_HID), GPIO_IDX(LED_HID), GPIO_LED_STATE(state));
}

void gpio_set_cdc_led(gpio_led_state_t state)
{
    gpio_write(GPIO_REG(LED_CDC), GPIO_IDX(LED_CDC), GPIO_LED_STATE(state));
}

void gpio_set_msc_led(gpio_led_state_t state)
{
    gpio_write(GPIO_REG(LED_MSC), GPIO_IDX(LED_MSC), GPIO_LED_STATE(state));
}

uint8_t gpio_get_reset_btn_no_fwrd(void)
{
    return 0;
}

uint8_t gpio_get_reset_btn_fwrd(void)
{
#ifdef RESET_BUTTON
    return gpio_read(GPIO_REG(RESET_BUTTON), GPIO_IDX(RESET_BUTTON)) ? 0 : 1;
#else
    return 0;
#endif
}

void gpio_set_board_power(bool powerEnabled)
{
#if defined(PIN_POWER)
if (powerEnabled)
    gpio_set(GPIO_REG(PIN_POWER), GPIO_IDX(PIN_POWER));
else
    gpio_clear(GPIO_REG(PIN_POWER), GPIO_IDX(PIN_POWER));
#endif
}
