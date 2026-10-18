const int in1 = 7;
const int in2 = 6;
const int enA = 9;
const int feedbackPin = A0;

// === PID variables ===
float Kp = 0.5;
float Ki = 0.00;
float Kd = 0.03;

int setpoint = 500; // Target posisi (0–1023)
int input = 0;
float error = 0;
float integral = 0;
float derivative = 0;
float previousError = 0;
int output = 0;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Baca input dari potensiometer
  input = analogRead(feedbackPin); // Nilai dari 0–1023

  // Hitung PID
  error = setpoint - input;
  integral += error;
  derivative = error - previousError;
  float pid = Kp * error + Ki * integral + Kd * derivative;
  previousError = error;

  // Batasi nilai output PWM
  output = constrain(pid, -255, 255);

  // Kendali arah dan kecepatan motor
  if (output > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, output);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, -output);
  }

  // Tampilkan data ke Serial Monitor
  Serial.print("Setpoint: "); Serial.print(setpoint);
  Serial.print(" | Input: "); Serial.print(input);
  Serial.print(" | Error: "); Serial.print(error);
  Serial.print(" | Output: "); Serial.println(output);

  delay(20); // Sampling time
}
