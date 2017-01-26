#include <Thread.h>
#include <ThreadController.h>
#include <fontALL.h>
#include <TVout.h>
#include <video_gen.h>
#include <EEPROM.h>

TVout TV;
const int MAX_X = 110;
const int MAX_Y = 88;
const int TEXT_X = 9;
const int MAX_CHAR = 19;
const int option = 0;

const int LastStateDown = 1;
const int LastStateUp = 1;
const int LastStateA = 1;
const int LastStateB = 1;
const int LastStateLeft = 1;
const int LastStateRight = 1;

const int PULL_DOWN  0
const int PULL_UP 1
  
//GAME CONTROLLER
const int BUTTON_A_PORT = 13;
const int BUTTON_B_PORT = 12;
const int BUTTON_UP_PORT = 4;
const int BUTTON_DOWN_PORT = 5;
const int BUTTON_LEFT_PORT = 6;
const int BUTTON_RIGHT_PORT = 7;

void setup() {
  //GAME CONTROLLER PIN_MODE INPUT
  pinMode(BUTTON_A_PORT, INPUT);
  pinMode(BUTTON_B_PORT, INPUT);
  pinMode(BUTTON_UP_PORT, INPUT);
  pinMode(BUTTON_DOWN_PORT, INPUT);
  pinMode(BUTTON_LEFT_PORT, INPUT);
  pinMode(BUTTON_RIGHT_PORT, INPUT);
  digitalWrite(BUTTON_UP_PORT, HIGH);
  digitalWrite(BUTTON_DOWN_PORT, HIGH);
  digitalWrite(BUTTON_A_PORT, HIGH);
  digitalWrite(BUTTON_B_PORT, HIGH);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  //TV BEGIN
  TV.begin(PAL, 120, 96);
  TV.select_font(font6x8);
  intro();
  //Pongintro();
  TV.clear_screen();
}

void loop() {
  bool exit = false;
  menu();
  TV.print_char(0, 20, '-');
  while(!exit)
  {
    if(digitalRead(BUTTON_UP_PORT) == PULL_DOWN)
    {
      TV.print_char(0, 40, ' ');
      TV.print_char(0, 20, '-');
      option = 0;
    }
    else if(digitalRead(BUTTON_DOWN_PORT) == PULL_DOWN)
    {
      TV.print_char(0, 20, ' ');
      TV.print_char(0, 40, '-');
      option = 1;
    }
    else if(digitalRead(BUTTON_A_PORT) == PULL_DOWN)
    {
      if(option == 0)
      {
        SImain();
      }
      else
      {
        Exit = Pongplay();
      }
    }
  }

}

void intro()
{
  for(int i = 0; i <= MAX_Y/2; i++)
  {
    TV.print(0, i, "CREADO POR DAVIDC96");
    delay(150);
    if(i != 0 && i != MAX_Y/2)
    {
     TV.print(0, i-1, "                   ");
    }
   }
   delay(3000);
}

void menu()
{
  TV.println("--------MENU-------");
  TV.println("\n");
  TV.print(10, 20, "SPACEINVADERS");
  TV.print(10, 40, "PONG");
  TV.print(0, 70, "USA LOS BOTONES ARRIBA Y ABAJO");
  TV.print(0, 88, "PULSE A PARA JUGAR");
}

//JUEGO PONG////////////////////////
bool Pongplay()
{
  TV.clear_screen();
  int IALevel = 1;
  bool gameExit = false;
  int StateUP;
  int StateDOWN;
  int StateA;
  option = 0;
  Pongintro();
  TV.clear_screen(); 
  PonggameMenu();
  TV.print_char(0, 20, '-');
   
  //Bucle del menu
  while(!gameExit)
  {
    StateUP = digitalRead(BUTTON_UP_PORT);
    StateDOWN = digitalRead(BUTTON_DOWN_PORT);
    if(StateUP == PULL_DOWN)
    {
     if(LastStateUp != StateUP)
     {
      if(option == 1)
      {
       TV.print_char(0, 40, ' ');
       TV.print_char(0, 20, '-');
       option = 0;
      }
      else if(option == 2)
      {
        TV.print_char(0, 60, ' ');
        TV.print_char(0, 40, '-');
        option = 1; 
      }
     }
    }
    else if(StateDOWN == PULL_DOWN)
    { 
      if(LastStateDown != StateDOWN)
      {
      if(option == 0)
      {
        option = 1;
        TV.print_char(0, 20, ' ');
        TV.print_char(0, 40, '-');
       }
      else if (option == 1)
      {
        TV.print_char(0, 40, ' ');
        TV.print_char(0, 60, '-');
        option = 2;
      } 
     }
   }
    else if(digitalRead(BUTTON_A_PORT) == PULL_DOWN)
    {
      if(option == 0)
      {
        PongGame(IALevel);
      }
      else if(option == 1)
      {
        PongDemoGame(IALevel);
      }
      else if(option == 2)
      {
        gameExit = true;
      }
    }
    LastStateUp = StateUP;
    LastStateDown = StateDOWN;
//    delay(100);
  }
  
  delay(2000);
  TV.clear_screen();
  intro();
  TV.clear_screen();
  return gameExit;
}

