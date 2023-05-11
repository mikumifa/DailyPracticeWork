import time
from datetime import date
from typing import List, Dict, Optional


def readPatientsFromFile(fileName):
    """
    Reads patient data from a plaintext file.
    fileName: The name of the file to read patient data from.
    Returns a dictionary of patient IDs, where each patient has a li
    The dictionary has the following structure:
    {
    patientId (int): [
    [date (str), temperature (float), heart rate (int), respiratory rate, systolic blood pressure, diastolic blood pressure,oxygen saturation]
    [date (str), temperature (float), heart rate (int), respiratory rate, systolic blood pressure, diastolic blood pressure,oxygen saturation]
    ...
    ],
    patientId (int): [
    [date (str), temperature (float), heart rate (int), respiratory rate, systolic blood pressure, diastolic blood pressure,oxygen saturation]
    ...
    ],
    ...
    }
    """
    patients = {}
    try:
        with open(fileName, 'r') as file:
            for lineNum, line in enumerate(file, start=1):
                line = line.strip()
                if not line:
                    continue
                parts = line.split(',')
                numFields = len(parts)
                if numFields != 8:
                    print(f"Invalid number of fields ({numFields}) in line {lineNum}: {line}")
                    continue
                try:
                    patientId = int(parts[0])
                    date = parts[1]
                    temperature = float(parts[2])
                    heartRate = int(parts[3])
                    respiratoryRate = int(parts[4])
                    systolicBP = int(parts[5])
                    dbp = int(parts[6])
                    spo2 = int(parts[7])
                except ValueError:
                    print(f"Invalid data type in line {lineNum}: {line}")
                    continue
                if not 35 <= temperature <= 42:
                    print(f"Invalid temperature value ({temperature}) in line {lineNum}: {line}")
                    continue
                if not 30 <= heartRate <= 180:
                    print(f"Invalid heart rate value ({heartRate}) in line {lineNum}: {line}")
                    continue
                if not 5 <= respiratoryRate <= 40:
                    print(f"Invalid respiratory rate value ({respiratoryRate}) in line {lineNum}: {line}")
                    continue
                if not 70 <= systolicBP <= 200:
                    print(f"Invalid systolic blood pressure value ({systolicBP}) in line {lineNum}: {line}")
                    continue
                if not 40 <= dbp <= 120:
                    print(f"Invalid diastolic blood pressure value ({dbp}) in line: {line}")
                    continue
                if not 70 <= spo2 <= 100:
                    print(f"Invalid oxygen saturation value ({spo2}) in line: {line}")
                    continue
                if patientId not in patients:
                    patients[patientId] = []
                patients[patientId].append([date, temperature, heartRate, respiratoryRate, systolicBP, dbp, spo2])
    except FileNotFoundError:
        print(f"The file '{fileName}' could not be found.")
        exit(-1)
    return patients


def displayPatientData(patients, patientId=0):
    """
    Displays patient data for a given patient ID.

    patients: A dictionary of patient dictionaries, where each patient has a list of visits.
    patientId: The ID of the patient to display data for. If 0, data for all patients will be displayed.
    """
    isFind = False
    for pid, visits in patients.items():
        if patientId == 0 or patientId == pid:
            print("Patient ID:", pid)
            for visit in visits:
                print(" Visit Date:", visit[0])
                print("  Temperature:", "%.2f" % visit[1], "C")
                print("  Heart Rate:", visit[2], "bpm")
                print("  Respiratory Rate:", visit[3], "bpm")
                print("  Systolic Blood Pressure:", visit[4], "mmHg")
                print("  Diastolic Blood Pressure:", visit[5], "mmHg")
                print("  Oxygen Saturation:", visit[6], "%")
            isFind = True
    if patientId != 0 and not isFind:
        print("Patient with ID", patientId, "not found.")


