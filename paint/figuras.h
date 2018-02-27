int mx,my,mbutton,grosor, width, height;
char color;
int t=1;


//pintar el canvas
int canvas(){
	int i, j;
	for (i=150; i<797;i++ ){
		for (j=3; j<500;j++){
			putpixel(i, j, 15);
		}
	}
	return 0;
}

int lapiz(){
	int x,y;
	GetMousePos(&mbutton,&mx, &my);
	mouseShow(mx,my);
	x=mx;
	y=my;
	while(mbutton==1){
		GetMousePos(&mbutton,&mx, &my);
		if(x!=mx || y!=my){
			mouseHide(x,y);
			mouseShow(mx,my);
			x=mx;
			y=my;
		}
		putpixeld(mx,my,grosor);
	}
	mouseHide(mx,my);
	return 0;
}

int praynspray(){
	int x,y;
	GetMousePos(&mbutton,&mx, &my);
	mouseShow(mx,my);
	x=mx;
	y=my;
	while(mbutton==1){
		GetMousePos(&mbutton,&mx, &my);
		if(x!=mx || y!=my){
			mouseHide(x,y);
			mouseShow(mx,my);
			x=mx;
			y=my;
		}
		spraynpray(mx,my,grosor);
	}
	mouseHide(mx,my);
	return 0;
}

int copy(){
	int x,y,x0,y0,x1,y1,xi,yi,i,j;
	while(t==1){
		GetMousePos(&mbutton,&mx,&my);
		if (mbutton==1)
			break;
	}
	x0=mx;
	y0=my;
	x=x0;
	y=y0;
	while(mbutton==1){
		GetMousePos(&mbutton,&mx, &my);
		if(x!=mx || y!=my){
			mouseHide(x,y);
			mouseShow(mx,my);
			x=mx;
			y=my;
		}
	}
	mouseHide(mx,my);
	x1=mx;
	y1=my;
	if (y1>y0)
		yi=y0;
	else
		yi=y1;
	if(x1>x0)
		xi=x0;
	else
		xi=x1;
	width=abs(x1-x0);
	height=abs(y1-y0);
	save("copy.bmp",xi,yi,width,height);
	return 0;
}

int cut(){
	int x,y,x0,y0,x1,y1,xi,yi,i,j;
	while(t==1){
		GetMousePos(&mbutton,&mx,&my);
		if (mbutton==1)
			break;
	}
	x0=mx;
	y0=my;
	x=x0;
	y=y0;
	while(mbutton==1){
		GetMousePos(&mbutton,&mx, &my);
		if(x!=mx || y!=my){
			mouseHide(x,y);
			mouseShow(mx,my);
			x=mx;
			y=my;
		}
	}
	mouseHide(mx,my);
	x1=mx;
	y1=my;
	if (y1>y0)
		yi=y0;
	else
		yi=y1;
	if(x1>x0)
		xi=x0;
	else
		xi=x1;
	width=abs(x1-x0);
	height=abs(y1-y0);
	save("copy.bmp",xi,yi,width,height);
	for(x=0;x<=width;x++){
		for(y=0;y<=height;y++){
			putpixel(xi+x,yi+y,15);
		}
	}
	return 0;
}

int paste(int x0, int y0){
	read("C:\\TURBOC3\\BIN\\copy.bmp",x0,y0);
	return 0;
}


int recieve(int button,int x, int y, char col,int grosor){
	mx=x;
	my=y;
	mbutton=button;
	color=col;
	return 0;
}

putpixeld(int x, int y){
	switch (grosor){
		case 1:
		putpixel(x,y,color);
		break;
		case 2:
		putpixel2(x,y,color);
		break;
		case 3:
		putpixel3(x,y,color);
		break;
	}
}

int putpixel2(int x, int y, char col){
	putpixel(x, y+1, col);
	putpixel(x,y,col);
	putpixel(x-1,y,col);
	putpixel(x+1,y,col);
	putpixel(x,y-1,col);
	return 0;
}


int putpixel3(int x, int y, char col){
	putpixel2(x, y+1, col);
	putpixel2(x,y,col);
	putpixel2(x-1,y,col);
	putpixel2(x+1,y,col);
	putpixel2(x,y-1,col);
	return 0;
}