void Pongintro()
{
  for(int i = 0; i <= MAX_Y/2 + 10; i++)
  {
    TV.print(0, i, "POWERED BY TECNOUAB");
    delay(100);
    if(i != 0 && i != MAX_Y/2 + 10)
    {
     TV.print(0, i-1, "                     ");
    }
  }
  delay(5000);
  TV.clear_screen();
  for(int i = 0; i <= MAX_Y/2; i++) 
  {
    TV.print(MAX_X/2 - 30, i, "CRAZY PONG");
    delay(100);
    if(i != 0 && i != MAX_Y/2)
    {
     TV.print(0, i-1, "               ");
    }
  }
     
  while(!digitalRead(BUTTON_A_PORT))
  {
    TV.println(0, MAX_Y/2 + 20, "PULSA A PARA CONTINUAR");  
  }
  delay(1000);
}

void PonggameMenu()
{
  TV.println("--------MENU-------");
  TV.println("\n");
  TV.print(10, 20, "JUGAR");
  TV.print(10, 40, "DEMO");
  TV.print(10, 60, "SALIR");
}

void PongDemoGame(int IALevel)
{
  delay(2000);
  int PX = 20;
  int PY = 40;
  int IAX = 100;
  int IAY = 20;
  int PilX = 58;
  int PilY = 45;
  int dirY = -1; //DIR Y: UP = -1 DOWN = 1
  int dirX = 1; //DIR X: LEFT = -1 RIGHT = 1
  int dirIA = 1;
  int dirIA2 = 1;
  int pl1Score = 0;
  int pl2Score = 0;
  bool fingame = false;
  TV.clear_screen();
  
  //Cargamos el backGround
  PongBackGround(PX, PY, IAX, IAY, pl1Score, pl2Score);
  while(digitalRead(BUTTON_A_PORT) != PULL_DOWN)
  {
   PongBackGround(PX, PY, IAX, IAY, pl1Score, pl2Score);
   ballMovement(PilX, PilY, PX, PY, IAX, IAY, dirY, dirX, 'O', pl1Score, pl2Score);
   IAMovement(IAX, IAY, dirIA, PilY, PilX, IALevel);
   IA2Movement(PX, PY, dirIA2, PilY, PilX, IALevel);
   //playerMovement(PX, PY);
   //player2Movement(IAX, IAY);
   //fingame = checkWin(pl1Score, pl2Score);
            
  }
  /*while(digitalRead(BUTTON_A_PORT) != PULL_DOWN)
  {
    TV.println(0, 60, "Pulsa A para continuar");
  
  
  }*/
  delay(2000);
  Pongplay();
}

/* I will add a comment here */
  int PX = 20;
  int PY = 40;
  int IAX = 100;
  int IAY = 20;

void PongGame(int IALevel)
{
  int PilX = 58;
  int PilY = 45;
  int dirY = -1; //DIR Y: UP = -1 DOWN = 1
  int dirX = 1; //DIR X: LEFT = -1 RIGHT = 1
  int dirIA = 1;
  int dirIA2 = 1;
  int pl1Score = 0;
  int pl2Score = 0;
  bool fingame = false;
  TV.clear_screen();
  //Cargamos el backGround
  PongBackGround(PX, PY, IAX, IAY, pl1Score, pl2Score);
  Thread player = Thread();
  Thread player2 = Thread();
  player.enabled = true;
  player.setInterval(1000000);
  player.onRun(playerMovement);
  player2.enabled = true;
  player2.setInterval(1000000);
  player2.onRun(player2Movement);
  
  while(!fingame)
  {
   PongBackGround(PX, PY, IAX, IAY, pl1Score, pl2Score);
   ballMovement(PilX, PilY, PX, PY, IAX, IAY, dirY, dirX, 'O', pl1Score, pl2Score);
   player2.run();
   player.run();
//   IAMovement(IAX, IAY, dirIA, PilY, PilX, IALevel);
//   playerMovement(PX, PY);
//   player2Movement(IAX, IAY);
   fingame = checkWin(pl1Score, pl2Score);
            
  }
  while(digitalRead(BUTTON_A_PORT) != PULL_DOWN)
  {
    TV.println(0, 60, "Pulsa A para continuar");
  }
  Pongplay();
}

