//miniprojet

#include<Grapic.h>
#include <iostream>
using namespace std;
using namespace grapic;
const int DIMW = 500;
const int MAXSTAR =50;
const int MAXFISH =5;
const int MAXCORAL=2;
const int MAXBALL =100;

struct Complex
{ float x; //reel
  float y; //imagine
};
struct Color
{
    int r,g,b;

};
Color make_color (int r, int g, int b)
{
    Color c ;
    c.r= r;
    c.g= g;
    c.b =b;
    return c;
}
Complex make_Complex(float x, float y )
{
    Complex c ;
    c.x=x; //creer partie reel
    c.y=y; //creer partie imagine
    return c;
}
Complex make_Complex_exp (float r, float theta_deg)
{
    Complex c ;
    float theta = theta_deg*M_PI/180.0;
    c.x = r*cos(theta);
    c.y =r*sin(theta);
    return c;
}
Complex operator+( Complex c1, Complex c2)
{
    Complex c;
    c.x = c1.x+c2.x; //partie reel 1 + partie reel 2
    c.y = c1.y+c2.y; //partie imagine 1 + partie imagine 2
    return c;
}
Complex operator-(Complex c1, Complex c2)
{
    Complex c;
    c.x = c1.x - c2.x; //partie reel 1 - partie reel 2
    c.y = c1.y - c2.y; //partie imagine 1 - partie imagine 2
    return c;

}

Complex operator*(Complex c ,float lambda)
{
    Complex c2;
    c2.x = c.x*lambda;
    c2.y = c.y*lambda;
    return c2;
}
Complex operator* (Complex c1,Complex c2) //(a+bi) * (a1+b1i)= aa1-bb1 + i (ab1+a1b)
{
    Complex c ;
    c.x= c1.x * c2.x - c1.y*c2.y; //
    c.y = c1.x * c2.y + c1.y * c2.x;
    return c;
}
float distance(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}
struct sea
{
    Complex pos;
};

struct star
{  Complex pos;
   Color col;
};
struct sky
{
    star S[MAXSTAR];
    int nbstar; //nombre etoile
};
struct ship
{ Complex pos;
   float angle;
};
struct fish
{ Complex pos[MAXFISH];
   Image fish[MAXFISH];
     int radius[MAXFISH];
     int nbf;
};
struct moon {};
struct ball//balle
{ Complex p;
  Complex v;
  Complex f;
  float m ;
};
struct world
{
     int nbp;
     ball P[MAXBALL];
};
struct bulle //bulle d'air
{  Complex pos;
   Color col;
};
struct world_bulle
{
    int nb_bulle;
    bulle B[MAXBALL];
};
struct net //filet
{
    Complex pos;
    int radius;
};
struct coral
{
    Complex pos[MAXCORAL];
    Image coral[MAXCORAL];
};
//la lune
ball ball_Init ()
{
    ball bal ;
    bal.p = make_Complex(DIMW / 4, DIMW -100);
    bal.v=make_Complex(rand ()%101 -50,rand ()%40 +10);
    bal.m= 1.0;
    bal.f=make_Complex(0,0);
    return bal;
}