int spraynpray(int x, int y){
	if (x>150 && x<797 && y<500 && y>3){
	int r1, r2,d,x0,y0;
	r1= rand() %17;
	r2= rand() %17;
	r1=r1-8;
	r2=r2-8;
	x0=x+r1;
	y0=y+r2;
	if (x>150 && x<797 && y<500 && y>3){
	putpixeld(x0,y0);
	}
	delay(5);
	}
	return 0;
}



int drawLine(int x0, int y0, int x1, int y1){
	int dx;
	int dy;
	int cont;
	dx=x1-x0;
	dy=y1-y0;
	if (abs(dy)<abs(dx)){
		if (x0>x1){
			plotLineLow(x1,y1,x0,y0);
		}
		else
			plotLineLow(x0,y0,x1,y1);
	}
	else{
		if(y0>y1)
			plotLineHigh(x1,y1,x0,y0);
		else
			plotLineHigh(x0,y0,x1,y1);
	}
	return 0;	
}

int plotLineLow(int x0, int y0, int x1, int y1){
	int dx;
	int dy;
	int yi;
	int x;
	int y;
	int D;
	dx=x1-x0;
	dy=y1-y0;
	yi=1;
	if (dy<0){
		yi=-1;
		dy=-dy;
	}
	D=(2*dy)-dx;
	y=y0;
	for (x=x0;x<=x1;x++){
		if (x>150 && x<797 && y<500 && y>3){
		putpixeld(x,y);
		}
		if (D>0){
			y=y+yi;
			D=D-(2*dx);
		}
		D=D+(2*dy);
	}
	return 0;
}

int plotLineHigh(int x0, int y0, int x1, int y1){
	int dx;
	int dy;
	int xi;
	int x;
	int y;
	int D;
	dx=x1-x0;
	dy=y1-y0;
	xi=1;
	if (dx<0){
		xi=-1;
		dx=-dx;
	}
	D=(2*dx)-dy;
	x=x0;
	//putpixel(x0,y0,color);
	//putpixel(x1,y1,color);
	for (y=y0;y<=y1;y++){
		if (x>150 && x<797 && y<500 && y>3){
		putpixeld(x,y);
		}
		if (D>0){
			x=x+xi;
			D=D-(2*dy);
		}
		D=D+(2*dx);
	}
	return 0;
}

int line(){
	int x,y,x0,y0,x1,y1;
	while(t==1){
		GetMousePos(&mbutton,&mx,&my);
		if (mbutton==1)
			break;
	}
	x0=mx;
	y0=my;
	x=x0;
	y=y0;
	while(mbutton==1){
		GetMousePos(&mbutton,&mx, &my);
		if(x!=mx || y!=my){
			mouseHide(x,y);
			mouseShow(mx,my);
			x=mx;
			y=my;
		}
	}
	mouseHide(mx,my);
	x1=mx;
	y1=my;
	drawLine(x0,y0,x1,y1);
	return 0;
}

int square(){
	int x,y,x0,y0,x3,y3;
	while(t==1){
		GetMousePos(&mbutton,&mx,&my);
		if (mbutton==1)
			break;
	}
	x0=mx;
	y0=my;
	x=x0;
	y=y0;
	while(mbutton==1){
		GetMousePos(&mbutton,&mx, &my);
		if(x!=mx || y!=my){
			mouseHide(x,y);
			mouseShow(mx,my);
			x=mx;
			y=my;
		}
	}
	mouseHide(mx,my);
	x3=mx;
	y3=my;
	drawLine(x0,y0,x3,y0);
	drawLine(x0,y0,x0,y3);
	drawLine(x3,y0,x3,y3);
	drawLine(x0,y3,x3,y3);
	return 0;
}

int triangle(){
	int x,y,x0,y0,x1,y1;
	while(t==1){
		GetMousePos(&mbutton,&mx,&my);
		if (mbutton==1)
			break;
	}
	x0=mx;
	y0=my;
	x=x0;
	y=y0;
	while(mbutton==1){
		GetMousePos(&mbutton,&mx,&my);
		if(x!=mx || y!=my){
			mouseHide(x,y);
			mouseShow(mx,my);
			x=mx;
			y=my;
		}
	}
	mouseHide(mx,my);
	x1=mx;
	y1=my;
	drawLine(x0,y0,x1,y1);
	drawLine(x1,y1, (x1-2*(x1-x0)),y1);
	drawLine(x0,y0,(x1-2*(x1-x0)),y1);
	return 0;
}

