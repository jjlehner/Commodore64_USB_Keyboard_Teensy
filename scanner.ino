
void setupPins()
{
  for ( int i = 0; i < ROWS; i++ )
  {
    pinMode( rowPins[i], INPUT );
    pinMode( rowPins[i], INPUT_PULLUP );
  }
  for ( int i = 0; i < COLS; i++ )
  {
    pinMode( colPins[i], OUTPUT );
    digitalWrite( colPins[i], HIGH );
  }
}

unsigned long last_pressed[ROWS * COLS] = {millis()};
bool state[ROWS * COLS] = {false};

int keys[ROWS][COLS] = {
  {'1', '3', '5', '7', '9', '+', '£', KEY_BACKSPACE},
  {KEY_ESC, 'w', 'r', 'y', 'i', 'p', '*', KEY_RETURN},
  {KEY_LEFT_CTRL, 'a', 'd', 'g', 'j', 'l', ';', KEY_RIGHT_ARROW},
  {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'x', 'v', 'n', ',', '/', KEY_DOWN_ARROW},
  {' ', 'z', 'c', 'b', 'm', '.', KEY_RIGHT_SHIFT, KEY_F1},
  {KEY_LEFT_ALT, 's', 'f', 'h', 'k', ':', '=', KEY_F3},
  {'q', 'e', 't', 'u', 'o', '@', KEY_PAGE_DOWN, KEY_F5},
  {'2', '4', '6', '8', '0', '-', KEY_TAB, KEY_F7}
};

int shifted_keys[ROWS][COLS] = {
  {'1', '#', '5', '\'', '0', '+', '£', KEY_BACKSPACE},
  {KEY_ESC, 'w', 'r', 'y', 'i', 'p', '*', KEY_RETURN},
  {KEY_LEFT_CTRL, 'a', 'd', 'g', 'j', 'l', ']', KEY_LEFT_ARROW},
  {KEY_LEFT_ALT, KEY_LEFT_SHIFT, 'x', 'v', 'n', ',', '/', KEY_UP_ARROW},
  {' ', 'z', 'c', 'b', 'm', '.', KEY_RIGHT_SHIFT, KEY_F1},
  {KEY_LEFT_GUI, 's', 'f', 'h', 'k', '[', '=', KEY_F3},
  {'q', 'e', 't', 'u', 'o', '@', KEY_PAGE_DOWN, KEY_F5},
  {'2', '4', '7', '9', '0', '-', KEY_TAB, KEY_F7}
};

int getKey( int y, int x )
{
  bool l_shift = state[25];
  bool r_shift = state[38];
  if ( l_shift || r_shift )
  {
    return shifted_keys[y][x];
  }
  return keys[y][x];
}

void press()
{
  for ( int x = 0; x < COLS; x++ )
  {
    digitalWrite( colPins[x], LOW );
    for ( int y = 0; y < ROWS; y++ )
    {
      bool pressed = !digitalRead( rowPins[y] );
      bool no_bounce = millis() - last_pressed[y * COLS + x] > 200;
      bool prev_state = state[y * COLS + x];
      if ( pressed && no_bounce && !prev_state )
      {
        state[y * COLS + x] = true;
        if ( getKey( y, x ) == '#' || getKey( y, x ) == '\'' || getKey( y, x ) == KEY_LEFT_ARROW || getKey( y, x ) == KEY_UP_ARROW )
        {
          bool l_shift = state[25];
          bool r_shift = state[38];

          if ( l_shift )
          {
            Keyboard.release( KEY_LEFT_SHIFT );
          }
          if ( r_shift )
          {
            Keyboard.release( KEY_RIGHT_SHIFT );
          }
          if ( getKey( y, x ) == '#' )
          {
            Keyboard.press( '#' );
          }
          if ( getKey( y, x ) == '\'' )
          {
            Keyboard.press( '\'' );
          }
          if ( getKey( y, x ) == KEY_LEFT_ARROW )
          {
            Keyboard.press( KEY_LEFT_ARROW );
          }
          if ( getKey( y, x ) == KEY_UP_ARROW )
          {
            Keyboard.press( KEY_UP_ARROW );
          }
          if ( l_shift )
          {
            Keyboard.press( KEY_LEFT_SHIFT );
          }
          if ( r_shift )
          {
            Keyboard.press( KEY_LEFT_SHIFT );
          }
        }
        else
        {
          Keyboard.press( getKey( y, x ) );
        }
        last_pressed[y * COLS + x] = millis();
      }
      else if ( !pressed && no_bounce && prev_state )
      {
        state[y * COLS + x] = false;
        Keyboard.release( getKey( y, x ) );
      }
    }
    digitalWrite( colPins[x], HIGH );
  }
}
