const int LED1 = 11;
const int LED2 = 10;
const int LED3 = 9;
const int LED4 = 6;

void setup()
{
}

void loop()
{
  float in, out;
  
  for (in = 0; in < 6.283; in = in + 0.001)
  {
    out = cos(in) * 127.5 + 127.5;
    analogWrite(LED1,out);
    out = cos(in+1.5708) * 127.5 + 127.5;
    analogWrite(LED2,out);
    out = cos(in+3.1415) * 127.5 + 127.5;
    analogWrite(LED3,out);
    out = cos(in+4.7124) * 127.5 + 127.5;
    analogWrite(LED4,out);
  }
}