def displayStats(patients, patientId=0):
    """
    Prints the average of each vital sign for all patients or for the specified patient.

    patients: A dictionary of patient IDs, where each patient has a list of visits.
    patientId: The ID of the patient to display vital signs for. If 0, vital signs will be displayed for all patients.
    """
    if not isinstance(patients, dict):
        print("Error: 'patients' should be a dictionary.")
        return

    try:
        patientId = int(patientId)
    except ValueError:
        print("Error: 'patientId' should be an integer.")
        return

    if patientId == 0:
        avg_temp = sum(visit[1] for visits in patients.values() for visit in visits) / sum(
            len(visits) for visits in patients.values())
        avg_hr = sum(visit[2] for visits in patients.values() for visit in visits) / sum(
            len(visits) for visits in patients.values())
        avg_rr = sum(visit[3] for visits in patients.values() for visit in visits) / sum(
            len(visits) for visits in patients.values())
        avg_sbp = sum(visit[4] for visits in patients.values() for visit in visits) / sum(
            len(visits) for visits in patients.values())
        avg_dbp = sum(visit[5] for visits in patients.values() for visit in visits) / sum(
            len(visits) for visits in patients.values())
        avg_spo2 = sum(visit[6] for visits in patients.values() for visit in visits) / sum(
            len(visits) for visits in patients.values())

        print("Vital Signs for All Patients:")
        print(" Average temperature:", "%.2f" % avg_temp, "C")
        print(" Average heart rate:", "%.2f" % avg_hr, "bpm")
        print(" Average respiratory rate:", "%.2f" % avg_rr, "bpm")

        print(" Average systolic blood pressure:", "%.2f" % avg_sbp, "mmHg")
        print(" Average diastolic blood pressure:", "%.2f" % avg_dbp, "mmHg")
        print(" Average oxygen saturation:", "%.2f" % avg_spo2, "%")
        return
    else:
        for pid, visits in patients.items():
            if patientId == pid:
                avg_temp = sum(visit[1] for visit in visits) / len(visits)
                avg_hr = sum(visit[2] for visit in visits) / len(visits)
                avg_rr = sum(visit[3] for visit in visits) / len(visits)
                avg_sbp = sum(visit[4] for visit in visits) / len(visits)
                avg_dbp = sum(visit[5] for visit in visits) / len(visits)
                avg_spo2 = sum(visit[6] for visit in visits) / len(visits)

                print(f"Vital Signs for Patient {patientId}:")
                print(" Average temperature:", "%.2f" % avg_temp, "C")
                print(" Average heart rate:", "%.2f" % avg_hr, "bpm")
                print(" Average respiratory rate:", "%.2f" % avg_rr, "bpm")

                print(" Average systolic blood pressure:", "%.2f" % avg_sbp, "mmHg")
                print(" Average diastolic blood pressure:", "%.2f" % avg_dbp, "mmHg")
                print(" Average oxygen saturation:", "%.2f" % avg_spo2, "%")
                return
        print("No data found for patient with ID {}.".format(patientId))


def is_valid_date(D_str):
    try:
        nums = list(map(int, D_str.split("-")))
        if len(nums) != 3:
            return False
        return True
    except:
        return False


def is_true_date(year, month, day):
    try:
        date(year=year, month=month, day=day)
        return True
    except:
        return False


def addPatientData(patients, patientId, date, temp, hr, rr, sbp, dbp, spo2, fileName):
    """
    Adds new patient data to the patient list by appending to the di
    patients: The dictionary of patient IDs, where each patient has
    patientId: The ID of the patient to add data for.
    date: The date of the patient visit in the format 'yyyy-mm-dd'.
    temp: The patient's body temperature.
    hr: The patient's heart rate.
    rr: The patient's respiratory rate.
    sbp: The patient's systolic blood pressure.
    dbp: The patient's diastolic blood pressure.
    spo2: The patient's oxygen saturation level.
    fileName: The name of the file to append new data to.
    """
    try:
        if not is_valid_date(date):
            print("Invalid date format. Please enter date in the format 'yyyy-mm-dd'.")
            return
        year, month, day = map(int, date.split('-'))
        if not is_true_date(year, month, day):
            print("Invalid date. Please enter a valid date.")
            return
        if not (35<= temp <= 42):
            print("Invalid temperature. Please enter a temperature between 35.0 and 42.0 Celsius.")
            return
        if not (30 <= hr <= 180):
            print("Invalid heart rate. Please enter a heart rate between 30 and 180 bpm.")
            return
        if not (5 <= rr <= 40):
            print("Invalid respiratory rate. Please enter a respiratory rate between 5 and 40 bpm.")
            return
        if not (70 <= sbp <= 200):
            print(
                "Invalid systolic blood pressure. Please enter a systolic blood pressure between 70 and 200 mmHg.")
            return
        if not (40 <= dbp <= 120):
            print(
                "Invalid diastolic blood pressure. Please enter a diastolic blood pressure between 40 and 120 mmHg.")
            return
        if not (70 <= spo2 <= 100):
            print("Invalid oxygen saturation. Please enter an oxygen saturation between 70 and 100%.")
            return
        if patientId not in patients:
            patients[patientId] = []
        patients[patientId].append([date, temp, hr, rr, sbp, dbp, spo2])
        with open(fileName, 'w') as f:
            for patientId, visits in patients.items():
                for visit in visits:
                    line = ','.join([str(patientId), visit[0], str(visit[1]), str(visit[2]),
                                     str(visit[3]), str(visit[4]), str(visit[5]), str(visit[6])])
                    f.write(line + '\n')
        print(f"Visit is saved successfully for Patient #{patientId}")

    except:
        print("An unexpected error occurred while adding new data.")


