#define PARSING
//#define PARSING2

char* Letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.","...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };
char* Numbers[] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

const int buttonPin = 2;
int buttonState_prev = 0;
int buttonState_now = 0;
signed long up_stamp, down_stamp, now_time;
int debounce = 0;

char button_buf[8];
char button_idx = 0;

void setup()                
{
  pinMode(13, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop()                   
{
  char info;
  
#ifdef PARSING
  int i, j, k;
  
  buttonState_now = digitalRead(buttonPin);
  
  //Serial.print("Input Pin: ");
  //Serial.println(buttonState_now);
  
  now_time = millis();
  
  //Serial.print("Now: ");
  //Serial.println(now_time);
  
  if ((buttonState_now == 1) && (buttonState_prev == 0))
  {
      digitalWrite(13,HIGH);
      up_stamp = millis();
      buttonState_prev = buttonState_now;
      
      if (up_stamp > down_stamp)
      {
          if ((up_stamp - down_stamp) < 250)
          {
              debounce = 1;
          }
      }
      
      delay(200);
  }
  else if ((buttonState_now == 0) && (buttonState_prev == 1))
  {
      digitalWrite(13,LOW);
      down_stamp = millis();
      buttonState_prev = buttonState_now;
      
      if ((down_stamp - up_stamp) > 350)
      {
          //Serial.println("long!!!!!!!");
          Serial.print("-");
          button_buf[button_idx++] = '-';
      }
      else
      {
          if (debounce)
          {
              //Serial.println("debounce!!!!!!!");
              debounce = 0;
          }
          else
          {
              //Serial.println("short!!!!!!!");
              Serial.print(".");
              button_buf[button_idx++] = '.';
          }
      }
      
      delay(200);
  }
  else if ((buttonState_now == 0) && (buttonState_prev == 0) && (button_idx != 0))
  {
      digitalWrite(13,LOW);
      if ((now_time - down_stamp) > 1000)
      {
          button_buf[button_idx++] = '\0';

      for (i = 0; i < 26; i++)
        {
            if (compare_char(Letters[i], button_buf) == 1)
            {
                //Serial.print("Parsing: ");
                Serial.print(" ; I sent: ");
                Serial.write('A' + i);
                Serial.println();
                break;
            }
        }
        if (i >= 26)
        {
            Serial.println(" ; No Result");
        }
        button_idx = 0;
        for (k = 0; k < 8; k++)
        {
          button_buf[k] = 0;
        }
      }
  }
#endif

#ifdef PARSING2
  
#endif
  
  
  if (Serial.available() > 0) {
    info = Serial.read();
    
    Serial.print("I received: ");
    Serial.write(info);
    Serial.print("  ");
    
    if (info >= 'a' && info <= 'z') {      
      letterId(Letters[info - 'a']);
    }
    else if(info >= 'A' && info <= 'Z') {
      letterId(Letters[info - 'A']);
    }
    else if(info >= '0' && info <= '9') {
      letterId(Numbers[info - '0']);
    }
    else if(info == ' ') {
      delay(1000); 
    }
  }
}

int compare_char(char* c1, char*c2)
{
  int i = 1;
  char* c1temp = c1;
  char* c2temp = c2;
  
  while(*c1temp != '\0') 
  {
      if ((*c1temp) != (*c2temp))
      {
          return 0;
      }
      
      c1temp++;
      c2temp++;
  }
  
  if ((*c1temp) != (*c2temp))
  {
      return 0;
  }
  
  return 1;
}

void letterId(char* character)
{
  int i = 0;
   while(character[i] != '\0') 
   {
    output(character[i]);
    i++;
   }
  Serial.println();
  delay(700);
}

void output(char ID) {
  
//  Serial.print("I received: ");
    Serial.write(ID);
//  Serial.println();
          
  digitalWrite(13,HIGH);
  if (ID == '.') {
    delay(100);          
  } else {
    delay(700);          
  }
  digitalWrite(13,LOW);
  delay(100);
}
