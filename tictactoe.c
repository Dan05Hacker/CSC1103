#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

// Define constants
#define PLAYER_1 'X'
#define PLAYER_2 'O'
#define FILE_NAME "tic-tac-toe.data"
#define MAX_LINES 958
#define MAX_SIZE 30

// Define functions GTK GUI
void marking_player_move(gpointer ptr);
void quit_game(gpointer ptr);
void start_game(gpointer ptr);
void reset_board();
void change_gamemode(gpointer ptr);
void change_difficulty(gpointer ptr);
void change_algo(gpointer ptr);

// Define functions for game flow
void main_page(GtkApplication *app);
void computer_move();
void marking_computer_move(int move);
int check_winning(const char grid[9]);

// Define functions for minimax
int minimax(char grid[9], int player, int depth);

// Define functions for ML
void swap_lines(char lines[MAX_LINES][MAX_SIZE]);
void readFile(char data[MAX_LINES][MAX_SIZE]);
void training_data(char data[MAX_LINES][MAX_SIZE], int training_dataset);
void testing_data(char datap[MAX_LINES][MAX_SIZE], int testing_dataset);

// Define global variables and global pointers for GTK widgets
GtkWidget *board[3][3];                                                                            // 3x3 grid buttons
GtkWidget *status, *gamemode, *difficulty, *algorithm, *quit, *text_box;                           // Setting buttons
const gchar *button_label, *current_status, *current_gamemode, *current_difficulty, *current_algo; // Current settings
char grid[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
bool start_flag = false, win_flag = false;
int player = -1, count = 0;
double positive = 0, negative = 0;
char data[MAX_LINES][MAX_SIZE];
double count_array[9][6];
double probability_array[9][6];

double total_time_minimax = 0;
double total_time_ml = 0;

// This function is called when any of the grid buttons are clicked
void marking_player_move(gpointer ptr)
{
    struct timeval start, end;
    button_label = gtk_button_get_label(GTK_BUTTON(ptr)); // Reading the button label

    // Initializing local variables
    char symbol[5], player_symbol;

    // Checks if the board has already over and whether the button is empty as well as whether the start button is pressed
    if (start_flag && strncmp(button_label, "\0", 2) == 0 && !win_flag)
    {
        // Assigning X or O according to player
        if (player == -1)
        {
            sprintf(symbol, "%s", "X");
            player_symbol = PLAYER_1;
            gtk_button_set_label(GTK_BUTTON(text_box), "Player 2's Turn!");
        }
        else
        {
            sprintf(symbol, "%s", "O");
            player_symbol = PLAYER_2;
            gtk_button_set_label(GTK_BUTTON(text_box), "Player 1's Turn!");
        }

        gtk_button_set_label(GTK_BUTTON(ptr), symbol); // Setting the clicked button to the player's symbol
        ++count;                                       // Increases count to 9 to prevent
        player *= -1;                                  // Switches player

        // Marking player's move to check winning conditions and for computer's minimax
        if (ptr == board[0][0])
        {
            grid[0] = player_symbol;
        }
        else if (ptr == board[0][1])
        {
            grid[3] = player_symbol;
        }
        else if (ptr == board[0][2])
        {
            grid[6] = player_symbol;
        }
        else if (ptr == board[1][0])
        {
            grid[1] = player_symbol;
        }
        else if (ptr == board[1][1])
        {
            grid[4] = player_symbol;
        }
        else if (ptr == board[1][2])
        {
            grid[7] = player_symbol;
        }
        else if (ptr == board[2][0])
        {
            grid[2] = player_symbol;
        }
        else if (ptr == board[2][1])
        {
            grid[5] = player_symbol;
        }
        else if (ptr == board[2][2])
        {
            grid[8] = player_symbol;
        }

        // Check if there is winner
        int winner = check_winning(grid);
        if (winner == -1)
        {
            win_flag = true;
            gtk_button_set_label(GTK_BUTTON(text_box), "Player 1 Wins!");
            // printf("\nTotal time for minimax: %f", total_time_minimax);
            // printf("\nTotal time for ml: %f", total_time_ml);
            if (strncmp(current_gamemode, "Singleplayer", 12) == 0 && strncmp(current_algo, "ML", 2) == 0 && strncmp(current_difficulty, "MEDIUM", 6) == 0)
            {
                positive++;
                for (int i = 0; i < 9; i++)
                {
                    if (grid[i] == PLAYER_1)
                    {
                        count_array[i][0] += 1;
                    }
                    else if (grid[i] == PLAYER_2)
                    {
                        count_array[i][1] += 1;
                    }
                    else
                    {
                        count_array[i][2] += 1;
                    }
                }
            }
        }
        else if (winner == 1)
        {
            win_flag = true;
            gtk_button_set_label(GTK_BUTTON(text_box), "Player 2 Wins!");
        }
        else if (count == 9)
        {
            gtk_button_set_label(GTK_BUTTON(text_box), "It's a Tie!");
            // printf("\nTotal time for minimax: %f", total_time_minimax);
            // printf("\nTotal time for ml: %f", total_time_ml);
            if (strncmp(current_gamemode, "Singleplayer", 12) == 0 && strncmp(current_algo, "ML", 2) == 0 && strncmp(current_difficulty, "MEDIUM", 6) == 0)
            {
                negative++;
                for (int i = 0; i < 9; i++)
                {
                    if (grid[i] == PLAYER_1)
                    {
                        count_array[i][3] += 1;
                    }
                    else if (grid[i] == PLAYER_2)
                    {
                        count_array[i][4] += 1;
                    }
                    else
                    {
                        count_array[i][5] += 1;
                    }
                }
            }
        }
        else if (strncmp(current_gamemode, "Singleplayer", 12) == 0 && player == 1) // If its Singleplayer, switches to computer immediately after player make a move
        {
            // gettimeofday(&start, NULL);
            computer_move();
            // gettimeofday(&end, NULL);
            // if (strncmp(current_algo, "MINIMAX", 7) == 0)
            // {
            //     total_time_minimax += end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6;
            // }
            // else
            // {
            //     total_time_ml += end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6;
            // }
        }
    }
    else if (!start_flag)
    {
        gtk_button_set_label(GTK_BUTTON(text_box), "Please click 'START' to start the game."); // Outputting error if start button not pressed
    }
    else if (strncmp(button_label, "\0", 2) != 0 && count < 9)
    {
        gtk_button_set_label(GTK_BUTTON(text_box), "Please choose another box."); // Outputting error if board button is selected
    }
}

// This function is called when the quit button is clicked
void quit_game(gpointer ptr)
{
    exit(0); // Stop the code and close the window.
}

void reset_board()
{
    // Initializing local variable
    char current_number[5];

    // Clear entire board
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            gtk_button_set_label(GTK_BUTTON(board[i][j]), "\0");
            sprintf(current_number, "%d", (i * 3) + (j + 1));
            grid[i * 3 + j] = current_number[0];
        }
    }

    // Reset certain global variable and
    gtk_button_set_label(GTK_BUTTON(text_box), "\0");
    win_flag = false;
    player = -1;
    count = 0;
}

