#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(led_app, LOG_LEVEL_INF);

#if !IS_ENABLED(CONFIG_LED_SUBSYSTEM)
#error "LED subsystem disabled"
#endif
//#define SLEEP_TIME_MS 1000

#define BLINK_TIME          CONFIG_BLINK_TIME_MS
#define LED_BRIGHTNESS      CONFIG_LED_BRIGHTNESS
#define LED_FADE            CONFIG_LED_FADE_DURATION

/* The devicetree node identifier for the "led0" alias. */


static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(app_led), gpios);
//static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);

/* Stack sizes */
#define STACK_SIZE   512
#define PRIORITY_LED0  5
#define PRIORITY_LED1  6

/* ---- Task: blink LED0 at 500ms ---- */
void task_led0(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1); ARG_UNUSED(p2); ARG_UNUSED(p3);

    if (!gpio_is_ready_dt(&led0))
    {
        return;
    }
    gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);

    while (1) 
    {
        gpio_pin_toggle_dt(&led0);
        k_msleep(BLINK_TIME);
        if (IS_ENABLED(CONFIG_LED_DEBUGGING)) 
        {
        LOG_INF("LED0 toggle at %d ms", BLINK_TIME);
        }
        if (IS_ENABLED(CONFIG_LED_CUSTOM_PATTERNS)) 
        {
         // Example: different pattern
        gpio_pin_toggle_dt(&led0);
         k_msleep(BLINK_TIME * 10);
        }
    }
}

/* ---- Task: blink LED1 at 200ms ---- */
/*void task_led1(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1); ARG_UNUSED(p2); ARG_UNUSED(p3);

    if (!gpio_is_ready_dt(&led1))
    {
        return;
    }

    gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);

    while (1) 
    {
        gpio_pin_toggle_dt(&led1);
        k_msleep(BLINK_TIME / 5);
        if (IS_ENABLED(CONFIG_LED_DEBUGGING))
        {
        LOG_INF("LED1 toggle at %d ms", BLINK_TIME);
        }
        if (IS_ENABLED(CONFIG_LED_CUSTOM_PATTERNS)) 
        {
         // Example: different pattern
        gpio_pin_toggle_dt(&led1);
         k_msleep(BLINK_TIME / 10);
        }
    }
}
*/
/* Static thread definitions — no main() needed to spawn these */
K_THREAD_DEFINE(led0_tid, STACK_SIZE, task_led0, NULL, NULL, NULL, PRIORITY_LED0, 0, 0);
//K_THREAD_DEFINE(led1_tid, STACK_SIZE, task_led1, NULL, NULL, NULL, PRIORITY_LED1, 0, 0);