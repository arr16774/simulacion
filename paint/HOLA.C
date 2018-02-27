//paint
//Rodrigo Juarez
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<malloc.h>
#include<dos.h>
#include<mem.h>

//liberia de mouse
#include<mouse.h>

//libreria para putpixel y getpixel y el cambio de modo
#include<pixel.h>

//carga y guardado de bitmaps
#include<load.h>
#include<bitmap.h>

//linea, spray, llenado y figuras
#include<figuras.h>

//screen in 13h is set to 320x200
//SVGA 0x101
//text 0x03

//variables para el mouse y funciones
int mx,my, mbutton,x0,y0,function,grosor,i,j,cont,cond;
//para while infinito
int t;
//color que se usa
char color;
char str[80];
int main (int argc, char *argv[]){
	int j;
	int i;
	int x;
	t=1;
	x=0;
	cont=0;
	cont=0;
	
	initvid(); // video interrupt

	//inicializacion del mouse y restriccion de la pantalla
	InitMouse();

	//iniciar mouse
	RestrictMousePtr(0,0,800,600);

	//valores iniciales: lapiz negro de grueso de un pixel
	color=17;
	function=1;
	grosor=1;


	//preparar el canvas
	canvas();


	x=1;
	//pintar los colores para seleccionar
	for (i=165; i<770;i++ ){
		for (j=520; j<580;j++){
			if(j<540){
				putpixel(i, j, x);
			}
			if(j>540 && j<560){
				putpixel(i, j, x+1);
			}
			if(j>560){
				putpixel(i, j, x+2);
			}
			if(i%20==0){
				putpixel(i,j,199);
			}
			if (x>256) x=0;
		}
		if(i%20==0)
			x+=3;
	}

	//el color actual
	for (i=20;i<=50;i++){
		for (j=520;j<=550;j++){
			putpixel(i,j,color);
		}
	}
	GetMousePos(&mbutton,&mx,&my);
	x0=mx;
	y0=my;
	mouseShow(x0,y0);

	//carga del menu del paint
	loadbitmap("C:\\TURBOC3\\Projects\\menu2.bmp",0,0);

	//while infinito que mantiene todo funcionando
	while(t==1){

		//captura y actualizacion del puntero del mouse
		GetMousePos(&mbutton,&mx,&my);
		if(x0!=mx || y0!=my){
			mouseHide(x0,y0);
			mouseShow(mx,my);
			x0=mx;
			y0=my;
		}
		recieve(mbutton,mx,my,color,grosor);

		//acciones del mouse
		if (mbutton==1){
			//nuevo;
			if (mx>4 && mx<43 && my>4 && my<38){
				sprintf(str,"temp%d.bmp",cont);
				save(str,150,3,647,497);
				cont++;
				canvas();
				cond=0;
			}
			if (mx>51 && mx<88 && my>5 && my<29){
				save("image.bmp",150,3,647,497);
				cond=0;
			}
			if (mx>97 && mx<138 && my>3 && my<38){
				sprintf(str,"temp%d.bmp",cont);
				save(str,150,3,647,497);
				cont++;
				mouseHide(mx,my);
				read("C:\\TURBOC3\\BIN\\image.bmp",150,3);
				mouseShow(mx,my);
				cond=0;
			}
			if(mx>46 && mx<64 && my>42 && my<53){
				if(cont>0){
					cont--;
					sprintf(str,"C:\\TURBOC3\\BIN\\temp%d.bmp",cont);
					read(str,150,3);
					cond=1;
				}
			}
			if(mx>85 && mx<99 && my>42 && my<53){
				if(cond==1){
					cont++;
					sprintf(str,"C:\\TURBOC3\\BIN\\temp%d.bmp",cont);
					read(str,150,3);
				}
			}
			if (mx>17 && mx<47 && my>60 && my<86)
				//coloca el grosor del lapiz en un pixel
				grosor=1;
			if (mx>58 && mx<91 && my>60 && my<86)
				//Coloca el grosor del lapiz en una cruz de tres pixeles
				grosor=2;
			if (mx>98 && mx<131 && my>60 && my<86)
				//Coloca el grosor del lapiz en una cruz de cuatro pixeles
				grosor=3;
			if (mx>17 && mx<62 && my>97 && my<140)
				//funcion de lapiz
				function=1;
			if (mx>77 && mx<123 && my>98 && my<140)
				//funcion de spray
				function=2;
			if (mx>17 && mx<62 && my>151 && my<192)
				//funcion de get color
				function=3;
			if (mx>77 && mx<123 && my>152 && my<194)
				//funcion de linea
				function=4;
			if (mx>17 && mx<62 && my>203 && my<247)
				//funcion de cuadrado
				function=5;
			if (mx>77 && mx<123 && my>204 && my<247)
				//triangulo
				function=6;
			if (mx>17 && mx<62 && my>252 && my<297)
				//circulo
				function=7;
			if (mx>77 && mx<123 && my>254 && my<298)
				//elipse
				function=8;
			if (mx>17 && mx<62 && my>305 && my<349)
				//poligono
				function=9;
			if (mx>77 && mx<123 && my>305 && my<349)
				//fill
				function=10;
			if (mx>17 && mx<62 && my>358 && my<400)
				//cut
				function=11;
			if (mx>77 && mx<123 && my>358 && my<400)
				//eraser
				function=12;
			if (mx>17 && mx<62 && my>410 && my<450)
				//copy
				function=13;
			if (mx>77 && mx<123 && my>410 && my<450)
				//paste
				function=14;
			if (mx>17 && mx<62 && my>410 && my<450);
				//function=15;
			if (mx>77 && mx<123 && my>461 && my<503)
				//exit
				t=2;

			if (mx>150 && mx<797 && my<500 && my>3){
				switch (function){
					case 1:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						lapiz();
						x0=mx;
						y0=my;
						mouseShow(x0,y0);
						cond=0;
						break;
					case 2:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						praynspray();
						x0=mx;
						y0=my;
						mouseShow(x0,y0);
						cond=0;
						break;
					case 3:
						color=getpixel(mx,my);
						for (i=20;i<=50;i++){
							for (j=520;j<=550;j++){
								putpixel(i,j,color);
							}
						}
						break;
					case 4:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						MoveMousePtr(mx,my);
						mouseShow(mx,my);
						line();
						x0=mx;
						y0=my;
						mouseShow(x0,y0);
						cond=0;
						break;
					case 5:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						MoveMousePtr(mx,my);
						mouseShow(mx,my);
						square();
						x0=mx;
						y0=my;
						mouseShow(x0,y0);
						cond=0;
						break;
					case 6:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						MoveMousePtr(mx,my);
						mouseShow(mx,my);
						triangle();
						x0=mx;
						y0=my;
						mouseShow(x0,y0);
						cond=0;
						break;
					case 7:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						MoveMousePtr(mx,my);
						mouseShow(mx,my);
						circle();
						x0=mx;
						y0=my;
						mouseShow(x0,y0);
						cond=0;
						break;
					case 8:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						MoveMousePtr(mx,my);
						mouseShow(mx,my);
						elipse();
						x0=mx;
						y0=my;
						mouseShow(x0,y0);
						cond=0;
						break;
					case 9:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						MoveMousePtr(mx,my);
						mouseShow(mx,my);
						polygon();
						x0=mx;
						y0=my;
						mouseShow(x0,y0);
						cond=0;
						break;
					case 10:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						MoveMousePtr(mx,my);
						mouseShow(mx,my);
						mouseHide(mx,my);
						fill(mx,my);
						mouseShow(mx,my);
						cond=0;
						break;
					case 11:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						MoveMousePtr(mx,my);
						mouseShow(mx,my);
						cut();
						mouseShow(x0,y0);
						cond=0;
						break;
					case 12:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						MoveMousePtr(mx,my);
						mouseShow(mx,my);
						//eraser();
						cond=0;
						break;
					case 13:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						MoveMousePtr(mx,my);
						mouseShow(mx,my);
						copy();
						mouseShow(x0,y0);
						cond=0;
						break;
					case 14:
						sprintf(str,"temp%d.bmp",cont);
						mouseHide(mx,my);
						save(str,150,3,647,497);
						cont++;
						MoveMousePtr(mx,my);
						mouseShow(mx,my);
						mouseHide(mx,my);
						paste(mx, my);
						mouseShow(mx,my);
						cond=0;
						break;
					case 16:
						t=2;
						break;

				}
			}
		}
		if(mbutton==2){
			color=getpixel(mx,my);
			for (i=20;i<=50;i++){
				for (j=520;j<=550;j++){
					putpixel(i,j,color);
				}
			}
		}


	}
	ret();
	getch();
	return 1;
}











	