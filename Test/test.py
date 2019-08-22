import serial

ser = serial.Serial('/dev/ttyAMC0', 9600)

print("Programme de contrôle d'accès\n")
action = int(input("Démarrer le processus (appuyer 1)"))


