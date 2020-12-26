#include "user.h"
#include "button.h"

static const char *TAG = "USER";

void pressed1_cb();
void pressed2_cb();
void pressed3_cb();
void hold_2s_cb();
void hold_3s_cb();
void hold_10s_cb();

void user_setup(void *args)
{
    ESP_LOGW(TAG, LOG_FMT() );

    button_handle_t btn_g4_h = configure_push_button(GPIO_NUM_4, BUTTON_ACTIVE_LOW);
    if (btn_g4_h) 
    {
        // регистрируем коллбек короткого нажатия
        #define MAX_SHORT_PRESSED_COUNT 3
        button_cb *short_pressed_cb = calloc(MAX_SHORT_PRESSED_COUNT, sizeof(button_cb));
        // заполним массив указателями на функции
        short_pressed_cb[0] = &pressed1_cb;
        short_pressed_cb[1] = NULL; //&pressed2_cb; // NULL если не требуется обрабатывать 2-ое (n-Раз) нажатие
        short_pressed_cb[2] = &pressed3_cb;

        // 1..3 коротких нажатий в течение 500 мсек
        button_set_on_presscount_cb(btn_g4_h, 500, MAX_SHORT_PRESSED_COUNT, short_pressed_cb);

        // сработает при отпускании после 1 сек не зависимо сколько держали по времени
        #define BTN_HOLD_1_SEC 2
        button_add_on_release_cb(btn_g4_h, BTN_HOLD_1_SEC, hold_2s_cb, NULL);
        
        // сработает при удержании более 2 сек
        #define BTN_HOLD_2_SEC 3
        button_add_on_press_cb(btn_g4_h, BTN_HOLD_2_SEC, hold_3s_cb, NULL);        

        // сработает при удержании более 10 сек
        #define BTN_HOLD_10_SEC 10
        button_add_on_press_cb(btn_g4_h, BTN_HOLD_10_SEC, hold_10s_cb, NULL);
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
    ledcontrol_channel_set_group(ch[3], 2);
    // создадим новую группу 2 с именем Белая подсветка
    ledcontrol_http_add_group(ledc_h, "Белая подсветка", 2, 6);


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

void IRAM_ATTR pressed1_cb()
{
    ESP_LOGW(TAG, LOG_FMT() );
}

void IRAM_ATTR pressed2_cb()
{
    ESP_LOGW(TAG, LOG_FMT() );
}

void IRAM_ATTR pressed3_cb()
{
    ESP_LOGW(TAG, LOG_FMT() );
}

void hold_2s_cb()
{
    ESP_LOGW(TAG, LOG_FMT() );
}

void hold_3s_cb()
{
    ESP_LOGW(TAG, LOG_FMT() );
}

void hold_10s_cb()
{
    ESP_LOGW(TAG, LOG_FMT() );
}
