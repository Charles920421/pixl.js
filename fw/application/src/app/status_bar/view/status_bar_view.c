#include "status_bar_view.h"
#include "bat.h"
#include "app_status_bar.h"

static void chrg_callback(void) {
    mui_update(mui());
}

static void status_bar_view_on_draw(mui_view_t *p_view, mui_canvas_t *p_canvas) {
    mui_canvas_set_font(p_canvas, u8g2_font_siji_t_6x10);

    // 添加"我"字
    mui_canvas_set_font(p_canvas, u8g2_font_wqy12_t_chinese);  // 切换到中文字体
    mui_canvas_draw_str(p_canvas, 20, 8, "我");  // 在坐标(20,8)处显示"我"
    mui_canvas_set_font(p_canvas, u8g2_font_siji_t_6x10);  // 切换回图标字体

    if (get_stats()) {
        mui_canvas_draw_glyph(p_canvas, 100, 8, 0xe09e);
    }

    mui_canvas_draw_glyph(p_canvas, 0, 10, 0xe002);

    uint8_t bt = bat_get_level();
    mui_canvas_draw_glyph(p_canvas, 110, 8, 0xe24c + bt);
}

static void status_bar_view_on_input(mui_view_t *p_view, mui_input_event_t *event) {}

static void status_bar_view_on_enter(mui_view_t *p_view) {}

static void status_bar_view_on_exit(mui_view_t *p_view) {}

status_bar_view_t *status_bar_view_create() {
    status_bar_view_t *p_status_bar_view = mui_mem_malloc(sizeof(status_bar_view_t));

    mui_view_t *p_view = mui_view_create();
    p_view->user_data = p_status_bar_view;
    p_view->draw_cb = status_bar_view_on_draw;
    p_view->input_cb = status_bar_view_on_input;
    p_view->enter_cb = status_bar_view_on_enter;
    p_view->exit_cb = status_bar_view_on_exit;

    chrg_set_callback(chrg_callback);

    p_status_bar_view->p_view = p_view;

    return p_status_bar_view;
}
void status_bar_view_free(status_bar_view_t *p_view) {
    mui_view_free(p_view->p_view);
    mui_mem_free(p_view);
}
mui_view_t *status_bar_view_get_view(status_bar_view_t *p_view) { return p_view->p_view; }
