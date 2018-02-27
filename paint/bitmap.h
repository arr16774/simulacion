typedef unsigned int WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE; 
 
typedef struct tagBITMAPFILEHEADER {  
	WORD    bfType;         
	DWORD   bfSize;         
	WORD    bfReserved1;         
	WORD    bfReserved2; 
    DWORD   bfOffBits; 
} BITMAPFILEHEADER; 
 
typedef struct tagBITMAPINFOHEADER{    
	DWORD  biSize;    
	DWORD  biWidth;    
	DWORD  biHeight;    
	WORD   biPlanes;    
	WORD   biBitCount;    
	DWORD  biCompression;    
	DWORD  biSizeImage;    
	DWORD  biXPelsPerMeter;    
	DWORD  biYPelsPerMeter;    
	DWORD  biClrUsed;    
	DWORD  biClrImportant; 
} BITMAPINFOHEADER; 

typedef struct pixel_color{
    unsigned char  Red;
    unsigned char  Green;
    unsigned char  Blue;

} colorp;

void save(char* name, int x, int y, int width, int height){
	FILE *file;
	int i, j;
	BITMAPINFOHEADER infoh;
	BITMAPFILEHEADER fileh;
	int off;
	unsigned char pixel;
	long palette[256];

	off=54+(sizeof(long)*256);

	fileh.bfType= 'BM';
	fileh.bfSize= width*height+54;
	fileh.bfReserved1=0;
	fileh.bfReserved2=0;
	fileh.bfOffBits=54;

	infoh.biSize=40;
	infoh.biWidth=width;
	infoh.biHeight=height;
	infoh.biPlanes=1;
	infoh.biBitCount=8;
	infoh.biCompression=0;
	infoh.biSizeImage=width*height;
	infoh.biXPelsPerMeter=0;
	infoh.biYPelsPerMeter=0;
	infoh.biClrUsed=0;
	infoh.biClrImportant=0;

	file= fopen(name, "wb");
	fwrite(&fileh, sizeof(BITMAPFILEHEADER),1,file);
	fwrite(&infoh,sizeof(BITMAPINFOHEADER),1,file);
	activatePalette(palette);
	palette[0] = 000000;
  	palette[1] = 0x800000;
  	palette[2] = 0x008000;
  	palette[3] = 0x808000;
 	palette[4] = 0x000080;
  	palette[5] = 0x800080;
  	palette[6] = 0x008080;
  	palette[7] = 0xc0c0c0;
  	palette[8] = 0x808080;
  	palette[9] = 0xFF0000;
 	palette[10] = 0x00FF00;
  	palette[11] = 0xFFFF00;
 	palette[12] = 0x0000FF;
 	palette[13] = 0xFF00FF;
 	palette[14] = 0x00FFFF;
 	palette[15] = 0xFFFFFF;
 	palette[16] = 0x000000;
  	palette[17] = 0x00005F;
  	palette[18] = 0x000087;
  	palette[19] = 0x0000AF;
 	palette[20] = 0x0000D7;
  	palette[21] = 0x0000FF;
  	palette[22] = 0x005f00;
  	palette[23] = 0x005f5f;
  	palette[24] = 0x005f87;
  	palette[25] = 0x005faf;
 	palette[26] = 0x005fd7;
  	palette[27] = 0x005fff;
 	palette[28] = 0x008700;
 	palette[29] = 0x00875f;
 	palette[30] = 0x008787;
 	palette[31] = 0x0087af;

 	palette[32] = 0x0087d7;
  	palette[33] = 0x0087ff;
  	palette[34] = 0x00af00;
  	palette[35] = 0x00af5f;
 	palette[36] = 0x00af87;
  	palette[37] = 0x00afaf;
  	palette[38] = 0x00afd7;
  	palette[39] = 0x00afff;
  	palette[40] = 0x00d700;
  	palette[41] = 0x00d75f;
 	palette[42] = 0x00d787;
  	palette[43] = 0x00d7af;
 	palette[44] = 0x00d7d7;
 	palette[45] = 0x00d7ff;
 	palette[46] = 0x00ff00;
 	palette[47] = 0x00ff5f;
 	palette[48] = 0x00ff87;
  	palette[49] = 0x00ffaf;
  	palette[50] = 0x00ffd7;
  	palette[51] = 0x00ffff;
 	palette[52] = 0x5f0000;
  	palette[53] = 0x5f005f;
  	palette[54] = 0x5f0087;
  	palette[55] = 0x5f00af;
  	palette[56] = 0x5f00d7;
  	palette[57] = 0x5f00ff;
 	palette[58] = 0x5f5f00;
  	palette[59] = 0x5f5f5f;
 	palette[60] = 0x5f5f87;
 	palette[61] = 0x5f5faf;
 	palette[62] = 0x5f5fd7;
 	palette[63] = 0x5f5fff;
 	fwrite(palette, sizeof(long), 256,  file);
 	for (i=height; i>=0;i--){
		for (j=0;j<=width;j++){
			pixel= getpixel(x+j, y+i);
			fwrite(&pixel,1,1,file);
		}
	}
  fclose(file);
}

int read(char* file, int x, int y){
	int ch, ch1, ch2, width, height, i, j;
	FILE *ptr= NULL;
	unsigned char R,G,B;
	unsigned char pix;
	BITMAPINFOHEADER infoh;
	BITMAPFILEHEADER fileh;
	WORD type;  
	ptr=fopen(file, "rb");
	if(!ptr){
		return 0;
	} 

	fread(&type, sizeof(WORD), 1, ptr);
  	if (type !=0x4D42){        /* Comprobamos el formato */
     	 fclose(ptr);
      	return NULL;
   	}
   	fseek( ptr,0, SEEK_SET);
   	fread(&fileh, sizeof(BITMAPFILEHEADER), 1, ptr);

  /* Leemos la cabecera de información completa */
  	fread(&infoh, sizeof(BITMAPINFOHEADER), 1, ptr);
  	width=infoh.biWidth;
  	height=infoh.biHeight;

  	fseek(ptr, fileh.bfOffBits+sizeof(long)*256,SEEK_SET);

  	for (i=height;i>=0;i--){
  		for (j=0;j<=width;j++){
  			fread(&pix, sizeof(char),1,ptr);
  			putpixel(x+j,y+i,pix);
  			
  		}
  	}

  	fclose(ptr);
  	return 0;
}

int activatePalette ( char far *palette){
  asm {
    les dx, [palette]
    mov ax, 0x1017
    mov bx, 0
    mov cx, 256
    int 0x10
  }

  return 0;
}


