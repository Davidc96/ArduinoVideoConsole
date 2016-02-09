#include <fontALL.h>
#include <TVout.h>
#include <video_gen.h>
#include <EEPROM.h>

TVout TV;
int MAX_X = 110;
int MAX_Y = 88;
int TEXT_X = 9;
int MAX_CHAR = 19;
int option = 0;

int LastStateDown = 1;
int LastStateUp = 1;
int LastStateA = 1;
int LastStateB = 1;
int LastStateLeft = 1;
int LastStateRight = 1;

#define PULL_DOWN  0
#define PULL_UP 1
//GAME CONTROLLER
int BUTTON_A_PORT = 2;
int BUTTON_B_PORT = 3;
int BUTTON_UP_PORT = 4;
int BUTTON_DOWN_PORT = 5;
int BUTTON_LEFT_PORT = 6;
int BUTTON_RIGHT_PORT = 7;

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
  Pongplay();
  TV.clear_screen();
 

}

void loop() {
  bool Exit = false;
   menu();
   TV.print_char(0, 20, '-');
  while(!Exit)
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
  TV.print(10, 20, "FROGGY");
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
        
      }
      else if(option == 2)
      {
        gameExit = true;
      }
    }
    LastStateUp = StateUP;
    LastStateDown = StateDOWN;
    //delay(250);
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
  TV.print(10, 40, "OPCIONES");
  TV.print(10, 60, "SALIR");
  






}
void PongGame(int IALevel)
{
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
  while(!fingame)
  {
   PongBackGround(PX, PY, IAX, IAY, pl1Score, pl2Score);
   ballMovement(PilX, PilY, PX, PY, IAX, IAY, dirY, dirX, 'O', pl1Score, pl2Score);
   IAMovement(IAX, IAY, dirIA, PilY, PilX, IALevel);
   playerMovement(PX, PY);
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
    dirY = 0;
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
    dirY = random(1, 2);
    
  }
  
  X += 1 * dirX;
  Y += 1 * dirY;
  TV.print_char(X, Y, ball);
  delay(50);

}
void playerMovement(int X, int &Y)
{
  TV.draw_line(X, Y, X, Y+20, BLACK);
  int StateDOWN = digitalRead(BUTTON_DOWN_PORT);
  int StateUP = digitalRead(BUTTON_UP_PORT);
  if(StateDOWN == PULL_DOWN)
  {
    if(Y + 20 <= 88)
    Y += 1;  
  }
  else if(StateUP == PULL_DOWN)
  {
    if(Y >= 12) 
    Y += -1;
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
  if(PX > 85)
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
 if(pl1score >= 5)
 {
   TV.println(5, 45, "JUGADOR 1 HA GANADO");
   gamefinish = true;    
 }
 if(pl2score >= 5)
 {  

   TV.println(5, 45, "JUGADOR 2 HA GANADO");
  gamefinish = true;
 }
  return gamefinish;

}

 
