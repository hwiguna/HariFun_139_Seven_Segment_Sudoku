const byte segmentA = 0;
const byte segmentB = 1;
const byte segmentC = 2;
const byte segmentD = 3;
const byte segmentE = 4;
const byte segmentF = 5;
const byte segmentG = 6;
const byte segmentH = 7;

const byte digit0 = 8;
const byte digit1 = 9;
const byte digit2 = 10;

const int ON = LOW;
const int OFF = HIGH;

int n = 500;

void setup() {
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  pinMode(segmentH, OUTPUT);

  pinMode(digit0, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
}

void DrawLetter_F()
{
  digitalWrite(segmentA, ON);
  digitalWrite(segmentB, OFF);
  digitalWrite(segmentC, OFF);
  digitalWrite(segmentD, OFF);
  digitalWrite(segmentE, ON);
  digitalWrite(segmentF, ON);
  digitalWrite(segmentG, ON);
  digitalWrite(segmentH, OFF);
}
void DrawLetter_U()
{
  digitalWrite(segmentA, OFF);
  digitalWrite(segmentB, OFF);
  digitalWrite(segmentC, ON);
  digitalWrite(segmentD, ON);
  digitalWrite(segmentE, ON);
  digitalWrite(segmentF, OFF);
  digitalWrite(segmentG, OFF);
  digitalWrite(segmentH, OFF);
}
void DrawLetter_N()
{
  digitalWrite(segmentA, OFF);
  digitalWrite(segmentB, OFF);
  digitalWrite(segmentC, ON);
  digitalWrite(segmentD, OFF);
  digitalWrite(segmentE, ON);
  digitalWrite(segmentF, OFF);
  digitalWrite(segmentG, ON);
  digitalWrite(segmentH, OFF);
}

void Show_F(byte digitPin)
{
  for (int t = 0; t < n; t++)
  {
    DrawLetter_F();
    digitalWrite(digitPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(digitPin, LOW);
  }
}

void Show_U(byte digitPin)
{
  for (int t = 0; t < n; t++)
  {
    DrawLetter_U();
    digitalWrite(digitPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(digitPin, LOW);
  }
}

void Show_N(byte digitPin)
{
  for (int t = 0; t < n; t++)
  {
    DrawLetter_N();
    digitalWrite(digitPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(digitPin, LOW);
  }
}

void Show_Fun()
{
  //for (int t = 0; t < 500; t++)
  {
    DrawLetter_F();
    digitalWrite(digit0, HIGH);
    delayMicroseconds(500);
    digitalWrite(digit0, LOW);

    DrawLetter_U();
    digitalWrite(digit1, HIGH);
    delayMicroseconds(500);
    digitalWrite(digit1, LOW);

    DrawLetter_N();
    digitalWrite(digit2, HIGH);
    delayMicroseconds(500);
    digitalWrite(digit2, LOW);
  }
}

void loop() {
  if (n > 0)
  {
    if (n > 100) n -= 50; else n -= 5;
    Show_F(digit0);
    Show_U(digit1);
    Show_N(digit2);
  }
  else
  { 
    Show_Fun()
  }
}
