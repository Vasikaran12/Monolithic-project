#include <gtk/gtk.h>
#include <sqlite3.h>

typedef struct
{
    GtkWidget *entry[2];
} AppWidgets;

static int callback(void *data, int argc, char **argv, char **azColName)
{
    GtkWidget *dialog;
    GtkMessageType type = GTK_MESSAGE_INFO;
    gchar *message;

    if (argc == 0 || argv == NULL)
    {
        // No results, show not found message
        type = GTK_MESSAGE_WARNING;
        message = g_strdup("Not Found");
    }
    else
    {
        // Results found, create a message with details
        gchar *studentName = argv[0] ? g_strdup(argv[0]) : g_strdup("N/A");
        gchar *registerNumber = argv[1] ? g_strdup(argv[1]) : g_strdup("N/A");
        gchar *bookName = argv[2] ? g_strdup(argv[2]) : g_strdup("N/A");
        gchar *bookAuthor = argv[3] ? g_strdup(argv[3]) : g_strdup("N/A");
        gchar *bookId = argv[4] ? g_strdup(argv[4]) : g_strdup("N/A");

        message = g_strdup_printf("Student Name: %s\nRegister Number: %s\n\nBook Name: %s\nBook Author: %s\nBook ID: %s", studentName, registerNumber, bookName, bookAuthor, bookId);

        g_free(studentName);
        g_free(registerNumber);
        g_free(bookName);
        g_free(bookAuthor);
        g_free(bookId);
    }

    dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, type, GTK_BUTTONS_OK, "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    g_free(message);

    return 0;
}