int circle(){
	int xp,yp,x0,y0,r,f,ddf_x,ddf_y,x1,y1,x,y;
	while(t==1){
		GetMousePos(&mbutton,&mx,&my);
		if (mbutton==1)
			break;
	}
	x0=mx;
	y0=my;
	xp=x0;
	yp=y0;
	while(mbutton==1){
		GetMousePos(&mbutton,&mx,&my);
		if(xp!=mx || yp!=my){
			mouseHide(xp,yp);
			mouseShow(mx,my);
			xp=mx;
			yp=my;
		}
	}
	mouseHide(mx,my);
	x1=mx;
	y1=my;
	r=(sqrt(pow((x0-x1),2)+ pow((y0-y1),2)))/2;


	f=1-r;
	ddf_x=0;
	ddf_y=-2*r;
	x=0;
	y=r;

	while(x<y){
		if(f>=0){
			y--;
			ddf_y+=2;
			f+=ddf_y;
		}
		x++;
		ddf_x+=2;
		f+= ddf_x +1;
		putpixeld((x0+x),(y0+y));
		putpixeld((x0-x),(y0+y));
		putpixeld((x0+x),(y0-y));
		putpixeld((x0-x),(y0-y));
		putpixeld((x0+y),(y0+x));
		putpixeld((x0-y),(y0+x));
		putpixeld((x0+y),(y0-x));
		putpixeld((x0-y),(y0-x));
	}

	return 0;
}

int elipse(){
	double xp,yp,xc,yc,width,height,a2,b2,x,y,sigma,fa2,fb2;
	double x0,y0,x1,y1;
	while(t==1){
		GetMousePos(&mbutton,&mx,&my);
		if (mbutton==1)
			break;
	}
	x0=mx;
	y0=my;
	xp=x0;
	yp=y0;
	while(mbutton==1){
		GetMousePos(&mbutton,&mx,&my);
		if(xp!=mx || yp!=my){
			mouseHide(xp,yp);
			mouseShow(mx,my);
			xp=mx;
			yp=my;
		}
	}
	mouseHide(mx,my);
	x1=mx;
	y1=my;
	width=(int) abs((x1-x0)/2);
	xc=(int) (x0+(x1-x0)/2);
	yc=(int) (y0+(y1-y0)/2);
	height=(int) abs((y1-y0)/2);
	a2 = width * width;
    b2 = height * height;
    fa2 = 4 * a2;
    fb2 = 4 * b2;
    /* first half */
    for (x = 0, y = height, sigma = 2*b2+a2*(1-2*height); b2*x <= a2*y; x++)
    {
        putpixeld(xc + x, yc + y);
        putpixeld(xc - x, yc + y);
        putpixeld(xc + x, yc - y);
        putpixeld(xc - x, yc - y);
        if (sigma >= 0)
        {
            sigma += fa2 * (1 - y);
            y--;
        }
        sigma += b2 * ((4 * x) + 6);
    }

    /* second half */
    for (x = width, y = 0, sigma = 2*a2+b2*(1-2*width); a2*y <= b2*x; y++)
    {
        putpixeld (xc + x, yc + y);
        putpixeld (xc - x, yc + y);
        putpixeld (xc + x, yc - y);
        putpixeld (xc - x, yc - y);
        if (sigma >= 0)
        {
            sigma += fb2 * (1 - x);
            x--;
        }
        sigma += a2 * ((4 * y) + 6);
    }
	return 0;
}