void PongBackGround(int PX, int PY, int IAX, int IAY, int pl1Score, int pl2Score)
{
  TV.draw_rect(10, 10, 100, 80, WHITE);
  TV.draw_line(60, 10, 60, 90, WHITE);
  //TV.print_char(58, 45, 'O');
  //Dibujar a los jugadores
  TV.draw_line(PX, PY, PX, PY+20, WHITE);
  TV.draw_line(IAX, IAY, IAX, IAY+20, WHITE);
  //Dibujar el Marcador
  PongScore(pl1Score,pl2Score);
}

void PongScore(int pl1score, int pl2score)
{
  TV.println(40, 0, pl1score);
  TV.println(58, 0, "-");
  TV.println(70, 0, pl2score);
}

void ballMovement(int &X, int &Y, int PX, int PY, int IAX, int IAY, int &dirY, int &dirX, char ball, int &pl1score, int &pl2score)
{ 
  TV.print_char(X, Y, ' ');
 
  if(Y <= 12)
  {
    if(dirY == 2)
    {
    dirY = 2;
    }
    else
    {
      dirY = 1;
    }
  }
  if (Y >= 82)
  {
    if(dirY == -2)
    {
    dirY = -2;
    }
    else
    {
      dirY = -1; 
    }
  }
  if(X <= 12)
  {
   pl2score += 1;
   resetBall(X, Y);
   dirX = 1;
  }
  if(X >= 104)
  {
   pl1score += 1;
   resetBall(X, Y);
   dirX = -1;
  }

  if((Y >=PY - 5 && Y <= PY + 4) && X == PX)
  {
    dirX = 1;
    dirY = random(-2,0);
  }
  if((Y >=PY + 5 && Y <= PY + 14) && X == PX)
  {
    dirX = 1;
    if (dirY == 0)
    {
      dirY = random(-2,2);
    }
    else
    {
      dirY = 0;
    }
  }
  if((Y >=PY + 15 && Y <= PY + 20) && X == PX)
  {
    dirX = 1;
    dirY = random(1,2);
  }
  if((Y >= IAY - 5 && Y <= IAY + 4) && X == IAX - 5)
  {
    dirX = -1;
    dirY = random(-2, 0);
    
  }
   if((Y >= IAY + 5 && Y <= IAY + 14) && X == IAX - 5)
  {
    dirX = -1;
    dirY = random(-1, 1);
    if (dirY == -1 || dirY == 1) dirY = random(-1, 1);
   
  }
   if((Y >= IAY + 15 && Y <= IAY + 20) && X == IAX - 5)
  {
    dirX = -1;
    dirY = random(0, 2);
    
  }
  
  X += 1 * dirX;
  Y += 1 * dirY;
  TV.print_char(X, Y, ball);
  delay(50);

}

void playerMovement()
{
    TV.draw_line(PX, PY, PX, PY+20, BLACK);
    int StateDOWN = digitalRead(BUTTON_DOWN_PORT);
    int StateUP = digitalRead(BUTTON_UP_PORT);
    if(StateDOWN == PULL_DOWN)
    {
      if(PY + 20 <= 88)
      PY += 2;  
    }
    else if(StateUP == PULL_DOWN)
    {
      if(PY >= 12) 
      PY += -2;
    }
}

void player2Movement()
{
  TV.draw_line(IAX, IAY, IAX, IAY+20, BLACK);
  int StateDOWN = digitalRead(BUTTON_B_PORT);
  int StateUP = digitalRead(BUTTON_A_PORT);
  if(StateDOWN == PULL_DOWN)
  {
    if(IAY + 20 <= 88)
    IAY += 2;  
  }
  else if(StateUP == PULL_DOWN)
  {
    if(IAY >= 12) 
    IAY += -2;
  }
}

void IAMovement(int &IAX, int &IAY, int &dir, int PY, int PX, int nivel)
{
  TV.draw_line(IAX, IAY, IAX, IAY+20, BLACK);
  if(IAY > PY)
  {
    dir = -1;
  }
  if(IAY < PY)
  {
    dir = 1;
  }
  if(IAY + 20 >= 88)
  {
    dir = -1;
  }
  if(PX > 50)
  {
  IAY += 1 * dir * nivel;
  }
}

void IA2Movement(int &IAX, int &IAY, int &dir, int PY, int PX, int nivel)
{
  TV.draw_line(IAX, IAY, IAX, IAY+20, BLACK);
  if(IAY > PY)
  {
    dir = -1;
  }
  if(IAY < PY)
  {
    dir = 1;
  }
  if(IAY + 20 >= 88)
  {
    dir = -1;
  }
  if(PX < 50)
  {
  IAY += 1 * dir * nivel;
  }
}

void resetBall(int &X, int &Y)
{
 X = 55;
 Y = 45;
}

