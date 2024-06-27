#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/*
    * Proyecto 1
    * Autores: Antony Medina y Arley Grijalba
    * Fecha: 27/06/2024
    * Objetivo: Implementar el juego de Tic Tac Toe (Gato) usando GTK-3.



*/

 // Declaraciòn de las funciones
void on_button_clicked(GtkButton *button, gpointer user_data);
void initialize_buttons(GtkBuilder *builder);
void check_winner(); 


// Variables globales
GtkWidget *buttons[3][3];
char board[3][3];
char current_player = 'X';

// Función para manejar el clic en los botones
void on_button_clicked(GtkButton *button, gpointer user_data)
{
    const gchar *label = gtk_button_get_label(button);
    if (label[0] == ' ')
    {
        gtk_button_set_label(button, current_player == 'X' ? "X" : "O");
        // Actualizar el tablero
        const char *button_name = gtk_widget_get_name(GTK_WIDGET(button));
        int row = (button_name[3] - '1') / 3;
        int col = (button_name[3] - '1') % 3;
        board[row][col] = current_player;

        // Verificar el ganador
        check_winner();

        // Cambiar de jugador
        current_player = (current_player == 'X') ? 'O' : 'X';
    }
}

// Función para inicializar los botones
void initialize_buttons(GtkBuilder *builder)
{
    const char *button_names[3][3] = {
        {"btn1", "btn2", "btn3"},
        {"btn4", "btn5", "btn6"},
        {"btn7", "btn8", "btn9"}};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            buttons[i][j] = GTK_WIDGET(gtk_builder_get_object(builder, button_names[i][j]));
            if (!buttons[i][j])
            {
                g_printerr("Error: No se pudo encontrar el widget %s\n", button_names[i][j]);
                continue;
            }
            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(on_button_clicked), NULL);
            gtk_button_set_label(GTK_BUTTON(buttons[i][j]), " ");
            board[i][j] = ' '; // Inicializar el tablero vacío
        }
    }
}

// Función para verificar el ganador
void check_winner()
{
    bool hayGanador = false;
    char ganador = ' ';

    // Verificar filas y columnas para definir ganador
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
        {
            hayGanador = true;
            ganador = board[i][0];
            break;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
        {
            hayGanador = true;
            ganador = board[0][i];
            break;
        }
    }

    // Verificar diagonales
    if (!hayGanador)
    {
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        {
            hayGanador = true;
            ganador = board[0][0];
        }
        else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        {
            hayGanador = true;
            ganador = board[0][2];
        }
    }

    // Mostrar el resultado
    if (hayGanador)
    {
        printf("Ganador: %c\n", ganador);
        
        gtk_dialog_run(GTK_DIALOG(gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Ganador: %c", ganador)));
        gtk_main_quit(); // Salir del bucle principal de GTK
    }
    else
    {
        // Verificar si hay empate
        bool tableroLleno = true;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    tableroLleno = false;
                    break;
                }
            }
            if (!tableroLleno)
            {
                break;
            }
        }

        if (tableroLleno)
        {
            printf("Empate\n");
            gtk_dialog_run(GTK_DIALOG(gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Empate")));
            gtk_main_quit(); // Salir del bucle principal de GTK
        }
    }
}

// Función principal
int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    GtkWidget *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("tic_tac_toe.glade");
    if (!builder)
    {
        printf("Error: No se pudo cargar el archivo Glade\n");
        return 1;
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    if (!window)
    {
        printf("Error: No se pudo encontrar la ventana principal\n");
        return 1;
    }
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    initialize_buttons(builder);

    gtk_widget_show_all(window);
    
    gtk_main();

    return 0;
}
