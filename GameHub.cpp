#include <bits/stdc++.h>
using namespace std;

// ========== COLOR MACROS ==========
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[37m"
#define BBLACK "\033[1;30m"
#define BRED "\033[1;31m"
#define BGREEN "\033[1;32m"
#define BYELLOW "\033[1;33m"
#define BBLUE "\033[1;34m"
#define BMAGENTA "\033[1;35m"
#define BCYAN "\033[1;36m"
#define BG_WHITE "\033[47m"
#define NEON_CYAN "\033[38;5;51m"
#define NEON_GREEN "\033[38;5;46m"
#define NEON_YELLOW "\033[38;5;226m"
#define NEON_ORANGE "\033[38;5;208m"
#define NEON_RED "\033[38;5;196m"
#define HOT_PINK "\033[38;5;205m"
#define LIME_GREEN "\033[38;5;118m"
#define FIREBALL_RED "\033[38;5;9m"

// ========== HELPER FUNCTIONS ==========
void clearScreen()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void waitForEnter()
{
  cout << BYELLOW << "\nPress Enter to continue..." << RESET;
  cin.ignore();
  cin.get();
}

// ========== PLAYER CLASS ==========
class Player
{
private:
  string name;

  vector<int> wins;
  vector<int> losses;
  vector<int> draws;
  vector<int> rounds;

  string gameNames[3];

public:
  Player(string n = "Player")
      : name(n), wins(3, 0), losses(3, 0), draws(3, 0), rounds(3, 0)
  {
    gameNames[0] = "TicTacToe";
    gameNames[1] = "Rock Paper Scissors";
    gameNames[2] = "Hidden Number Guessing";
  }

  void setName(const string &n) { name = n; }
  string getName() const { return name; }

  void addWin(int gameIndex, int cnt)
  {
    wins[gameIndex] += cnt;
    rounds[gameIndex]++;
  }

  void addLoss(int gameIndex, int cnt)
  {
    losses[gameIndex] += cnt;
    rounds[gameIndex]++;
  }

  void addDraw(int gameIndex, int cnt)
  {
    draws[gameIndex] += cnt;
    rounds[gameIndex]++;
  }

  void showStats()
  {
    clearScreen();
    cout << "\n";
    cout << NEON_CYAN << " " << name << "'s STATS" << " : " << RESET << "\n";
    cout << HOT_PINK << string(45, '=') << RESET << "\n\n";

    for (int i = 0; i < 2; i++)
    {
      cout << BMAGENTA << gameNames[i] << RESET << ":\n";
      cout << "  Wins        : " << BGREEN << wins[i] << RESET << "\n";
      cout << "  Losses      : " << BRED << losses[i] << RESET << "\n";
      cout << "  Draws       : " << BYELLOW << draws[i] << RESET << "\n";
      cout << "  Total Rounds: " << WHITE << rounds[i] << RESET << "\n\n";
    }

    cout << BMAGENTA << gameNames[2] << RESET << ":\n";
    cout << "  Points.     : " << BGREEN << wins[2] << RESET << "\n";
    cout << "  Total Rounds: " << WHITE << rounds[2] << RESET << "\n\n";

    cout << BOLD << HOT_PINK << string(45, '=') << RESET << "\n";
    waitForEnter();
  }

  void changeName()
  {
    clearScreen();
    cout << BCYAN << "Enter new name for " << name << ": " << RESET;
    string newName;
    getline(cin, newName);
    setName(newName);
  }

  void compareStats(const Player &p2)
  {
    clearScreen();
    cout << NEON_CYAN << "\nComparing Stats :\n"
         << RESET;
    cout << BOLD << HOT_PINK << string(45, '=') << RESET << "\n\n";
    for (int i = 0; i < 3; i++)
    {
      cout << gameNames[i] << " -> ";
      if (wins[i] > p2.wins[i])
        cout << BCYAN << name << " is leading\n"
             << RESET;
      else if (wins[i] < p2.wins[i])
        cout << BCYAN << p2.getName() << " is leading\n"
             << RESET;
      else
        cout << BYELLOW << "Tied\n"
             << RESET;
    }
    waitForEnter();
  }

  void playersDetailsMenu(Player &p2)
  {
    int choice;
    do
    {
      clearScreen();
      cout << "\n"
           << NEON_CYAN << "PLAYER DETAILS MENU : " << RESET << "\n";
      cout << BOLD << HOT_PINK << string(45, '=') << RESET << "\n\n";
      cout << BYELLOW << "1. Change name ( " << NEON_CYAN << name << RESET << BYELLOW " )\n"
           << RESET << BYELLOW;
      cout << "2. Change name ( " << NEON_RED << p2.getName() << RESET << BYELLOW << " )\n"
           << RESET << BYELLOW;
      cout << "3. " << NEON_CYAN << name << RESET << BYELLOW << "'s Stats \n";
      cout << "4. " << NEON_RED << p2.getName() << RESET << BYELLOW << "'s Stats \n";
      cout << "5. Compare stats\n\n";
      cout << "0. Back\n"
           << RESET;
      cout << BCYAN << "Enter choice: " << RESET;
      cin >> choice;
      cin.ignore(1, '\n');

      switch (choice)
      {
      case 1:
        changeName();
        break;
      case 2:
        p2.changeName();
        break;
      case 3:
        showStats();
        break;
      case 4:
        p2.showStats();
        break;
      case 5:
        compareStats(p2);
        break;
      case 0:
        break;
      default:
        cout << BRED << "Invalid choice!" << RESET << "\n";
      }
    } while (choice != 0);
  }
};
void menu()
  {
    cout << "\n"
         << BGREEN << "=============================================\n"
         << RESET;
    cout << BYELLOW << "|   0. Home          |   1. Play Again      |\n"
         << RESET;
    cout << BGREEN << "=============================================\n"
         << RESET;
  }
// ========== BASE GAME CLASS ==========
class Game
{
public:
  virtual void play(Player &player1, Player &player2) = 0;

  virtual void Interface(Player &player1, Player &player2) = 0;

  virtual void GameLogic(Player &player1, Player &player2) = 0;

  virtual void set() = 0;

  friend void menu();

  template <typename YO>
  void playAgain(YO &player1, YO &player2)
  {
    int choice;
    menu();

    while (true)
    {
      cout << "\n"
           << BCYAN << "Enter your choice: " << RESET;
      cin >> choice;
      if (choice == 1)
      { // Play Again
        play(player1, player2);
        return;
      }
      else if (choice == 0)
      { // Go Back
        return;
      }
      else
      {
        cout << BRED << "Invalid choice! Try again." << RESET << "\n";
      }
    }
  }

  Player &selectPlayer(Player &player1, Player &player2)
  {

    int choice;

    cout << NEON_CYAN << "\n===== Select Player =====\n"
         << RESET;
    cout << LIME_GREEN << "[0] " << RESET << player1.getName() << "\n";
    cout << LIME_GREEN << "[1] " << RESET << player2.getName() << "\n";
    cout << NEON_CYAN << "=========================\n"
         << RESET;

    while (true)
    {
      cout << "\n"
           << BCYAN << "Enter your choice: " << RESET;
      cin >> choice;

      if (choice == 0)
        return player1;

      else if (choice == 1)
        return player2;

      else
      {
        cout << BRED << "Invalid choice! Try again." << RESET << "\n";
      }
    }
  }

  ~Game() {}
};

// ========== TIC TAC TOE ==========
class TicTacToe : public virtual Game
{
private:
  vector<vector<char> > Board;

  int move, turns, Row, Col;
  bool flag = 0;

public:
  void set()
  {
    turns = 9;
    Row = 3;
    Col = 3;

    Board = vector<vector<char> >(3, vector<char>(3));

    char num = '1';
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        Board[i][j] = num++;
  }

  void Interface(Player &player1, Player &player2)
  {
    cout << "\n";
    cout << BOLD << HOT_PINK << string(45, '=') << RESET << "\n";
    cout << "                " << NEON_CYAN << "TIC TAC TOE" << RESET << "\n";
    cout << BOLD << HOT_PINK << string(45, '=') << RESET << "\n";
    cout << NEON_YELLOW << "|       Terminal Edition v1.0       |" << RESET << "\n";
    cout << BOLD << HOT_PINK << string(45, '-') << RESET << "\n";

    cout << NEON_ORANGE << " Rules:" << RESET << "\n";
    cout << " . " << FIREBALL_RED << player1.getName() << "(X)" << RESET << "\n";
    cout << " . " << LIME_GREEN << player2.getName() << "(O)" << RESET << "\n";
    cout << " . Goal: Align three of your symbols.\n";

    cout << BOLD << HOT_PINK << string(45, '-') << RESET << "\n";
    cout << NEON_CYAN << "|   Press Enter to start playing!   |" << RESET << "\n";
    cout << BOLD << HOT_PINK << string(45, '=') << RESET << "\n\n";

    cin.ignore();
    cin.get();
  }

  void GameLogic(Player &player1, Player &player2)
  {

    PrintBoard(); // printing tic tac toe board

    if (flag)
      cout << WHITE << player2.getName() << "( " << RESET << GREEN << "O" << RESET << WHITE << " ) , Enter your move (1-9): " << RESET;
    else
      cout << WHITE << player1.getName() << "( " << RESET << RED << "X" << RESET << WHITE << " ) , Enter your move (1-9): " << RESET;

    cin >> move;

    if (move < 1 || move > 9)
      throw invalid_argument("Invalid move! Input must be between 1 and 9.");

    int r = (move - 1) / 3, c = (move - 1) % 3;

    if (Board[r][c] > '9')
      throw logic_error("Cell already taken! Try again.");

    if (flag & 1)
      Board[r][c] = 'O';
    else
      Board[r][c] = 'X';

    // Check winner
    if (CheckWin())
    {
      PrintBoard();

      if (flag)
      {
        cout << BGREEN << player2.getName() << " wins!\n"
             << RESET;
        player2.addWin(0, 1);
        player1.addLoss(0, 1);
      }
      else
      {
        cout << BRED << player1.getName() << " wins!\n"
             << RESET;
        player1.addWin(0, 1);
        player2.addLoss(0, 1);
      }

      turns = 0;
      return;
    }

    --turns;
    if (!turns)
    {
      PrintBoard();
      cout << BYELLOW << "... Match Drawn ..." << RESET << endl;
      player1.addDraw(0, 1);
      player2.addDraw(0, 1);
    }
  }

  void play(Player &player1, Player &player2)
  {
    clearScreen();

    set();

    Interface(player1, player2);

    while (turns)
    {
      try
      {
        GameLogic(player1, player2);
        flag ^= 1;
      }
      catch (const exception &e)
      {
        cout << BRED << e.what() << RESET << "\n";
      }
    }

    playAgain(player1, player2);
  }

  bool CheckWin()
  {

    for (int i = 0; i < 3; i++)
    {
      if (Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2])
        return 1; // row
      if (Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i])
        return 1; // col
    }
    if (Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2])
      return 1; // diag
    if (Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0])
      return 1; // anti-diag
    return 0;
  }

  void PrintBoard()
  {

    cout << endl;

    int row = 0, col = 0;

    for (int i = 0; i <= 4 * Row; i++)
    {
      for (int j = 0; j <= 4 * Col; j++)
      {

        if (i == 0 || j == 0 || i == Row * 4 || j == Col * 4)
          cout << "  ";
        else
        {

          if (i % 4 == 0 || j % 4 == 0)
            cout << BG_WHITE << "  " << RESET;
          else if (i % 2 == 0 && j % 2 == 0)
          {
            (Board[row][col] == 'X') ? cout << BRED : (Board[row][col] == 'O') ? cout << BGREEN
                                                                               : cout << BBLACK;
            cout << Board[row][col++] << " " << RESET;
          }
          else
            cout << "  ";
        }
      }
      cout << endl;
      if (col == 3)
      {
        row++;
        col = 0;
      }
    }
  }
};