// This function is called when the start or restart button is clicked
void start_game(gpointer ptr)
{
    // Getting the current label to differentiate between start and restart button
    current_status = gtk_button_get_label(GTK_BUTTON(ptr));

    // If is start button, initiate all setting buttons and their current settings. Otherwise, clear the entire board however remain the current settings
    if (strncmp(current_status, "START", 5) == 0)
    {
        start_flag = true;
        gtk_button_set_label(GTK_BUTTON(ptr), "RESTART");
        current_status = gtk_button_get_label(GTK_BUTTON(ptr));

        gtk_button_set_label(GTK_BUTTON(gamemode), "Multiplayer");
        current_gamemode = gtk_button_get_label(GTK_BUTTON(gamemode));

        gtk_button_set_label(GTK_BUTTON(text_box), "Player 1's Turn!");
    }
    else
    {
        reset_board();
        if (strncmp(current_gamemode, "Singleplayer", 12) == 0 && strncmp(current_algo, "ML", 2) == 0 && strncmp(current_difficulty, "MEDIUM", 6) == 0)
        {
            int training_dataset = floor(MAX_LINES * 0.8);
            int testing_dataset = MAX_LINES - training_dataset;
            for (int x = 0; x < 9; x++)
            {
                for (int y = 0; y < 6; y++)
                {
                    if (y < 3)
                    {
                        probability_array[x][y] = count_array[x][y] / positive;
                    }
                    else
                    {
                        probability_array[x][y] = count_array[x][y] / negative;
                    }
                }
            }
            printf("Positive: %f, Negative: %f\n", positive, negative);
            testing_data(data, testing_dataset);
        }
    }
}

