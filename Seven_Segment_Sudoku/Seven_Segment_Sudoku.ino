// Seven Segment Sudoku - Hari Wiguna, 2016

// v0.01 - Display actual digits 1..9

// v0.00 - Proof that we could control every segment of NINE digits.
//        One Shift Register drives the segments + decimal point.
//        Another Shift Register drives 8 columns (digits).
//        D8 drives the 9th column (digit).

//== Arduino Pin configuration ==
const byte COL_CLK_PIN = 2;
const byte COL_LATCH_PIN = 3;
const byte COL_SER_PIN = 4;

const byte COL_8_PIN = 8; // Shift register only has 8 columns, so handle 9th column special

const byte SEG_CLK_PIN = 5;
const byte SEG_LATCH_PIN = 6;
const byte SEG_SER_PIN = 7;

//== Digit bitmaps ==
byte digitBits[] = {
  B11111100, // 0
  B00001100, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
};

void setup() {
  pinMode(COL_CLK_PIN, OUTPUT);
  pinMode(COL_LATCH_PIN, OUTPUT);
  pinMode(COL_SER_PIN, OUTPUT);
  pinMode(SEG_CLK_PIN, OUTPUT);
  pinMode(SEG_LATCH_PIN, OUTPUT);
  pinMode(SEG_SER_PIN, OUTPUT);
  pinMode(COL_8_PIN, OUTPUT);
}

void SetCol(byte col)
{
  if (col == 8) {
    // turn on the special 9th column
    digitalWrite(COL_8_PIN, HIGH);
  }
  else
  {
    // Turn on the requested column (0..7)
    byte colByte = 0;
    bitSet(colByte, col);
    digitalWrite(COL_LATCH_PIN, LOW);
    shiftOut(COL_SER_PIN, COL_CLK_PIN, MSBFIRST, colByte);
    digitalWrite(COL_LATCH_PIN, HIGH);
  }
}

void ClearCol(byte col)
{
  if (col == 8) {
    // turn off the special 9th column
    digitalWrite(COL_8_PIN, LOW);
  } else {
    // Turn off all bits of column shift register
    digitalWrite(COL_LATCH_PIN, LOW);
    shiftOut(COL_SER_PIN, COL_CLK_PIN, MSBFIRST, 0);
    digitalWrite(COL_LATCH_PIN, HIGH);
  }
}

void SegmentTest()
{
  //== Scan through all the segments ===
  for (byte seg = 0; seg < 8; seg++)
  {
    byte segByte = 0;
    bitSet(segByte, seg);

    digitalWrite(SEG_LATCH_PIN, LOW);
    shiftOut(SEG_SER_PIN, SEG_CLK_PIN, MSBFIRST, ~segByte);
    digitalWrite(SEG_LATCH_PIN, HIGH);

    delay(100);
  }
}

void DisplayDigit(byte digit)
{
    byte segByte = digitBits[digit];

    digitalWrite(SEG_LATCH_PIN, LOW);
    shiftOut(SEG_SER_PIN, SEG_CLK_PIN, LSBFIRST, ~segByte);
    digitalWrite(SEG_LATCH_PIN, HIGH);

    delay(500);
}

void loop() {
  for (byte col = 0; col < 9; col++)
  {
    SetCol(col); // Turn on one of the columns...
    
    //SegmentTest();
    DisplayDigit(col+1);

    ClearCol(col); // Turn off all the columns
  }
}
