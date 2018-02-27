

int getpixel(int x, int y){
	double adr=((800.0*y)+x);
	int bank= (int)(adr/65536);
	int ofs= (int)(adr-(bank*65536));
	int col;
	 asm{
	 	mov ax,4f05h
	 	xor bx,bx
	 	mov dx,bank
	 	int 10h
	 }
	 
	 asm{
	 	push di
	 	mov ax,0a000h
	 	mov es,ax
	 	mov di,ofs
	 	mov al,[es:di]
	 }
	return (_AL);
}

int putpixel(int x, int y, char col){
	double adr=((800.0*y)+x);
	int bank= (int)(adr/65536);
	int ofs= (int)(adr-(bank*65536));
	 asm{
	 	mov ax,4f05h
	 	xor bx,bx
	 	mov dx,bank
	 	int 10h
	 }
	 asm{
	 	push di
	 	mov ax,0a000h
	 	mov es,ax
	 	mov di,ofs
	 	mov al, [col]
	 	mov [es:di],al
	 }
	return 0;
}

int initvid(){
	asm mov ax, 0x4F02; //0 = video mode
	asm mov bx, 0x103
	asm int 10h;
	return 0;
}

int ret(){
	asm mov ah, 0;
	asm mov al, 0x03;
	asm int 10h;
	getch();
	return 0;
}