// ========== ROCK PAPER SCISSORS ==========
class RockPaperScissors : public virtual Game
{
private:
  int userWins, compWins, draws, rounds;
  string choices[3];
  Player *player;

public:
  void set()
  {
    userWins = compWins = draws = 0;

    choices[0] = "Rock", choices[1] = "Paper", choices[2] = "Scissors";

    cout << BYELLOW << "Enter number of rounds: " << RESET;
    cin >> rounds;
  }

  void Interface(Player &player1, Player &player2)
  {
    clearScreen();
    cout << "\n";
    cout << BOLD << HOT_PINK << string(45, '=') << RESET << "\n";
    cout << "                " << NEON_CYAN << "ROCK PAPER SCISSORS" << RESET << "\n";
    cout << BOLD << HOT_PINK << string(45, '=') << RESET << "\n";
    cout << NEON_YELLOW << "|       Terminal Edition v1.0       |" << RESET << "\n";
    cout << BOLD << HOT_PINK << string(45, '-') << RESET << "\n";

    cout << NEON_CYAN << " Rules:" << RESET << "\n";
    cout << " r -> " << FIREBALL_RED << "Rock" << RESET << "\n";
    cout << " p -> " << LIME_GREEN << "Paper" << RESET << "\n";
    cout << " s -> " << NEON_YELLOW << "Scissors" << RESET << "\n";

    cout << BOLD << HOT_PINK << string(45, '-') << RESET << "\n";
    cout << NEON_CYAN << "|   Press Enter to start playing!   |" << RESET << "\n";
    cout << BOLD << HOT_PINK << string(45, '=') << RESET << "\n\n";

    cin.ignore();
    cin.get();
  }