// This function is called when the difficulty button is pressed; only applicable to Singleplayer
void change_gamemode(gpointer ptr)
{
    // Getting the current label to differentiate between Multiplayer and Singleplayer
    current_gamemode = gtk_button_get_label(GTK_BUTTON(ptr));

    // Toggles between Multiplayer and Singleplayer
    if (strncmp(current_gamemode, "Multiplayer", 11) == 0)
    {
        gtk_button_set_label(GTK_BUTTON(ptr), "Singleplayer");
        current_gamemode = gtk_button_get_label(GTK_BUTTON(ptr));

        gtk_button_set_label(GTK_BUTTON(difficulty), "EASY");
        current_difficulty = gtk_button_get_label(GTK_BUTTON(difficulty));

        gtk_button_set_label(GTK_BUTTON(algorithm), "MINIMAX");
        current_algo = gtk_button_get_label(GTK_BUTTON(algorithm));

        reset_board();
    }
    else if (strncmp(current_gamemode, "Singleplayer", 12) == 0)
    {
        gtk_button_set_label(GTK_BUTTON(ptr), "Multiplayer");
        current_gamemode = gtk_button_get_label(GTK_BUTTON(ptr));

        gtk_button_set_label(GTK_BUTTON(difficulty), "\0");
        current_difficulty = gtk_button_get_label(GTK_BUTTON(difficulty));

        gtk_button_set_label(GTK_BUTTON(algorithm), "\0");
        current_algo = gtk_button_get_label(GTK_BUTTON(algorithm));

        gtk_button_set_label(GTK_BUTTON(text_box), "Player 1's Turn!");

        reset_board();
    }
}

// This function is called when the difficulty button is pressed to change difficulty; only applicable to Singleplayer
void change_difficulty(gpointer ptr)
{
    // Getting the current label to differentiate between EASY, MEDIUM and HARD
    current_difficulty = gtk_button_get_label(GTK_BUTTON(ptr));

    // Toggle between the three difficulties
    if (strncmp(current_difficulty, "EASY", 4) == 0)
    {
        gtk_button_set_label(GTK_BUTTON(ptr), "MEDIUM");
        current_difficulty = gtk_button_get_label(GTK_BUTTON(ptr));

        reset_board();
    }
    else if (strncmp(current_difficulty, "MEDIUM", 6) == 0)
    {
        if (strncmp(current_algo, "ML", 2) == 0)
        {
            gtk_button_set_label(GTK_BUTTON(ptr), "EASY");
            current_difficulty = gtk_button_get_label(GTK_BUTTON(ptr));
        }
        else
        {
            gtk_button_set_label(GTK_BUTTON(ptr), "HARD");
            current_difficulty = gtk_button_get_label(GTK_BUTTON(ptr));
        }

        reset_board();
    }
    else if (strncmp(current_difficulty, "HARD", 4) == 0)
    {
        gtk_button_set_label(GTK_BUTTON(ptr), "EASY");
        current_difficulty = gtk_button_get_label(GTK_BUTTON(ptr));

        reset_board();
    }
}

// This function is called when the algorithm option button is pressed
void change_algo(gpointer ptr)
{
    // Getting the current label to differentiate between MINIMAX and ML
    current_algo = gtk_button_get_label(GTK_BUTTON(ptr));

    // Toggle between the two algorithms
    if (strncmp(current_algo, "MINIMAX", 7) == 0)
    {
        gtk_button_set_label(GTK_BUTTON(ptr), "ML");
        gtk_button_set_label(GTK_BUTTON(difficulty), "EASY");
        current_algo = gtk_button_get_label(GTK_BUTTON(ptr));
        current_difficulty = gtk_button_get_label(GTK_BUTTON(difficulty));

        reset_board();
    }
    else if (strncmp(current_algo, "ML", 2) == 0)
    {
        gtk_button_set_label(GTK_BUTTON(ptr), "MINIMAX");
        gtk_button_set_label(GTK_BUTTON(difficulty), "EASY");
        current_algo = gtk_button_get_label(GTK_BUTTON(ptr));
        current_difficulty = gtk_button_get_label(GTK_BUTTON(difficulty));

        reset_board();
    }
}

