/* ppm file IO headerfile ------ myppm.h */

/* Constant declaration */
#define MAX_IMAGESIZE  1024
#define MAX_BRIGHTNESS  255 /* Maximum gray level */
#define GRAYLEVEL       256 /* No. of gray levels */
#define MAX_FILENAME    256 /* Filename length limit */
#define MAX_BUFFERSIZE  256

/* Global constant declaration */
/* Image storage arrays */
unsigned char pmage1[3][MAX_IMAGESIZE][MAX_IMAGESIZE];
unsigned char pmage2[3][MAX_IMAGESIZE][MAX_IMAGESIZE];
int x_size1, y_size1; /* width & height of pmage1 */
int x_size2, y_size2; /* width & height of pmage2 */

/* Prototype declaration of functions */
void load_pmage_data( ); /* image input */
void save_pmage_data( ); /* image output*/
void load_pmage_file(char *); /* image input */
void save_pmage_file(char *); /* image output*/


/* Main body of functions */

void load_pmage_data( )
     /* Input of header & body information of ppm file */
     /* for pmage1[3][ ][ ]，x_size1，y_size1 */
{
  char file_name[MAX_FILENAME];
  char buffer[MAX_BUFFERSIZE];
  FILE *fp;     /* File pointer */
  int max_color; /* Maximum color level */

  int x, y;     /* Loop variable */

  /* Input file open */
  printf("\n-----------------------------------------------------\n");
  printf("Color image file input routine \n");
  printf("-----------------------------------------------------\n\n");
  printf("     Only ppm binary file is acceptable\n\n");
  printf("Name of input image file? (*.ppm) : ");
  scanf("%s", file_name);
  fp = fopen(file_name, "rb");
  if (NULL == fp) {
    printf("     The file doesn't exist!\n\n");
    exit(1);
  }
  /* Check of file-type ---P6 */
  fgets(buffer, MAX_BUFFERSIZE, fp);
  if (buffer[0] != 'P' || buffer[1] != '6') {
    printf("     Mistaken file format, not P6!\n\n");
    exit(1);
  }
  /* input of x_size1, y_size1 */
  x_size1 = 0;
  y_size1 = 0;
  while (x_size1 == 0 || y_size1 == 0) {
    fgets(buffer, MAX_BUFFERSIZE, fp);
    if (buffer[0] != '#') {
      sscanf(buffer, "%d %d", &x_size1, &y_size1);
    }
  }
  /* input of max_color */
  max_color = 0;
  while (max_color == 0) {
    fgets(buffer, MAX_BUFFERSIZE, fp);
    if (buffer[0] != '#') {
      sscanf(buffer, "%d", &max_color);
    }
  }
  /* Display of parameters */
  printf("\n     Image width = %d, Image height = %d\n", x_size1, y_size1);
  printf("     Maximum color level = %d\n\n",max_color);
  if (x_size1 > MAX_IMAGESIZE || y_size1 > MAX_IMAGESIZE) {
    printf("     Image size exceeds %d x %d\n\n", MAX_IMAGESIZE, MAX_IMAGESIZE);
    printf("     Please use smaller images!\n\n");
    exit(1);
  }
  if (max_color != MAX_BRIGHTNESS) {
    printf("     Invalid value of maximum color level!\n\n");
    exit(1);
  }
  /* Input of image data*/
  for (y = 0; y < y_size1; y++) {
    for (x = 0; x < x_size1; x++) {
      pmage1[0][y][x] = (unsigned char)fgetc(fp); // R
      pmage1[1][y][x] = (unsigned char)fgetc(fp); // G
      pmage1[2][y][x] = (unsigned char)fgetc(fp); // B
    }
  }
  printf("-----Image data input OK-----\n\n");
  printf("-----------------------------------------------------\n\n");


  fclose(fp);
}


