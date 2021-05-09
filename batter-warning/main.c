#include <gtk/gtk.h>

struct app_layout_t {
    GtkWidget *m_main_window;
    GtkWidget *m_vbox; // 主窗口最底层的容器
} g_layout = {
    .m_main_window = NULL,
    .m_vbox = NULL,
};

GtkApplication *g_app = NULL;

void show_label(GApplication *app, gpointer user_data) {
    (void)app;
    (void)user_data;

    gchar str_win[] = "<span foreground='red' weight='bold' "
                      "font='40'>电池电量低, 请及时充电!!!</span>";
    GtkWidget *lbl = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(lbl), str_win);
    gtk_box_pack_start(GTK_BOX(g_layout.m_vbox), lbl, TRUE, TRUE, 0);
}

void accelerator_Q_pressed(void) { g_application_quit(G_APPLICATION(g_app)); }

void setup_accelerator(GApplication *app, gpointer user_data) {
    (void)app;
    (void)user_data;

    GClosure *closure =
        g_cclosure_new(G_CALLBACK(accelerator_Q_pressed), NULL, NULL);
    GtkAccelGroup *accel_group = gtk_accel_group_new();

    gtk_accel_group_connect(accel_group, GDK_KEY_Q, 0, 0, closure);
    gtk_window_add_accel_group(GTK_WINDOW(g_layout.m_main_window), accel_group);
}

void main_window_activate(GApplication *app, gpointer user_data) {
    (void)user_data;

    g_layout.m_main_window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(g_layout.m_main_window), "batter warning");
    // gtk_window_set_default_size(GTK_WINDOW(g_layout.m_main_window), 800,
    // 600);
    // gtk_window_set_keep_above(GTK_WINDOW(g_layout.m_main_window),
    // TRUE);
    gtk_window_fullscreen(GTK_WINDOW(g_layout.m_main_window));
    gtk_window_set_position(GTK_WINDOW(g_layout.m_main_window),
                            GTK_WIN_POS_CENTER | GTK_WIN_POS_CENTER_ON_PARENT);

    g_layout.m_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_container_add(GTK_CONTAINER(g_layout.m_main_window), g_layout.m_vbox);

    show_label(app, NULL);
    setup_accelerator(app, NULL);
    gtk_widget_show_all(g_layout.m_main_window);
}

int main(int argc, char **argv) {
    g_app = gtk_application_new("main.window", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(g_app, "activate", G_CALLBACK(main_window_activate), NULL);
    int status = g_application_run(G_APPLICATION(g_app), argc, argv);
    g_object_unref(g_app);
    return status;
}