// This function is called to create the windows and the buttons
void main_page(GtkApplication *app)
{
    // Creates GTK widget pointer for user interface
    GtkWidget *window;
    GtkWidget *board_grid, *main_grid, *settings_grid;

    // Create the pop up window which will contain all other GTK widget
    window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 500);       // Set window size
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Set window position to be in the center of the screen
    gtk_window_set_title(GTK_WINDOW(window), "Tic Tac Toe");         // Set window's title

    // Creates all the grid for difference purposes
    main_grid = gtk_grid_new();     // Main grid holds both 3x3 grid and setting grid
    board_grid = gtk_grid_new();    // Board grid hold only 3x3
    settings_grid = gtk_grid_new(); // Setting grid hold all buttons to set the settings

    // Add main grid to window
    gtk_container_add(GTK_CONTAINER(window), main_grid);

    // Creating setting buttons and giving them the signal for onClicked to do their respective jobs
    status = gtk_button_new_with_label("START");
    g_signal_connect(status, "clicked", G_CALLBACK(start_game), status);

    gamemode = gtk_button_new_with_label("\0");
    g_signal_connect(gamemode, "clicked", G_CALLBACK(change_gamemode), gamemode);

    difficulty = gtk_button_new_with_label("\0");
    g_signal_connect(difficulty, "clicked", G_CALLBACK(change_difficulty), difficulty);

    algorithm = gtk_button_new_with_label("\0");
    g_signal_connect(algorithm, "clicked", G_CALLBACK(change_algo), algorithm);

    quit = gtk_button_new_with_label("QUIT");
    g_signal_connect(quit, "clicked", G_CALLBACK(quit_game), NULL);

    // Creating text box for information
    text_box = gtk_button_new_with_label("\0");
    gtk_widget_set_hexpand(text_box, TRUE);

    // Make the button expand to fill the grid horizontally
    gtk_widget_set_hexpand(status, TRUE);
    gtk_widget_set_hexpand(gamemode, TRUE);
    gtk_widget_set_hexpand(difficulty, TRUE);
    gtk_widget_set_hexpand(algorithm, TRUE);
    gtk_widget_set_hexpand(quit, TRUE);

    // Attach the buttons to the position of the grid
    gtk_grid_attach(GTK_GRID(settings_grid), status, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(settings_grid), gamemode, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(settings_grid), difficulty, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(settings_grid), algorithm, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(settings_grid), quit, 4, 0, 1, 1);

    // Creating 3x3 grid buttons
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            board[i][j] = gtk_button_new_with_label("\0");
            gtk_widget_set_hexpand(board[i][j], TRUE);                                              // Make the button expand to fill the grid horizontally
            gtk_widget_set_vexpand(board[i][j], TRUE);                                              // Make the button expand to fill the grid vertically
            gtk_grid_attach(GTK_GRID(board_grid), board[i][j], i, j + 1, 1, 1);                     // Attach the board buttons to the board grid
            g_signal_connect(board[i][j], "clicked", G_CALLBACK(marking_player_move), board[i][j]); // Giving each button a signal for onClicked to set the symbol
        }
    }

    // Attaching setting grid and board grid in the main grid
    gtk_grid_attach(GTK_GRID(main_grid), settings_grid, 0, 0, 3, 3);
    gtk_grid_attach(GTK_GRID(main_grid), text_box, 0, 3, 3, 3);
    gtk_grid_attach(GTK_GRID(main_grid), board_grid, 0, 6, 3, 3);

    // Show all widgets
    gtk_widget_show_all(window);
}