void save_pmage_data( )
     /* Output of pmage2[3][ ][ ], x_size2, y_size2 in ppm format*/
{
  char file_name[MAX_FILENAME];
  FILE *fp; /* File pointer */
  int x, y; /* Loop variable */

  /* Output file open */
  printf("-----------------------------------------------------\n");
  printf("Color image file output routine\n");
  printf("-----------------------------------------------------\n\n");
  printf("Name of output image file? (*.ppm) : ");
  scanf("%s",file_name);
  fp = fopen(file_name, "wb");
  /* output of ppm file header information */
  fputs("P6\n", fp);
  fputs("# Created by Image Processing\n", fp);
  fprintf(fp, "%d %d\n", x_size2, y_size2);
  fprintf(fp, "%d\n", MAX_BRIGHTNESS);
  /* Output of image data */
  for (y = 0; y < y_size2; y++) {
    for (x = 0; x < x_size2; x++) {
      fputc(pmage2[0][y][x], fp); // R
      fputc(pmage2[1][y][x], fp); // G
      fputc(pmage2[2][y][x], fp); // B
    }
  }
  printf("\n-----Image data output OK-----\n\n");
  printf("-----------------------------------------------------\n\n");
  fclose(fp);
}


void load_pmage_file(char * filename)
     /* Input of header & body information of ppm file */
     /* for pmage1[3][ ][ ]，x_size1，y_size1 */
{
  char buffer[MAX_BUFFERSIZE];
  FILE *fp;     /* File pointer */
  int max_color; /* Maximum color level */

  int x, y;     /* Loop variable */

  /* Input file open */
  fp = fopen(filename, "rb");
  if (NULL == fp) {
    printf("     The file doesn't exist!\n\n");
    exit(1);
  }
  /* Check of file-type ---P6 */
  fgets(buffer, MAX_BUFFERSIZE, fp);
  if (buffer[0] != 'P' || buffer[1] != '6') {
    printf("     Mistaken file format, not P6!\n\n");
    exit(1);
  }
  /* input of x_size1, y_size1 */
  x_size1 = 0;
  y_size1 = 0;
  while (x_size1 == 0 || y_size1 == 0) {
    fgets(buffer, MAX_BUFFERSIZE, fp);
    if (buffer[0] != '#') {
      sscanf(buffer, "%d %d", &x_size1, &y_size1);
    }
  }
  /* input of max_color */
  max_color = 0;
  while (max_color == 0) {
    fgets(buffer, MAX_BUFFERSIZE, fp);
    if (buffer[0] != '#') {
      sscanf(buffer, "%d", &max_color);
    }
  }
  /* Display of parameters */
  if (x_size1 > MAX_IMAGESIZE || y_size1 > MAX_IMAGESIZE) {
    printf("     Image size exceeds %d x %d\n\n", MAX_IMAGESIZE, MAX_IMAGESIZE);
    printf("     Please use smaller images!\n\n");
    exit(1);
  }
  if (max_color != MAX_BRIGHTNESS) {
    printf("     Invalid value of maximum color level!\n\n");
    exit(1);
  }
  /* Input of image data*/
  for (y = 0; y < y_size1; y++) {
    for (x = 0; x < x_size1; x++) {
      pmage1[0][y][x] = (unsigned char)fgetc(fp); // R
      pmage1[1][y][x] = (unsigned char)fgetc(fp); // G
      pmage1[2][y][x] = (unsigned char)fgetc(fp); // B
    }
  }

  fclose(fp);
}


void save_pmage_file(char * filename)
     /* Output of pmage2[3][ ][ ], x_size2, y_size2 in ppm format*/
{
  FILE *fp; /* File pointer */
  int x, y; /* Loop variable */

  /* Output file open */
  fp = fopen(filename, "wb");
  /* output of ppm file header information */
  fputs("P6\n", fp);
  fputs("# Created by Image Processing\n", fp);
  fprintf(fp, "%d %d\n", x_size2, y_size2);
  fprintf(fp, "%d\n", MAX_BRIGHTNESS);
  /* Output of image data */
  for (y = 0; y < y_size2; y++) {
    for (x = 0; x < x_size2; x++) {
      fputc(pmage2[0][y][x], fp); // R
      fputc(pmage2[1][y][x], fp); // G
      fputc(pmage2[2][y][x], fp); // B
    }
  }

  fclose(fp);
}
