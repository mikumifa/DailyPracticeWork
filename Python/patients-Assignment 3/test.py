from main import readPatientsFromFile

parentDict = readPatientsFromFile("patients.txt")
print(parentDict)
print("  Heart Rate:", 12, "bpm")