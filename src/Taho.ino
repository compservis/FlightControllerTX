boolean counted = false;
int t1 = 0, t2 = 0;
int hits = 0;
int rps = 0;
 
 
void initTaho()
{
  pinMode(PMS_PIN, INPUT);
}
 
int readTaho()
{
  t2 = millis();
 
  if(digitalRead(PMS_PIN) == HIGH)
  {
    if(!counted)
    {
      counted = true;
      hits++;
    }
  } 
  else 
  {
    counted = false;
  }
  if(t2 >= (t1 + 1000))
  {
    rps = hits;
    hits = 0;
    t1 = t2;
  }
  return rps * 60;
}
