#include <gtk/gtk.h>

typedef struct _Contact {
	char name[100];
	char company[100];
	char phone[100];
	char email[100];
	char im[100];
} Contact;

Contact contacts[100];
int num_contacts = 0;

// 声明界面控件
GtkWidget* name_entry, * company_entry, * phone_entry, * email_entry, * im_entry;
GtkWidget* search_entry;
GtkWidget* contacts_view;
GtkWidget* window;

// 添加联系人
void add_contact(GtkWidget* widget, gpointer data) {
	// 获取用户输入的信息
	const gchar* name = gtk_entry_get_text(GTK_ENTRY(name_entry));
	const gchar* company = gtk_entry_get_text(GTK_ENTRY(company_entry));
	const gchar* phone = gtk_entry_get_text(GTK_ENTRY(phone_entry));
	const gchar* email = gtk_entry_get_text(GTK_ENTRY(email_entry));
	const gchar* im = gtk_entry_get_text(GTK_ENTRY(im_entry));

	// 将联系人添加到通讯录中
	Contact new_contact;
	strcpy(new_contact.name, name);
	strcpy(new_contact.company, company);
	strcpy(new_contact.phone, phone);
	strcpy(new_contact.email, email);
	strcpy(new_contact.im, im);

	contacts[num_contacts++] = new_contact;

	// 清空用户输入框
	gtk_entry_set_text(GTK_ENTRY(name_entry), "");
	gtk_entry_set_text(GTK_ENTRY(company_entry), "");
	gtk_entry_set_text(GTK_ENTRY(phone_entry), "");
	gtk_entry_set_text(GTK_ENTRY(email_entry), "");
	gtk_entry_set_text(GTK_ENTRY(im_entry), "");
}

// 删除联系人
void remove_contact(GtkWidget* widget, gpointer data) {
	GtkTreeModel* model;
	GtkTreeIter iter;

	// 获取选中的行
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(data), &model, &iter)) {
		// 从通讯录中删除该联系人
		gtk_tree_model_get(model, &iter, 0, &num, -1);

		for (int i = num; i < num_contacts - 1; i++) {
			contacts[i] = contacts[i + 1];
		}
		num_contacts--;

		// 刷新联系人列表
		gtk_tree_view_set_model(GTK_TREE_VIEW(contacts_view), GTK_TREE_MODEL(create_contacts_list()));
	}
}

// 创建联系人列表
GtkListStore* create_contacts_list() {
	GtkListStore* store;
	GtkTreeIter iter;

	// 创建联系人列表的列
	store = gtk_list_store_new(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	// 将联系人添加到列表中
	for (int i = 0; i < num_contacts; i++) {
		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, 0, contacts[i].name, 1, contacts[i].company, 2, contacts[i].phone, 3, contacts[i].email, 4, contacts[i].im, -1);
	}

	return store;
}

// 查找联系人
void search_contact(GtkWidget* widget, gpointer data) {
	const gchar* search_str = gtk_entry_get_text(GTK_ENTRY(search_entry));
	GtkTreeModel* model = gtk_tree_view_get_model(GTK_TREE_VIEW(contacts_view));
	GtkTreeIter iter;
	gboolean found = FALSE;

	// 在列表中查找联系人
	if (gtk_tree_model_get_iter_first(model, &iter)) {
		do {
			gchar* name, * company, * phone, * email, * im;
			gtk_tree_model_get(model, &iter, 0, &name, 1, &company, 2, &phone, 3, &email, 4, &im, -1);

			// 比较联系人信息和搜索字符串
			if (strstr(name, search_str) || strstr(company, search_str) || strstr(phone, search_str) || strstr(email, search_str) || strstr(im, search_str)) {
				found = TRUE;
				gtk_tree_selection_select_iter(GTK_TREE_SELECTION(data), &iter);
				break;
			}

			g_free(name);
			g_free(company);
			g_free(phone);
			g_free(email);
			g_free(im);
		} while (gtk_tree_model_iter_next(model, &iter));
	}

	// 如果没有找到联系人，显示一个消息框
	if (!found) {
		GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			"未找到该联系人");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
}

int main(int argc, char* argv[]) {
	// 初始化 GTK
	gtk_init(&argc, &argv);
	// 创建主窗口
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "通讯录");
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

	// 创建主布局容器
	GtkWidget* main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window), main_box);

	// 创建用户输入框
	name_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "姓名");
	company_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(company_entry), "工作单位");
	phone_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(phone_entry), "电话");
	email_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(email_entry), "电子邮件");
	im_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(im_entry), "即时通话号码");

	// 创建添加和删除按钮
	GtkWidget* add_button = gtk_button_new_with_label("添加");
	GtkWidget* remove_button = gtk_button_new_with_label("删除");

	// 创建联系人列表
	contacts_view = gtk_tree_view_new();
	GtkTreeSelection* selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(contacts_view));
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(contacts_view), TRUE);
	gtk_tree_view_set_model(GTK_TREE_VIEW(contacts_view), GTK_TREE_MODEL(create_contacts_list()));

	// 创建搜索框
	search_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(search_entry), "搜索联系人");

	// 创建搜索按钮
	GtkWidget* search_button = gtk_button_new_with_label("搜索");

	// 创建添加、删除、搜索的布局容器
	GtkWidget* button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(button_box), add_button, FALSE, 0, 10);
	gtk_box_pack_start(GTK_BOX(button_box), remove_button, FALSE, 0, 10);
	gtk_box_pack_start(GTK_BOX(button_box), search_entry, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(button_box), search_button, FALSE, 0, 10);

	// 创建联系人列表和搜索布局容器
	GtkWidget* list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start(GTK_BOX(list_box), contacts_view, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(list_box), button_box, FALSE, FALSE, 0);

	// 将用户输入框添加到主布局容器
	gtk_box_pack_start(GTK_BOX(main_box), name_entry, FALSE, 0, 10);
	gtk_box_pack_start(GTK_BOX(main_box), company_entry, FALSE, 0, 10);
	gtk_box_pack_start(GTK_BOX(main_box), phone_entry, FALSE, 0, 10);
	gtk_box_pack_start(GTK_BOX(main_box), email_entry, FALSE, 0, 10);
	gtk_box_pack_start(GTK_BOX(main_box), im_entry, FALSE, 0, 10);

	// 将联系人列表和搜索布局容器添加到主布局容器
	gtk_box_pack_start(GTK_BOX(main_box), list_box, TRUE, TRUE, 10);

	// 连接添加和删除按钮的信号处理函数
	g_signal_connect(add_button, "clicked", G_CALLBACK(on_add_button_clicked), NULL);
	g_signal_connect(remove_button, "clicked", G_CALLBACK(on_remove_button_clicked), NULL);

	// 连接搜索按钮和搜索输入框的信号处理函数
	g_signal_connect(search_button, "clicked", G_CALLBACK(on_search_button_clicked), NULL);
	g_signal_connect(search_entry, "activate", G_CALLBACK(on_search_button_clicked), NULL);

	// 连接联系人列表的信号处理函数
	g_signal_connect(selection, "changed", G_CALLBACK(on_contact_selection_changed), NULL);

	// 显示窗口并进入主事件循环
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
