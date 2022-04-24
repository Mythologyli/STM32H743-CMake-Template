#include "lv_demos.h"

#include "main.h"

static void ta_event_cb(lv_event_t *e);

static lv_obj_t *kb;

void lv_example_textarea_2(void)
{
    /*Create the password box*/
    lv_obj_t *pwd_ta = lv_textarea_create(lv_scr_act());
    lv_textarea_set_password_mode(pwd_ta, true);
    lv_textarea_set_one_line(pwd_ta, true);
    lv_obj_set_width(pwd_ta, lv_pct(40));
    lv_obj_set_pos(pwd_ta, 5, 20);
    lv_obj_add_event_cb(pwd_ta, ta_event_cb, LV_EVENT_ALL, NULL);

    /*Create a label and position it above the text box*/
    lv_obj_t *pwd_label = lv_label_create(lv_scr_act());
    lv_label_set_text(pwd_label, "Password:");
    lv_obj_align_to(pwd_label, pwd_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

    /*Create the one-line mode text area*/
    lv_obj_t *text_ta = lv_textarea_create(lv_scr_act());
    lv_textarea_set_one_line(text_ta, true);
    lv_textarea_set_password_mode(text_ta, false);
    lv_obj_set_width(text_ta, lv_pct(40));
    lv_obj_add_event_cb(text_ta, ta_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_align(text_ta, LV_ALIGN_TOP_RIGHT, -5, 20);


    /*Create a label and position it above the text box*/
    lv_obj_t *oneline_label = lv_label_create(lv_scr_act());
    lv_label_set_text(oneline_label, "Text:");
    lv_obj_align_to(oneline_label, text_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

    /*Create a keyboard*/
    kb = lv_keyboard_create(lv_scr_act());
    lv_obj_set_size(kb, LV_HOR_RES, LV_VER_RES / 2);

    lv_keyboard_set_textarea(kb, pwd_ta); /*Focus it on one of the text areas to start*/
}

static void ta_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED)
    {
        /*Focus on the clicked text area*/
        if (kb != NULL) lv_keyboard_set_textarea(kb, ta);
    }

    else if (code == LV_EVENT_READY)
    {
        LV_LOG_USER("Ready, current text: %s", lv_textarea_get_text(ta));
    }
}

static void lv_test(void)
{
    static lv_style_t style_kaiti;
    lv_style_init(&style_kaiti);
    lv_style_set_text_font(&style_kaiti, &lv_font_kaiti_14);

    lv_obj_t *button = lv_btn_create(lv_scr_act());
    lv_obj_center(button);
    lv_obj_set_size(button, 150, 100);
    lv_obj_t *label = lv_label_create(button);
    lv_obj_center(label);
    lv_obj_add_style(label, &style_kaiti, 0);
    lv_label_set_text(label, "汉字显示测试\nButton");
}

void StartMainTask(void *argument)
{
    lv_init();
    lv_port_disp_init();

    // lv_test();
    // lv_demo_benchmark();
    // lv_demo_widgets();
    // lv_demo_stress();
    lv_example_textarea_2();

    for (;;)
    {
        osDelay(1);
    }
}