bool checkWin(int pl1score, int pl2score)
{
 PongScore(pl1score, pl2score);
 bool gamefinish = false;
 if(pl1score >= 3)
 {
   TV.println(3, 45, "JUGADOR 1 HA GANADO");
   gamefinish = true;    
 }
 if(pl2score >= 3)
 {  
  TV.println(3, 45, "JUGADOR 2 HA GANADO");
  gamefinish = true;
 }
  return gamefinish;
}

//---------------------Space Invaders----------------------------
//--------------Definitions---------------
/* I will put the definitions into another file */
typedef struct
{
  int PosX;
  int PosY;
  bool visible;
  char graphic;
}Laser;

typedef struct
{
  int ShipX;
  int ShipY;
  int counter;
  int score;
}Player;

typedef struct
{
  int ID;
  char graphic;
  int points;
  bool visible;
  int PosX;
  int PosY;
}Invaders;

const int MAX_ALIENS 20
Invaders invaders[MAX_ALIENS];
Player player;
Laser laser;

void LoadAllData()
{
  int i;
  
  //Initialize Player Data
  player.ShipY = 100;
  player.ShipX = 50;
  player.score = 0;
  player.counter = 0;

  //Initialize Laser Data
  laser.PosX = 0;
  laser.PosY = 0;
  laser.visible = false;
  laser.graphic = '|';
  int c = 0;
  int d = 0;
  int e = 0;
  
  //Initialize Invaders Data
  for(i = 0; i < MAX_ALIENS; i++)
  {
    invaders[i].ID = i;
    if(i < 10)
    {
      invaders[i].graphic = 'B';
      invaders[i].points = 100;
      invaders[i].PosX = 0 + c*10;
      invaders[i].PosY = 20;
      invaders[i].visible = true;
      c++;
    }
    else if(i < 21 && i >= 10)
    {
      invaders[i].graphic = 'A';
      invaders[i].points = 75;
      invaders[i].PosX = 0 + d*10;
      invaders[i].PosY = 10;
      invaders[i].visible = true;
      d++;
    }/*
    else if( i < 34 && i >= 24)
    {
      invaders[i].graphic = 'B';
      invaders[i].points = 50;
      invaders[i].PosX = 20 + e*10;
      invaders[i].PosY = 30;
      invaders[i].visible = true;
      e++;
    }*/
  TV.print_char(invaders[i].PosX, invaders[i].PosY, invaders[i].graphic);
  }
}
void UpdateInvadersPosition(int oldX[], int oldY[])
{
  Serial.println("---------- UpdateInvaderPosition----------");
    for(int i = 0; i < MAX_ALIENS; i++)
    {
      if(invaders[i].visible != false)
      {   
        TV.print_char(oldX[i], oldY[i], ' ');
        invaders[i].PosX += 5;
        TV.print_char(invaders[i].PosX, invaders[i].PosY, invaders[i].graphic);
        Serial.println(invaders[MAX_ALIENS - 1].PosX);
      }
    }
    Serial.println("---------- UpdateInvaderPosition----------");
}

void LaserCollision()
{
  for(int i = 0; i < MAX_ALIENS; i++)
  {
    if(laser.PosX == invaders[i].PosX && laser.PosY == invaders[i].PosY)
    {
      invaders[i].visible = false;
      laser.visible = false;
      player.score += invaders[i].points;
    }
  }
}

void LaserMovement()
{
 if(laser.visible == true)
 {
  laser.PosY -= 5;
  if (laser.PosY < 0) 
  {
    laser.visible = false;
  }
 }
}

void updateLaserPosition()
{
  if(laser.visible == true)
  {
    TV.print_char(laser.PosX, laser.PosY, laser.graphic);
  }
}

void SImain()
{
 TV.clear_screen();
 LoadAllData();
 int i = 0;
 bool finish = false;
 int oldX[MAX_ALIENS];
 int oldY[MAX_ALIENS];
 int counter = 0;
 int desp = 0;
 while(!finish)
 {
    //Baja muy lento
    if(i >= MAX_ALIENS)
    {
      UpdateInvadersPosition(oldX, oldY);
      i = 0;
      if(counter >= 3)
      {
        counter = 0;
        desp = 0;
      }
      else
      {
        counter++;
      }

      desp += 5; 
      //(1);
    }
    else
    {
      oldY[i] = invaders[i].PosY;
      Serial.println("---------- Bucle----------");
      Serial.println(counter);
      oldX[i] = invaders[i].PosX;
      if(counter == 3)
      {
        oldY[i] = invaders[i].PosY;
        invaders[i].PosY += 10;
        Serial.println(invaders[MAX_ALIENS - 1].PosX);
        invaders[i].PosX -= desp;
        Serial.println(invaders[MAX_ALIENS - 1].PosX);
      }
      
      i++;
    } 
 }
}
