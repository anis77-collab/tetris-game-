#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#include<time.h>
using namespace sf;


struct point{
  int x,y;
}a[4],tmp[4];

const int C =21;
const int N =15;

int field[C][N]={0};

int pieces[7][4]={
     1,  4,  7, 10, //I
     3,  6,  7, 10, //Z
     4,  7,  6, 9 , //S
     4,  7,  6, 10, //T
     3,  4,  7, 10, //L
     4,  7,  10, 9, //J
     3,  4,  6,  7, //O
    };

    //verify the collision between the border and the pieces

bool verify(){
for(int i=0; i <4; i++){
  if(a[i].x<0||a[i].x>=N||a[i].y>=C) return 1;
  else if(field[a[i].y][a[i].x] )return 1;
}
    return 0;
}

int main(){


  srand(time(0));

  RenderWindow window(VideoMode(330, 540), "let's play Tetris!!");

  Texture t1,t2;
  t1.loadFromFile("tiles.png");
  t2.loadFromFile("back.jpg");
  Sprite s(t1);
  Sprite s1(t2);

  s.setTextureRect(IntRect(0, 0, 18, 18));

  float timer =0, delay = 0.3;
  Clock clock;

  Music music;
  if (!music.openFromFile("Tetris.ogg"))
    return -1; // error

	music.play();
  music.setLoop(true); // play Music



  int dx= 0, max= 0; bool rotation = false; int color= 1;

  Font font;

  if(!font.loadFromFile("arial.ttf"))
 {
   return -1;
 }
std::cout<<"write your name :  ";
Text text,text1;
std::string name;  ///player name;
getline(std::cin, name);

text.setString(name); // Texte
text.setFont(font); // Fonte
text.setPosition(0, 420);




  while(window.isOpen()){
    float time =clock.getElapsedTime().asSeconds();
    clock.restart();
    timer+=time;

    Event e;
    while(window.pollEvent(e)){
      if(e.type == Event::Closed)
      window.close();
      if(e.type == Event::KeyPressed)
        if(e.key.code==Keyboard::Up) rotation = true;
          else if(e.key.code==Keyboard::Right) dx =1;
            else if(e.key.code==Keyboard::Left) dx= -1;


    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;


    // move to the bottom of the screen ///

    //   move HORIZANTLY ///
    for (int i =0; i<4 ; i++) {
        tmp[i] =a[i];
        a[i].x +=dx;
    }
    if (verify()){
      for(int i=0; i<4; i++){
        a[i]=tmp[i];
      }
    }

    /// rotation ////
    if(rotation){
      point center = a[1];
      for (int i =0; i<4 ; i++){
        int x =a[i].y-center.y;
        int y =a[i].x-center.x;

        a[i].x = center.x - x;
        a[i].y = center.y + y;
      }
      if (verify()){
        for(int i=0; i<4; i++){
          a[i]=tmp[i];
        }
      }
    }

    if (time!=0){

     int   count1=0;
    for(int j= 0; j<N-1; j++){
      if(field[1][j])count1++;
    }

    if(count1!=0) window.close();
  }


    if(timer>delay)
    {
      for(int i =0; i < 4; i++)
      {
        a[i]=tmp[i];
        a[i].y+=1;}

        if (verify()){
          for(int i=0; i<4; i++){
            field[tmp[i].y][tmp[i].x]=color;
          }
          color =1+rand()%7;
           int n= rand()%7;

           for (int i= 0; i<4; i++){
                a[i].x =pieces[n][i]%3;
                a[i].y =pieces[n][i]/3;
           }
        }


      timer =0;
    }

    // check every line ///
    int k=C-1;
        for (int i=C-1;i>0;i--)
        {
            int count=0;
            for (int j=0;j<N;j++)
            {
                if (field[i][j]) count++;
                field[k][j]=field[i][j];
            }
            if(count == N) max++;
          else  if (count<N) k--;

        }
      std::string  count = std::to_string(max);///  the high score
      text1.setString(count); // Texte
      text1.setFont(font); // Fonte
      text1.setPosition(0, 460);


    window.clear();
    window.draw(s1);

   dx= 0; rotation=false;delay =0.3;


   for(int i=0; i<C; i++){
     for(int j=0; j<N;j++){
       if (field[i][j]==0) continue;
       s.setTextureRect(IntRect(field[i][j]*18, 0, 18, 18));
       s.setPosition(j*18, i*18);
       s.move(28, 31);
       window.draw(s);
     }
   }


    for(int i= 0; i < 4;i++){
      s.setTextureRect(IntRect(color*18, 0,18, 18));
      s.setPosition(a[i].x*18, a[i].y*18);
      s.move(28, 31);
      window.draw(s);
    }

  window.draw(text);
  window.draw(text1);

  window.display();
  }


  std::cout<< " Game Over!!"<<std::endl;
  std::cout<< " player " << name << " high score " << max;
  return 0;

}