void addforce(ball &bal, Complex F )
{
    bal.f=bal.f + F ;
}
//bulle d'air
void init_bulle(world_bulle &b, int nbbulle)
{
    int i ;
    b.nb_bulle = nbbulle;
    for ( int i=1; i<= b.nb_bulle; i++)
    {
        b.B[i].pos = make_Complex(rand()% 500 , rand()%200 );
        b.B[i].col= make_color(rand()% +70,50,rand()% 255 +100 );
    }
}
//ciel
void init_Sky ( sky &sk, int nbstar)
{  int i;
    sk.nbstar=nbstar;
    for ( i=0; i< sk.nbstar; i++)
    {
      sk.S[i].pos = make_Complex(rand()% 500 + 10, rand ()% 500+200);
      sk.S[i].col = make_color(rand()% DIMW, rand ()% DIMW,rand ()% DIMW);
    }
}
//bateau
void init_Ship (ship &si)
{
    si.pos=make_Complex(150, 190);
    si.angle =600;
}
void init_fishNet( fish &fi,net &ne)
{
    int i;
    fi.nbf= 5;
    for (int i=0; i< fi.nbf; i++)
    {
         fi.radius[i]= 40;
    }

        fi.pos[0]=make_Complex (50, 70);
        fi.fish[0]=image("data/projet/fish1.png");

         fi.pos[1] = make_Complex(90, 100);
        fi.fish[1]=image("data/projet/fish2.png");

        fi.pos[2] = make_Complex (10,10);
        fi.fish[2]=image("data/projet/fish3.png");

        fi.pos[3] = make_Complex (440, 150);
        fi.fish[3]=image("data/projet/fish4.png");

        fi.pos[4] = make_Complex (480, 40);
        fi.fish[4]=image ("data/projet/shrimp.png");
        //filet de pêche
        ne.pos.x= 150;
        ne.pos.y= 150;
        ne.radius=20;

}
void Init_Coral (coral &C)
{
        C.pos[0]=make_Complex(0, 5);
        C.coral[0]=image("data/projet/coral2.png");

        C.pos[1]=make_Complex(450, 10);
        C.coral[1]=image("data/projet/coral3.png");

}
void draw (sea S,sky sk, ship si,fish fi,net ne,coral C, world_bulle b)
{   Complex an = make_Complex_exp(20,si.angle);

      int i ;
      int nbstar =50;
      //sea
    color (121, 248, 248) ;
    rectangleFill(0,0,DIMW, 200);
    //stars
     for (int i=0; i< nbstar; i++)
    {     color( sk.S[i].col.r, sk.S[i].col.g, sk.S[i].col.b);
         circleFill(sk.S[i].pos.x, sk.S[i].pos.y , 2);
        }

//ship
      color (249, 235,234);
      rectangleFill(si.pos.x, si.pos.y  , si.pos.x + 90 , si.pos.y + 50);
      line (si.pos.x + 45,si.pos.y + 50, si.pos.x + 45, si.pos.y + 130  );

      color (243,156,18);
     triangleFill(si.pos.x , si.pos.y + 80,si.pos.x + 45, si.pos.y + 140,si.pos.x + 45, si.pos.y + 80 );
//wheel
        color (255,  rand()% DIMW,rand()% DIMW);
     circleFill(si.pos.x + 24, si.pos.y + 25, 20);
     circleFill (si.pos.x + 67, si.pos.y +25, 20);

      color ( 0,0,0);
      circleFill(si.pos.x + 25, si.pos.y + 25, 1);
         circleFill (si.pos.x + 66, si.pos.y +25, 1);
         line (si.pos.x + 25, si.pos.y + 25,si.pos.x + 25 -an.x,si.pos.y + 25 +an.y );
         line (si.pos.x + 66, si.pos.y +25 , si.pos.x + 66 -an.x,si.pos.y + 25 +an.y);
         //fish
      for (int i =0; i< fi.nbf; i++)
   {
       image_draw (fi.fish[i],fi.pos[i].x,fi.pos[i].y,fi.radius[i],fi.radius[i]);
   }
    //net
           color (0,0,0);
           circle(ne.pos.x,ne.pos.y  ,ne.radius);

//Coral
    for ( int i=0; i< MAXCORAL; i++)
    {
        image_draw(C.coral[i], C.pos[i].x, C.pos[i].y, 50, 55);
    }
           //bulle
          int nb_bulle =20;
           for (int i=0; i<20;i++)
           {
               color (b.B[i].col.r,b.B[i].col.g,b.B[i].col.b);
               circleFill(b.B[i].pos.x, b.B[i].pos.y , 4);
           }

//regle
     color (171,235,198);
     rectangleFill(390, 450, 500, 500 );
     color(0,0,0);
     fontSize(14);
      print(392,480,"Using arrow keys ");
      print(392,460,"for the game ");

}