// This function is called only during Singleplayer and immediately after player make his/her move
// For this function only, PLAYER_2 refers to COMPUTER
void computer_move()
{
    // Setting seed for random number generator
    srand(time(NULL));

    // Initializing local variable
    int cpu_move;
    if ((strncmp(current_difficulty, "EASY", 4) == 0) ||                                                          // Easy difficulty --> Using completely random number generator to determine Computer's move
        (strncmp(current_difficulty, "MEDIUM", 6) == 0 && count < 2 && strncmp(current_algo, "MINIMAX", 7) == 0)) // First step of medium for minimax only difficulty --> Using completely random number generator to determine Computer's move
    {
        while (1)
        {
            // Assign computer move to a random number generated
            cpu_move = rand() % 9;
            if (grid[cpu_move] != PLAYER_1 && grid[cpu_move] != PLAYER_2 && cpu_move >= 0 && cpu_move < 9) // Checks if slot is taken and whether number generated is between 0 to 8
            {
                grid[cpu_move] = PLAYER_2; // Register Computer's move in array
                ++count;                   // Increases count for determining whether it's tie a not
                player = -1;               // Switches to player's turn

                // Setting GTK button to computer's move
                marking_computer_move(cpu_move);
                break; // To get out of the while loop when computer make it's move
            }
        }
    }
    else // Hard difficulty --> Using completely minimax algorithm to determine Computer's move / Medium difficulty --> Use minimax from Computer's second move and above / Algo is ML then use ML to play
    {
        if (strncmp(current_algo, "ML", 2) == 0)
        {
            // Initialize local variables for this if condition
            double total_pprobability = 1;
            double total_nprobability = 1;
            double current_probability = 0;
            int move = 0, sign;
            char int_str[5];
            char symbol;

            // Calculate the probability of X winning and O winning
            for (int i = 0; i < 9; i++)
            {
                if (grid[i] == PLAYER_1)
                {
                    total_pprobability *= probability_array[i][0];
                }
                else if (grid[i] == PLAYER_2)
                {
                    total_nprobability *= probability_array[i][4];
                }
            }

            // Compare to see if computer is going to play defensive or offensive
            if (total_pprobability > total_nprobability)
            {
                symbol = PLAYER_1;
                sign = -1;
            }
            else
            {
                symbol = PLAYER_2;
                sign = 1;
            }

            // Base on whether is it defensive or offensive, choose a suitable move relative to respective playing style
            for (int i = 0; i < 9; i++)
            {
                double probability = sign;
                if (grid[i] != PLAYER_1 && grid[i] != PLAYER_2)
                {
                    grid[i] = symbol;
                    probability *= (symbol == PLAYER_1 ? probability_array[i][0] : probability_array[i][4]);
                    probability *= (symbol == PLAYER_1 ? total_pprobability : total_nprobability);
                    if (symbol == 'X')
                    {
                        if (probability < current_probability)
                        {
                            current_probability = probability;
                            move = i;
                        }
                    }
                    else
                    {
                        if (probability > current_probability)
                        {
                            current_probability = probability;
                            move = i;
                        }
                    }
                    printf("Probability for move %d is %g\n", i + 1, probability);
                    sprintf(int_str, "%d", i + 1);
                    grid[i] = int_str[0];
                }
            }

            printf("Best move: %d\n", move + 1);
            grid[move] = PLAYER_2; // Register Computer's move in array
            ++count;               // Increases count for determining whether it's tie a not
            player = -1;           // Switches to player's turn

            // Setting GTK button to computer's move
            marking_computer_move(move);
        }
        else
        {
            // Computer's move and minimax algorithm
            int move = -1, score = -100, i;
            char int_str[5];
            for (i = 0; i < 9; ++i)
            {
                if (grid[i] != PLAYER_1 && grid[i] != PLAYER_2)
                {
                    grid[i] = PLAYER_2; // Start the first move

                    int tempScore = -minimax(grid, -1, 100 - count); // Call minimax as opponent's move
                    // Reset the backend grid
                    sprintf(int_str, "%d", i + 1);
                    grid[i] = int_str[0];

                    // If returned score from minimax is higher than score, store the score value as returned score to compare if there is a better option
                    if (tempScore > score)
                    {
                        score = tempScore;
                        move = i;
                    }
                }
            }

            grid[move] = PLAYER_2; // Register Computer's move in array
            ++count;               // Increases count for determining whether it's tie a not
            player = -1;           // Switches to player's turn

            // Setting GTK button to computer's move
            marking_computer_move(move);
        }
    }
}

