with open('mark.txt', 'r',encoding="UTF-8") as file:
    lines = file.readlines()
    for line in lines:
        name, score = line.strip().split(' ')
        print('{}的成绩是{}'.format(name, score))
