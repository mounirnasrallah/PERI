/*
 * RpiLab: lab2
 *
 * LCD Display in user mode.
 */

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <gpio.h>


// Définition des GPIOs
#define GPIO_EN 23
#define GPIO_RS 18
#define GPIO_D0 4
#define GPIO_D1 17
#define GPIO_D2 27
#define GPIO_D3 22


// Définition des signaux RS pour distinguer envoie d'une commande
// ou l'envoie de données
#define RS_CMD 0
#define RS_DATA 1


// Définition de "Function set"
// DL - Sets interface data length
//  N - Number of display line
//  F - Character font
#define CMD_FUNC     0x20
#define CMD_FUNC_DL  0x10
#define CMD_FUNC_N   0x8
#define CMD_FUNC_F   0x4


// Définition de "Entry mode set"
// I/D - Sets cursor move direction
//   S - Specifies to shift the display
#define CMD_ENTRY    0x4
#define CMD_ENTRY_ID 0x2
#define CMD_ENTRY_S 0x1


// Définition de "Display on/off control"
// D - Sets on/off of all display
#define CMD_DISPLAY_ON_OFF 0x8
#define CMD_DISPLAY_ON_OFF_D 0x4


// Définition de "Cursor/display shift"
// S/C - Sets cursor-move or display-shift (S/C)
// R/L - Shift direction
#define CMD_CDSHIFT    0x10
#define CMD_CDSHIFT_RL 0x4
#define CMD_CDSHIFT_SC 0x8


// Définition de "Clear display"
#define CMD_CLEAR 0x1

// Définition de "Cursor home"
#define CMD_CURSOR_HOME 0x2


// Tableau contenant les GPIOs selon leur poid
const int gpio_data[] = {GPIO_D0,GPIO_D1,GPIO_D2,GPIO_D3};





// Attente de "x" microsecondes
static void udelay ( unsigned int x )
{
  usleep(x);
}



// Permet de créer un front descendant sur le GPIO EN
void lcd_strobe(){
  gpio_update(GPIO_EN, 1);
  udelay(50);
  gpio_update(GPIO_EN,0);
  udelay(50);
}



// Envoie 4 bits à l'écran lcd, puis réalise un front descendant
// pour prendre en compte les signaux envoyés
void lcd_write_4bit_value(char data){
  int i;

  for(i=0;i<4;i++){
    gpio_update(gpio_data[i], ( data & 0x1 ));
    data >>= 1;
  }

  lcd_strobe();
}



// Envoie 8 bits l'écran lcd, en utilisant la fonction lcd_write_4bit_value
// On envoie les bits de poids forts puis les bits de poids faibles
void lcd_write_value(const char data){

  lcd_write_4bit_value(data>>4);
  lcd_write_4bit_value(data);
}



// Envoie d'une commande sur 4 bits
void lcd_send_4bit_cmd(const char data){
  gpio_update(GPIO_RS, RS_CMD);
  lcd_write_4bit_value(data);
}


// Envoie d'une commande sur 8 bits
void lcd_send_cmd(const char data){
  gpio_update(GPIO_RS, RS_CMD);
  lcd_write_value(data);
}


// Envoie de données sur 8 bits
void lcd_send_data(const char data){
  gpio_update(GPIO_RS, RS_DATA);
  lcd_write_value(data);
}


// Envoie la commande "Clear display" à l'écran lcd
void clear_display(){
  lcd_send_cmd(CMD_CLEAR);
  udelay(2000);
}


// Configuration de l'écran LCD et nettoyage du LCD
void lcd_config_clear(){

  char func = CMD_FUNC | CMD_FUNC_DL;

  // Envoie d'une commande pour la configuration sur
  // 8 bits */
  lcd_send_4bit_cmd ( func >> 4 );
  udelay ( 50 );
  lcd_send_4bit_cmd ( func >> 4 );
  udelay ( 50 );
  lcd_send_4bit_cmd ( func >> 4);
  udelay ( 50 );

  /* 4 bits */
  func = CMD_FUNC;
  lcd_send_4bit_cmd ( func >> 4 );
  udelay ( 2000 );

  /* 2 rows on LCD */
  func |= CMD_FUNC_N;
  lcd_send_cmd ( func );
  udelay ( 50 );

  /* Entry mode. */
  lcd_send_cmd ( CMD_ENTRY | CMD_ENTRY_ID );
  udelay ( 50 );

  /* Display on */
  lcd_send_cmd ( CMD_DISPLAY_ON_OFF | CMD_DISPLAY_ON_OFF_D );
  udelay ( 50 );

  /* Cursor */
  lcd_send_cmd ( CMD_CDSHIFT | CMD_CDSHIFT_RL );
  udelay ( 50 );

  /* Clear */
  clear_display();
}



// Initialisation du LCD
int lcd_init(){

  if(gpio_setup()==-1)
    return -1;

  if(gpio_config(GPIO_EN,GPIO_OUTPUT_PIN)==-1 ||
     gpio_config(GPIO_RS,GPIO_OUTPUT_PIN)==-1 ||
     gpio_config(GPIO_D0,GPIO_OUTPUT_PIN)==-1 ||
     gpio_config(GPIO_D1,GPIO_OUTPUT_PIN)==-1 ||
     gpio_config(GPIO_D2,GPIO_OUTPUT_PIN)==-1 ||
     gpio_config(GPIO_D3,GPIO_OUTPUT_PIN)==-1
    )
    return -1;

  lcd_config_clear();
  return 0;
}



// Déinitialisation du LCD
int lcd_deinit(){
  int i;

  clear_display();

  for(i=0;i<4;i++){
    gpio_update(gpio_data[i], 0);
  }

  gpio_update(GPIO_RS, 0);
  gpio_update(GPIO_EN, 0);

  if(gpio_config(GPIO_EN,GPIO_INPUT_PIN)==-1 ||
     gpio_config(GPIO_RS,GPIO_INPUT_PIN)==-1 ||
     gpio_config(GPIO_D0,GPIO_INPUT_PIN)==-1 ||
     gpio_config(GPIO_D1,GPIO_INPUT_PIN)==-1 ||
     gpio_config(GPIO_D2,GPIO_INPUT_PIN)==-1 ||
     gpio_config(GPIO_D3,GPIO_INPUT_PIN)==-1
    ){
    return -1;
  }

  gpio_teardown();

  return 0;
}



// Envoie de "Hello World" sur l'écran LCD
void helloworld(){
  lcd_send_data('H');
  lcd_send_data('e');
  lcd_send_data('l');
  lcd_send_data('l');
  lcd_send_data('o');
  lcd_send_data(' ');
  lcd_send_data('W');
  lcd_send_data('o');
  lcd_send_data('r');
  lcd_send_data('l');
  lcd_send_data('d');
}



// Affichage du monitoring
void monitoring(){
  int fd;
  char buf;

  fd = open("/proc/loadavg",O_RDONLY);
  while(read(fd,&buf,1)){

    if(buf!='\n'){
      lcd_send_data(buf);
    }
  }

}



// Fonction principale
int main ( int argc, char *argv[] )
{

  if(lcd_init()==-1){
    return -1;
  }

  helloworld();

  sleep (2); // On attend pour voir le résultat

  lcd_config_clear();
  monitoring();

  sleep(5); // On attend pour voir le résultat

  lcd_deinit();

  return 0;
}