  void GameLogic(Player &player1, Player &player2)
  {
    srand(time(0));
    for (int i = 0; i < rounds; i++)
    {
      char user;
      cout << BBLUE << "\nRound " << (i + 1) << ": Enter (r/p/s): " << RESET;
      cin >> user;

      int comp = rand() % 3;
      string compChoice = choices[comp];
      if (user == 'r' || user == 'p' || user == 's')
      {
        string userChoice = (user == 'r') ? "Rock" : (user == 'p') ? "Paper"
                                                                   : "Scissors";
        cout << BCYAN << "You: " << userChoice << " | Computer: " << compChoice << RESET << "\n";

        if (userChoice == compChoice)
        {
          cout << BYELLOW << "Result: Draw!" << RESET << "\n";
          draws++;
          player->addDraw(1, 1);
        }
        else if ((userChoice == "Rock" && compChoice == "Scissors") ||
                 (userChoice == "Paper" && compChoice == "Rock") ||
                 (userChoice == "Scissors" && compChoice == "Paper"))
        {
          cout << BGREEN << "Result: You Win!" << RESET << "\n";
          userWins++;
          player->addWin(1, 1);
        }
        else
        {
          cout << BRED << "Result: You Lose!" << RESET << "\n";
          compWins++;
          player->addLoss(1, 1);
        }
      }
      else
      {
        cout << BRED << "Invalid input! Skipping round..." << RESET << "\n";
      }
    }
  }

