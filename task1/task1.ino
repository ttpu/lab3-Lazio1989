y
#define BTN 33

#define RED 4
#define GRN 5
#define YLW 19
#define BLU 22

void setup() {
  // configure button as input
  pinMode(BTN, INPUT);
  // configure serial port speed
  Serial.begin(115200);
}

void loop() {
  // this variable keeps the counting number of button pressed event
  static int count = 0;
  // this variable keeps its value even the function is called multiple times
  static int prev_btn = LOW;
  // read current button state (HIGH means pressed)
  int btn = digitalRead(BTN);

  // detect button pressed event
  if (btn == HIGH && prev_btn == LOW){
    count++;
    Serial.println(count);
  }
  // save current btn state into a variable to be used in next loop iteration
  prev_btn = btn;
  delay(100);
}