int polygon(){
	int x,y,x0,y0,x1,y1,xi,yi,xf,yf;
	while(t==1){
		GetMousePos(&mbutton,&mx,&my);
		if (mbutton==1)
			break;
	}
	xi=mx;
	yi=my;
	x0=xi;
	y0=yi;
	x=xi;
	y=yi;
	while(mbutton==1){
		GetMousePos(&mbutton,&mx,&my);
		if(x!=mx || y!=my){
			mouseHide(x,y);
			mouseShow(mx,my);
			x=mx;
			y=my;
		}
	}
	mouseHide(mx,my);
	while (xf!=xi && yf!=yi){
		while(mbutton!=1){
			GetMousePos(&mbutton,&mx,&my);
			if(x!=mx || y!=my){
				mouseHide(x,y);
				mouseShow(mx,my);
				x=mx;
				y=my;
			}
		}
		xf=mx;
		yf=my;
		for (x1=-10;x1<=10;x1++){
			for (y1=-10;y1<=10;y1++){
				if ((xi==(xf+x1)) && (yi==(yf+y1))){
					yf=yi;
					xf=xi;
					drawLine(x0,y0,xi,yi);
					break;
				}
			}
		}
		drawLine(x0,y0,xf,yf);
		x0=xf;
		y0=yf;
		while(mbutton==1){
			GetMousePos(&mbutton,&mx,&my);
		}
	}
}

int fill(int x0, int y0){
	char col,ref;
	int x,y,z,w;
	x=0;
	col=getpixel(x0,y0);
	while(col==getpixel(x0+x,y0)){
		y=0;
		while(col==getpixel(x0+x,y0+y)){
			if (color==getpixel(mx+x,my+y))
				break;
			z=1;
			while(col==getpixel(x0+x+z,y0+y)){
				
				w=1;
				while (col==getpixel(x0+x+z,y0+y-w)){
					putpixel(x0+x+z,y0+y-w,color);
					w++;
				}
				w=1;
				while (col==getpixel(x0+x+z,y0+y+w)){
					putpixel(x0+x+z,y0+y+w,color);
					w++;
				}
				putpixel(x0+x+z,y0+y,color);
				z++;
			}
			putpixel(x0+x,y0+y,color);
			y++;
		}
		y=1;
		while(col==getpixel(x0+x,y0-y)){
			if (color==getpixel(x0+x,y0-y))
				break;
			
			z=1;
			while(col==getpixel(x0+x+z,y0-y)){
				
				w=1;
				while (col==getpixel(x0+x+z,y0-y+w)){
					putpixel(x0+x+z,y0-y+w,color);
					w++;
				}
				w=1;
				while (col==getpixel(x0+x+z,y0-y-w)){
					putpixel(x0+x+z,y0-y-w,color);
					w++;
				}
				putpixel(x0+x+z,y0-y,color);
				z++;
			}
			putpixel(x0+x,y0-y,color);
			y++;
		}
		x++;
	}
	x=1;
	while(col==getpixel(x0-x,y0)){
		y=0;
		while(col==getpixel(x0-x,y0+y)){
			if (color==getpixel(x0-x,y0+y))
				break;
			
			z=1;
			while(col==getpixel(x0-x-z,y0+y)){
				
				w=1;
				while (col==getpixel(x0-x-z,y0+y-w)){
					putpixel(x0-x-z,y0+y-w,color);
					w++;
				}
				w=1;
				while (col==getpixel(x0-x-z,y0+y+w)){
					putpixel(x0-x-z,y0+y+w,color);
					w++;
				}
				putpixel(x0-x-z,y0+y,color);
				z++;
			}
			putpixel(x0-x,y0+y,color);
			y++;
		}
		y=1;
		while(col==getpixel(x0-x,y0-y)){
			if (color==getpixel(x0-x,y0-y))
				break;
			
			z=1;
			while(col==getpixel(x0-x-z,y0-y)){
				
				w=1;
				while (col==getpixel(x0-x-z,y0-y+w)){
					putpixel(x0-x-z,y0-y+w,color);
					w++;
				}
				w=1;
				while (col==getpixel(x0-x-z,y0-y-w)){
					putpixel(x0-x-z,y0-y-w,color);
					w++;
				}
				putpixel(x0-x-z,y0-y,color);
				z++;
			}
			putpixel(x0-x,y0-y,color);
			y++;
		}
		x++;
	}
	return 0;
}

int fill2(){
	return 0;
}


//pintar el fondo
	/*
	for (i=0; i<=800;i++ ){
		for (j=0; j<=600;j++){
			putpixel(i, j, 0);
		}
	}*/