void marking_computer_move(int move)
{
    // Initializing local variable
    char string[100];

    // Setting GTK button to computer's move
    if (move == 0)
    {
        gtk_button_set_label(GTK_BUTTON(board[0][0]), "O");
    }
    else if (move == 1)
    {
        gtk_button_set_label(GTK_BUTTON(board[1][0]), "O");
    }
    else if (move == 2)
    {
        gtk_button_set_label(GTK_BUTTON(board[2][0]), "O");
    }
    else if (move == 3)
    {
        gtk_button_set_label(GTK_BUTTON(board[0][1]), "O");
    }
    else if (move == 4)
    {
        gtk_button_set_label(GTK_BUTTON(board[1][1]), "O");
    }
    else if (move == 5)
    {
        gtk_button_set_label(GTK_BUTTON(board[2][1]), "O");
    }
    else if (move == 6)
    {
        gtk_button_set_label(GTK_BUTTON(board[0][2]), "O");
    }
    else if (move == 7)
    {
        gtk_button_set_label(GTK_BUTTON(board[1][2]), "O");
    }
    else if (move == 8)
    {
        gtk_button_set_label(GTK_BUTTON(board[2][2]), "O");
    }

    // Check if there is winner
    int winner = check_winning(grid);
    if (winner == 1)
    {
        win_flag = true;
        gtk_button_set_label(GTK_BUTTON(text_box), "Computer Wins!");
        if (strncmp(current_algo, "ML", 2) == 0 && strncmp(current_difficulty, "MEDIUM", 6) == 0)
        {
            negative++;
            for (int i = 0; i < 9; i++)
            {
                if (grid[i] == PLAYER_1)
                {
                    count_array[i][3] += 1;
                }
                else if (grid[i] == PLAYER_2)
                {
                    count_array[i][4] += 1;
                }
                else
                {
                    count_array[i][5] += 1;
                }
            }
        }
    }
    else if (winner == 0)
    {
        // Setting information text on GUI
        sprintf(string, "COMPUTER chose grid %d!", move + 1);
        gtk_button_set_label(GTK_BUTTON(text_box), string);
    }
}

int check_winning(const char grid[9])
{
    // Check which player win already otherwise return 0
    unsigned wins[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    int i;
    for (i = 0; i < 8; ++i)
    {
        if ((grid[wins[i][0]] == PLAYER_1 || grid[wins[i][0]] == PLAYER_2) &&
            grid[wins[i][0]] == grid[wins[i][1]] &&
            grid[wins[i][0]] == grid[wins[i][2]])
        {
            if (grid[wins[i][0]] == PLAYER_1)
            {
                return -1;
            }
            else if (grid[wins[i][0]] == PLAYER_2)
            {
                return 1;
            }
        }
    }

    return 0;
}

int minimax(char grid[9], int player, int depth)
{
    // Initializing local variables
    char shape, int_str[5];
    int move = -1, score = -100, i;

    // Checks if the game has already ended
    int winner = check_winning(grid);

    // If game ended, return which player won
    if (winner != 0)
        return winner * player * depth;

    // Sorting player's move shape
    if (player == -1)
    {
        shape = PLAYER_1;
    }
    else if (player == 1)
    {
        shape = PLAYER_2;
    }

    // Start of minimax algorithm
    for (i = 0; i < 9; ++i)
    {
        int current_depth = depth;
        if (grid[i] != PLAYER_1 && grid[i] != PLAYER_2)
        {
            grid[i] = shape; // Try next move

            // Run minimax function for next step as next player
            int thisScore = -minimax(grid, player * -1, current_depth - 1);
            if (thisScore > score)
            {
                score = thisScore;
                move = i;
            }

            // Reset the backend grid
            sprintf(int_str, "%d", i + 1);
            grid[i] = int_str[0];
        }
    }

    // If there are no more moves, return 0
    if (move == -1)
        return 0;

    return score;
}

void swap_lines(char lines[MAX_LINES][MAX_SIZE])
{
    // Setting seed for random value
    srand(time(NULL));

    // Swap all the lines starting from the first line till the last
    for (int x = 0; x < MAX_LINES; x++)
    {
        // Randomly generate a number from 0 to MAX_SIZE to swap x with
        int i = rand() % (x + 1);
        char temp[MAX_SIZE];
        strcpy(temp, lines[x]);
        strcpy(lines[x], lines[i]);
        strcpy(lines[i], temp);
    }
}

void readFile(char data[MAX_LINES][MAX_SIZE])
{
    // Read dataset file
    FILE *file = fopen(FILE_NAME, "r");

    // Check if can open file
    if (file == NULL)
    {
        printf("Error opening file");
        exit(1);
    }

    // Change newline flag to end string flag for each row
    for (int i = 0; i < MAX_LINES; i++)
    {
        if (fgets(data[i], sizeof(data[0]), file))
        {
            data[i][strcspn(data[i], "\n")] = '\0';
        }
    }

    // Close file
    fclose(file);
}

void training_data(char data[MAX_LINES][MAX_SIZE], int training_dataset)
{
    // Iterate each row to count number of x, o, and b and the positive and negative outcome to calculate probability
    for (int i = 0; i < training_dataset; i++)
    {
        // Get current line
        char *current_line = data[i];

        // Get either positive or negative at the end of current line
        char *label = strrchr(current_line, ',') + 1;

        // Iterate through current line with increment of x by 2 to skip commas
        if (strcmp(label, "positive") == 0)
        {
            positive++;
            for (int x = 0; x < 17; x += 2)
            {
                if (current_line[x] == 'x')
                {
                    count_array[x / 2][0] += 1;
                }
                else if (current_line[x] == 'o')
                {
                    count_array[x / 2][1] += 1;
                }
                else if (current_line[x] == 'b')
                {
                    count_array[x / 2][2] += 1;
                }
            }
        }
        else if (strcmp(label, "negative") == 0)
        {
            negative++;
            for (int x = 0; x < 17; x += 2)
            {
                if (current_line[x] == 'x')
                {
                    count_array[x / 2][3] += 1;
                }
                else if (current_line[x] == 'o')
                {
                    count_array[x / 2][4] += 1;
                }
                else if (current_line[x] == 'b')
                {
                    count_array[x / 2][5] += 1;
                }
            }
        }
    }
    printf("Positive: %f, Negative: %f\n", positive, negative);

    // Calculate the probability of each move which result in winning or losing
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 6; y++)
        {
            if (y < 3)
            {
                probability_array[x][y] = count_array[x][y] / positive;
            }
            else
            {
                probability_array[x][y] = count_array[x][y] / negative;
            }
        }
    }
}