void update_ShipBulle (ship &Si, world_bulle &wb)
{
     //Déplacez le navire et le moteur fonctionne
    float ecart = 100;
    const float vitesse = 0.1;
    Si.angle += ecart * sin(vitesse * elapsedTime());

    if (Si.pos.x >2) Si.pos.x +=0.03f;

//update bulle
  int nb_bulle=20;
    for (int i= 0 ; i< nb_bulle; i++)
     {
         wb.B[i].pos.y += 0.05f;
         {if (wb.B[i].pos.y > 200)
         wb.B[i].pos.y = 2;
         }

     }
}
void update_FishNet(fish &fi,net &ne, bool &iswin )
{
   //move net
      if (isKeyPressed(SDLK_UP)) ne.pos.y += 7;
     if (isKeyPressed(SDLK_DOWN)) ne.pos.y  -= 7;
     if (isKeyPressed(SDLK_LEFT)) ne.pos.x-= 7;
     if (isKeyPressed(SDLK_RIGHT)) ne.pos.x += 7;

//move fish
      for (int i =0; i< fi.nbf; i++)
    {
        fi.pos[0].x += 0.01f;
        fi.pos[1].x += 0.01f;
         fi.pos[2].x += 0.03f;
          fi.pos[3].x -= 0.02f;
           fi.pos[4].x -= 0.02f;

        if (fi.pos[i].x <0 ) fi.pos[i].x =500;
        if (fi.pos[i].x >500) fi.pos[i].x =0;

//la collision entre le filet et des poissons
        float d = distance(fi.pos[i].x, fi.pos[i].y, ne.pos.x, ne.pos.y);

        if (d < fi.radius[i] + ne.radius)
    {
       fi.radius[i]=0; //les poissons disparaissent quand le filet touche
    }

} bool allfishdead = true ;
  for (int i=0; i< fi.nbf; i++)
  {
       if (fi.radius[i] > 0) {
            allfishdead= false;
            break;
  }
    }
 if (allfishdead) {
        iswin = true;
    }
}

void draw_moon ( moon mo)
{
        color (247, 220,111);
    circleFill(DIMW / 4, DIMW -100, 100);
}
void update_moon ( ball &bal, float dt)
    {
        bal.f=make_Complex(0,0);
    addforce(bal, make_Complex( 0, -9.81));
   bal.v=bal.v + bal.f * (1/bal.m) * dt;
    bal.p= bal.p + bal.v * dt ;

    //mur
     float  distance = sqrt ( pow ( DIMW/4 -bal.p.x ,2)
                           + pow ( DIMW -100 - bal.p.y  ,2));

     float sortie = distance - 100;

   if ( distance > 100 && bal.p.y > DIMW) //haut
    {
        bal.p.y = -bal.p.y ;
          bal.v. y = - bal.v.y ;
        bal.v = bal.v * 0.9;
        }
    if (distance > 100 && bal.p.y <400) //bas
      {
          bal.p.y = 400- sortie  ;
          bal.v.y = -bal.v.y;
          bal.v = bal.v ;
      }

   if (distance > 100 && bal.p.x > (DIMW /4))//droite
   {
       bal.p.x = bal.p.x - sortie ;
       bal.v.x = - bal.v .x;
       bal.v = bal.v *0.9;}

   if ( distance > 100 && bal.p.x < (DIMW/4)) //gauche
       {
           bal.p.x = bal.p.x + sortie  ;
           bal.v.x = - bal.v.x ;
           bal.v = bal.v *0.9;
       }

     }

int main(int , char**)
{
     bool stop = false;
	winInit("Jeu de peche",DIMW ,DIMW);
	sea se;
	sky sk;
	ship si;
	fish fi;
	coral C;
	net ne;
	moon mo;
	world W;
	world_bulle wb;

	bool iswin =false;

	float dt = 0.005;
	ball bal;
	bal= ball_Init();
	 for ( int i =0 ; i<MAXBALL ; i++)
     {
         W.P[i] =ball_Init();
     }
	init_Sky (sk , 50);
	init_Ship(si);
	init_fishNet(fi,ne);
	Init_Coral(C);
	init_bulle(wb,20);
	backgroundColor(0,0,0);
	while (!stop )
    {
        winClear();
        draw(se,sk,si,fi,ne,C,wb);
       draw_moon(mo);
        update_ShipBulle(si,wb);
        update_FishNet(fi,ne,iswin);
        if (iswin) //changer la couleur de fond lorsque tous les poissons disparaissent
        {
            backgroundColor(170,80,240);
            fontSize(50);
            color (255,255,0);
            print(150,240, "You Win!");
        }

         for ( int i =0; i<MAXBALL ; i++)
    {
        update_moon(W.P[i], dt);
        color ( 255,(i*255)/MAXBALL, 255 - (i*255)/MAXBALL);
        circleFill(W.P[i].p.x , W.P[i].p.y ,3);
    }
        stop =winDisplay();
    }
	winQuit();
	return 0;
}
