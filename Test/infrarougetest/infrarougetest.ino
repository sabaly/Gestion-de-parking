//int LED = 13; // Use the onboard Uno LED
int isObstaclePin[3] = {22, 24, 26};  // This is our input pin

int isObstacle[3] = {HIGH,HIGH,HIGH};

void setup() {
//pinMode(LED, OUTPUT);
  for(int i=0; i<3; i++){
    pinMode(isObstaclePin[i], INPUT);  
  }

  Serial.begin(9600);
  
}
void loop() {
  for(int i=0; i<3; i++){
    isObstacle[i] = digitalRead(isObstaclePin[i]);  
  }
  int nbr_de_place = getNombre_Place(isObstacle);
  
 switch(nbr_de_place){
    case 1:
      Serial.print(nbr_de_place);
      Serial.println(" place (s) libre (s)");
      break;
    case 2:
      Serial.print(nbr_de_place);
      Serial.println(" place (s) libre (s)");
      break;
    case 3:
      Serial.print(nbr_de_place);
      Serial.println(" place (s) libre (s)");
      break;
    default:
      Serial.print("Aucune place n'est occupée");
      break;
 }
  delay(200);
}

int getNombre_Place(int ir[3]){
  int j=0;
  for(int i=0; i<3; i++){
    if(ir[i] == LOW)
      j++;
  }

  return 3-j;
}