void confirm_button_clicked(GtkWidget *widget, gpointer data)
{
    // Assuming data is a struct containing the necessary information (register number and ISBN)
    AppWidgets *widgets = (AppWidgets *)data;

    const gchar *registerNumber = gtk_entry_get_text(GTK_ENTRY(widgets->entry[0]));
    const gchar *ISBN = gtk_entry_get_text(GTK_ENTRY(widgets->entry[1]));

    // Database operations here to insert into the issue table
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("library.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    gchar *sql = g_strdup_printf("INSERT INTO issue (ISBN, register_number) VALUES ('%s', '%s');", ISBN, registerNumber);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to insert data into the issue table\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    sqlite3_close(db);
}

static void on_issue_submit_clicked(GtkButton *button, gpointer user_data)
{
    // Handle submit button click event
    // GtkWidget *form = gtk_widget_get_parent(button);
    // GtkWidget *entry1 = gtk_bin_get_child(GTK_BIN(form));
    // GtkWidget *entry2 = gtk_bin_get_child(GTK_BIN(form));

    AppWidgets *widgets = (AppWidgets *)user_data;

    // Retrieve values from entry fields directly
    const gchar *registerNumber = gtk_entry_get_text(GTK_ENTRY(widgets->entry[0]));
    const gchar *ISBN = gtk_entry_get_text(GTK_ENTRY(widgets->entry[1]));

    // Database operations here to check student and book details
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("library.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Check student details
    gchar *sqlStudent = g_strdup_printf("SELECT name, register_number FROM student WHERE register_number='%s';", registerNumber);
    rc = sqlite3_exec(db, sqlStudent, callback, NULL, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to select student data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Check book details
    gchar *sqlBook = g_strdup_printf("SELECT book_name, book_author, book_id FROM book WHERE ISBN='%s';", ISBN);
    rc = sqlite3_exec(db, sqlBook, callback, NULL, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to select book data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    sqlite3_close(db);

    // After checking, display the details and confirm button
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK_CANCEL, "Details found, do you want to confirm the issue?");
    g_signal_connect(GTK_DIALOG(dialog), "response", G_CALLBACK(confirm_button_clicked), widgets);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    g_free(sqlStudent);
    g_free(sqlBook);

    // Display values (you can customize this part based on your requirements)
    g_message("Issue Submit button clicked.\nRegister Number: %s\nISBN: %s", registerNumber, ISBN);

    // Clear the entries
    gtk_entry_set_text(GTK_ENTRY(widgets->entry[0]), "");
    gtk_entry_set_text(GTK_ENTRY(widgets->entry[1]), "");
}

static void on_return_submit_clicked(GtkButton *button, gpointer user_data)
{
    // Handle submit button click event
    // GtkWidget *form = gtk_widget_get_parent(button);
    // GtkWidget *entry1 = gtk_bin_get_child(GTK_BIN(form));
    // GtkWidget *entry2 = gtk_bin_get_child(GTK_BIN(form));

    AppWidgets *widgets = (AppWidgets *)user_data;

    // Retrieve values from entry fields directly
    const gchar *value1 = gtk_entry_get_text(GTK_ENTRY(widgets->entry[0]));
    const gchar *value2 = gtk_entry_get_text(GTK_ENTRY(widgets->entry[1]));

    // g_print("%s %s", value1, value2);
    // g_print("Hello");

    // Display values (you can customize this part based on your requirements)
    g_message("Return Submit button clicked.\nRegister Number: %s\nISBN: %s", value1, value2);

    // Clear the entries
    gtk_entry_set_text(GTK_ENTRY(widgets->entry[0]), "");
    gtk_entry_set_text(GTK_ENTRY(widgets->entry[1]), "");
}

static void on_renewal_submit_clicked(GtkButton *button, gpointer user_data)
{
    // Handle submit button click event
    // GtkWidget *form = gtk_widget_get_parent(button);
    // GtkWidget *entry1 = gtk_bin_get_child(GTK_BIN(form));
    // GtkWidget *entry2 = gtk_bin_get_child(GTK_BIN(form));

    AppWidgets *widgets = (AppWidgets *)user_data;

    // Retrieve values from entry fields directly
    const gchar *value1 = gtk_entry_get_text(GTK_ENTRY(widgets->entry[0]));
    const gchar *value2 = gtk_entry_get_text(GTK_ENTRY(widgets->entry[1]));

    // g_print("%s %s", value1, value2);
    // g_print("Hello");

    // Display values (you can customize this part based on your requirements)
    g_message("Renewal Submit button clicked.\nRegister Number: %s\nISBN: %s", value1, value2);

    // Clear the entries
    gtk_entry_set_text(GTK_ENTRY(widgets->entry[0]), "");
    gtk_entry_set_text(GTK_ENTRY(widgets->entry[1]), "");
}

// Callback function for button click event
static void on_button_clicked(GtkWidget *button, gpointer user_data)
{
    // Get the button label to determine which button was clicked
    const gchar *button_label = gtk_button_get_label(GTK_BUTTON(button));

    // Create a form with fields
    GtkWidget *form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    GtkWidget *label = gtk_label_new(button_label);

    GtkWidget *label1 = gtk_label_new("Register Number:");
    GtkWidget *label2 = gtk_label_new("ISBN:");

    AppWidgets *widgets = g_malloc(sizeof(AppWidgets));

    // Add three entry fields to the box
    widgets->entry[0] = gtk_entry_new();
    widgets->entry[1] = gtk_entry_new();

    GtkWidget *submit_button = gtk_button_new_with_label("Submit");

    gtk_widget_set_size_request(form, 300, 500);

    gtk_box_pack_start(GTK_BOX(form), label, FALSE, FALSE, 20);
    gtk_box_pack_start(GTK_BOX(form), label1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(form), widgets->entry[0], FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(form), label2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(form), widgets->entry[1], FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(form), submit_button, FALSE, FALSE, 15);

    // Replace the image in the right column with the form
    GtkWidget *right_column = GTK_WIDGET(user_data);
    gtk_container_foreach(GTK_CONTAINER(right_column), (GtkCallback)gtk_widget_destroy, NULL);
    gtk_container_add(GTK_CONTAINER(right_column), form);

    gtk_widget_set_halign(GTK_WIDGET(right_column), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(right_column), GTK_ALIGN_CENTER);

    // Show all widgets in the right column
    gtk_widget_show_all(right_column);

    // Connect the submit button click event
    if (strcmp(button_label, "Book Issue") == 0)
    {
        g_signal_connect(submit_button, "clicked", G_CALLBACK(on_issue_submit_clicked), widgets);
    }
    else if (strcmp(button_label, "Book Return") == 0)
    {
        g_signal_connect(submit_button, "clicked", G_CALLBACK(on_return_submit_clicked), widgets);
    }
    else
    {
        g_signal_connect(submit_button, "clicked", G_CALLBACK(on_renewal_submit_clicked), widgets);
    }
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "TCE LIBRARY");

    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    gtk_window_maximize(GTK_WINDOW(window));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box to contain two columns
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Create left column with buttons
    GtkWidget *left_column = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(left_column), 10);
    gtk_box_pack_start(GTK_BOX(box), left_column, TRUE, TRUE, 0);

    gtk_widget_set_halign(GTK_WIDGET(left_column), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(left_column), GTK_ALIGN_CENTER);

    GtkWidget *button_issue = gtk_button_new_with_label("Book Issue");
    GtkWidget *button_return = gtk_button_new_with_label("Book Return");
    GtkWidget *button_renewal = gtk_button_new_with_label("Book Renewal");

    gtk_widget_set_size_request(button_issue, 250, 100);
    gtk_widget_set_size_request(button_return, 250, 100);
    gtk_widget_set_size_request(button_renewal, 250, 100);

    gtk_box_pack_start(GTK_BOX(left_column), button_issue, FALSE, FALSE, 20);
    gtk_box_pack_start(GTK_BOX(left_column), button_return, FALSE, FALSE, 20);
    gtk_box_pack_start(GTK_BOX(left_column), button_renewal, FALSE, FALSE, 20);

    // Create right column with an image
    GtkWidget *right_column = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_set_border_width(GTK_CONTAINER(right_column), 10);
    gtk_box_pack_start(GTK_BOX(box), right_column, TRUE, TRUE, 0);

    // Load an image (replace "path/to/your/image.jpg" with the actual path)
    GtkWidget *image = gtk_image_new_from_file("C:/Users/Administrator/Documents/VASIKARAN/Monolithic project/TCE.png");
    gtk_box_pack_start(GTK_BOX(right_column), image, TRUE, TRUE, 0);

    g_signal_connect(button_issue, "clicked", G_CALLBACK(on_button_clicked), right_column);
    g_signal_connect(button_return, "clicked", G_CALLBACK(on_button_clicked), right_column);
    g_signal_connect(button_renewal, "clicked", G_CALLBACK(on_button_clicked), right_column);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
