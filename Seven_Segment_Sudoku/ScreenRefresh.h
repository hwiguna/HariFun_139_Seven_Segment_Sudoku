void ClearAllColumns()
{
    // turn off the special 9th column
    digitalWrite(COL_8_PIN, LOW);

    // Turn off all bits of column shift register
    digitalWrite(COL_LATCH_PIN, LOW);
    shiftOut(COL_SER_PIN, COL_CLK_PIN, MSBFIRST, 0);
    digitalWrite(COL_LATCH_PIN, HIGH);
}

void SetColumn(byte col)
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

void DisplayDigit(byte digit)
{
  byte segByte = digitBits[digit];
  shiftOut(SEG_SER_PIN, SEG_CLK_PIN, LSBFIRST, ~segByte);
}

void DrawColumn(byte col)
{
  digitalWrite(SEG_LATCH_PIN, LOW); // Do not reflect bit changes (yet)
  
  for (byte row = 0; row < 1; row++)
  {
    DisplayDigit( sudoku[row][col] );
  }
  
  digitalWrite(SEG_LATCH_PIN, HIGH); // Slam bits that we've just setup to the shift register output pins
}

void Refresh(void)
{
  noInterrupts();

  //-- Compute new row --
  int8_t prevCol = gCol;
  gCol++;
  if (gCol > 8) gCol = 0;

  ClearAllColumns(); // Turn off all columns so we won't have shadow of previous column in the new current column
  DrawColumn(gCol); // Spit out the bit pattern for all nine ROWS of "current" column
  SetColumn(gCol); // Turn on JUST the "current" colum

  interrupts();
}

void SetupTimer()
{
  cli();
  // Reset any PWM that arduino may have setup automatically
  TCCR2A = 0;
  TCCR2B = 0;

  TCCR2A |= (1 << WGM21); // CTC mode. Reset counter when OCR2 is reached

  TCCR2B |= (1 << CS21) | (1 << CS22); // Prescaler = 256
  //TCCR2B |= (1 << CS20) | (1 << CS22); // Prescaler = 128
  OCR2A = 70; // Fire interrupt when timer2 has looped 80 times

  TCNT2 = 0; // initial counter value = 0;
  TIMSK2 |= (1 << OCIE2A); // Enable CTC interrupt
  sei();
}

ISR (TIMER2_COMPA_vect)
{
  Refresh();
}


