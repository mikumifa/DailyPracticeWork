SD = [['1', '250 GB', 69.99], ['2', '500 GB', 93.99], ['3', '4 TB', 219.99]]
HDD = [['1', '500 GB', 106.33], ['2', '1 TB', 134.33]]
CPU = [['1', 'Intel Core i7-11700K', 499.99], ['2', 'AMD Ryzen 7 5800X', 312.99]]
MOTHERBOARD = [['1', 'MSI B550-A PRO', 197.46], ['2', 'MSI Z490-A PRO', 262.30]]
RAM = [['1', '16 GB', 82.99], ['2', '32 GB', 174.99]]
GRAPHICS_CARD = [['1', 'MSI GeForce RTX 3060 12GB', 539.99]]
PSU = [['1', 'Corsair RM750', 164.99]]
CASE = [['1', 'Full Tower (black)', 149.99], ['2', 'Full Tower (red)', 149.99]]
PREBUILTS = [['1', 'Legion Tower Gen 7 with RTX 3080 Ti', 3699.99], ['2', 'SkyTech Prism II Gaming PC', 2839.99],
             ['3', 'ASUS ROG Strix G10CE Gaming PC', 1099.99]]

chosen_list = []


# print the string and judge whether the input is legal
def inputFunction(string, first, last, have):
    while True:
        chosen = input(string)
        if have and (chosen == 'x' or chosen == 'X'):
            return chosen
        if chosen.isdigit() and first <= int(chosen) <= last:
            return chosen


# print the string and my_list according to the list chosen
def printList(string, my_list, chosen):
    print(string)
    for i in chosen:
        print("%d : %s, $%.2f" % (i, my_list[i - 1][1], my_list[i - 1][2]))


def custom():
    now_money = 0
    # CPU
    print("\nGreat! Let's start building your PC!\n")
    printList("First, let's pick a CPU.", CPU, [1, 2])
    chosen = inputFunction("Choose the number that corresponds with the part you want: ", 1, 2, False)
    now_money += CPU[int(chosen) - 1][2]
    # compatible motherboard
    can_chosen_num = 0
    if chosen == '1':
        can_chosen_num = 2
    else:
        can_chosen_num = 1
    printList("\nNext, let's pick a compatible motherboard.", MOTHERBOARD, [can_chosen_num])
    chosen = inputFunction("Choose the number that corresponds with the part you want: ", can_chosen_num,
                           can_chosen_num, False)
    now_money += MOTHERBOARD[int(chosen) - 1][2]
    # RAM
    printList("\nNext, let's pick your RAM.", RAM, [1, 2])
    chosen = inputFunction("Choose the number that corresponds with the part you want: ", 1, 2, False)
    now_money += RAM[int(chosen) - 1][2]
    # PSU
    printList("\nNext, let's pick your PSU.", PSU, [1])
    chosen = inputFunction("Choose the number that corresponds with the part you want: ", 1, 1, False)
    now_money += PSU[int(chosen) - 1][2]
    # case
    printList("\nNext, let's pick your case.", CASE, [1, 2])
    chosen = inputFunction("Choose the number that corresponds with the part you want: ", 1, 2, False)
    now_money += CASE[int(chosen) - 1][2]
    # SSD
    printList("\nNext, let's pick an SSD (optional, but you must have at least one SSD or HDD).", SD, [1, 2, 3])
    chosen = inputFunction("Choose the number that corresponds with the part you want (or X to not get an SSD): ", 1, 3,
                           True)
    # HHD
    if chosen == 'x' or chosen == 'X':
        printList("\nNext, let's pick an HDD (optional, but you must have at least one SSD or HDD).", HDD, [1, 2])
        chosen = inputFunction(
            "Choose the number that corresponds with the part you want (since you did not get an SSD, you must get an "
            "HDD): ",
            1, 2, False)
        now_money += HDD[int(chosen) - 1][2]
    else:
        now_money += SD[int(chosen) - 1][2]
        printList("\nNext, let's pick an HDD (optional, but you must have at least one SSD or HDD).", HDD, [1, 2])
        chosen = inputFunction("Choose the number that corresponds with the part you want (or X to not get an HDD): ",
                               1, 2,
                               True)
        now_money += HDD[int(chosen) - 1][2]
    # GRAPHICS_CARD
    printList("\nFinally, let's pick your graphics card (or X to not get a graphics card).", GRAPHICS_CARD, [1])
    chosen = inputFunction(
        "Choose the number that corresponds with the part you want: ", 1, 1, True)
    if chosen != 'x' and chosen != 'X':
        now_money += GRAPHICS_CARD[int(chosen) - 1][2]
    print("\nYou have selected all of the required parts! Your total for this PC is $%.2f" % now_money)
    chosen_list.append(now_money)
    return


def pre_built():
    now_money = 0
    printList("\nWhich prebuilt would you like to order?", PREBUILTS, [1, 2, 3])
    chosen = inputFunction("Choose the number that corresponds with the part you want: ", 1, 3, False)
    now_money += PREBUILTS[int(chosen) - 1][2]
    chosen_list.append(now_money)
    print("\nYour total price for this prebuilt is $%.2f" % now_money)
    return


def checkout():
    return


def pickItems():
    print("Welcome to my PC shop!")
    while True:

        chosen = inputFunction(
            "\nWould you like to build a custom PC (1), purchase a pre-built PC (2), or would you like to checkout ("
            "3)? ",
            1,
            3,
            False)
        if chosen == '1':
            custom()
        elif chosen == '2':
            pre_built()
        elif chosen == '3':
            print(chosen_list)
            return


pickItems()