def findVisitsByDate(patients, year=None, month=None):
    """
    Find visits by year, month, or both.
    patients: A dictionary of patient IDs, where each patient has a l
    year: The year to filter by.
    month: The month to filter by.
    return: A list of tuples containing patient ID and visit that mat
    """
    # create an empty list to store the matching visits
    result = []
    try:

        if year is not None and (int(year) >= 10000 or int(year) <= 999):
            return []
        if month is not None and (int(month) >= 13 or int(month) <= 0):
            return []
        if month is not None and year is None:
            return []
        for patientId, visits in patients.items():
            for visit in visits:
                date = visit[0]
                parts = date.split("-")
                visit_year = int(parts[0])
                visit_month = int(parts[1])
                if (year is None or year == visit_year) and (month is None or month == visit_month):
                    result.append((patientId, visit))
    except:
        return []

    # return the result list
    return result


def findPatientsWhoNeedFollowUp(patients):
    """
    Find patients who need follow-up visits based on abnormal vital s
    patients: A dictionary of patient IDs, where each patient has a l
    return: A list of patient IDs that need follow-up visits due to a
    """
    followup_patients = []
    for patient_id, visits in patients.items():
        for visit in visits:
            if (visit[2] > 100 or visit[2] < 60 or
                    visit[4] > 140 or visit[5] > 90 or
                    visit[6] < 90):
                followup_patients.append(patient_id)
                break
    return followup_patients


def deleteAllVisitsOfPatient(patients, patientId, filename):
    """
    Delete all visits of a particular patient.
    patients: The dictionary of patient IDs, where each patient has a
    patientId: The ID of the patient to delete data for.
    filename: The name of the file to save the updated patient data.
    return: None
    """
    try:
        if int(patientId) not in patients:
            print(f"No data found for patient with ID {patientId}")
            return

        # remove the patient's visits from the dictionary
        del patients[patientId]
        print(f"Data for patient {patientId} has been deleted.")

        # write the updated patient data to the file
        with open(filename, 'w') as f:
            for patientId, visits in patients.items():
                for visit in visits:
                    line = ','.join([str(patientId), visit[0], str(visit[1]), str(visit[2]),
                                     str(visit[3]), str(visit[4]), str(visit[5]), str(visit[6])])
                    f.write(line + '\n')
    except:
        print(f"No data found for patient with ID {patientId}")
        return


def main():
    patients = readPatientsFromFile('patients.txt')
    while True:
        print("\n\nWelcome to the Health Information System\n\n")
        print("1. Display all patient data")
        print("2. Display patient data by ID")
        print("3. Add patient data")
        print("4. Display patient statistics")
        print("5. Find visits by year, month, or both")
        print("6. Find patients who need follow-up")
        print("7. Delete all visits of a particular patient")
        print("8. Quit\n")

        choice = input("Enter your choice (1-8): ")
        if choice == '1':
            displayPatientData(patients)
        elif choice == '2':
            patientID = int(input("Enter patient ID: "))
            displayPatientData(patients, patientID)
        elif choice == '3':
            patientID = int(input("Enter patient ID: "))
            date = input("Enter date (YYYY-MM-DD): ")
            try:
                temp = float(input("Enter temperature (Celsius): "))
                hr = int(input("Enter heart rate (bpm): "))
                rr = int(input("Enter respiratory rate (breaths per minute): "))
                sbp = int(input("Enter systolic blood pressure (mmHg): "))
                dbp = int(input("Enter diastolic blood pressure (mmHg): "))
                spo2 = int(input("Enter oxygen saturation (%): "))
                addPatientData(patients, patientID, date, temp, hr, rr, sbp, dbp, spo2, 'patients.txt')
            except ValueError:
                print("Invalid input. Please enter valid data.")
        elif choice == '4':
            patientID = input("Enter patient ID (or '0' for all patients): ")
            displayStats(patients, patientID)
        elif choice == '5':
            year = input("Enter year (YYYY) (or 0 for all years): ")
            month = input("Enter month (MM) (or 0 for all months): ")
            visits = findVisitsByDate(patients, int(year) if year != '0' else None,
                                      int(month) if month != '0' else None)
            if visits:
                for visit in visits:
                    print("Patient ID:", visit[0])
                    print(" Visit Date:", visit[1][0])
                    print("  Temperature:", "%.2f" % visit[1][1], "C")
                    print("  Heart Rate:", visit[1][2], "bpm")
                    print("  Respiratory Rate:", visit[1][3], "bpm")
                    print("  Systolic Blood Pressure:", visit[1][4], "mmHg")
                    print("  Diastolic Blood Pressure:", visit[1][5], "mmHg")
                    print("  Oxygen Saturation:", visit[1][6], "%")
            else:
                print("No visits found for the specified year/month.")
        elif choice == '6':
            followup_patients = findPatientsWhoNeedFollowUp(patients)
            if followup_patients:
                print("Patients who need follow-up visits:")
                for patientId in followup_patients:
                    print(patientId)
            else:
                print("No patients found who need follow-up visits.")
        elif choice == '7':
            patientID = input("Enter patient ID: ")
            deleteAllVisitsOfPatient(patients, int(patientID), "patients.txt")
        elif choice == '8':
            print("Goodbye!")
            break
        else:
            print("Invalid choice. Please try again.\n")


if __name__ == '__main__':
    main()