  void result()
  {

    cout << "\n"
         << BOLD << GREEN << "========== Final Score ==========" << RESET << "\n";
    cout << BCYAN << player->getName() << " Wins: " << userWins << RESET << "\n";
    cout << BRED << "Computer Wins: " << compWins << RESET << "\n";
    cout << BYELLOW << "Draws: " << draws << RESET << "\n";

    if (userWins > compWins)
      cout << BGREEN << player->getName() << " is the Champion!" << RESET << "\n";
    else if (compWins > userWins)
      cout << BRED << " Computer Wins the Match!" << RESET << "\n";
    else
      cout << BYELLOW << "It's a Tie Overall!" << RESET << "\n";
  }

  void play(Player &player1, Player &player2)
  {

    Interface(player1, player2);

    player = &selectPlayer(player1, player2);

    set();

    GameLogic(player1, player2);

    result();

    playAgain(player1, player2);
  }
};

// ========== HIDDEN NUMBER GUESSING ==========
class HiddenNumber : public virtual Game
{
private:
  int maxAttempts;
  int range;

  Player *player;

public:
  void set()
  {
    maxAttempts = 10;
    range = 100;
  }

  void Interface(Player &player1, Player &player2)
  {
    clearScreen();
    cout << "\n";
    cout << BOLD << HOT_PINK << string(50, '=') << RESET << "\n";
    cout << "                " << NEON_CYAN << "HIDDEN NUMBER GUESSING" << RESET << "\n";
    cout << BOLD << HOT_PINK << string(50, '=') << RESET << "\n";
    cout << NEON_YELLOW << "      |        Terminal Edition v1.0       |" << RESET << "\n";
    cout << BOLD << HOT_PINK << string(50, '-') << RESET << "\n";

    cout << NEON_ORANGE << " Rules:" << RESET << "\n";
    cout << " - Guess the secret number within " << FIREBALL_RED << maxAttempts << RESET << " attempts.\n";

    cout << BOLD << HOT_PINK << string(50, '-') << RESET << "\n";
    cout << NEON_CYAN << "|   Press Enter to start playing!   |" << RESET << "\n";
    cout << BOLD << HOT_PINK << string(50, '=') << RESET << "\n\n";

    cin.ignore();
    cin.get();
  }