void testing_data(char data[MAX_LINES][MAX_SIZE], int testing_dataset)
{
    // Initialize truePositive, falsePositive, trueNegative, falseNegative
    double tp = 0, fp = 0, tn = 0, fn = 0;

    // Iterate through the rest of the dataset (20%) for testing
    for (int i = MAX_LINES - testing_dataset; i < MAX_LINES; i++)
    {
        // Calculate the positive and negative probability of 80%
        double pprobability = positive / (positive + negative);
        double nprobability = negative / (positive + negative);

        // Get current line
        char *current_line = data[i];

        // Get either positive or negative at the end of current line
        char *label = strrchr(current_line, ',') + 1;

        // Iterate through current line with increment of x by 2 to skip commas and calculate the current probability of that state
        for (int x = 0; x < 17; x += 2)
        {
            if (current_line[x] == 'x')
            {
                pprobability *= probability_array[x / 2][0];
                nprobability *= probability_array[x / 2][3];
            }
            else if (current_line[x] == 'o')
            {
                pprobability *= probability_array[x / 2][1];
                nprobability *= probability_array[x / 2][4];
            }
            else if (current_line[x] == 'b')
            {
                pprobability *= probability_array[x / 2][2];
                nprobability *= probability_array[x / 2][5];
            }
        }

        // Check if positive probability is higher than negative probability, if positive is higher, predicted result is positive else otherwise
        if (pprobability > nprobability)
        {
            if (strcmp(label, "positive") == 0)
            {
                tp += 1;
            }
            else
            {
                fp += 1;
            }
        }
        else
        {
            if (strcmp(label, "negative") == 0)
            {
                tn += 1;
            }
            else
            {
                fn += 1;
            }
        }
    }

    // Output the accuracy of the test data
    printf("Error: %g\n", ((fp + fn) / (tp + fp + tn + fn)) * 100);
    printf("True Positive: %g\n", tp);
    printf("False Positive: %g\n", fp);
    printf("True Negative: %g\n", tn);
    printf("False Negative: %g\n", fn);
    printf("Accuracy: %g\n", ((tp + tn) / (tp + fp + tn + fn)) * 100);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int training_dataset = floor(MAX_LINES * 0.8);
    int testing_dataset = MAX_LINES - training_dataset;
    int status;

    // Start of ML to prepare for ML mode during the game
    readFile(data);
    swap_lines(data);
    training_data(data, training_dataset);
    testing_data(data, testing_dataset);

    app = gtk_application_new("com.p2t3.csc1103_project", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(main_page), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}