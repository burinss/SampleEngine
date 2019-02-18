
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"
static int
overview(struct nk_context *ctx){
	/* window flags */
	static int show_menu = nk_true;
	static int titlebar = nk_true;
	static int border = nk_true;
	static int resize = nk_true;
	static int movable = nk_true;
	static int no_scrollbar = nk_false;
	static int scale_left = nk_false;
	static nk_flags window_flags = 0;
	static int minimizable = nk_true;

	/* popups */
	static enum nk_style_header_align header_align = NK_HEADER_RIGHT;
	static int show_app_about = nk_false;

	/* window flags */
	window_flags = 0;
	ctx->style.window.header.align = header_align;
	if (border) window_flags |= NK_WINDOW_BORDER;
	if (resize) window_flags |= NK_WINDOW_SCALABLE;
	if (movable) window_flags |= NK_WINDOW_MOVABLE;
	if (no_scrollbar) window_flags |= NK_WINDOW_NO_SCROLLBAR;
	if (scale_left) window_flags |= NK_WINDOW_SCALE_LEFT;
	if (minimizable) window_flags |= NK_WINDOW_MINIMIZABLE;

	if (nk_begin(ctx, "Overview", nk_rect(10, 10, 400, 600), window_flags))
	{
		if (show_menu)
		{
			/* menubar */
			enum menu_states { MENU_DEFAULT, MENU_WINDOWS };
			static nk_size mprog = 60;
			static int mslider = 10;
			static int mcheck = nk_true;
			nk_menubar_begin(ctx);

			/* menu #1 */
			nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
			nk_layout_row_push(ctx, 45);
			if (nk_menu_begin_label(ctx, "MENU", NK_TEXT_LEFT, nk_vec2(120, 200)))
			{
				static size_t prog = 40;
				static int slider = 10;
				static int check = nk_true;
				nk_layout_row_dynamic(ctx, 25, 1);
				if (nk_menu_item_label(ctx, "Hide", NK_TEXT_LEFT))
					show_menu = nk_false;
				if (nk_menu_item_label(ctx, "About", NK_TEXT_LEFT))
					show_app_about = nk_true;
				nk_progress(ctx, &prog, 100, NK_MODIFIABLE);
				nk_slider_int(ctx, 0, &slider, 16, 1);
				nk_checkbox_label(ctx, "check", &check);
				nk_menu_end(ctx);
			}
			/* menu widgets */
			nk_layout_row_push(ctx, 70);
			nk_progress(ctx, &mprog, 100, NK_MODIFIABLE);
			nk_slider_int(ctx, 0, &mslider, 16, 1);
			nk_checkbox_label(ctx, "check", &mcheck);
			nk_menubar_end(ctx);
		}
		nk_end(ctx);
		return !nk_window_is_closed(ctx, "Overview");
	}
}
