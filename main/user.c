#include "user.h"
#include "button.h"
#include "effects.h"

static const char *TAG = "USER";

void btn_short_press_1_cb();
void btn_short_press_2_cb();
void btn_short_press_3_cb();
void btn_hold_release_cb();
void btn_hold_only_cb();


static button_cb *short_pressed_cb;
static button_handle_t btn_h;

void user_setup(void *args)
{
    ESP_LOGW(TAG, LOG_FMT() );

    btn_h = configure_push_button(USER_BTN_GPIO, BUTTON_ACTIVE_LOW);
    if (btn_h) 
    {
        // регистрируем коллбек короткого нажатия
        
        short_pressed_cb = calloc(MAX_SHORT_PRESSED_COUNT, sizeof(button_cb));
        
        // заполним массив указателями на функции
        short_pressed_cb[0] = &btn_short_press_1_cb;
        short_pressed_cb[1] = &btn_short_press_2_cb;
        short_pressed_cb[2] = &btn_short_press_3_cb;

        button_set_on_presscount_cb(btn_h, USER_BTN_SHORT_PRESS_TIME, MAX_SHORT_PRESSED_COUNT, short_pressed_cb, NULL);
        // сработает только после отпускания через указанное время
        button_add_on_release_cb(btn_h, BTN_HOLD_AND_RELEASE_SEC, btn_hold_release_cb, NULL);
        
        // сработает при удержании более Х сек, не зависит от отпускания
        button_add_on_press_cb(btn_h, BTN_HOLD_SEC, btn_hold_only_cb, NULL);        
    }

}

void user_http_init(void *args)
{
    // функция вызывается после user_setup и старта webserver'a
    ESP_LOGW(TAG, LOG_FMT() );

    // ledcontrol_http_add_group(ledc_h, "RGB Controller", 1, 5);
    // ledcontrol_http_add_group(ledc_h, "Белая подсветка", 2, 6);

    // пример как вынести некоторые каналы в отдельную группу
    // поставил каналу 3 (белый) группу 2
    //ledcontrol_channel_set_group(ch[3], 2);
    // создадим новую группу 2 с именем Белая подсветка
    //ledcontrol_http_add_group(ledc_h, "Белая подсветка", 2, 6);


}

// функция вызывается после user_setup и старта mqtt
// в этой функции можно зарегистрировать свои кастомные колбеки на отправку и получение данных
void user_mqtt_init(void *args)
{
    ESP_LOGW(TAG, LOG_FMT() );

    //mqtt_add_periodic_publish_callback( "test1", test1, NULL);
    //mqtt_add_periodic_publish_callback( "test2", test2, NULL);

    //mqtt_add_receive_callback("recv1", 1, test_recv1, NULL);
    //mqtt_add_receive_callback("recv2", 1, test_recv2, NULL);


}

// функция вызывает в основном цикле каждую секунду
void user_loop(uint32_t sec)
{
    //int level = gpio_get_level(GPIO_NUM_4);
    //ESP_LOGW( TAG, "gpio4 = %d", level);

   
}

#ifdef CONFIG_USER_WEB_PRINT
// функция вывод данные в пользовательском блоке на главной
void user_web_main(httpd_req_t *req)
{
    ESP_LOGW(TAG, LOG_FMT() );

    //httpd_resp_sendstr_chunk(req, "Hello!");
    //USER_WEB_PRINT("Hello User!");

    //char data[20];
    //sprintf(data, "<br>Temp: %2.1f", sht21_get_temp());
    //USER_WEB_PRINT(data);

}
#endif 

#ifdef CONFIG_USER_WEB_CONFIG
void user_web_options(httpd_req_t *req)
{
    ESP_LOGW(TAG, LOG_FMT() );
       
    //USER_WEB_PRINT("Hello User Options!");


}


void user_process_param(httpd_req_t *req, void *args)
{
    ESP_LOGW(TAG, LOG_FMT() );
    //ESP_LOGW(TAG, "Hello User process param!");
}
#endif

//mqtt_add_periodic_publish_callback( const char *topic, func_mqtt_send_cb fn_cb);
// void mqtt_add_receive_callback( const char *topic, func_mqtt_recv_cb fn_cb); -
/*
void test1(char **buf, void *args) {
    static uint32_t cnt = 0;
    itoa(cnt++, *buf, 10);
}

void test2(char **buf, void *args){
    static uint32_t cnt = 1000000;
    sprintf(*buf, "%d", cnt);
    cnt -= 10;
    if ( cnt == 0) cnt = 1000000;
}

void test_recv1(char *buf, void *args)
{
    ESP_LOGI(TAG, "received topic 'recv1' with data: %s", buf);
}

void test_recv2(char *buf, void *args)
{
    ESP_LOGI(TAG, "received topic 'recv2' with data: %s", buf);
}
*/

void btn_short_press_1_cb()
{
    ESP_LOGW(TAG, LOG_FMT() );
    effects_next_effect();
}

void btn_short_press_2_cb()
{
    ESP_LOGW(TAG, LOG_FMT() );
    effects_prev_effect();
}

void btn_short_press_3_cb()
{
    ESP_LOGW(TAG, LOG_FMT() );
        effects_set_effect_by_name("rnd");
}

void btn_hold_release_cb()
{
    ESP_LOGW(TAG, LOG_FMT() );
    effects_set_effect_by_name("wheel");
}

void btn_hold_only_cb()
{
    ESP_LOGW(TAG, LOG_FMT() );
    effects_stop_effect();
    // reset color - off
    rgb_ledc->set_color_int(0);
}