  void GameLogic(Player &player1, Player &player2)
  {
    int totalScore = 0;
    srand(time(0));
    int secret = rand() % range + 1;
    int levelPoints = 0;

    cout << NEON_ORANGE << "Guess the secret number between "
         << LIME_GREEN << "1" << NEON_ORANGE << " and "
         << NEON_YELLOW << range << NEON_ORANGE << ". You have "
         << FIREBALL_RED << maxAttempts << NEON_ORANGE << " attempts." << RESET << endl;

    for (int attempt = 1; attempt <= maxAttempts; attempt++)
    {
      int guessNum;
      cout << NEON_CYAN << "Attempt " << attempt << " of "
           << maxAttempts << RESET << ": ";
      cin >> guessNum;

      if (guessNum == secret)
      {
        levelPoints = maxAttempts - attempt + 1;
        cout << "\n\n";
        cout << BGREEN << BOLD << "Congratulations! " << RESET
             << HOT_PINK << "You guessed the secret number "
             << secret << " in " << attempt << " attempts!" << RESET << endl;
        cout << NEON_YELLOW << "Points earned: " << levelPoints << RESET << endl;
        break;
      }
      else if (guessNum < secret)
      {
        cout << NEON_YELLOW << "Too " << NEON_GREEN << "low" << NEON_YELLOW
             << ", try a higher number." << RESET << endl;
      }
      else
      {
        cout << NEON_YELLOW << "Too " << NEON_RED << "high" << NEON_YELLOW
             << ", try a lower number." << RESET << endl;
      }

      if (attempt == maxAttempts)
      {
        levelPoints = 0;
        cout << "\n\n";
        cout << BRED << BOLD << "YOU Failed !!! \nYou've used all attempts! " << RESET
             << NEON_YELLOW << "The secret number was " << secret << "." << RESET << endl;
        cout << NEON_YELLOW << "Points earned: " << levelPoints << RESET << endl;
      }
    }

    totalScore += levelPoints;
    player->addWin(2, totalScore);
    cout << BOLD << NEON_YELLOW << "\nYour total score: " << totalScore << RESET << endl;
  }

  void play(Player &player1, Player &player2)
  {
    clearScreen();
    set();
    Interface(player1, player2);
    player = &selectPlayer(player1, player2);
    GameLogic(player1, player2);
    playAgain(player1, player2);
  }
};

// ========== Player details ==========
class playersDetails : public virtual TicTacToe,
                       public virtual RockPaperScissors,
                       public virtual HiddenNumber
{

public:
  void set() {} // Not used for competition setup

  void Interface(Player &p1, Player &p2)
  {}

  void GameLogic(Player &p1, Player &p2)
  {
  }

  void play(Player &p1, Player &p2)
  {
    p1.playersDetailsMenu(p2);
  }
};

// ========== GAMEHUB ==========
class GameHub
{

  Player player1, player2;

public:

  void showMenu()
  {
    clearScreen();
    cout << "\n";
    cout << BOLD << HOT_PINK << string(45, '=') << RESET << "\n";
    cout << "                " << NEON_CYAN << "GAMEHUB" << RESET << " " << "\n";
    cout << BOLD << HOT_PINK << string(45, '=') << RESET << "\n\n";

    cout << NEON_YELLOW << " 1. TicTacToe\n"
         << " 2. Rock Paper Scissors\n"
         << " 3. Hidden Number Guessing\n"
         << " 4. Players Details\n"
         << " 0. Exit\n"
         << RESET;

    cout << "\n"
         << NEON_CYAN << " | " << RESET
         << FIREBALL_RED << player1.getName() << RESET << NEON_CYAN << " | \t | " << RESET
         << FIREBALL_RED << player2.getName() << RESET << NEON_CYAN << " | \n"
         << RESET;

    cout << "\n"
         << LIME_GREEN << "Enter your choice: " << RESET;
  }

  void run()
  {
    int choice;
    do
    {
      showMenu();
      cin >> choice;
      Game *game = nullptr;

      switch (choice)
      {
      case 1:
        game = new TicTacToe();
        break;
      case 2:
        game = new RockPaperScissors();
        break;
      case 3:
        game = new HiddenNumber();
        break;
      case 4:
        game = new playersDetails();
        break;

      case 0:
        cout << BGREEN << "Thank you for playing GameHub!" << RESET << "\n";
        break;
      default:
        cout << BRED << "Invalid choice!" << RESET << "\n";
        break;
      }

      if (game)
      {
        game->play(player1, player2);
        delete game;
      }
    } while (choice != 0);
  }
};

// ========== MAIN ==========
int main()
{
  GameHub hub;
  hub.run();

  return 0;
}
